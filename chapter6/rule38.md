# 通过复合塑模出`has-a`或者"根据某物实现出"
- 首先阐述复合关系: 就是表示某一种类型的对象中内含有另外一种类型的对象,比如如下代码:
```cpp
class Address { ... };
class Date { ... };
class Person{
private:
    Address address;
    Date birthday;
};
```
- 程序中的对象相当于你所塑造的世界中的某些事物,例如人等(不是为了完成什么功能的实现而被塑造出来的),这些对象属于"应用域",其他对象纯粹用于实现某些细节的人工制品比如互斥锁,信号量,缓冲区等这些对象被成为实现域对象
- 当复合发生在应用域对象的时候,表现出`has - a`的关系,当它发生在实现域对象中就是表示`is-implemented-in-terms-of`的关系(也就是"根据某物实现出")

- 使用一个例子来明确 "`is - a`"和`is - implemented-in-terms-of`的区别,考虑使用`std::list`实现一个`set`类来承装互相不重复的元素
- 第一种方案:
```cpp
class Set: public std::list 
{
    ...
}
```
- 利用`public`继承就可以得到`is - a`,但是这一种模型要求父类和子类的行为相同,但是`std::list`可以存储重复元素,不满足`is-a`的规则,所以不可行,考虑如下情况:
```cpp
template<typename T>
class Set {
public:
    ...
private:
    std::list<T> rep; // 用于存储Set的数据
};
```
- 以上的复合关系就是利用了`is-implemented-in-terms-of`的模型(也就是之前提到过的"根据某物实现出")

- 总结:
  - 复合的意义和`public`继承完全不同
  - 在应用域,复合意味着`has-a`,但是在实现域中,复合意味着`is-implemented-in-terms-of`(根据某物实现出)