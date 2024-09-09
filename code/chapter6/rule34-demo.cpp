#include<iostream>
using namespace std;
class Bird {
public:
    virtual void fly() = 0;
protected:
    
};

class Red_Bird: public Bird {
public:
    virtual void fly() override {
        cout << "红色的小鸟在飞翔" << endl;
    }
};

class Blue_Bird: public Bird {
public:
    virtual void fly()
    {
        Bird::fly();
    }
};

void Bird::fly()
{
    cout << "小鸟在飞翔" << endl;
}
int main()
{
    Bird* b = new Blue_Bird();
    b -> fly();
    Bird* b1 = new Red_Bird();
    b1 -> fly();
}