#include<iostream>
#include<string>
using namespace std;
class Uncopyable{
public:
    Uncopyable(){}
    ~Uncopyable(){}
private:
    Uncopyable(const Uncopyable&);
    void operator= (Uncopyable&);
};
class Person{
public:
    int age;
    string name;
    Person(int age , string name): age(age) , name(name) {}
    Person() {}
private: 
    // Person(const Person& p){
    //     this -> age = p.age;
    //     this -> name = p.name;
    // }

    // void operator=(Person& p){
    //     this -> age = p.age;
    //     this -> name = p.name;
    // }

    Person(const Person& );
    void operator= (Person&);
};
int main()
{

}