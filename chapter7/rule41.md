# 了解隐式接口和编译时多态
- 首先明确显示接口和原型时多态的含义,一个显式接口如下:
```cpp
// 显式接口
class My_Num {
public:
    My_Num(int val): val(val) {}

    int get_val()
    {
        return val;
    }

    bool operator> (My_Num& m)
    {
        return val > m.get_val();
    }

    void swap(My_Num& other)
    {
        using std::swap;
        cout << "交换中 ..." << endl;
    }
    virtual ~My_Num()
    {

    }
    My_Num() {}
private:
    int val;
};

// 运行时多态
void do_some(My_Num& m)
{
    cout << m.get_val() << endl;
    My_Num m1(20);
    if(m > m1)
    {
        cout << "true" << endl;
    }
}
```
- 注意这一个`My_Num`也就是一个显式接口,它的形式以及签名(比如函数的名称等)都在源码中是可见的
- 对于这一个函数,由于`My_Num`还是可能作为很多函数的父类,所以具体的`m`的类型还是需要运行是才可以确定,所以这就是原型时多态
- 把上述代码改造成如下这一种:
```cpp
template<typename T>
void do_real_thing(T& t)
{
    cout << t.get_val() << endl;
    T t1(20);
    if(t > t1)
    {
        cout << "true" << endl;
    }
}
```
- 这一个函数支持哪一类参数不是由它的签名决定,而是由它其中具体合法的表达式决定的,比如这一个参数必须含有`get_val`方法还有重载了`>`的运算符号,所以这就是通过合法的表达时确定了可以传入的参数,这一类接口就是隐式接口
- 另外这一个函数模板中,只用当确定传入参数类型的时候才知道调用哪一个函数,也就是根据不同的`template`具象化`function template`会导致调用不同的函数,这便是所谓的编译时多态(编译时期多态在编译完成之后就可以确定具体调用哪一个类型的函数了,所以称之为编译时多态)

- 注意决定隐式接口的要素就是其中的合法的表达时也就是确定的含有相关函数或者运算符号的参数

- 总结:
  - `classes`和`templates`都支持接口和多态
  - 对于`classes`而言接口是显式的,以函数签名为中心,多态则是通过`virtual`函数发生于运行时的
  - 对于`template`而言,接口是隐式的,基于有效表达式,多态则是通过`template`具象化和函数重载解析发生于编译时期