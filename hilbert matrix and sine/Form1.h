#pragma once

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

		//c = order*order;	// put the # of elements in the matrix in c.
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

namespace HilbertMatrixAndSine {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->SuspendLayout();
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(292, 273);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
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
			 }
	};
}

