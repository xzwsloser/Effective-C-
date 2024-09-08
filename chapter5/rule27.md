# 尽量少做转型动作
- 首先先回顾以下常见的转型操作:
- 旧式转型:
```cpp
(T)expression;

T(expression);
```
- `C++` 提供的四种新型转型:
```cpp
const_cast<T>(expression);
dynamic_cast<T>(expression);
reinterpret_cast<T>(expression);
static_cast<T>(expression);
```
- 这几种转型的作用如下:
  - `const_cast`通常用于将对象的常量性移除(比如之前说过的,让非`const`修饰的方法调用`const`修饰的成员方法)
  - `dynamic_cast`主要用于执行"安全向下转型",也就是用于决定某一个对象是否归属于继承体系中的某一个类型,它是唯一无法使用旧式转型的动作,也是唯一一个可能耗费中到资源的转型动作
  - `reinterpret_cast`意图执行低级转型,实际动作(和结果)可能取决于某一个编译器,这也就表示它不可以移植(类似于`C`语言中的显式强制类型转换)
  - `static_cast`用于强迫隐式类型转换,例如把`non-const`转换为`const`,可以进行各种转型操作比如把父类的指针转型到子类的指针,但是无法把`const`转换成`non-const`
- 下面提出一种使用旧式类型转换的代码:
```cpp
class Wiget{
public:
    exlicit Widget(int size);  // 修饰符号的作用: 防止隐式类型转换
};

void do_some(const Widget& w);

do_some(Widget(10));

do_som(static_cast<Widget>(100)); 
```
- 注意这里作者表示为了隐藏自己转型的意图,所以使用第一种方式比较多
- 任何一个类型转换(不论是通过转型操作而进行的显式转换,或者通过编译器完成的隐式转换,往往真的令编译器编译出运行期间执行的代码)

- 比如 `C ++`中的多态:
```cpp
class Base {}
class Derived: public Base {}

Derived d;
Base* b = &d;
```
- 注意上述代码中(也就是多态),运行多个指针指向同一个对象(也就是 `d`和`b`都执行同样一个对象)

- 这就会引发使用转型的第一个问题,比如如下代码中:
```cpp
class Window {
public:
    virtual void onResize() { ... }
};

class SpecialWindow : public Window {
public:
    virtual void onResize()
    {
        static_cast<Window>(*this).onResize();
    }
};
```
- 注意上述代码中反应的问题(其实也是所有转型中可能出现的问题,转换得到的对象其实就是对于原来对象的部分属性的拷贝): 它调用的不是当前对象上的函数,而是稍早转型动作所建立的一个`*this`对象之`base class`成分的暂时副本身上的`onResize`
- 这就会导致,如果在父类中的`onResize`改变了某些属性并且子类的`onResize`也改变某一些属性,由于父类使用副本,所以实际的改变不会影响到子类对象本身的改变,所以就会造成数据改变不同步的错误
- 下面讨论`dynamic_cast`的缺点:
- 首先`dynamic_cast`的一种实现方式就是不断比较`class`名称,所以对于这一种转型动作(`dynamic_cast`)的调用的消耗成本比较高,一种关于四种类型转换函数的描述: https://zhuanlan.zhihu.com/p/690005832
- 不使用`dynamic_cast`的解决方式:
  - 尽量不要进行子类和父类之间的类型转换,如果是调用子类中的函数就使用子类对象调用即可
  - 在父类中提供`virtual`函数表示你相对每一个子类做的事情,并且在子类中实现,比如:
```cpp
#include<iostream>
#include<memory>
#include<vector>
using namespace std;
class Animal{
public:
    virtual void speak() {};
};

class Dog: public Animal{
public:
    virtual void speak()
    {
        cout << "小狗在说话 ..." << endl;
    }
};
int main()
{
    vector<shared_ptr<Animal>> spas;
    spas.push_back(shared_ptr<Animal>(new Dog()));
    spas.push_back(shared_ptr<Animal>(new Dog()));
    spas.push_back(shared_ptr<Animal>(new Dog()));
    spas.push_back(shared_ptr<Animal>(new Dog()));
    for(const auto& item : spas)
    {
        item -> speak();
    }
    
    // 或者直接使用转型,最好不用使用
    for(auto& item : spas)
    {
        Dog* d = dynamic_cast<Dog*>(item.get());
        d -> speak();
    }
}
```
- 最后注意不要使用连串的`dynamic_cast`,并且使用`dynamic_cast`的时候也需要进行异常捕捉
- 总结:
  - 如果可以,尽量避免转型操作,特别是在注重效率的代码中避免`dynamic_cast`,如果有一个设计需要转型动作,尝试发展不需要转型的方案
  - 如果转型是必要的,尝试把它隐藏在某一个函数背后,客户随后可以调用该函数,并且不需要把转型放入到自己的代码中
  - 宁可使用新式转型,不要使用旧式转型,前者很容易辨识,而且也更加有着分门别类的职责