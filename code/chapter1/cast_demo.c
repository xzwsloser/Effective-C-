#include<stdio.h>
int main()
{
    // 显示类型转换
    int a = 1;
    double b = 3.14;
    int c = (int)(a + b);
    printf("c = %d \n" , c);  // 4
    // 将指针类型转换为数字类型
    int* p = &a;
    int d = (int)p;
    printf("d = %d , p = %x \n" , d  , p); // 注意此时把 p 指向的数第的之赋值给了 d
    void* pv = 120;
    int f = (int)pv;
    int* pi = 120;
    int k = (int)pi;
    printf("f = %d , k = %d \n" , f , k); // 120,指向常数可以直接转换
    char* str = "1234";
    // 使用内置函数
    int i = atoi(str);
    printf("i = %d \n" , i);

}