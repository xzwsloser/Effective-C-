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