# 编写new和delete的时需固守常规
- 重写`operator new`函数的时候,里面应该包含一个无限循环,无限循环中不断判断是否可以获取到合法的内存,如果获取到合法的内存就可以推出,或者当`new_handler`函数可以找到可以用于申请更大内存的`handler`的时候也就可以退出了,一种`operator new`的实现方式如下:
```cpp
void* operator new(size_t size) throw(bad_alloc)
{
    using namespace std;
    if(size == 0)
    {
        size = 1;
    }
    while(true)
    {
        if(内存分配成功)
        {
            return {一个指针,指向分配得到的内存}
        }
        new_handler global_handler = set_new_handler(0);
        set_new_handler(global_handler);
        if(globalhandler) (*globalhandler)()
        else throw bad_alloc();
    }
}
```
- 对于`delete`的实现,请注意永远记住,删除空指针的时候(也就是删除`nullptr`的时候)的安全性

- 总结:
  - `operator new`底层需要包含一个无限循环,并且在其中尝试分配内存,如果它无法满足内存需求,就需要 调用一个`new_handler`,它也应该有能力处理`0 bytes`申请,`Class`专属版本则还应该处理"比正确大小更大的(错误)申请"