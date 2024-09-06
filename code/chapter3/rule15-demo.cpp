#include<iostream>
#include<memory>
#include<functional>
#include<string>
using namespace std;
class Person{
public:
    string name;
    int age;
    Person(string name , int age): name(name) , age(age) {}
    Person() {}
};

class MyNum{
public:
    MyNum(int num): num(num) {}
    MyNum() {}
    // 注意此时的函数可以没有返回值,这是由于不可以进行返回值的转换
    operator int() {
        return num;
    }
private:
    int num;
};
void func(Person* p)
{
    cout << "func is working" << endl;
}

void func1(int a)
{
    cout << "a = " << a << endl;
}
int main()
{
    shared_ptr<Person> sp(new Person("lisi" , 20));
    // func(sp); // err
    func(sp.get());
    func1(MyNum(10));
}