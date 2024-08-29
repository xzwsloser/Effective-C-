#include<iostream>
#include<string>
using namespace std;
class Base{
public:
    Base(string str): text(str) {}
    const char& operator[] (int index) const 
    {
        cout << "模拟业务逻辑代码 ..." << endl;
        return text[index];
    }
    char& operator[] (int index)
    {
        return const_cast<char&>(
            (static_cast<const Base&>(*this))[index]
        );
    }

private:
     string text;
};
int main()
{
    Base b("hello");
    cout << b[1] << endl;
}