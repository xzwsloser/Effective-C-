#include<iostream>
using namespace std;
class Base{
public:
    virtual void foo()
    {
        cout << "this is father " << endl;
    }
};

class Son: public Base{
public:
    virtual void foo()
    {
        cout << "this is son " << endl;
    }
};
int main()
{
    double b = 3.14;
    int a = static_cast<int>(b);
    cout << "a = " << a << endl;

    int c = 20;
    void* d = static_cast<void*>(&c);

    // Base* pb1 = new Son();
    // Son* pb = static_cast<Son*>(pb1);
    // pb -> foo();  // 底层的指针还是指向了子函数

    const int num = 10;
    int* pn = const_cast<int*>(&num);
    *pn = 101;
    cout << num << endl;
    cout << *pn << endl;

    Base* pb ;
    Son* pa;
    pa = static_cast<Son*>(pb);

    Base* pb1;
    Son* pa1;
    pb1 = pa1;  // 直接转换成功
    // Base* pb ;
    // Son* pa;
    // pa = dynamic_cast<Son*>(pb);  error 检查 是否指向子类,种现象子类才可以转换成功
}