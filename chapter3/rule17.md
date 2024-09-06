# 以独立语句将newed对象放入到智能指针中
- 首先明确这一句话的含义: 也就是利用`RAII`思想的时候,一定需要注意利用一个独立的语句完成智能指针底层的指针的封装,不要让这一个行为和其他的行为一起串行执行
- 比如如下代码中:
```cpp
func(std::tr1::shared_ptr<Person> sp(new Person) , priority());
```
- 以上函数中需要完成如下三件事情:
  - `new Person()` 创建一个指向`Person`的指针
  - 把这一个指针放入到`shared_ptr`中进行资源管理
  - 调用`priority`方法得到返回值
- 像其他的语言比如`Java`等,这三件事情的执行顺序一定时固定的,但是`C++`中不是如此,所以可能造成如下的执行顺序:
  - `new Person`
  - `priority()`
  - 把对象放入到`shared_ptr`中
- 一旦形成这一种情况就会导致如果第二步中出现了异常就会导致前面创建的指针无法释放(当然如果直接捕捉异常或者吞掉也可以)
- 演示`demo`如下:
```cpp
#include<iostream>
#include<memory>
#include<string>
#include<functional>
using namespace std;
int priority()
{
    char* c = "hello";
    c[2] = 'D';
    return 1;
}

class Person{
public:
    ~Person()
    {
        cout << "~Person" << endl;
    }
};

void func(shared_ptr<Person> sp , int a)
{
    cout << "func" << endl;
}
int main()
{
    // err
    // func(shared_ptr<Person>(new Person()) , priority());
    shared_ptr<Person> sp(new Person() , [=](Person* p) {
        cout << "delete" << endl;
        delete p;
    }); 
    func(sp , priority());
}
```
- 总结: 以独立语句将`newed`对象存储于智能指针中,如果不这样做,一旦异常被抛出,有可能导致难以察觉的资源泄漏
