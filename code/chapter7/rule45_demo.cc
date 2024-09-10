#include<iostream>
#include<string>
using namespace std;
class Person {
public:
    Person(string name , int age): name(name) , age(age) {}
    Person() {}
    virtual ~Person() {}
    string get_name() { return this -> name; }
    int get_age() { return this -> age;}
private:
    string name;
    int age;
};

class Son: public Person {
public:
    Son() {}
    Son(string name , int age): Person(name , age) {}
};

// 一个智能指针类
template<typename T>
class SmartPtr {
public:
    // 模板构造函数
    template<typename U>
    SmartPtr(SmartPtr<U>& ptr)
    {
        T* p = ptr.get();
        data = new T(*p);  // 防止重复释放
    }
    SmartPtr() : data(nullptr) {}
    SmartPtr(T t): data(new T(t)) {}
    ~SmartPtr()
    {
        if(data != nullptr)
        {
            delete data;
            data = nullptr;
        }
    }

    T* get() { return data; }
private:
    T* data;
};
int main()
{
    SmartPtr<Son> sms(Son("张三" , 20));
    SmartPtr<Person> smp = sms;  // 调用拷贝构造或者赋值运算符号
    cout << sms.get() -> get_age() << endl;
    cout << sms.get() -> get_name() << endl;
}