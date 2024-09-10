# 了解 new-handler 的行为
- 当`operator new`抛出异常来反映一个没有获得满足的内存需求之前,它会首先调用一个客户端指定的错误处理函数,一个所谓的`new-handler`(其实`operator new`所做的事情更加复杂)
- 定义与`<new>`中的`set_new_handler`就可以设置全局的`new_hanlder`,定义如下:
```cpp
namespace std {
    typedef void (*new_handler)();
    new_handler set_new_handler(new_handler p) throw();
};
```
- 比如可以这样设置`new_handler`:
```cpp
void out_of_mem()
{
    cerr << "can't get enough memory!" << endl;
    abort();  //  打断程序的继续运行
}

set_new_handler(out_of_mem);
```
- 一个好的`new_handler`中需要做的事情:
  - 当`operator new`无法满足内存申请需求的时候,就会不断调用`new_handler`函数,直到找到足够的内存,比如可以一开始就是分配一个大内存,之后当`new_hanlder`第一次被调用把他们归还给程序使用
  - 安装另外一个`new_handler`,可以调用另外一个可以申请更大内存的`new_handler`从而来申请更大的内存
  - 卸载`new_handler`,也就是将`null`指针传递给`set_new_handler`,一旦吗没有安装任何`new_handler`,`operator new`就会在内存分配不成功的时候抛出异常
  - 抛出`bad_alloc`,这样的异常不会被`operator new`捕捉,而是会被传递到内存需要之处(调用之处)
  - 不返回,通常调用`abort`或者`exit`

- 如果想要为一个类单独设置`new_handler`,那么可以自己提供这一个类的`set_new_handler`和`operator new`运算符号

- `set_new_handler`中只用保存原来调用时候的状态,并且需要维护一个`current_handler`用于记录现在的处理方法,同时注意`operator new`中需要做的事情如下:
  - 调用标准的`set_new_handler`,注册`Widget`的错误处理函数,这会把`Widget`的`new_hanlder`安装为`global new_handler`
  - 调用`global operator new`,执行实际的内存分配,如果内存分配失败,`global operator_new` 会调用`Widget`的`new_handler`函数,如果`global operator new`最终无法分配足够的内存,会抛出一个`bad_alloc`异常,在此情况下
`Widget`的`operator new`必须恢复之前的`global new-handler`,并且传播异常,为了确保原来的`new_handler`总是能够被重新安装回去,`Widget`可以将全局的`new_handler`市视为资源,利用`RAII class`
  - 如果可以分配一个对象,就可以直接返回指针,执行分配得到的空间,`Widget`的析构函数会管理`global new_handler`,它会自动将`Widget的operator new`被调用之前的哪一个`global`恢复过来(利用`set_new_hanlder`记录的状态)

- 同时可以使用模板让所有的类都拥有这一套处理方案:
```cpp
template<typename T>
class NewHandlerSupport {
public:
    static new_handler set_new_handler(new_handler p) throw();   // 作用就是一个set函数的作用设置成员属性
    static void* operator new(size_t size) throw(bad_alloc);
private:
    static new_handler currentHandler;
};
// 实现
template<typename T>
new_handler NewHandlerSupport<T>::set_new_handler(new_handler p)
{
    new_handler old_handler = current_handler;
    current_handler = p;
    return old_handler;
}

template<typename T>
void* NewHandlerSupport::operator new(size_t size) thr_ow(bad_alloc)
{
    NewHandlerSupport h(std::set_handler(currentHandler));  // 对于这一个临时对象,作用就是改变全局的 new_handler
    return ::operator new(size);
}

template<typename T>
new_handler NewHandlerSupport<T>::currentHandler = nullptr;


class Widget: public NewHandlerSupport<Widget>
{
    ...
}

void* Widget::operator_new(size_t size) throw(bad_alloc)
{
    NewHandlerSupport h(std::set_handler(currentHandler));  // 对于这一个临时对象,作用就是改变全局的 new_handler
    return ::operator new(size);
}
```
- 注意设置为`static`的好处就是可以不断延续`new_handler`的使用,应该还需要在析构函数中重新设置`set_new_handler`(应该是自动调用的)
- 总结:
  - `set_new_handler`允许客户指定一个函数,在内存分配无法满足时被调用
  - `Nothrow new`是一个颇为局限的工具,因为它只适用于内存分配,后继的构造函数还是可能抛出异常