# 绝对不重新定义继承而来的缺省(默认)参数值
- 由于不可以重写`non-virtual`函数,所以这一个条款可以变成 "决定不要重新定义继承而来的`virtual`函数的缺省参数值"
- 静态参数: 表示类型就是声明时候的类型,编译时期已经确定了类型
- 动态参数: 表示目前的类型,也就是说,动态类型可以表现出一个对象会有什么行为,比如多态
- 所以本条条款成立的理由就是: `virtual`函数就是动态绑定参数,但是默认参数值却是动态绑定的

1. 问题提出,考虑如下代码:
```cpp
#include<iostream>
#include<string>
using  namespace std;
class Shape {
public:
    enum ShapeColor {RED , BLUE , PINK};
    virtual void draw(ShapeColor color = PINK) = 0;
};

class Rectangle: public Shape {
public:
    void draw(ShapeColor color = BLUE) 
    {
        if(color == PINK){
            cout << "是粉色" << endl;
        } else if(color == BLUE){
            cout  << "是蓝色" << endl;
        }
    }
};
int main()
{
    Shape* s = new Rectangle();
    s -> draw();
}
```
- 运行结果发现此时采用的默认才是还是父类中的默认参数,所以重新定义默认参数不可行

2. 解决方式: 利用`NVI`的方式可以让`draw`函数的默认参数总是一致的:
```cpp
#include<iostream>
#include<string>
using  namespace std;
class Shape {
public:
    enum ShapeColor {RED , BLUE , PINK};
   void draw(ShapeColor color = PINK)
   {
        do_draw(color);
   }
private:
    virtual void do_draw(ShapeColor color)
    {
        if(color == PINK){
            cout << "是粉色" << endl;
        } else if(color == BLUE){
            cout  << "是蓝色" << endl;
        }
    }
};

class Rectangle: public Shape {
public:
   
private:
    virtual void do_draw(ShapeColor color)
    {
        if(color == PINK){
            cout << "是粉色" << endl;
        } else if(color == BLUE){
            cout  << "是蓝色" << endl;
        }
    }
};
int main()
{
    Shape* s = new Rectangle();
    s -> draw();
}
```
- 这就可以保证`draw`函数的默认参数总是`PINK`,如果不指定默认参数就没有默认参数了

- 总结:
  - 绝对不要重新定义一个继承而来的缺省参数值,因为缺省参数只读总是静态绑定的,而`virtual`函数 -- 唯一一个需要重写的东西 -- 却是静态绑定的