#pragma once
#include  "Person.h"
using namespace std;
class RealPerson: public Person {
public:
    RealPerson(string name , int age): name(name) , age(age) {}
    string get_name() override {
        return name;
    }
    int get_age() override {
        return age;
    }
    virtual ~RealPerson() {}
private:
    string name;
    int age;
};
shared_ptr<Person> Person::createPerson(string  name , int age)
{
    return shared_ptr<Person>(new RealPerson(name ,age));
}