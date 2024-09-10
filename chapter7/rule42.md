# 了解typename 的双重意义
- 首先了解`typename`的第一种含义: 也就是指定模板参数,在这一种含义下`typename`等价于`class`,比如:
```cpp
template<typename T>
template<class T>
```
- 可以选择一直使用`typename`或者`class`
- 在讨论第二种含义之前首先明确几种类型:
  - `template`内出现的名称如何相依与某一个参数(指的就是模板参数列表中的符号(比如上述的`T`)),称之为从属类型
  - 如果从属名称在`class`里面呈现嵌套式,我们称之为嵌套从属名称,比如如下代码:
```cpp
template<typename C>
void for_each(const C& container)
{
    C::const_iterator iter(container.begin());
}
```
- 其中的`C::const_iterator`也就是一种嵌套从属类型,但是在`C++`中往往不认为`C::const_iterator`是一种变量而不是一种类型,所以如何指定它为一种类型,这就引出`typename`的第二种含义,指定某一个嵌套类型为变量的类型而不是一种变量:
```cpp
template<typename C>
void for_each(const C& container)
{
    typename C::const_iterator iter(container.begin());
}
```
- 但是上述情况仍然存在特例: 在类的继承列表和初始化列表中不可以出现`typename`标记类型名称
```cpp
template<typename T>
class Son: public Base<T>::Nested {
public:
    Son(T& t): Base<T>::Nested(t) {}
}
```
- 有时候还可以使用`typedef`来简化名称:
```cpp
typedef typename std::iterator_traits<IterT>::value_type value_type;
```
- 总结:
  - 声明`template`关键字的时候,前缀关键字`class`和`typename`可以互换
  - 请使用关键字`typename`表示嵌套从属类型名称,但是不得在`base class lists`(基类列)或者`member initialization list`(成员初始值列表)内以它作为`base class`修饰符