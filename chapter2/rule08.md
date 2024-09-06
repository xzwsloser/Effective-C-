# 别让异常逃离析构函数
- 考虑一种场景: 如果自定义一种数据类型`Person`,利用一个容器装下这一种数据类型的实例化对象,比如`vector<Person>(10 , Person())` 比如在销毁这一个`vector`容器的时候,如果在删除第一个`Person`的同时,出现错误,如果直接把以后异常吞掉,那么就会导致之后的对象不会被释放
- 可以在析构函数捕捉异常,比如一个管理数据库连接的对象`DBConn`如下:
```c
class DBConn{
public:
    ~DBConn()
    {
        try{
            db.close();
        } catch(Exception& e){
            std::abort();
        }
    }
private:
    DBConnection db;
};
```
- 以上代码中使用`abort`函数终止程序的执行,如果不使用`abort`终止程序(就是把异常吞了),就会发生不明确行为(比如内存泄漏)
- 另外最好为外界提供一个接口用于控制是否调用这一个析构函数,这就可以让用户对于问题的排查更加容易
```cpp
class DBConn{
public:
    void close()
    {
        db.close();
        close = true;
    }
    ~DBConn()
    {
        if(!closed){
            try{
                db.close();
            } catch(Exception& e){
                    std::abort();
            }
        }
    }
private:
    DBConnection db;
    bool closed;
};
```
- 总结: 析构函数不用吐出异常,如果一个析构函数调用的函数可能抛出异常,析构函数需要捕捉任何异常,之后吞下他们(可以处理的情况下)或者结束程序
- 如果客户需要对于某一个操作函数运行期间抛出的异常做出反应,那么就需要提供一个普通函数执行这一个操作
