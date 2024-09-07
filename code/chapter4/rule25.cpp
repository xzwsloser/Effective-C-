#include<iostream>
#include<string>
using namespace std;
// 一个普通的类
class Int_pointer{
public:
    Int_pointer(int val){
        this -> val = new int(val);
    }
    ~Int_pointer()
    {
        if(val != nullptr)
        {
            delete val;
            val = nullptr;
        }
    }
    // 提供一个交换方法
    void swap(Int_pointer& b)
    {
        using std::swap;
        swap(this -> val , b.val);
    }
    int get_val()
    {
        return *val;
    }
private:
    int* val;
};
// 并且提供 std::swap的特化方法
namespace std{
    template<>
    void swap<Int_pointer>(Int_pointer& a , Int_pointer& b)
    {
        a.swap(b);
    }
}

// 对于类模板的特化方式
namespace Temp{
template<class T>
class T_pointer{
public:
    T_pointer(T val){
        this -> val = new T(val);
    }
    ~T_pointer()
    {
        if(val != nullptr)
        {
            delete val;
            val = nullptr;
        }
    }
    // 提供一个交换方法
    void swap(T_pointer& b)
    {
        using std::swap;
        swap(this -> val , b.val);
    }
    T get_val()
    {
        return *val;
    }
private:
    T* val;
};

template<typename T>
void swap(T_pointer<T>& a , T_pointer<T>& b)
{
    a.swap(b);
}
}

int main()
{
    Int_pointer pa(1);
    Int_pointer pb(2);
    swap(pa , pb);
    cout << "pa = " << pa.get_val() << endl;
    cout << "pb = " << pb.get_val() << endl;
    Temp::T_pointer<int> pc(10);
    Temp::T_pointer<int> pd(20);
    Temp::swap(pc , pd);
    cout << "pc = " << pc.get_val() << endl;
    cout << "pd = " << pd.get_val() << endl;
}