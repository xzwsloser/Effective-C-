# 为多态基类声明`virtual`析构函数
- 在利用多态的时候,需要使用父类的指针或者引用指向子类对象,所以这个时候就会出现如下问题:
  - 当一个子类对象经过一个父类指针被删除的时候,并且父类指针带有非`virtual`修饰的析构函数的时候,就会导致被指向的子类对象占用的空间没有完全被释放,造成内存泄漏
- 解决方式就是为父类的析构函数添加一个`virtual`关键字,此时就会调用子类的析构函数了
```cpp
class Animal{
public:
    virtual ~Animal(){
        cout << "Base class was destoryed !" << endl;
    }
};

class Dog: public Animal{
public:
    ~Dog(){
        cout << "derived class was destoryed !" << endl;
    }
};
```
- 如果想要实现出`virtual`关键字,对象就必须携带一些信息,主要用于决定运行时期使用哪一个`virtual`函数会被调用,这一个信息通常就是`vptr`指针指出的,它指向一个有函数指针构成的数组,称为`vtbl`,每一个带有`virtual`函数的`class`都有一个`vtbl`,实际上被调用的函数取决于`vptr`和所指向的`vtbl`
- 另外一个注意事项就是不要把一个不会被作为父类的类中的析构函数声明为`virtual`,这会增加它占用的内存空间,由于`C++`中没有`final`等关键字,所以可以继承`STL`容器或者内置数据类型,但是这一种情况都是不可取的,这是由于内置数据类型都没有`virtual`析构函数
- 对于抽象类,如果没有函数需要定义为纯虚函数但是又需要抽象类,那么此时就可以把析构函数定义为纯虚函数,但是需要为纯虚函数提供定义 : `AWOV::~AWOV(){}`
- 这是由于析构函数的运行机制就是: 
  - 最深层的哪一个类的析构函数最先被调用,然后每一个`base class`的析构函数被调用
- 总结:
  - 在多态中,父类需要声明一个`virtual`修饰的析构函数,如果`class`带有任何`virtual`函数,它就需要拥有一个`virtual`析构函数
  - 一个类的设计如果不是作为`base class`使用,或者不是为了实现多态,就不应该被声明为`virtual`析构函数