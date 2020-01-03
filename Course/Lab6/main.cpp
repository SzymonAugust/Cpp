#include <iostream>

using namespace std;

class Vector2D {
public:
    Vector2D(double x = 0, double y = 0) : x_{x},y_{y}
    {
        cout << "Vector2D constructor working..." << endl;
    }
    ~Vector2D()
    {
        cout << "~Vector2D destructor working..." << endl;
    }
    Vector2D(const Vector2D &other) : x_{other.x_},y_{other.y_}
    {
        cout << "Vector2D copy-constructor working..." << endl;
    }
    Vector2D& operator=(const Vector2D & other)
    {
        cout << "Vector2D operator= working..." << endl;
        if (this != &other)
        {
            x_ = other.x_;
            y_ = other.y_;
            cout << "this != &other" << endl;
        }
        else {
            cout << "this == &other" << endl;
        }

        return *this;
    }

    void operator+=(double i)
    {
        this->x_ += i;
        this->y_ += i;
    }

    void operator*=(double i)
    {
        this->x_ *= i;
        this->y_ *= i;
    }

private:
    double x_;
    double y_;
    friend ostream& operator<< (ostream& os, const Vector2D& vec);
    friend Vector2D operator+(const Vector2D& other1, const Vector2D& other2);
    friend Vector2D operator*(double i, const Vector2D& other);
    friend Vector2D operator*(const Vector2D& other, double i);
    friend double operator*(const Vector2D& other1, const Vector2D& other2);
    friend bool operator==(const Vector2D& other1, const Vector2D& other2);
    friend bool operator!=(const Vector2D& other1, const Vector2D& other2);
    friend Vector2D operator-(const Vector2D& other);
};

Vector2D operator-(const Vector2D& other)
{
    return Vector2D(-other.x_,-other.y_);
}

Vector2D operator+(const Vector2D& other1, const Vector2D& other2)
{
    return Vector2D(other1.x_ + other2.x_, other1.y_ + other2.y_);
}

double operator*(const Vector2D& other1, const Vector2D& other2)
{
    return (other1.x_ * other2.x_ + other1.y_ * other2.y_);
}

Vector2D operator*(double i, const Vector2D& other)
{
    return Vector2D(i*other.x_, i*other.y_);
}

Vector2D operator*(const Vector2D& other, double i)
{
    return Vector2D(i*other.x_, i*other.y_);
}

ostream& operator<< (ostream& os, const Vector2D& vec)
{
    os << "[" << vec.x_ << ", " << vec.y_ << "]";
    return os;
}

bool operator==(const Vector2D& other1, const Vector2D& other2)
{
    return other1.x_ == other2.x_ and other1.y_ == other2.y_;
}

bool operator!=(const Vector2D& other1, const Vector2D& other2)
{
    return !(other1 == other2);
}

int main()
{
    Vector2D v1, v2(1,2), v3(5), v4(v2), v5 = v4 + v2, v6 = 2*v5, v7 = v2 * 3 + v3;
    double score = v5 * v4;
    cout << v1 << endl
         << v2 << endl
         << v3 << endl
         << v4 << endl
         << v5 << endl
         << v6 << endl
         << v7 << endl
         << score << endl
         << (v2 == v4) << endl
         << (v1 != v2) << endl << endl;
         v1 += 6;
         v4 *= 2;
         v3 = -v2;
         cout << v1 << endl
         << v2 << endl
         << v3 << endl
         << v4 << endl
         << v5 << endl
         << v6 << endl
         << v7 << endl
         << score << endl
         << (v2 == v4) << endl
         << (v1 != v2) << endl;

    return 0;
}
