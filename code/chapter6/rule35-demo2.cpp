#include<iostream>
#include<string>
using namespace std;
class Person;
void default_handler(Person& p)
{
    cout << "起床了" << endl;
}
class Person{
public:
    using get_up_handler = void(*)(Person&);  // 定义函数指针类型
    Person(get_up_handler handler = default_handler): handler(handler) {}
    void get_up()
    {
        // 前置增强
        handler(*this);
        // 后置增强
    }

private:
    get_up_handler handler;
};

class Student: public Person {
public:
    Student(get_up_handler handler = default_handler): Person(handler) {}
};


class Worker: public Person {
public:
    Worker(get_up_handler handler = default_handler): Person(handler) {}
};

void student1_get_up(Person& p)
{
    cout << "第一个学生起床了" << endl;
}

void student2_get_up(Person& p)
{
    cout << "第二个学生起床了" << endl;
}

void worker_get_up(Person& p)
{
    cout << "工人起床了" << endl;
}
void func(Person* p)
{
    p -> get_up();
}

int main()
{   
    Person* sp1 = new Student(student1_get_up);
    Person* sp2 = new Student(student2_get_up);
    Person* wp = new Worker(worker_get_up);
    func(sp1);
    func(sp2);
    func(wp);
}   
