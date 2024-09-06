# 复制对象的时候不要忘记每一个成分
1. 如果你拒绝使用编译器提供的拷贝构造函数和赋值运算符,那么就会导致如果你没有写出一些成员的拷贝方式(也就是拷贝的时候忽略了一些成员),那么编译器也不会给你报错或者提醒(书中叫做一种"复仇行为"),这一种情况的解决方式就是注意给一个类中的每一个成员在拷贝构造函数或者赋值运算符号中进行相应的拷贝或者赋值操作
2. 第二种容易忽略拷贝一个类中的各种成员的情况就是忽略了父类中各种成员的拷贝(其实可以粗略的把子类理解成 父类 + 子类中的特有属性和方法),第二种错误的解决方式就是在子类的拷贝构造函数或者赋值运算符中把父类相关的属性进行拷贝(拷贝的时候当然可以调用父类中的拷贝函数)
3. 另外为了避免代码的重复可以定义一个第三方函数,在拷贝构造函数和赋值运算符中分别调用这一个第三方函数完成拷贝和赋值操作(有时候拷贝构造函数和赋值运算符号中的代码重复比较多)
- 一种实践如下:
```cpp
#include<iostream>
#include<string>
using namespace std;
class Base;
class Base{
public:
    int age;
    string name;
    Base(int age , string name) : age(age), name(name) {}
    Base() {}
};

class Son: public Base{
public:
    int gender;
    Son(int age , string name , int gender): Base(age , name) , gender(gender) {}
    Son(const Son& s): Base(s.age , s.name) , gender(s.gender) {}
    Son& operator=(const Son& s)
    {
         init(s); // 其实代码可以复用
         return *this;
    }
    void show_person()
    {
        cout << this -> name << "  " << this -> age << "  " << this -> gender << endl;
    }
private:
    void init(const Son& s)
    {
        this -> name = s.name;
        this -> age = s.age;
        this -> gender = s.gender;
    }
};

int main()
{
    Son s1(10 , "zhangsan" , 1);
    Son s2(s1);
    s1.show_person();
    s2.show_person();
    Son s3 = s1;
    s3.show_person();
}
```
- 总结:
  - 拷贝构造函数需要确保赋值对象内的所有成员变量以及所有的`base class`成分
  - 不要尝试使用某一个拷贝函数另外一个拷贝函数,应该将所有的共同机能的放入到第三方函数中,并且由两个拷贝函数共同调用