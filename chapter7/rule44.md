# 将与参数无关的代码抽离templates
- 共性与变性分析法: 分析一个函数或者类的时候,抽离出他们共性的内容放入到另外一个类或者函数中,再在这些类或者函数中继承或者调用之前的类和函数即可
- 针对于函数或者类中的代码的重复确实容易发现,但是针对于模板中代码重复却十分那一察觉,考虑如下案例(`SquareMatrix`用于求解逆矩阵)：
```cpp
template<typename T , size_t n>   // 表示存储类型为 T , 并且大小为 n * n 的矩阵
class SquareMatrix {
public:
    void invert();   // 执行翻转操作
}
```
- 这一个类的测试用例如下:
```cpp
SquareMatrix<double , 5> ms1;
ms1.invert();
SquareMatrix<double , 10> ms2;
ms2.invert();
```
- 可见,`n`值的不同导致生成不同的`invert`函数,并且这些`invert`函数中的`n`值固定(毕竟是非类型模板参数)
- 所以考虑抽出共性代码放入到另外一个类模板中,所以可以做如下改进:
```cpp
template<typename T>
class SquareMatrixBase {
public:
    void invert(int n)
    {
        ... 处理矩阵...
    }
};

template<typename T , size_t n>
class SquareMatrixBase: private SquareMatrixBase<T>
{
public:
    void  invert()
    {
        this -> invert(n);  // 防止覆盖命名
    }
}
```
- 这样的一种修改的确降低了代码的重复性,但是由带来了另外一个问题: 如果获取操作的矩阵,或许解决思路如下:
  - 在`SquareMatrix`中定义一个而为数组用于装载矩阵,在`SquareMatrixBase`中定义一个指针指向而为数组的首地址
  - 并且在子类中的指针可以在堆区分配内存,甚至定义为`RAII`对象,比如改进如下:
```cpp
template<typename T>
class SquareMatrixBase {
public:
    SquareMatrixBase(T* data  , size_t n): data(data),n(n) {}
    void invert()
    {

    }
private:
    T* data;
    size_t n;
};

template<typename T , size_t n>
class SquareMatrix: public SquareMatrixBase<T>
{
public:
    SquareMatrix(): SquareMatrixBase(nullptr , 0),pData(new T[n][n]) 
    {
        this -> set_pdata(pData);
    }
    void  invert()
    {
        this ->  invert();
    }
private:
    boost::scoped_array<T> pData;  // 表示底层的指针
}
```
- 以上即使讨论非类型参数的处理方式,对于类型参数的处理方式类似,比如对于`vector<int>`和`vector<long>`,可能由的连接器会合并二者的代码但是其他的链接器不会,对于指针类型作为泛型的函数模板,一般都会重写一个`void*`类型为参数的函数模板,之后其他类型的函数调用`void*`版本的实现即可

- 总结:
  - `Templates`生成多个`classes`和多个函数,所以任何`template`代码都不该和某一个造成膨胀的`template`参数产生相依赖的关系
  - 由于非类型模板参数而造成的代码膨胀,往往可以消除,做法就是以函数参数或者`class`成员变量替换`template`参数
  - 由于类型模板参数而造成的代码膨胀,往往可以降低,做法就是让带有完全相同的二进制表示的具现类型共享实现代码