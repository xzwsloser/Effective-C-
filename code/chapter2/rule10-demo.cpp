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