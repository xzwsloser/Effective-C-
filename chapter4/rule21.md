# 必须返回对象的时候,别妄想返回其 reference
- 有时候使用`pass-by-reference-to-const`的方式传递返回值和使用`pass-by-value`方式的传递返回值略显逊色
- 比如使用`pass-by-reference-to-const`的方式传递返回值的缺点如下:
1. 如果选择在栈区创建一个对象并且返回它的引用,这一种行为是及其错误的,这是由于当函数执行完毕之后,栈区的内容就会被释放,那么此时你创建的对象也就会被释放,如果返回这一个对象的引用就会导致不明确行为
2. 如果选择在栈区创建一个对象并且返回它的引用,可能会导致内存泄漏的风险,比如如下代码中:
```cpp
#include<iostream>
#include<string>
using namespace std;
class Rational{
friend const Rational& operator*(const Rational& lhs , const Rational& rhs);
public:
    Rational(int up , int down): up(up) , down(down) {}
    Rational() {}
private:
    int up;
    int down;
};

const Rational& operator*(const Rational& lhs , const Rational& rhs)
{
    Rational* res = new Rational(lhs.up*rhs.up , lhs.down*rhs.down);
    return *res;
}
int main()
{
    Rational w,x,y,z;
    w = x * y * z;
}
```
- 对于以上代码,`x * y`会在堆区创建一个对象,`(x * y) * z`也会在堆区创建一个对象,但是这两个对象无法得到及时的释放所以会引发内存泄漏
3. 如果采用返回一个类中的`static`修饰的对象的引用,这一种方式虽然不会引发前面的问题,但是问题就是如果调用这一个函数返回的对象都是相同的,那么进行比较运算符号比较的时候就会发生两个相同对象之间的比较,这很明显不是我们想要看到的
4. 解决方式: 就是返回一个新的对象,比如:
```cpp
const Rational operator* (const Rational& lhs , const Rational& rhs)
{
    return Rational(lhs.up * rhs.up , lhs.down * rhs.down);
}
```
- 这虽然会引发多次构造函数和析构函数的调用,但是别无它选
- 总结:
  - 绝对不要返回`pointer`或者`reference`指向一个`local stack`对象,或者返回一个引用指向分配到堆区的对象,或者返回一个引用或者指针指向一个`local static`对象而有可能同时需要这一些对象,这在多线程环境下明显是不合适的