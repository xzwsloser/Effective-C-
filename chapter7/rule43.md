# 学习处理模板化基类内的名称
- 考虑以下类,这一个类用于发送给每一个公司明文秘报和暗文秘报:
```cpp
class CompanyA {
public:
    void send_clear();
    void send_password();
};

class CompanyB {
public:
    void send_clear();
    void send_password();
};

template<typename T>
class MsgSender {
public:
    void send_msg(const string msg)
    {
        ...
        T c;
        c.send_clear(msg);
    }

    void send_password(const string msg)
    {
        ...
    }
};
```
- 上述代码中只要提供相应的泛型就可以调用不同的方法发送消息,但是如果此时我想要拓展一个可以记录的发送消息的类,可能会出现这一种情况:
```cpp
template<typename T>
class LoggingMsgSender: public MsgSender<T> {
public:
    void send_log_msg(const string& msg)
    {
        log(msg);
        send_msg(msg);  // 问题就在这一句代码中
    }

};
```
- 考虑出问题的一句代码,为什么会编译出错考虑如下情况,如果定义另外一个公司类,这一个公司只会发送暗文秘报:
```cpp
class CompanyC {
public:
    void send_password()
    {

    }
};
```
- 所以对于这一个公司不可以作为`MsgSender`的泛型,所以需要进行特化`MsgSender`:
```cpp
template<>
class MsgSender<CompanyC> {
public:
    void  send_password()
    {
        ...
    }
};
```
- 问题就来了,如果`CompanyC`作为`LoggingMsgSender`的参数就会导致调用`send_msg`方法出错,所以`C++`提前预料到这一点所以就会报错
- 解决方式由三种:
  - 使用 `this -> send_msg()` 调用方法(这一种调用方式对于`virtual`函数同样有效)
  - 使用 `using MsgSender<T>::send_msg()`
  - 使用 `MsgSender<T>::send_msg()`(这一种方法最糟糕,限定死了调用的`send_msg`无法形成多态)
- 总结:
  - 可以在子类中通过`this -> `指涉`base class templates`内的成员名称,或者由一个明白写出的`base class`资格修饰符完成