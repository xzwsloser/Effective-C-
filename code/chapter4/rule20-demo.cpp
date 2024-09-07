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