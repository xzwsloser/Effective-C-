#include<iostream>
#include<string>
using namespace std;
class Rational{
friend const Rational& operator*(const Rational& lhs , const Rational& rhs);
public:
    Rational(int up , int down): up(up) , down(down) {}
    Rational() {}
private:
    int up;
    int down;
};

const Rational& operator*(const Rational& lhs , const Rational& rhs)
{
    Rational* res = new Rational(lhs.up*rhs.up , lhs.down*rhs.down);
    return *res;
}
int main()
{
    Rational w,x,y,z;
    w = x * y * z;
}
