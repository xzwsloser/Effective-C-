#include "RealPerson.h"
int main()
{
    shared_ptr<Person> pp = Person::createPerson("lisi" , 20);
    cout << "name = " << pp -> get_name() << endl;
    cout << "age = " << pp -> get_age() << endl;
}