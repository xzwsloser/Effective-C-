#pragma once
#include "PersonImpl.h"
#include<memory>
class PersonImpl;  // 表示前置声明
class Person {
public:
    Person(const string& name , const int& age): pi(new PersonImpl(name , age)) {}
    inline string get_name() { return pi -> get_name(); }
    inline int get_age() { return pi -> get_age(); }
private:
    shared_ptr<PersonImpl> pi;
};