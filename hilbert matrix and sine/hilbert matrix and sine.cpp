// hilbert matrix and sine.cpp : main project file.

#include "stdafx.h"

/*
 * file main.cpp
 * created by Nightmare
 * on 5 ��� 2008
 */

using std::cout;
using std::cin;
using std::cerr;
using std::endl;

using std::ofstream;

using std::setprecision;

using std::fabs;

using std::clock;


class Test
{
public:
	static double sine(register double x)
	{
		register double sum = x;
		register double term = x;
		register int i = 2;

		x = -x*x;
		//cout<<x<<endl;
		term = x*term / ((i + 1)*i);

		while(fabs(term/sum) > 1e-15/*fabs(term) > 1e-9*/)
		{
			sum += term;
			//cout<<sum<<endl;
			i += 2;
			term = (x*term) / ((i + 1)*i);
		} // end while

		return sum;
	}

	static void hilb(double *A , unsigned int order)
	{
		register double *p;
		register double *q;
		register unsigned int c,i,n;
		double x;

		//c = order*order;	// but the # of elements in the matrix in c.
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
		}											//times to compute hilb(5000):
		while(--c)									//with Microsoft C++ compiler (Native):
		{											//Debug: 422ms	Release: 344ms	Optimized: 281ms
			*(q = p += order) = x = 1.0/i;
			++i;									//with Microsoft C++ compiler (Managed):
			n = c;									//Debug: 390ms or 375	Release: 329ms	Optimized: 328ms
			while(--n)
			{										//with gcc 390ms 390 or 375 optimized
				*(q += order-1) = x;
			}
		}

	} // end fuction hilb
}; // end class Test

using namespace System;

int main(array<System::String ^> ^args)
{
	clock_t outTime , inTime;
	ofstream outFile("c:/stats.txt");	// variables required for measuring and storing the results.

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