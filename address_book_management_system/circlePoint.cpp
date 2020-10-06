#include<iostream>
using namespace std;

class Point
{
public:
 
    void setX(int x)
    {
        m_X = x;
    }
    int getX()
    {
        return m_X;
    }
    void setY(int y)
    {
        m_Y = y;
    }
    int getY()
    {
        return m_Y;
    }
private:
  int m_X;
   int m_Y;
};


class Circle
{
public:
    void setR(int r)
    {
        m_R = r;
    }
    int getR()
    {
        return m_R;
    }
    void setCenter(Point p)
    {
        pCenter = p;
    }
    Point getCenter()
    {
        return pCenter;
    }
private:
    int m_R;
    Point pCenter;

};

void isInCircle(Point &p, Circle &c)
{
    int distance = 
     (c.getCenter().getX()- p.getX())*(c.getCenter().getX()- p.getX())
    +(c.getCenter().getY()- p.getY())*(c.getCenter().getY()- p.getY());

    int rDistance = c.getR() * c.getR();
    
    if(distance == rDistance)
    {
        cout << "The point is on the circle"<< endl;
    }
    else if(distance > rDistance)
    {
        cout << "The point is outside of the circle"<< endl;
    }
    else
    {
         cout << "The point is inside of the circle"<< endl;
    }
}

int main(){

    Circle c;
    c.setR(10);
    Point center;
    center.setX(10);
    center.setY(0);
    c.setCenter(center);

    Point p;
    p.setX(10);
    p.setY(9);

    isInCircle(p,c);
    system("pause");
    return 0;
}


