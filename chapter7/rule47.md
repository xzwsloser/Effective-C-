# 请使用traits classes表现类型信息
- 首先关注一个问题: 对于一个`STL`容器它的迭代器可能种类很多,对于不同种类的迭代器运算方式自然户通,那么如何确定不同迭代器的运算方式,`STL`容器中通过一个函数模板来处理对于各种迭代器的操作,比如：
```cpp
template<typename IterT , typename DistT>
void advance(IterT& itert , DistT d);   // 表示让 itert前进 d 个单位
```
- 那么这一个函数中如何区分迭代器中的种类,首先回顾迭代器的五种类型:
  - 输入迭代器
  - 输出迭代器
  - 前向迭代器
  - 双向迭代器
  - 随机访问跌打器
- 各种迭代器都提供了标记结构体:
```cpp
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag: public input_iterator_tag {};
struct bidirectional_iterator_tag: public forward_iterator_tag {};
struct random_access_iterator_tag: public bidirectional_iterator_tag {};
```
- 其实继承结构也就表示功能的增强
- 可以通过`Traits`技术来标记不同种类的迭代器,其实这不是一个关键字而是一个协议规范,任何使用`Traits`的都需要遵循这一个规范,`traits`类有很多往往用于比标记种类,其中`iterator_traits`用于标记结构体种类,声明如下:
```cpp
template<typename IterT>
struct iterator_traits;
```
- `iterator_traits`的运行方式就是针对于每一个可能的迭代器类型,在`struct iterator_traites<IterT>`中一定声明某一个`typedef`名为`iterator_category`,这一个`typedef`用于确定`IterT`的迭代器分支,所以在相关的容易中也一定会声明自己的迭代器类型:
```cpp
template<...>
class vector {
public:
    class iterator {
        public:
            typedef random_access_iterator_tag iterator_category;
    };
};


template<...>
class list {
public:
    class iterator {
        public:
            typedef bidirectional_iterator_tag iterator_category;
    };
};
```
- 那么在`traits class`中的对应方式就是:
```cpp
template<typename IterT>
struct iterator_traits {
    typedef typename IterT::iterator_category iterator_category;  // 其实就是作为一个中转站来标记类型
};
```
- 所以 `advance` 函数可以写成:
```cpp
template<typename IterT , typename DistT>
void advance(IterT& t , DistT d)
{
    if(typeid(typename iterator_traits<IterT>::iterator_catetory) == typeid(random_access_iterator_tag)) 
    {
        // 随机访问迭代器的操作
    }

}
```
- 注意对于嵌套类型(比如 `C::const_iterator`)需要使用`typename`标记这是一个类型,也就是表示`typename`是一个类型
- 但是以上代码仍然有缺陷,判断在运行时期执行,但是确定类型在编译时期已经确定,不可能延长确定类型的时间,所以这一种做法不合理
- 可以总结一下自己创建`traits class`的方法:
  - 首先确定若干个你将来可以取得类型相关信息,例如对于迭代器而言,我们希望把他们分类
  - 为该信息选择一个名称(`iterator_category`)
  - 提供一个`template`和一个特化版本,内含你希望处理的类型的相关信息
- 这里解释以下内涵版本,这里一般希望`traits class`也可以处理指针,所以需要提供一个指针的特化版本,比如:
```cpp
template<typename IterT>
struct iterator_traits<IterT*>
{
    typedef random_access_iterator_tag iterator_category;  // 表示内置数据类型就就是可以看成随机访问迭代器
}
```
- 但是还是需要继续改进这一个方法,可以想到的就是为不同种类的迭代器提供不同的方法,所以可以使用函数重载的方式,比如:
```cpp
template<typename IterT , typename DistT>
void do_advance(IterT& iter , DistT d , std::random_access_iterator_tag)
{
    iter += d;
}


template<typename IterT , typename DistT>
void do_advance(IterT& iter , DistT d , std::bidirectional_iterator_tag)
{
    if(d >= 0) { while(d--) ++iter; }
    else { while(d++) --iter; }
}

//.......
```
- 但是还是需要一个函数来控制这些重载函数的运用,所以得到`advance`的最终版本:
```cpp
template<typename IterT , typename DistT>
void advance(IterT& t , DistT d)
{
    do_advance<IterT , DistT>(t , d , typename iterator_traits<IterT>::iterator_category());
}
```
- 所以使用`traits class`的方式如下:
  - 建立一组重载函数或者函数模板,把彼此之间的差异就只是在于各自的`traits`参数,令每一个函数实现代码和它接受的`traits`信息相符合
  - 建立一个控制函数或者函数模板,它调用上述那些重载函数,并且传递`traits class`需要的信息
- 在标准库中定义了许多`traits class`用于标记内置数据类型或者数组类型

- 总结
  - `Traits class`使得类型相关的信息在编译器可用,它们以`templates`和`templates`特化完成实现
  - 整合重载技术之后,`traits classes`有可能在编译期对于类型执行`if...else`测试