/*
 * Example of Operator Overloading
 */
#include <iostream>
#include <cstdint>

using namespace std;

//
// In operator overloading - which operator type can be applied is based
// on the signature of the use of the operator
//
// for eg:-
// 	int << int : this would mean a left bit shift.
// 	ostream& << int : this would mean a output operator
//
//
enum class days:int8_t
{
	SUNDAY,
	MONDAY,
	TUESDAY,
	WEDNESDAY,
	THURSDAY,
	FRIDAY,
	SATURDAY
};

// unlike plain enums C++11 enum class is typesafe and does not silently
// convert to int.
//

// overload the << operator.
inline ostream& operator<<(ostream& out, const days& d)
{
	out << static_cast<int>(d);
	return out;
}

// overload prefix operator
//
inline days operator++(days& d)
{
	d = static_cast<days>((static_cast<int>(d) + 1) % 7);
	return d;
}

// overload postfix operator
//
inline days operator++(days& d, int)
{
	days temp = d;
	d = static_cast<days>((static_cast<int>(d) + 1) % 7);
	return temp;
}

int
main()
{
	days today{days::MONDAY};

	cout << "Demonstrate class enum" << endl;
	cout << "Monday value is: " << today << endl;
	cout << "Increment value is: " << ++today << endl;
	cout << "Increment value is: " << today++ << endl;
	cout << "Increment value is: " << today << endl;

	return 0;
}
