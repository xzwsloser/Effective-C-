#include<iostream>
#include<string>
using namespace std;
class Base{
public:
    Base(string str): text(str) {}
    const char& operator[] (int index) const
    {
        cout << "return a const reference to char " << endl;
        return text[index];
    }

    char& operator[] (int index)
    {
        cout << "return a reference to char" << endl;
        return text[index];
    }

private:
    string text;
};
int main()
{
    Base b1("hello");
    const Base b2("hello");
    cout << b1[2] << endl;
    cout << b2[2] << endl;
}