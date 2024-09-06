# 在资源管理类中提供对于原始资源的访问
- 虽然利用`RAII`对象管理资源很好用,但是还是存在一些情况需要取出`RAII`对象底层包裹的对象,比如某一个函数的参数要求`RAII`底层封装的对象才可以调用
- 所以对于一个`RAII`对象,还是需要提供对于其封装的原始对象进行访问的接口,比如`shared_ptr`和`unique_ptr`对象中就提供了相应的`get`方法来提供对于原始对象的访问
- 演示`demo`如下:
```cpp
#include<iostream>
#include<memory>
#include<functional>
#include<string>
using namespace std;
class Person{
public:
    string name;
    int age;
    Person(string name , int age): name(name) , age(age) {}
    Person() {}
};

void func(Person* p)
{
    cout << "func is working" << endl;
}
int main()
{
    shared_ptr<Person> sp(new Person("lisi" , 20));
    // func(sp); // err
    func(sp.get());
}
```
- 同理,我们在封装`RAII`对象的时候也需要提供访问原始资源的接口,这一种方式包含显示转换或者隐式转换:
  - 显示转换,主要就是提供相应的接口返回元素对象,比如`shared_ptr`的`get`方法
  - 隐式转换,可以通过重载强制类型转换运算符号的方式进行隐式转换(注意重载方法即可):
```cpp
#include<iostream>
#include<memory>
#include<functional>
#include<string>
using namespace std;

class MyNum{
public:
    MyNum(int num): num(num) {}
    MyNum() {}
    // 注意此时的函数可以没有返回值,这是由于不可以进行返回值的转换
    operator int() {
        return num;
    }
private:
    int num;
};

void func1(int a)
{
    cout << "a = " << a << endl;
}
int main()
{
    func1(MyNum(10));
}
```
- 总结:
  - `APIs`往往要求访问原始资源,所以每一个`RAII`对象应该提供一个"取得其所管理的资源"的方法
  - 对于原始资源的访问可能经由显式转换或者隐式转换,一般而言,显式转换比较安全，但是隐式转换对于客户比较方便
