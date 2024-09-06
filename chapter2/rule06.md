# 如果不想要使用编译器自动生成的函数,就需要明确拒绝
- 如果不想要使用编译器自动生成的构造函数,可以重写构造函数或者析构函数
## 如何放置外界调用本来不想要被调用的拷贝构造函数和拷贝运算符
1. 第一种解决方式: 将重写的拷贝构造函数和拷贝运算符定义为`private`修饰的,但是这一种方法对于友元函数还有成员函数失效
```cpp
class Person{
public:
    int age;
    string name;
    Person(int age , string name): age(age) , name(name) {}
    Person() {}
private: 
    Person(const Person& p){
        this -> age = p.age;
        this -> name = p.name;
    }

    void operator=(Person& p){
        this -> age = p.age;
        this -> name = p.name;
    }
};
```
2. 第二种解决方法: 直接声明拷贝构造函数和拷贝运算符但是不定义(实现),这一种方法解决了上一种方法的缺点,但是错误可能会发生在连接的阶段(比如友元函数尝试拷贝),但是错误最好发生在编译阶段容易定位
```cpp
class Person{
public:
    int age;
    string name;
    Person(int age , string name): age(age) , name(name) {}
    Person() {}
private: 
    Person(const Person& );
    void operator= (Person&);
};
```
3. 第三种解决方法: 定义一个父类,这一个父类的作用就是放置拷贝,在这一个父类中利用`private`声明拷贝构造和赋值运算符但是不定义即可
```cpp
class Uncopyable{
public:
    Uncopyable(){}
    ~Uncopyable(){}
private:
    Uncopyable(const Uncopyable&);
    void operator= (Uncopyable&);
};
class Person{
public:
    int age;
    string name;
    Person(int age , string name): age(age) , name(name) {}
    Person() {}
};
```
- 请记住: 为了防止编译器自动提供的机能,可以将相应的成员函数声明为`private`并且不实现或者使用防止拷贝的父类也可以
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             