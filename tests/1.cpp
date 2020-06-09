#include <iostream>
#include "supercalc.hpp"

using namespace std;

int main()
{
	SuperCalc<int> sc(1, 11);
	
	sc(0, 10) = 0;
	for (int i = 0; i < 10; i++) {
		sc(0, 10) += sc(0, i);
	}
	
	for (int i = 0; i < 10; i++) {
		int x;
		cin >> x;
		sc(0, i) = x;
	}
	
 	cout << (int)sc(0, 10) << endl; //  сумма с (0, 0) по (0, 9) в ячейке (0, 10)
	return 0;
}
