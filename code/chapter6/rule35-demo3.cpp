#include<iostream>
#include<string>
#include<functional>
using namespace std;
class Person;
void default_handler(Person& p)
{
    cout << "起床了" << endl;
}
class Person {
public:
    using get_up_handler = function<void(Person&)>;
    Person(get_up_handler handler = default_handler): handler(handler) {};
    void get_up()
    {
        // ...
        handler(*this);
        // ...
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

class Student2_hanlder{
public:
    void operator()(Person& p)
    {
        cout << "学生2起床了" << endl;
    }
};
void func(Person* p)
{
    p -> get_up();
}

void work_handler(Person& p)
{
    cout << "工人起床了" << endl;
}
int main()
{
    Person* p1 = new Student([=](Person& p){
        cout << "学生1起床了" << endl;
    });

    Person* p2 = new  Student(Student2_hanlder());

    Person* p3 = new Worker(work_handler);

    func(p1);
    func(p2);
    func(p3);

}