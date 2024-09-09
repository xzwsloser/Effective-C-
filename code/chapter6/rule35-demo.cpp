#include<iostream>
#include<string>
using namespace std;
class Person {
public:
    void get_up()
    {
        cout << "睡觉中 ..." << endl;  // 准备工作
        way_to_get_up();
        cout << "刷牙 ..." << endl;  // 结束工作
    }
private:
    virtual void way_to_get_up()
    {
        cout << "起床了" << endl;
    }
};

class Student: public Person {
private:
    virtual void way_to_get_up() override 
    {
        cout << "学生起床了" << endl;
    }
};

class Worker: public Person {
private:
    virtual void way_to_get_up() override 
    {
        cout << "工人起床了" << endl;
    }
};

void func(Person* p)
{
    p -> get_up();
}

int main()
{
    Person* p = new Student();
    Person* p1 = new Worker();
    func(p);
    func(p1);
}