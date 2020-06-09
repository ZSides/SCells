#include <iostream>
#include "supercalc.hpp"

using namespace std;

int main()
{
	SuperCalc<int> sc(1, 3);
	sc(0, 2) = (sc(0, 0) + sc(0, 1)) * (sc(0, 0) - sc(0, 1));
	sc(0, 1) = 2 * sc(0, 0);
	sc(0, 0) = 10;
	cout << (int)sc(0, 2) << endl; //  -300
	sc(0, 0) = 20;
	cout << (int)sc(0, 2) << endl; //  -1200
	sc(0, 1) = 5;
	cout << (int)sc(0, 2) << endl; //  375
	return 0;
}

