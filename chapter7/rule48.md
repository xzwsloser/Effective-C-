# 认识template元编程
- 模板元编程(`TMP`)是编写基于模板的`C++`程序并且执行与编译时期的过程
- `TMP`的好处:
  - 完成某些不可以完成的操作
  - 执行与编译时期,可以把工作从运行时期转移到编译时期,可以提前发现一些出现在运行时期的错误
  - 较小的可执行文件,较短的运行期以及较少的内存需求
- 缺点: 编译时间变长了

- 上一个条款中提到的`triaits class`其实就是模板模板元编程的一种用途,试想如果不使用模板元编程,那么就会导致定义的`advance`函数中有一部分代码无效,但是利用模板元编程就可以把类型的判断移动到编译时期,效率更高
- 可见模板元编程中的`if else`条件判断可以使用函数重载实现
- 同样,模板元编程中的循环可以使用递归函数实现,下面尝试利用模板元编程求解阶乘:
```cpp
#include<iostream>
using namespace std;
template<unsigned n>
struct Factional {
    enum {value = n * Factional<n - 1>::value};
};

template<>
struct Factional<0> {
    enum{ value = 1 };
};
int main()
{
    // cout << Factional<5>::value << endl;
    // cout << Factional<10>::value << endl;
    cout << Factional<10>::value << endl;
}
```
- 总结以下使用模板元编程的好处和注意事项:
  - 选择正确的量度
  - 可以优化矩阵运算
  - 可以生活曾客户定制的设计模式
- 但是还不支持调试功能

- 总结:
  - 模板元编程可以把工作从运行时期转移到编译时期,因此可以实现早期错误侦测和更加高效的实行效率
  - 模板元编程可以用于生成"基于政策选择组合"的客户定制代码,也可以用于避免生成某些特殊类型并不合适的代码