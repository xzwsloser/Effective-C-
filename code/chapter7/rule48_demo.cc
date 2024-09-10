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