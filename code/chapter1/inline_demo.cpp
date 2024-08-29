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