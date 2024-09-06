# Effective C++阅读笔记
- 如下是本人阅读`Effective C++`时所做的笔记

|`chapter1`|让自己习惯`C++`|
|---|---|
|条款01|[视C++为一个语言联邦](./chapter1/rule01.md)|
|条款02|[尽量使用 `const` `enum`和`inline`替换`#defind`](./chapter1/rule02.md)| 
|条款03|[尽可能使用 `const` 关键字](./chapter1/rule03.md)|
|条款04|[确定对象使用前已经初始化](./chapter1/rule04.md)|

|`chapter2`|构造/析构/赋值运算符|
|---|---|
|条款05|[了解`C++`默认编写并且调用了那些函数](./chapter2/rule05.md)|
|条款06|[如果不想使用编译器自动生成的函数,就应该明确拒绝](./chapter2/rule06.md)|
|条款07|[为多态基类声明`virtual`析构函数](./chapter2/rule07.md)|
|条款08|[请别让异常逃离析构函数](./chapter2/rule08.md)|
|条款09|[绝不要在构造和析构的过程中调用`virtual`函数](./chapter2/rule09.md)|
|条款10|[令`operator`返回一个`reference to *this`](./chapter2/rule10.md)|
|条款11|[在`operator=`中处理自我赋值操作](./chapter2/rule11.md)|
|条款12|[复制对象的时候不要忘记它的每一个成分](./chapter2/rule12.md)|