# 在`operator=`中处理自我赋值操作
- 有时候会发生自我赋值操作,但是这些操作有时是无意的,比如让多个指针指向一个对象,之后进行指针之间的赋值,或者让多个引用指向同一个对象,甚至让不同的父类指针指向同一个子类对象,这些情况都可能为自我赋值的发生提高基础
- 自我赋值的危害如下,考虑如下代码:
```cpp
class Person{
public:
    int* pa;
    Person& operator=(Person& rhs)
    {
        if(pa != nullptr)
        {
            delete pa;
            pa = nullptr;
        }
        pa = new int(*rhs.pa);
        return *this;
    }
};
```
- 如果 `rhs` 指向将要赋值给的对象,很容易就会引发异常情况
- 所以最好在这一个重载运算符号中检查自我赋值比如如下代码:
```cpp
class Person{
public:
    int* pa;
    Person& operator=(Person& rhs)
    {
        if(this == &rhs) return *this; // 查看指向的地址是否一致
        if(pa != nullptr)
        {
            delete pa;
            pa = nullptr;
        }
        pa = new int(*rhs.pa);
        return *this;
    }
};
```
- 另外一种方法就是首先不进行删除操作赋值原来的样本之后改变执行,最后删除即可:
```cpp
Widget& Widget::operator=(const Widget& rhs)
{
    BitMap* porig = pb;
    pb = new Bitmap(*rhs.pb);
    delete porig;
    return *this;
}
```
- 但是在这一种情况之下,还是有可能会导致赋值失败,比如 `new Bitmap`抛出异常的情况下就无法保证异常安全
- 所以另外一种方法就是使用 拷贝和交换技术(之后详细展开):
```cpp
Widget& Widget::operator=(const Widget& rhs)
{
    Widget temp(rhs); // 拷贝副本
    swap(temp); // 进行交换
    return *this;
}
```
- 上述代码其实就是利用了值传递的方式进行数据的拷贝操作
- 总结:
  - 确保当对象自我赋值的时候的`operator=`有良好的行为,其中技术包括比较"来源对象"和"目标对象"的地址,精心周到的语句顺序,以及`copy-and-swap`
  - 确定任何函数如果操作一个以上对象,而其中的多个对象是同一个对象,其行为仍然正确
