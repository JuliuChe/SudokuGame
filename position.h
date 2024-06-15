#ifndef POSITION_H
#define POSITION_H


class Position
{
public:
    Position(int x=0, int y=0);
    int getXPos();
    int getYPos();
    void setXPos(int x);
    void setYPos(int y);
    void setPos(int x, int y);

private:
    int x,y;

};

#endif // POSITION_H
