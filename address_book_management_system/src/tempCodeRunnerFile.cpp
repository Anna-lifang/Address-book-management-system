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