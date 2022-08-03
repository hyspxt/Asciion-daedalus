struct Position
{
    int x;
    int y;
    int life;
    Position *next;
};
typedef Position *p_Position;

class Coordinate
{
protected:
    Position point;

public:
    Coordinate();
    Coordinate(Position point);
    void setPosition(Position point);
    Position getPosition();
};
