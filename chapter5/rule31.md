# 将文件之间的编译依存关系降低到最小
- 考虑如下类的实现式:
```cpp
#include<string>
#include "date.h"
#include "address.h"
class Person{
public:
    Person(const std::string& name , const Date& birthday , const Address& addr);
    std::string name() const;
    std::string birthDay() const;
    std::string addresss() const;
private:
    std::string name;   // 实现细目
    Date birthday;      // 实现细目
    Address theAddress;  // 实现细目
};
```
- 上述代码中,如果这些头文件中有任何一个发生更改,那么所有包含`Person`这一个`class`类的文件就需要重新编译,这样的连串编译依赖依存关系会对于许多项目造成难以形容的灾难
- 下面讨论解决这一个问题的方法
## handle class
- 也就是利用句柄类来解决,也就是把实现和接口进行分割,比如把`Person`分割成两个类,一个类只是负责提供接口,另外一个类负责实现该接口,如果负责实现该接口的类被称为 `PersonImpl`,那么`Person`的定义方式可以写成:
```cpp
#include<iostream>
#include<string>
class PersonImpl;
class Date;
class Address;
class Person {
public:
    Person(const std::string& name , const Date& birthday , const Address& addr);
    std::string name() const;
    std::string birthDay() const;
    std::string addresss() const;
private:
    shared_ptr<PersonImpl> pImpl;
};
```
- 注意里面的具体实现方式就是 前置声明 + 类的声明式
- 对于类中的函数在头文件中定义还是在`.cpp`文件中定义都可以
- 对于一个类中的函数,可以自定义".cpp"文件实现,或者直接在类中实现也可以(或者比较简单的函数声明为`inline`并且在类中实现,比较复杂的函数单独实现即可)

- `Person.h`
```cpp
#pragma once
#include "PersonImpl.h"
#include<memory>
class PersonImpl;  // 表示前置声明
class Person {
public:
    Person(const string& name , const int& age): pi(new PersonImpl(name , age)) {}
    inline string get_name() { return pi -> get_name(); }
    inline int get_age() { return pi -> get_age(); }
private:
    shared_ptr<PersonImpl> pi;
};
```

- `PersonImpl.h`
```cpp
#pragma once
#include<iostream>
#include<string>
using namespace std;
class PersonImpl {
public:
    PersonImpl(const string& name , const int& age): name(name) , age(age) {}
    inline string get_name() {return name;}
    inline int get_age() {return age;}
private:
    string name;
    int age;
};
```

- `main.cpp`
```cpp
#include "Person.h"
int main()
{
    Person p("张三" , 10);
    cout << "name = " << p.get_name() << "age = " << p.get_age() << endl;
}
```
- 类中的函数自动加上`inline`,所以比较简单的函数直接写在类中,但是比较复杂的函数最好写在类外实现(另外使用一个`.cpp`文件即可)
## Interface class
- 也就是接口类,`C++`中没有接口的概念 , 所以使用抽象类来模拟一个接口,通常还可以通过一个静态方法向外提供一个工厂方法获取一个指向抽象类的指针(还是利用了多态的性质),从而使得抽象了可以调用各种方法
- `Person.h`
```cpp
#pragma once
#include<iostream>
#include<string>
#include<memory>
using namespace std;
class Person {
public:
    static shared_ptr<Person> createPerson(string  name , int age);
    virtual ~Person(){};
    virtual string get_name() = 0;
    virtual int get_age() = 0;
};
```
- `RealPerson.h`
```cpp
#pragma once
#include  "Person.h"
using namespace std;
class RealPerson: public Person {
public:
    RealPerson(string name , int age): name(name) , age(age) {}
    string get_name() override {
        return name;
    }
    int get_age() override {
        return age;
    }
    virtual ~RealPerson() {}
private:
    string name;
    int age;
};
shared_ptr<Person> Person::createPerson(string  name , int age)
{
    return shared_ptr<Person>(new RealPerson(name ,age));
}
```
- `main.cpp`
```cpp
#include "RealPerson.h"
int main()
{
    shared_ptr<Person> pp = Person::createPerson("lisi" , 20);
    cout << "name = " << pp -> get_name() << endl;
    cout << "age = " << pp -> get_age() << endl;
}
```
- 这里父类的虚构函数需要写成`virtual`类型便于调用子类的析构函数

- 总结:
  - 支持"编译依存性最小化"的一般构思就是: 相依于声明式,不要相依于定义式,几次这一个构想的两个方式: `Handle class`和`Interface class`
  - 程序库头文件应该完全使用完全仅有声明式的形式存在,这一种做法无论是否设计`template`都适用