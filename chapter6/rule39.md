# 明智而审慎地使用private继承
- 继承权限于成员访问权限之间的关系如下:
![alt text](<../img/image copy.png>)
- 如果利用`public`继承,那么就会形成一种`is - a`的模型, 比如 `Student`类使用`public`继承的方式继承`Person`类,那么这一种情况下,`Person`类在多态的时候就会转换为`Student`类,但是如果`Student`使用`private`的方式继承`Person`,那么就会导致`Person`无法转换为一个`Student`对象,应为二者变量的可见性不同

- 注意: `private`继承意味着`implemented-in-terms-of`(根据某物实现出),和复合在实现域中的意义一致,但是应该选择那一种方式呢(也就是说`private`在软件设计中没有意义,但是在软件实现中有意义)
- 一般来说: 尽可能使用复合,必要的时候才使用`private`继承,主要是当`protected`成员或者`virtual`函数牵扯进来的时候需要使用`private`
- 考虑如下例子,这一类用于记录方法的调用次数:
```cpp
class Timer {
public:
    Timer(int tickFrequency);
    virtual void onTick() const;
}
```
- 所以如果出现一个类需要记录方法调用的次数,那么就需要利用这里的`onTick`方法,有时需要重写`onTick`方法,这里考虑两种策略：
```cpp
// 使用 private 继承之后重写的方法
class Widget: private Timer {
private:
    virtual void onTick() const
    {
        ...
    }
};
```
```cpp
class WidgetTimer: public Timer {
public:
    virtual void onTick() const
    {
        ...
    }
};

class Widget {
private:
    shared_ptr<WidgetTimer> wt;
}
```
- 第二种做法比第一种做法的原因:
  - 如果你想要让`Widget`成为一个父类,同时需要让它的子类继承父类中的元素,但是不可以重写`onTick`方法,那么如果利用第一种方法,子类还是可以重写父类中的`onTick`方法(在虚函数表中),但是利用第二种方式,子类就无法重写父类中的`onTick`方法(封装到对象中了)
  - 减少了编译的依存性,如果使用第一种方法一定需要引入`Timer.h`,如果`Timer.h`发生变化就需要重新编译,但是如果利用第二种方式,只用带有`WidgetTimer`的声明式子即可(定义式可以放在`Timer.h`中或者其他位置)

- 一种需要使用`private`继承的场景: 当一个意欲成为子类这想要访问一个意欲成为父类者的`protect`成分,或者为了重新定义一个或者多个`virtual`函数的时候
- 另外一种情况就是空间最优化,考虑如下一个空类:
```cpp
class Empty{};
class A {
private:
    int x;
    Empty  e;
};

class B : private Empty{
private:
    int x;
};
```
- 可以得到`sizeof(A) > sizeof(int)`但是`sizeof(B) == sizeof(int)`
- 这是由于空类中塞入了一个`char`,由于内存对齐的原因,导致这种场景,第二种方式成为`EBO`(空白基类最优化)

- 但是脱离于这两种情况,其他的情况占大多数,所以还是推荐使用复合的形式来模拟 "根据某物实现"

- 总结:
  - `private`继承意味着根据某物实现,它通常比利用复合的级别低,但是当子类需要访问父类中受保护的成员或者重新定义继承而来的`virtual`函数的时候,这样的设计就是合理的
  - 和复合不同,`private`继承可以造成`empty base`最优化,这对于致力于"对象尺寸最小化"的程序开发者而言,可能比较重要