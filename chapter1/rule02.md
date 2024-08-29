# 尽量使用 const,enum,inline代替 #define
## enum类型
- 一种用户自定的数据类型,定义方式如下:
```cpp
enum 枚举名称 {枚举常量表}
```
- 为了防止枚举类型总是被强制转换为 `int` 类型,所以 `C++11` 中引入了强枚举类型,定义方式如下:
```cpp
enum class 枚举名称: 类型 {枚举常量表}
```
- 使用 `enum` 的 `demo` 如下:
```cpp
#include<iostream>
using namespace std;
// 定义枚举类型  默认从 0 开始
// 但是类型被转换为整形
enum Color {RED , GREEN , YELLOW ,WHITE = 10 , BLACK};
// C++11 新特性: 强类型枚举
// 可以指定类型
enum Number : unsigned int {ONE = 1 , TWO , THREE , FOUR};
int main()
{
    int a = RED;  
    cout << "a = " << a << endl;
    // 可以发生隐式类型转换
    char c = BLACK; // 11 注意从赋值的下一个位置开始
    cout << "c = " << (int)c << endl;
    Color d = YELLOW;
    cout << "d = " << d << endl; // Color  相当于int的别名
    // 强类型枚举
    int e = Number::ONE; //
    Number num = Number::FOUR;
    int k = num; 
    cout << "e = " << e <<endl;
    cout << "k = " << k << endl; 

}
```
## inline 内联函数
- `C` 语言中如果频繁调用某一个函数,这一个函数就会不断进栈出栈,消耗大量资源,所以引入了 `inline` 关键字,着一个关键字拥有声明函数为内联函数,内联函数在编译时会被替换(函数被替换成内部的逻辑操作),这样就节约了栈空间
- 但是内联函数的使用注意事项如下:
  - 声明和定义在一起,并且`inline`关键字在定义前面
  - 最好放在头文件中
  - 里面不要执行复杂的逻辑(比如循环判断递归等)
  - `inline`只是建议,具体会不会当成内联函数还需要编译器判断函数复杂度
  - 最好和 `static` 一起使用,这样就只用分配一次空间即可
- 内联函数的缺点:
  - 空间换时间,大量展开内联函数需要消耗大量空间,多次调用导致固件膨胀
- 优点:
  - 与宏定义相比,多了语法检查的过程
  - 与普通函数相比,减少了上下文环境的切换,执行更迅速
- 内联函数使用 `demo` 如下:
```cpp
#include<iostream>
using namespace std;

inline int Add(int x , int y);
inline int Add(int x , int y)
{
    return x + y;
}

static inline int Sub(int x , int y);
static inline int Sub(int x, int y)
{
    return x - y;
}
int main()
{
    int x = 10;
    int y = 20;
    cout << "x + y = " << Add(x , y) << endl;
    cout << "x -y = " << Sub(x , y) << endl;
}
```
## 使用 const 和 enums替代 #define
- 使用 `const` 替代 `#define` 的原因如下:
1. `#define` 定义的变量在预处理阶段被替换展开,所以编译器根本就无法看到`#define`定义的变量,这一个变量就不存在于符号表中,到时`debug`的时候无法看到具体的变量名称
- 这一种情况的解决方式就是在头文件中利用 `const` 定义常量,但是注意定义常量指针的定义方式:
```cpp
// 注意 const char* p 表示 p 指向的变量不可以修改
// char* const 表示 p的指向不可以修改,所以要使得 p 成为常量指针,需要使用如下方式:
const char* const p = "HELLO";
// 最好使用 string 代替 char*
const std::string p = "HELLO";
```
2. 对于类中的专属常量,不可以使用 `#define` 进行定义,需要使用 `staic` 进行修饰从而保证所有对象共享这一个常量,但是编译器要求`static` 修饰的常量在类里面定义,类外面声明
```cpp
class Person{
    static const int num;
};
const int Person::num = 20;
```
3. 所以如果类中需要使用 `num` 但是编译时期一开始不知道 `num` 的值,所以可以使用 `enum` 代替
```cpp
#include<iostream>
using namespace std;
class Person{
    static const int num;
    enum MyNum {ONE = 1 , TWO};
    int arr[TWO];
};
const int Person::num = 20;
```
## 使用 inline 函数代替宏定义函数
1. 这是由于利用 `#define` 定义的函数在预处理阶段使用替换的方式被替换到代码中来了,所以书写的时候必须特别注意,由于直接展开而产生的歧义,比如:
```cpp
#include<iostream>
using namespace std;
#define CALL_WITH_MAX(a,b)  my_print((a) > (b) ? (a) : (b))
void my_print(int val)
{
    cout << "val = " << val << endl;
}
int main()
{
    int a = 5 , b = 0;
    CALL_WITH_MAX(++a , b);  // 完全替换: (++a) > (b) ? (++a) : (b) ++ 执行了两次
    CALL_WITH_MAX(++a , b + 10);   // ++ 执行了一次
}
```
- 所以最好使用内联函数替代
```cpp
#include<iostream>
using namespace std;
#define CALL_WITH_MAX(a,b)  my_print((a) > (b) ? (a) : (b))
void my_print(int val)
{
    cout << "val = " << val << endl;
}
inline void add(int a , int b);
inline void add(int a , int b)
{
    my_print(a > b ? a : b);
}
int main()
{
    int a = 5 , b = 0;
    CALL_WITH_MAX(++a , b);  // 完全替换: (++a) > (b) ? (++a) : (b) ++ 执行了两次
    CALL_WITH_MAX(++a , b + 10);   // ++ 执行了一次

    add(a , b);
}
```
- 结论:
  - 对于单纯变量,最好使用 `const` 对象或者 `enum` 替换 `#define`
  - 对于形似函数的宏(`maros`),最好使用 `inline` 函数替代 `#define`