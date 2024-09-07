# 若所有的参数都需要类型转换,请为此采用non-member函数
- 考虑如下需求: 定义一个整数类完成,实现乘法运算符号并且实现混合运算
- 可以考虑如下类:
```cpp
class Rational{
public:
    Rational(int val): val(val) {}
    Rational() {}
    int get_val() {return val};
private:
    int val;
};
```
- 那么重载函数就可以有两种形式: 
  - 成员函数形式
  - 非成员函数形式
- 成员函数形式:
```cpp
const Rational operator* (const Rational& rhs)
{
    return Rational(val * rhs.get_val());
}
```
- 非成员函数形式:
```cpp
const Rational operator* (const Rational& lhs , const Rational& rhs)
{
    return Rational(lhs.get_val() * rhs.get_val());
}
```
- 对于成员函数形式,考虑以下两种情况:
```cpp
Rational a(10);
Rational b = a * 2;  // true
Rational c = 2 * a;  // err
```
- 第一种情况中`2`可以隐式转换为`Rational`(就比如 `Rational b = 2`),但是第二个语句中`int`类型的变量中没有参数为`Rational`的重载方法
- 所以这一种情况下使用非成员函数比较好,所以得到结论,如果想要想要让函数的每一个参数得到隐式类型转换,需要使用非成员函数
- 另外补充一点,此时的非成员函数不应该被声明为`friend`方式降低了类的封装程度,而是只依靠`public`接口中的方法来进行运算操作
- 总结:
  - 如果你需要为某一个函数的所有参数(包含被`this`指针所指向的哪一个隐喻参数)进行类型转换,那么这一个函数必须定义为非成员函数(考虑操作的拓展性)