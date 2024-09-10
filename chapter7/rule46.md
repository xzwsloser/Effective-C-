# 需要类型转换的时候请为模板定义非成员函数
- 这一条规则其实就是对应于面向对象的的规则中的条例`24`,所以可见不同的`C ++`模块可以总的规则并不相同,这里还会引发`friend`的第二个用途
- 首先对于条款`24`中的例子进行模板改写:
```cpp
#include<iostream>
using namespace std;
template<typename T>
class Rational {
public:
    Rational(const T& up = 0 , const T& down = 1): up(up) , down(down) {}
    Rational() {}
    const T get_up() const { return up; }
    const T get_down() const { return down; }
private:
    T up;
    T down;
};

template<typename T>
Rational<T> operator* (const Rational<T>& lhs , const Rational<T>& rhs)
{
    return Rational<T>(lhs.get_up() * rhs.get_up() , lhs.get_down() * rhs.get_down());
}
int main()
{
    Rational<int> r(1,2);
    Rational<int> r1(3, 4);
    Rational<int> res = r * r1;
    cout << res.get_down() << endl;
    cout << res.get_up() << endl;
    // Rational<int> res = r * 2;  // err
}
```
- 错误的原因就是对于第一个参数,可以通过类型推导推导出`T`就是`int`,但是对于第二个参数`int`,在`templates`实际参数推导过程中从来不会把隐式类型转换函数纳入考虑,所以解决方式就是把这一个实现方式换一个模块(比如换到`class`模块中),比如:
```cpp
template<typename T>
class Rational {
public:
    friend Rational operator* (const Rational& lhs ,const Rational& rhs);
    Rational(const T& up = 0 , const T& down = 1): up(up) , down(down) {}
    Rational() {}
    const T get_up() const { return up; }
    const T get_down() const { return down; }
private:
    T up;
    T down;
};
```
- 也就是利用了`friend`关键字把这一个非成员函数放入到类中,其实确定类的时候就已经确定了非成员函数的模板类型,并且诶在类中的类名称可以表示类名称 + 模板类型,也就是: `Rational`相当于`Rational<T>`
- 但是没有函数定义的话就会在链接阶段出现错误,所以正确的实现方式就是在类中进行函数定义:
```cpp
template<typename T>
class Rational {
public:
    friend Rational operator* (const Rational& lhs ,const Rational& rhs)
    {
        return Rational(lhs.get_up() * rhs.get_up() , lhs.get_down() * rhs.get_down());
    }
    Rational(const T& up = 0 , const T& down = 1): up(up) , down(down) {}
    Rational() {}
    const T get_up() const { return up; }
    const T get_down() const { return down; }
private:
    T up;
    T down;
};
```
- 所以最后改建的代码如下:
```cpp
#include<iostream>
using namespace std;
template<typename T>
class Rational {
public:
    friend Rational operator* (const Rational& lhs , const Rational& rhs)
    {
        return Rational(lhs.get_up() * rhs.get_up() , lhs.get_down() * rhs.get_down());
    }
    Rational(const T& up = 0 , const T& down = 1): up(up) , down(down) {}
    Rational() {}
    const T get_up() const { return up; }
    const T get_down() const { return down; }
private:
    T up;
    T down;
};

int main()
{
    Rational<int> r(1,2);
    Rational<int> r1(3, 4);
    Rational<int> res = r * r1;
    cout << res.get_down() << endl;
    cout << res.get_up() << endl;
    Rational<int> res1 = r * 2;  
    cout << res1.get_down() << endl;
    cout << res1.get_up() << endl;
}
```
- 并且`operator*`会被声明为内联函数,所以如果逻辑比较复杂,可以定义一个第三方的辅助函数,利用赋值函数完成工作,这就可以让这一个`operator*`继续被`inline`修饰
```cpp
#include<iostream>
using namespace std;
template<typename T>
class Rational {
public:
    friend Rational operator* (const Rational& lhs , const Rational& rhs)
    {
        return get_res(lhs , rhs);
    }
    Rational(const T& up = 0 , const T& down = 1): up(up) , down(down) {}
    Rational() {}
    const T get_up() const { return up; }
    const T get_down() const { return down; }
private:
    T up;
    T down;
};


template<typename T>
Rational<T> get_res(const Rational<T>& lhs , const Rational<T>& rhs)
{
    return Rational(lhs.get_up() * rhs.get_up() , lhs.get_down() * rhs.get_down());
}
int main()
{
    Rational<int> r(1,2);
    Rational<int> r1(3, 4);
    Rational<int> res = r * r1;
    cout << res.get_down() << endl;
    cout << res.get_up() << endl;
    Rational<int> res1 = r * 2;  
    cout << res1.get_down() << endl;
    cout << res1.get_up() << endl;
}
```
- 这一条准则体现了`C++`在两种模式之间的切换方式,就是利用`friend`关键字作为媒介

- 总结:
  - 当我们编写一个`class template`的时候,而它提供的"和这一个`template`相关的"函数支持"所有参数之隐式类型转换"时,请将那些函数定义为"`class template`内部 的`friend`函数"