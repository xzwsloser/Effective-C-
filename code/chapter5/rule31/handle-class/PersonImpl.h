#pragma once
#include<iostream>
#include<string>
using namespace std;
class PersonImpl {
public:
    PersonImpl(const string& name , const int& age): name(name) , age(age) {}
    inline string get_name() {return name;}
    inline int get_age() {return age;}
private:
    string name;
    int age;
};