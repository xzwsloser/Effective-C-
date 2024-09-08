# 避免返回handles指向对象内部成分
- `handles`: 指的就是 引用,指针或者迭代器这一种用于标记变量地址的量
- 使用`handles`返回对象内部成分的缺点如下:
1. 会改变原有属性的访问权限(比如原来的变量是`private`访问权限,返回之后可能"变成"`public`访问权限)
- 比如如下例子:
```cpp
class Point{
public:
    Point(int x , int y): x(x) , y(y) {}
    void setX(int val);
    void setY(int val);
private:
    int x;
    int y;
};

struct RectData{
    Point ulhc;
    Point lrhc;
};

class Rectangle{

private:
    shared_ptr<RectData> pData;
};
```
- 如果返回内部对象的引用,比如:
```cpp
public:
    Point& upper_left() const {return pData -> ulhc};
    Point& lower_right() const {return pData -> lrhc};
```
- 这一种情况下,就可以利用返回的`Point&` 对于矩形中的`private`修饰的变量进行修改,也就是降低了访问权限(也就是虽然没有提供对外访问的接口但是还是可以访问)
- 所以应该注意:
  - 成员变量的封装性最好只是等于"返回 `reference`"的函数的访问权限
  - 如果一个`const`成员函数传出了一个`reference`,后者所指向的数据于对象自身有关联,而它又被储存在对象之外,函数的调用这可以修改这个变量
- 注意自己提供对外的接口不算降低访问权限,没有提供接口但是可以访问才是降低了访问权限!!!
2. 如果使用`const`情况会不一样吗:
```cpp
public:
    const Point& upper_left() const {return pData -> ulhc};
    const Point& lower_right() const {return pData -> lrhc};
```
- 对于以上代码,虽然不可以修改返回的变量,但是可能发生 "`dangling handles`的问题",比如如下代码中:
```cpp
const Rectangle get_rec(const GUIObject&  obj);
const Point& res = (get_rec(obj).upper_left);
```
- 调用结束之后,其实`get_rec`返回的对象就被销毁了,所以这就导致引用指向了一个空对象,出现了 "虚调号码牌"的问题
- 经过以上的讨论,可以看出利用`handles`返回一个对象的内部成分是不安全的

- 总结:
  - 避免返回`handles`(包含`references`,指针,迭代器)指向对象外部,遵循这一个条款可以增强封装性,帮助`const`成员函数的行为像一个`const`,并将发生"虚调号码牌"的可能性将到最低