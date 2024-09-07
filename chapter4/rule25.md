# 考虑写出一个不抛出异常的swap函数
- `swap`函数在数据的拷贝和异常安全中起这非常关键的作用,但是有时候对于某一个类,我们需要特化`swap`,那应该怎么做呢?
- 考虑`std`命令空间中的`swap`实现方式:
```cpp
namespace std{
template <typename T>
void swap(T& a , T& b)
{
    T temp(a);
    a = b;
    b = temp;
}
}
```
- 但是加入存在一个类,这一个类中只有一个指针在交换的时候需要交换,但是类中其他的成员都不需要交换,如果还是调用`std`中的这一个函数那就会导致调用多次拷贝构造函数构造一个很大的对象,从而浪费资源
1. `default swap`的特化方式
- 可以考虑将这一个类异化,比如:(这也就是`default swap`的特化方法)
```cpp
namespace std{
template <>
void swap<Widget>(Widget& a , Widget& b)
{
    swap(a.pImpl , b.pIml);
}
}
```
- 以上方法是不合法的,这是由于类中的指针是`private`权限保护的
2. 成员函数的特化方式
- 所以对于一般的类,可以把这一个需要使用的`swap`函数声明为成员函数并且在特化`swap`函数的时候调用成员函数,比如:
```cpp
class Widget{
public:
    void swap(Widget& b)
    {
        using std::swap;
        swap(pIml , b.pIml);
    }
private:
    int* pIml;
};

namespace std{
template <typename T>
void swap<Widget>(Widget& a , Widget& b)
{
    a.swap(b);
}
}
```
- 以上就是对于一个普通类的`swap`的特化方法,下面讨论对于类模板的特化方法:
3. 类模板中成员函数的特化方式
- 考虑如下类模板:
```cpp
template<class T>
class Widget {...}
```
- 考虑如下特化方式:
```cpp
template<typename T>
void swap<Widget<T>>(Widget<T>&a , Widget<T>& b)
{
    a.swap(b);
}
```
- 上述代码是完全错误的,注意此时`T`表示函数模板的参数,但是确用于指明类模板,在`C++`中只允许对于类模板进行特化,在函数模板上进行特化是实现的,所以考虑提供重载版本:
```cpp
template<typename T>
void swap(Widget<T>&a , Widget<T>& b)
{
    a.swap(b);
}
```
- 但是在`std`中最好不要添加新的类模板,解决方式就是定义新的命名空间,在新的命名空间中定义交换方式,比如:
```cpp
namespace WidgetStuff{
template<typename T>
class Widget {...}

template<typename T>
void swap(Widget<T>&a , Widget<T>& b)
{
    a.swap(b);
}
};
```
4. `swap`调用方式的确定
- 如果你想要让你的`classes`专属版的`swap`在尽可能多的语境下被调用,你需要同时在该`class`所在的命名空间中写一个非成员函数版本和`std::swap`特化版本,比如:
- 可以使用`using`确定调用方式:
```cpp
template<typename T>
void do_some(T& obj1 , T& obj2)
{
    using std::swap;
    swap(obj1 , obj2);
}
```
- 注意如果使用`std::swap`就是表示只可以使用`std`中的`swap`但是不可以使用其他位置的合理的`swap`

- 所以需要`swap`的时候考虑如下几点:
1. 提供一个`public swap`成员函数,让它高效置换你的类型的两个对象值
2. 在你的`class`或者`template`锁在的命名空间提供一个非成员函数,并且让它调用`swap`成员函数
3. 如果你正在编写一个类,为你的`class`特化`std::swap`,并且调用成员函数
- 注意由于`swap`的一个作用就是异常安全,所以不要让成员函数的`swap`抛出异常
- 最佳实践:
```cpp
#include<iostream>
#include<string>
using namespace std;
// 一个普通的类
class Int_pointer{
public:
    Int_pointer(int val){
        this -> val = new int(val);
    }
    ~Int_pointer()
    {
        if(val != nullptr)
        {
            delete val;
            val = nullptr;
        }
    }
    // 提供一个交换方法
    void swap(Int_pointer& b)
    {
        using std::swap;
        swap(this -> val , b.val);
    }
    int get_val()
    {
        return *val;
    }
private:
    int* val;
};
// 并且提供 std::swap的特化方法
namespace std{
    template<>
    void swap<Int_pointer>(Int_pointer& a , Int_pointer& b)
    {
        a.swap(b);
    }
}

// 对于类模板的特化方式
namespace Temp{
template<class T>
class T_pointer{
public:
    T_pointer(T val){
        this -> val = new T(val);
    }
    ~T_pointer()
    {
        if(val != nullptr)
        {
            delete val;
            val = nullptr;
        }
    }
    // 提供一个交换方法
    void swap(T_pointer& b)
    {
        using std::swap;
        swap(this -> val , b.val);
    }
    T get_val()
    {
        return *val;
    }
private:
    T* val;
};

template<typename T>
void swap(T_pointer<T>& a , T_pointer<T>& b)
{
    a.swap(b);
}
}

int main()
{
    Int_pointer pa(1);
    Int_pointer pb(2);
    swap(pa , pb);
    cout << "pa = " << pa.get_val() << endl;
    cout << "pb = " << pb.get_val() << endl;
    Temp::T_pointer<int> pc(10);
    Temp::T_pointer<int> pd(20);
    Temp::swap(pc , pd);
    cout << "pc = " << pc.get_val() << endl;
    cout << "pd = " << pd.get_val() << endl;
}
```
- 总结:
  - 当`std::swap`对于你的类型效率不高的时候,提供一个不抛出异常的`swap`成员函数
  - 如果你提供一个了成员的`swap`函数,也提供一个非成员函数调用前者,对于普通的类,请特化`std::swap`
  - 调用`swap`时应该针对`std::swap`使用`using`声明式,然后调用`swap`并且不带任何"命名空间修饰"
  - 为"用户自定义类型"进行`std template`的全特化是好的,但是前往不要在`std`里面加入对于某些`std`全新的东西