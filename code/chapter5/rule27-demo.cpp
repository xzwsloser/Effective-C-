#include<iostream>
#include<memory>
#include<vector>
using namespace std;
class Animal{
public:
    virtual void speak() {};
};

class Dog: public Animal{
public:
    virtual void speak()
    {
        cout << "小狗在说话 ..." << endl;
    }
};
int main()
{
    vector<shared_ptr<Animal>> spas;
    spas.push_back(shared_ptr<Animal>(new Dog()));
    spas.push_back(shared_ptr<Animal>(new Dog()));
    spas.push_back(shared_ptr<Animal>(new Dog()));
    spas.push_back(shared_ptr<Animal>(new Dog()));
    for(const auto& item : spas)
    {
        item -> speak();
    }
    
    // 或者直接使用转型,最好不用使用
    for(auto& item : spas)
    {
        Dog* d = dynamic_cast<Dog*>(item.get());
        d -> speak();
    }
}