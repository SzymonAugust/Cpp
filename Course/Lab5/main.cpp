#include <iostream>

using namespace std;

struct Position {
    Position(double posX, double posY) : x{posX}, y{posY} {
        cout << "Position::Position()" << endl;
    }
    ~Position() {
        cout << "Position::~Position()" << endl;
    }
    Position(const Position& other) {
        x = other.x;
        y = other.y;
        cout << "Position::Position(const Position& other)" << endl;
    }
    double x;
    double y;
};

class Ball {
public:
    void moveTo(double, double);
    Position position();
    Ball (double posX = 0, double posY = 0) : m_pos{posX,posY} {
        cout << "Ball::Ball(double, double)" << endl;
    }
    ~Ball() {
        cout << "Ball::~Ball(double, double)" << endl;
    }
private:
    Position m_pos;
};

//Ball::Ball (double a, double b)
//{
//    Ball::m_pos.x = a;
//    Ball::m_pos.y = b;
//}

void Ball::moveTo(double x, double y)
{
    m_pos.x = x;
    m_pos.y = y;
}

Position Ball::position()
{
    return m_pos;
}

ostream& operator<<(ostream& os, const Position& position)
{
    os << "(" << position.x << "," << position.y << ")";
    return os;
}

int main()
{
    Ball b;

    cout << b.position() << endl;
    b.moveTo(1,2);
    cout << b.position() << endl;

    return 0;
}
