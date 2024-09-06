# 绝对不要在构造或者析构函数中调用`virtual`函数
- 注意`virtual`函数存在的意义: 一般来说就是让子类重写父类中的某些成员函数,所以在多态中,需要调用的一般都是子类的`virtual`函数,而不是父类的相应函数
- 如果在构造的过程中调用`virtual`函数,由于构造子类之前会首先构造父类也就是首先执行父类的构造函数,但是此时父类中的`virtual`方法还是父类本身的而不是子类的,所以就会在多态的时候引发错误,对于析构函数的讨论也是一样的
- 注意问题的重点在于: 在执行子类的构造函数之前,其实对象本质上还是一个父类的对象而不是 子类对象,所以调用的函数自然也是父类的函数而不是子类的函数,执行完子类的析构函数之类,这一个类本质上也是父类的一个析构函数
- 一种合理的解决方式就是在子类中显示的调用父类中的析构函数,从而达到初始化父类中的某些信息的作用
- 为什么可以显示的初始化父类: https://blog.csdn.net/sevenjoin/article/details/82222895
- `demo`演示如下:
```cpp
#include<iostream>
#include<string>
using namespace std;
class Animal{
public:
    string name;
    Animal() {}
    Animal(string name): name(name) {}
};
class Dog: public Animal{
public:
    int age;
    Dog() {}
    Dog(int age , string  name): Animal(name) , age(age) {}
};
int main()
{
    Dog d(10 , "dog");
    cout << d.name << endl;
    cout << d.age << endl;
}
```
- 总结:
  - 构造函数和析构函数期间不要调用`virtual`函数,因为这一类函数调用从不会下降到子类