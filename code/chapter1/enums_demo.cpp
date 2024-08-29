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