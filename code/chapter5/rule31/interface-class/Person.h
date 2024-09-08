#pragma once
#include<iostream>
#include<string>
#include<memory>
using namespace std;
class Person {
public:
    static shared_ptr<Person> createPerson(string  name , int age);
    virtual ~Person(){};
    virtual string get_name() = 0;
    virtual int get_age() = 0;
};