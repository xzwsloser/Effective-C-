#include<iostream>
#include<string>
using namespace std;
class Base;
class Base{
public:
    int age;
    string name;
    Base(int age , string name) : age(age), name(name) {}
    Base() {}
};

class Son: public Base{
public:
    int gender;
    Son(int age , string name , int gender): Base(age , name) , gender(gender) {}
    Son(const Son& s): Base(s.age , s.name) , gender(s.gender) {}
    Son& operator=(const Son& s)
    {
         init(s); // 其实代码可以复用
         return *this;
    }
    void show_person()
    {
        cout << this -> name << "  " << this -> age << "  " << this -> gender << endl;
    }
private:
    void init(const Son& s)
    {
        this -> name = s.name;
        this -> age = s.age;
        this -> gender = s.gender;
    }
};

int main()
{
    Son s1(10 , "zhangsan" , 1);
    Son s2(s1);
    s1.show_person();
    s2.show_person();
    Son s3 = s1;
    s3.show_person();
}