# 另operator= 返回一个 reference to *this
- 对于连锁赋值操作 `x = y = z = 10` 如果想要达到这一种链式的操作,就必须让`operator=`返回一个赋值运算符
- 同理对于其他的运算符号也需要返回一个`reference to this`
- 这是一个规定,被很多内置的数据类型遵守
```cpp
#include<iostream>
#include<string>
using namespace std;
class Person{
public:
    int age;
    string name;
    Person(int age , string name): age(age) , name(name) {}
    Person() {}
    Person& operator= (const Person& p)
    {
        this -> age = p.age;
        this -> name = p.name;
        return *this;
    }
};
int main()
{
    Person p1;
    Person p2;
    Person p3;
    p1 = p2 = p3 = Person(10 , "zhangsan");
    cout << p1.name << "  " << p1.age << endl;
    cout << p2.name << "  " << p2.age << endl;
    cout << p3.name << "  " << p3.age << endl;
}
```
- 总结: 
  - 另赋值运算符号返回一个`reference to *this`
