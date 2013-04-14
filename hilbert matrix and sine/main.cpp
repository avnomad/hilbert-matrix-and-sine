//	Copyright (C) 2008, 2012 Vaptistis Anogeianakis <nomad@cornercase.gr>
/*
 *	This file is part of hilbert matrix and sine.
 *
 *	hilbert matrix and sine is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	hilbert matrix and sine is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with hilbert matrix and sine.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>
using std::cout;
using std::cin;
using std::cerr;
using std::endl;

#include <fstream>
using std::ofstream;

#include <iomanip>
using std::setprecision;

#include <cmath>
using std::fabs;

#include <ctime>
using std::clock;

#include <cfloat>


class Test
{
public:
	static void hilb(double *A , unsigned int order)
	{
		register double *p;
		register double *q;
		register unsigned int c,i,n;
		double x;


		p = A;	// set p at the beginning of A.

		c = 0;
		i = 2;
		*p = 1.0;	// set the first element of A to 1.

		while(++c != order)
		{
			*(q = ++p) = x = 1.0/i;
			++i;
			n = c;
			while(n--)
			{
				*(q += order-1) = x;
			}
		}
		while(--c)
		{
			*(q = p += order) = x = 1.0/i;
			++i;
			n = c;
			while(--n)
			{
				*(q += order-1) = x;
			}
		}

	} // end fuction hilb
}; // end class Test


int main()
{
	clock_t outTime , inTime;
	ofstream outFile("stats.txt");	// variables required for measuring and storing the results.

	unsigned int order = 0;	// variables needed for the program itself.
	double *A;

	outTime = clock();

	for(order = 1000 ; order <= 6000 ; order += 20)
	{
		A = new double[order*order];
		inTime = clock();
		Test::hilb(A,order);
		outFile<<clock()-inTime<<endl;
		delete[] A;
	}

	outFile<<"\n\n"<<clock()-outTime<<endl;



	//system("PAUSE");
	return 0;
} // end function main
