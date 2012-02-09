/*				
 * file main.cpp				
 * created by Nightmare				
 * on 5 Íïå 2008				
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
