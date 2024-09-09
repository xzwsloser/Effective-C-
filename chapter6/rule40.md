# 明确而审慎地使用多重继承
- 首先讨论多重继承的缺点:
1. 程序有可能从多个父类中继承相同的名称(比如函数或者`typedef`等),考虑如下程序:
```cpp
class BorrowableItem {
public:
    void check() const;
};

class ElectronicGadget {
private:
    bool check() const;
};

class MP3Player: public BorrowableItem , public ElectronicGadget {

};
```
- 此时最后的一个子类中就会有两个名为`private`的同名成员(尽管有一个不可见),此时确定调用哪一个`check`函数的方式就是: `m.BorrowableItem::check()`(就是指定作用域)
2. 会引发菱形继承的问题,比如如下继承结构:
```cpp
      File
    /      \
InputFile  OutputFile
    \      /
      IOFile
```
- 假设`File`中存在一个同名元素比如`filename`,那么`IOFile`中就会出现两份同名元素,此时的解决方式就是使用虚继承,也就是利用如下的继承方式:
```cpp
class InputFile: virtual public File {};
class OutputFile: virtual public File {};
class IOFile: public InputFile , public OutputFile {};
```
- `virtual`继承让两个子类共享一个虚基类对象,但是并不是意味着总是可以让`virtual`和`public`一起生效,`virtual`继承的缺点如下:
  - 利用`virtual`继承得到类产生的对象体积比较大,比那些`non-virtual`继承得到的类产生的对象的体积大,并且访问`virtual base classes`的成员变量的时候,也往往比访问那些`non-virtual base classes`的成员变量访问速度慢
  - 另外`virtual`继承的`class`在初始化的时候它的初始化责任是由继承体系中的最底层负责,也就是说`classes`如果继承来自`virtual bases`而需要初始化,必须认知其`virtual bases`,无论这些父类距离多远
  - 当一个子类加入到这一个继承体系的时候,比如承担`virtual bases`的初始化责任
- `virtual`继承使用时的注意事项:
  - 非必要不要使用`virtual bases`,平常可以使用`non-virtual`继承
  - 比如需要使用`virtual base classes`,尽可能避免在其中放置数据,这样依赖就不用担心在这些`classes`身上构造函数的不确定性

- 下面讨论一种合法使用多重继承的案例
- 如下这一个类表示一个抽象类(`Interface class`),定义如下:
```cpp
class IPerson {
public:
    virtual ~IPerson();
    virtual string name() const = 0;
    virtual string birthDate() const = 0;
};
```
- 所以自然而然的可以定义一个工厂类来制造产品:
```cpp
shared_ptr<IPerson> make_person(ask_user_for_database_id());
```
- 参数就是需要制造对象的`ID`

- 考虑另外一个类,这一个类的作用就是在调用工厂方法的时候对于创建对象的姓名提供一些`API`比如添加前缀后缀等,作用也就是"根据某物实现出",所以可以使用`private`继承或者复合,但是由于需要重新实现其中的方法所以可以使用`private`继承:
```cpp
class PersonInfo {
public:
    PersonInfo(DatabaseID pid);
    virtual ~PersonInfo();
    virtual const char* theName() const;
    virtual const char* theBirthDate() const;
    ...
private:
    virtual const char* value_delim_open() const; //添加前缀
    virtual const char* value_delim_close() const;  // 添加后缀
};
```
- 所以产品(也就是需要制造的对象的继承结构和实现方式如下):
```cpp
class CPerson: public IPerson,private PersonInfo {
public:
    CPerson(DatabaseID pid): PersonInfo(pid) {}
    virtual const char* theName() { return PersonInfo::theName };
    virtual  const char* birthDate() { return PersonInfo::birthDate };
private:
    // 重写 PersonInfo 中的方法
};
```
- 可见其实`PersonInfo`的职责就是提供制造`CPerson`的方法(包含查询数据库等动作),同时`CPerson`的作用就是充当实体

- 总结:
  - 多重继承比单一继承更加复杂,它可能导致新的歧义性,以及对于`virtual`继承的需要
  - `virtual`继承会增加大小,速度和初始化(以及赋值)复杂度等成本,如果`virtual base class`不带有任何参数,将是最具有使用价值的情况
  - 多重继承的确由正当用途,比如一个情节中涉及`public`继承某一个`Interface class`和`private`继承某个协助实现的`class`的两相结合