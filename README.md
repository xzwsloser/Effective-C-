# Effective C++阅读笔记
- 如下是本人阅读`Effective C++`时所做的笔记

|`chapter1`|让自己习惯`C++`|
|---|---|
|条款01|[视C++为一个语言联邦](./chapter1/rule01.md)|
|条款02|[尽量使用 `const` `enum`和`inline`替换`#define`](./chapter1/rule02.md)| 
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

|`chapter3`|资源管理|
|---|---|
|条款13|[以对象管理资源](./chapter3/rule13.md)|
|条款14|[在资源管理类中小心`copying`行为](./chapter3/rule14.md)|
|条款15|[在资源管理类中提供对于原始资源的访问](./chapter3/rule15.md)|
|条款16|[成对使用`new`和`delete`时采取相同的形式](./chapter3/rule16.md)|
|条款17|[以独立语句将`newed`对象置入到智能指针中](./chapter3/rule17.md)|

|`chapter4`|设计与声明|
|---|---|
|条款18|[让接口被正确使用,不易被误用](./chapter4/rule18.md)|
|条款19|[设计`class`犹如设置`type`](./chapter4/rule19.md)|
|条款20|[宁以`pass-by-reference-to-const`替代`pass-by-value`](./chapter4/rule20.md)|
|条款21|[必须返回对象的时候,别妄想返回其`reference`](./chapter4/rule21.md)|
|条款22|[将成员声明为`private`](./chapter4/rule22.md)|
|条款23|[宁以`non-member`,`non-friend`替换`member`函数](./chapter4/rule23.md)|
|条款24|[若所有的参数都需要类型转换,请为此采用`non-member`函数](./chapter4/rule24.md)|
|条款25|[考虑写出一个不抛出异常的`swap`函数](./chapter4/rule25.md)|

|`chapter5`|实现|
|---|---|
|条款26|[尽可能延后变量定义式出现事件](./chapter5/rule26.md)|
|条款27|[尽量少做转型动作](./chapter5/rule27.md)|
|条款28|[避免返回`handles`指向对象的内部成分](./chapter5/rule28.md)|
|条款29|[为"异常安全"而努力是值得的](./chapter/rule29.md)|
|条款30|[透彻了解`inlining`的里里外外](./chapter5/rule30.md)|
|条款31|[将文件之间的编译依赖关系下降到最低](./chapter5/rule31.md)|

|`chapter6`|继承与面向对象设计|
|---|---|
|条款32|[确定你的`public`继承塑模出`is-a`关系](./chapter6/rule32.md)|
|条款33|[避免遮掩继承而来的名称](./chapter6/rule33.md)|
|条款34|[区分接口继承与实现继承](./chapter6/rule34.md)|
|条款35|[考虑`virtual`函数之外的选择](./chapter6/rule35.md)|
|条款36|[绝不重新定义继承而来的`non-virtual`函数](./chapter6/rule36.md)|
|条款37|[绝不重新定义继承而来的缺省参数](./chapter6/rule37.md)|
|条款38|[通过复合塑模出`has-a`或者"根据某物实现出"](./chapter6/rule38.md)|
|条款39|[明智而审慎地使用`private`继承](./chapter6/rule39.md)|
|条款40|[明智而审慎地使用多重继承](./chapter6/rule40.md)|

|`chapter7`|模板与泛型编程|
|---|---|
|条款41|[了解隐式接口和编译时期多态](./chapter7/rule41.md)|
|条款42|[了解`typename`的双重意义](./chapter7/rule42.md)|
|条款43|[学习处理模板化基类内的名称](./chapter7/rule43.md)|
|条款44|[将与参数无关的代码抽离`templates`](./chapter7/rule44.md)|
|条款45|[运用成员函数模板接受所有兼容类型](./chapter7/rule45.md)|
|条款46|[需要类型转换的时候请为模板定义非成员函数](./chapter7/rule46.md)|
|条款47|[请使用`traits classes`表现类型信息](./chapter7/rule47.md)|
|条款48|[认识`template`元编程](./chapter7/rule48.md)|