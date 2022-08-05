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

struct Position     // Represents the position of some items / entities
{
    int x;
    int y;
    Position *next;
};
typedef Position *p_Position;
