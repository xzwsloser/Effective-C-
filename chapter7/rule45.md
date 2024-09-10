# 运用成员函数模板接受所有兼容类型
- 考虑如下问题,在对于一个智能指针类,假如存储的对象为`Person`和`Son`其中`Son`继承于`Person`,那么就会导致`SmartPtr<Person> 和 SmartPtr<Son> 之间的相互转换就会失败`,假如有`java`中的`<? extend T>`就不用担心这一个问题
- 解决问题的方式就是利用构造函数模板化即可,就是利用添加模板之后的构造函数就可以解决这一个问题,可以使用如下代码解决问题:
```cpp
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
```
- 注意上述代码中重写泛型拷贝构造函数不会影响原来的拷贝构造函数的生成
  
- 总结:
  - 请使用`member function templates`(成员函数模板)生成"可接受参数兼容类型"的函数
  - 如果你生成`member templates`用于"泛化`copy`构造"或者返回`assignment`操作,你还是需要声明正常的`copy`构造函数和`copy assignment`操作符