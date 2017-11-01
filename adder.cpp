#include <iostream>
#define SC_INCLUDE_FX
#include <systemc.h>
using namespace std;

/*
	Simple combinational adder (Sensitive to all input ports)
	
*/
SC_MODULE(adder)          // module (class) declaration
{
	sc_in<int> a, b;        // ports
	sc_out<int> sum;

	void do_add()           // process
	{
		sum.write(a.read() + b.read()); //or just sum = a + b
	}

	SC_CTOR(adder)          // constructor
	{
		SC_METHOD(do_add);    // register do_add to kernel
		sensitive << a << b;  // sensitivity list of do_add
	}
};

// Some references
// http://web.itu.edu.tr/~orssi/dersler/SLD/systemc1.pdf
// http://jameszhou2000.blogspot.co.uk/2013/12/example-code-to-use-system-c-for-fixed.html
// http://www.ti.uni-tuebingen.de/uploads/media/Presentation-5-UP1_vanderperren.pdf
void fixed_point(){
	float a = 1/3.0;  
	float b = 1/7.0;  
	float float_out;  
	sc_fixed <32, 4, SC_RND, SC_SAT> fixed_out0; // 32 bit, 4 bit integer, 28 fract  
	sc_fixed <16, 4, SC_RND, SC_SAT> fixed_out1; // 16 bit, 4 bit int, 12 bit fract  
	sc_fixed <8, 4, SC_RND, SC_SAT> fixed_out2; // 8 bit, 4 bit int; (Saturation)
	sc_fixed <8, 4, SC_RND, SC_WRAP> fixed_out3; // 8 bit, 4 bit int;(Wrap)
	printf(" fixed point example\n");  
	cout << " Hello world\n";  
	float_out = a + b;  
	fixed_out0 = a + b;  
	fixed_out1 = a + b;  
	fixed_out2 = a + b;  
	cout << " float_out is " << float_out << endl;  
	cout << " fixed_out0 is " << fixed_out0 << endl;  
	cout << " fixed_out1 is " << fixed_out1 << endl;  
	cout << " fixed_out2 is " << fixed_out2 << endl;
	fixed_out3 = fixed_out2;
	fixed_out2 += 30;
	fixed_out3 += 30;   
	cout << " fixed_out2(saturation) is " << fixed_out2 << endl;
	cout << " fixed_out3(Wrap) is " << fixed_out3 << endl;
	fixed_out2 -= 10000.0f;
	cout << " fixed_out2(saturation(neg)) is " << fixed_out2 << endl;    
	fixed_out2 += 100000.0f;
	cout << " fixed_out2(saturation(pos)) is " << fixed_out2 << endl;    
}

int sc_main(int argc, char* argv[]){
	sc_uint<16> a = 65535;
	sc_uint<16> b = 1;
	sc_uint<16> c = a+b;
	sc_uint<16> d = a+(b*10);

	// Some tests with unsigned int (16-bits)
	cout << "c=a(65535)+b(1)=" << c << endl;
	cout << "d=a+(b*1000)=" << d << endl;
	cout << "a+(b*1000)=" << a+(b*1000) << endl;

	// Some tests with Fixed-point
	fixed_point();  

	return 0;
}
