#include<iostream>
using namespace std;
class Animal{
public:
    virtual ~Animal(){
        cout << "Base class was destoryed !" << endl;
    }
};

class Dog: public Animal{
public:
    ~Dog(){
        cout << "derived class was destoryed !" << endl;
    }
};
int main()
{
    Dog d;
    Animal* a = &d;
}