#include<iostream>
#include<string>
using  namespace std;
class Shape {
public:
    enum ShapeColor {RED , BLUE , PINK};
   void draw(ShapeColor color = PINK)
   {
        do_draw(color);
   }
private:
    virtual void do_draw(ShapeColor color)
    {
        if(color == PINK){
            cout << "是粉色" << endl;
        } else if(color == BLUE){
            cout  << "是蓝色" << endl;
        }
    }
};

class Rectangle: public Shape {
public:
   
private:
    virtual void do_draw(ShapeColor color)
    {
        if(color == PINK){
            cout << "是粉色" << endl;
        } else if(color == BLUE){
            cout  << "是蓝色" << endl;
        }
    }
};
int main()
{
    Shape* s = new Rectangle();
    s -> draw();
}