# 写了placement new也要写placement delete
- 考虑如下代码:
```cpp
Widget* pw = new Widget;
```
- 如果分配内存成功但是调用构造函数失败,如果使用正常的`new`和`delete`当然就可以删除获取的空间,但是如果加上一需求: 需要记录日志,那么这一个需求就需要加上了另外一个参数的`new`来确定,这样的`new`也就是`placement new`,声明方式如下:
```cpp
void* operator new(std::size_t , void*  memry) throw(bad_alloc);
```
- 对应于`placement new`的也就是`placement delete`,也就是带有参数的`delete`:
```cpp
void operator delete(void*,void* memry) throw;
```
- 这一种情况在标准库中已经定义了,可以引入头文件: `<new>`即可
- 另外一个注意事项就是如果在一个类中重写了带有参数的`new`就会导致原来的`new`被隐藏(作用域被隐藏),解决方式就是可以定义另外一个类,这一各类中重写没有参数的`new`方法并且调用正常的`new`方法,之后需要使用正常的`new`方法的类就可以继承这一个类,之后使用`using`关键字就可以使用父类中的正常的`new`方法了

- 总结:
  - 当你写了一个`placement operator new`,请确定也写出了相应的`placement operator  delete`,如果没有这样做,你的程序就会发生隐微而时断时续的内存泄漏
  - 当你声明`placement new`和`placement delete`,请确定不要没有意识地掩盖它们的正常版本