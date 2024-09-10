#include<iostream>
using namespace std;
template<typename T>
class Rational {
public:
    friend Rational operator* (const Rational& lhs , const Rational& rhs)
    {
        return get_res(lhs , rhs);
    }
    Rational(const T& up = 0 , const T& down = 1): up(up) , down(down) {}
    Rational() {}
    const T get_up() const { return up; }
    const T get_down() const { return down; }
private:
    T up;
    T down;
};


template<typename T>
Rational<T> get_res(const Rational<T>& lhs , const Rational<T>& rhs)
{
    return Rational(lhs.get_up() * rhs.get_up() , lhs.get_down() * rhs.get_down());
}
int main()
{
    Rational<int> r(1,2);
    Rational<int> r1(3, 4);
    Rational<int> res = r * r1;
    cout << res.get_down() << endl;
    cout << res.get_up() << endl;
    Rational<int> res1 = r * 2;  
    cout << res1.get_down() << endl;
    cout << res1.get_up() << endl;
}