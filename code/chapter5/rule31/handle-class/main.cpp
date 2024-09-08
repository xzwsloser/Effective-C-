#include "Person.h"
int main()
{
    Person p("张三" , 10);
    cout << "name = " << p.get_name() << "age = " << p.get_age() << endl;
}