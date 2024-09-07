# 宁以pass-by-reference-to-const代替pass-by-value
- 本条款只是针对于用户自定义数据类型,而不是针对于内置数据类型或者`STL`容器的迭代器
- 利用`pass-by-value`的缺点如下:
1. 对于一个较大的对象(比如包含很多成员并且存在继承关系),试想,如果使用`pass-by-value`的方式传递对象就会调用多次构造函数(比如自己的构造函数,成员的构造函数和父类的构造函数等),甚至析构的时候也会调用多次析构函数,所以此时的解决方式就是使用`pass-by-reference-to-const`代替(但是前提就是不要改变参数的值),比如:
```cpp
void func(const Person& p);
```
2. 使用值传递的方式可能会导致对象分割的问题,也就是利用多态的时候可能会发生子类被解析成父类的情况,比如如下情况:
```cpp
#include<iostream>
using namespace std;
class Animal{
public:
    virtual void speak() const 
    {
        cout << "动物在说话" << endl;
    }

};

class Dog: public Animal {
public:
    virtual void speak() const override 
    {
        cout << "小狗在说话" << endl;
    }
};

// pass-by-value
void func(Animal a)
{
    a.speak();
}
// pass-by-reference-to-const
void func1(const Animal& a)
{
    a.speak();
}
int main()
{
    Dog d;
    func(d);  // 自动类型转换
    func1(d);
}
```
- 解决方式就是使用`reference-to-const`进行参数的传递,本质上其实就是父类指针指向子类的引用
- `reference`往往使用指针的方式实现出来,因此使用引用传递的真正传递的都是指针
- 但是如果是内置数据类型,一般来说使用值传递的方式往往优于使用引用传递的方式,但是这对于小的自定义数据类型失效,这是由于内置数据类型中的成员需要初始化并且可能发生扩充
- 总结：
  - 尽量使用`pass-by-reference-to-const`替换`pass-by-value`,前者往往比较高效,并且可避免切割问题
  - 以上的规则并不适用于内置数据类型,以及`STL`容器的迭代器和函数对象,对于他们而言,`pass-by-value`比较适当
