# 宁以`non-member`,`non-friend`替换`member`函数
- 比如对于如下的类(用于请求浏览器中的各种资源):
```cpp
class WebBrower{
public:
    void clear_cache();
    void clear_history();
    void clear_cookies();
};
```
- 此时还需要提供一个函数用于请求所有的东西(包含缓存,浏览历史和 `cookies`),有两种做法如下,一种就是封装成成员函数,另外一种就是封装成普通的非友元函数:
```cpp
class WebBrower{
public:
    void clear_everyting();
};
```
- 或者:
```cpp
void clear_everything();
```
- 面向对象守则要求,数据以及操作系统的那些函数应该被捆绑在一起,这就意味着它建议成员函数是比较好的选择但是事实上不是如此,考虑可封装性,对外的可以访问类的接口资源越小说明这一个类的封装性越高,可扩展性也就越好,所以选择非成员函数是一种不错的想法(就是只是在类中封装需要的成员函数,其他的不需要的成员函数(也就是不是之家操作类中的各种属性的成员函数可以考虑封装成非成员函数从而提高封装性和可扩展性))
- 另外以上规则只是适用于非成员函数和非友元函数而不适用于友元函数,这是由于友元函数提供了外界访问类中资源的接口对于封装性的冲击类似于成员函数
- 另外一种思想就是不一定一个类的非成员非友元函数就一定不可以是另外一个类的成员函数,比如如上例子中的函数就可以再次封装成一个管理类(比如封装成工具类与`Java`类似),一种和是的做法就是把这一个函数和管理的类放在同一个`namespace`中,比如:(这是由于`namespace`可以跨越多个源码文件存在但是`class`不可以)
```cpp
namespace WebBrowserStuff {
    class WebBrowser {}
    void clear_everything(WebBrowser& wb);
}
```
- 这一种封装思想就是把管理不同对象的函数放入到不同的头文件中但是隶属于同一个命令空间,意味着客户可以轻松扩展这一组函数
- 比如标准库中的各种头文件(`<vector>`,`<algorithm>`,`<memory>`)都是声明了同一个命名空间`std`
- 一般来说都是工具类可以声明在一个命名空间中,对于一个类中的成员一般类内声明,类外实现:
```cpp
// webbrowser.h
namespace WebBrowserStuff 
{
    class WebBrowser {}
}
// webbrowserbookmarks.h
namespace WebBrowserStuff {

};
// webbrowsercookies.h
namespace WebBrowserStuff {
    ...
};
```
- 作用: 一般就是用于声明工具类(包含各种工具,比如`.h`文件中利用`namespace`包含声明,`.cpp`文件中也使用`namespace`包含定义)
- 总结:
  - 宁可使用非成员函数非友元函数替换成员函数,这样做可以增加封装性,包裹弹性和机能扩展性
