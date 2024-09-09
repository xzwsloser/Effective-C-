# 区分接口继承和实现继承
- 接口继承也就是只是继承父类中函数的声明,但是不继承父类中函数的实现
- 实现继承也就是继承父类中函数的声明和函数的实现
- 重点就是围绕这`pure virtual`,`virtual`,`non-virtual`这三种函数的接口继承和实现继承的特性
- 考虑如下类:
```cpp
class Shape {
public:
    virtual void draw() const = 0;
    virtual void error(const std::string& msg);
    int objectID() const; 
};

class Rectangle: public Shape {...};
class Ellipse: public Shape {...};
```
- 首先明确一点: 成员函数的接口总是会被继承,`public`继承中的模型就是`is - a`模型
## pure virtual
- 声明一个`pure virtual`函数的目的就是让子类只继承函数接口
- 子类需要提供函数接口的实现(否则子类也就会成为一个抽象类)
```cpp
class Rectangle: public Shape {
public:
    void draw()
    {
        cout << "drawing !!!" << endl;
    }
}
```
- 调用的方式可以通过多态的方式进行调用:
```cpp
Rectangle r;
Shape& s = r;
s.draw();
```
## impure virtual
- 非纯虚函数的目的是让子类继承父类的接口和缺省实现(也就是默认实现)
- 子类需要继承父类的接口,可以重写父类中的方法或者不可以重写父类中的方法
- 比如:
```cpp
class Rectangle: public Shape {
public:
    virtual void error(const string& msg)
    {
        cout << msg << endl;
    }
}; 
```
- 这比较合理,就像各种类中都需要有自己的错误处理方法,但是不同的类的错误处理方法不同
- 但是如果子类忘记了声明父类中的`impure virtual`方法也就会发生错误(也就是没有自己的状态)
```cpp
#include<iostream>
using namespace std;
class Bird {
public:
    virtual void fly()
    {
        cout << "小鸟在飞翔" << endl;
    }
};

class Red_Bird: public Bird {
public:
    virtual void fly() override {
        cout << "红色的小鸟在飞翔" << endl;
    }
};

class Blue_Bird: public Bird {

};
int main()
{
    Bird* b = new Blue_Bird();
    b -> fly();
    Bird* b1 = new Red_Bird();
    b1 -> fly();
}
```
- 第一种解决方式: 让这一种函数的声明和定义分开来,并且定义可以声明为`protected`控制权限
```cpp
#include<iostream>
using namespace std;
class Bird {
public:
    virtual void fly() = 0;
protected:
    void defaultFly()
    {
        cout << "小鸟在飞翔" << endl;
    }
};

class Red_Bird: public Bird {
public:
    virtual void fly() override {
        cout << "红色的小鸟在飞翔" << endl;
    }
};

class Blue_Bird: public Bird {
public:
    virtual void fly()
    {
        Bird::defaultFly();
    }
};
int main()
{
    Bird* b = new Blue_Bird();
    b -> fly();
    Bird* b1 = new Red_Bird();
    b1 -> fly();
}
```
- 但是这一种情况可能造成`class`命名空间的污染
- 所以可以考虑如下情况,就是可以利用纯虚函数的实现:
```cpp
#include<iostream>
using namespace std;
class Bird {
public:
    virtual void fly() = 0;
protected:
    
};

class Red_Bird: public Bird {
public:
    virtual void fly() override {
        cout << "红色的小鸟在飞翔" << endl;
    }
};

class Blue_Bird: public Bird {
public:
    virtual void fly()
    {
        Bird::fly();
    }
};

void Bird::fly()
{
    cout << "小鸟在飞翔" << endl;
}
int main()
{
    Bird* b = new Blue_Bird();
    b -> fly();
    Bird* b1 = new Red_Bird();
    b1 -> fly();
}
```
## non-virtual
- 非`virtual`修饰的函数的目的就是让子类强制实现这一个方法(也就是没有选择性,直接拥有这一个方法)

- 所以利用好`virtual`关键字就可以让子类对于父类中元素的继承更加多样化,至于效率(考虑`80 - 20`法则)

- 总结:
  - 接口继承和实现继承不同,在`public`继承之下,子类总是继承父类的接口
  - 纯虚函数只具体指定接口继承
  - 简朴的非纯虚函数具体指定接口继承和默认实现继承
  - 非`virtual`函数具体指定接口继承以及强制性实现继承