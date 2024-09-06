#include<iostream>
#include<memory>
#include<string>
#include<functional>
using namespace std;
int priority()
{
    char* c = "hello";
    c[2] = 'D';
    return 1;
}

class Person{
public:
    ~Person()
    {
        cout << "~Person" << endl;
    }
};

void func(shared_ptr<Person> sp , int a)
{
    cout << "func" << endl;
}
int main()
{
    // err
    // func(shared_ptr<Person>(new Person()) , priority());
    shared_ptr<Person> sp(new Person() , [=](Person* p) {
        cout << "delete" << endl;
        delete p;
    }); 
    func(sp , priority());
}