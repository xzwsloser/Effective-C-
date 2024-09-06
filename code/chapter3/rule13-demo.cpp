#include<iostream>
#include<string>
#include<memory>
#include<functional>
using namespace std;
class Person{
public:
    string name;
    int age;
    Person(string name , int age): name(name) , age(age) {}
    Person() {}
    ~Person()
    {
        cout << "~Person 执行了" << endl;
    }
};
void f()
{
    shared_ptr<Person> spp(new Person("李四" , 10));
    // 演示其他几种初始化方式,注意不要使用一个内存空间初始化多个智能指针
    shared_ptr<Person> spp1 = make_shared<Person>("张三" , 10);
    shared_ptr<Person> spp2(move(spp)); // 调用移动构造函数
    // cout << spp -> name << endl;
    // cout << spp -> age << endl;
}
int main()
{
    f();
    cout << "f 调用结束" << endl;
    //当然也可以使用 unique_ptr 管理资源
    Person* p = new Person();
    unique_ptr<Person , function<void(Person*)>> up(p , [=](Person* p){
        cout << "删除器函数被调用了" << endl;
        delete p;
    });

}