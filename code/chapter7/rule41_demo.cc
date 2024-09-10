#include<iostream>
using namespace std;
// 显式接口
class My_Num {
public:
    My_Num(int val): val(val) {}

    int get_val()
    {
        return val;
    }

    bool operator> (My_Num& m)
    {
        return val > m.get_val();
    }

    void swap(My_Num& other)
    {
        using std::swap;
        cout << "交换中 ..." << endl;
    }
    virtual ~My_Num()
    {

    }
    My_Num() {}
private:
    int val;
};

// 运行时多态
void do_some(My_Num& m)
{
    cout << m.get_val() << endl;
    My_Num m1(20);
    if(m > m1)
    {
        cout << "true" << endl;
    }
}
template<typename T>
void do_real_thing(T& t)
{
    cout << t.get_val() << endl;
    T t1(20);
    if(t > t1)
    {
        cout << "true" << endl;
    }
}
int main()
{
    My_Num m(100);
    do_some(m);
}