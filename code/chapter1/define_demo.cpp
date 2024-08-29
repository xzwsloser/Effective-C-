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