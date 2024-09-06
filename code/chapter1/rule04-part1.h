#ifndef _PART1_H_
#define _PART1_H_
class Part1{
public:
    static int a;
};
int Part1::a = 10;
extern Part1 p1; // 表示暴露给外界的对象

#endif