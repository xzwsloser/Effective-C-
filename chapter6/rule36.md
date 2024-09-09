# 绝不重新定义继承而来的non-virtual函数
- 考虑如下代码:
```cpp
class B {
public:
    void mf()
    {
        ...
    }
};

class D: public B {
public:
    void mf()
    {
        ...
    }
};
```
- 考虑如下测试用例:
```cpp
D d;
B* b = &d;
D* dl = &d;

b -> mf();  // 此时调用的还是 B::mf
dl ->mf();  // 调用的就是 D::mf
```
- 可见重写了`non-virtual`方法之后,虽然利用不同类型的指针指向同一个对象,但是被指向的这一个对象的行为居然不同(精神分裂?),这就引发了这样的后果
- 注意: 任何情况下都不应该重新定义一个继承而来的`non-virtual`函数
- 考虑析构函数,那么就变成如果需要使用析构函数那么就需要加上`virtual`关键字,否则无法调用子类的析构函数
- 这是由于`non-virtual`函数是静态绑定的,但是`virtual`函数是采用动态绑定的
- 总结: 绝对不要重新定义继承而来的`non-virtual`函数