#include <iostream>

using namespace std;

class point {
	public:
		// default constructor
		point()
		{
			this->x = 0.0;
			this->y = 0.0;
		}

		// constructor
		point(double x, double y)
		{
			this->x = x;
			this->y = y;
		}

		void setx(double v)
		{
			x = v;
		}

		void sety(double v)
		{
			y = v;
		}

		double getx()
		{
			return x;
		}

		double gety()
		{
			return y;
		}

	private:
		double x, y;
};

ostream& operator<<(ostream& out, point& p)
{
	out << "(" << p.getx() << ", " << p.gety() << ")";
	return out;
}

point operator+(point& p1, point& p2)
{
	point sum((p1.getx() + p2.getx()), (p1.gety() + p2.gety()));
	return sum;
}
		

int
main()
{
	point p1(3.5, 4.5);
	point p2;

	cout << "Point p1: " << p1 << endl;
	cout << "Point p2: " << p2 << endl;

	p1.setx(4);
	p1.sety(6);

	p2.setx(7);
	p2.sety(8);

	cout << "Point p1: " << p1 << endl;
	cout << "Point p2: " << p2 << endl;
	cout << "Point p3: " << p1 + p2 << endl;

	return (0);
}
