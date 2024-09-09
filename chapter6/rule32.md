# 确定你的public继承塑模出is-a关系
- 首先记住一句话: 使用`C++`进行面向对象编程,最重要的一个规则就是`public-inheritance`(公开继承)意味着"`is-a`"(是一种)的关系
- 比如`class D`使用`public`继承`class B`,就可以看成`D`是一种`B`,也就是`B`中的所有动作全部可以由`D`完成,但是反之则不然,比如人(`Person`)和学生(`Student`)之间的关系

- 但是这一种`is - a`模型有时候却会引发错误,比如如下的例子中:
```cpp
class Bird {
public:
    virtual void fly() 
    {
        cout << "Bird can fly" << endl;
    }
};

class Penguin: class Bird 
{

}
```
- 很明显,虽然🐧是一种鸟,但是🐧不会飞,这也就是貌似满足`is - a` 关系,但是父类的行为在子类中不适用的情况
- 所以改为如下的例子(通过分层):
```cpp
class Bird {
public:
   
};
class FlyBird : public Bird {
public:
    virtual void fly() 
    {
        cout << "Bird can fly" << endl;
    }
}
class Penguin: class Bird 
{

}
```
- 另外还是会有一些反直觉的继承关系,比如:
```cpp
class Rectangle
{
private:
    int width;
    int height;
}

void make_bigger(Rectangle& r)
{
    int old_height = r.height;
    r.setWidth(r.width() + 10);  // 假设存在这些方法
    assert(r.width() == r.height());
}

class Square: public Rectangle 
{

}
```
- 这一次没有发生上面的错误,但是仍然存在错误,比如利用多态传递函数参数的时候,其实也会存在不合理的地方,这也就是`is - a`模型的第二种不合理的地方

- 总结:
  - `public`继承意味着`is - a`,适用于`base classes`身上的每一件事情(成员函数或者非成员函数)一定也适用于子类身上,因为每一个子类也是一种父类对象
