# 以对象的方式管理资源
- 首先可以复习一下智能指针的知识: https://xzwsloser.github.io/2024/08/19/2024-C-11%E7%89%B9%E6%80%A7-%E6%99%BA%E8%83%BD%E6%8C%87%E9%92%88/
- 对于系统分配的资源,使用完毕之后一定需要返还给系统,如果不这样就可能会在造成内存泄漏的问题
- 比如对于以下代码:
```cpp
void f()
{
    Investment* pInv = createInvestment();
    代码片段
    delete pInv;
}
```
- 对于上面的代码如果代码片段中出现`return`语句或者抛出异常并且没有捕捉的话,那么就会导致`delete`语句不会再执行,也就是说这一个被申请的空间不会被释放了,为了解决这一个问题就需要使用"以对象管理资源的方式",这一种方式的体现就是智能指针技术
- 比如书中提到智能指针`auto_ptr`,但是这一种智能指针已经被废弃(被`C++11`中的`unique_ptr`取代)
- 使用对象管理资源的两个关键想法:
  - 获取资源之后立刻放入管理对象中: 也就是所谓的 "资源取得时机便是初始化时机(`Resource Acquisiton Is Initialization`(`RAII思想`))"
  - 管理资源运用析构函数确保资源被释放
- 使用智能指针管理资源代码如下:
```cpp
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
```
- 注意指定由于`shared_ptr`和`unique_ptr`不可以的默认删除器不可以删除数组,所以需要指定删除器函数删除指向的数组对象
- 总结:
  - 为了防止资源泄漏,请使用`RAII`对象,他们在构造函数中获得资源并且在析构函数中释放资源
  - 两个常被使用的智能指针对象: `shared_ptr`和`unique_ptr`,前者的拷贝行为比较直观但是无法解决依赖循环等问题(可以使用`weak_ptr`解决这一个问题)