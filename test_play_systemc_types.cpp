#include <iostream>
#include <gtest/gtest.h>
#define SC_INCLUDE_FX
#include <systemc.h>

TEST(AdditionTest,twoValues){

	sc_uint<16> a = 65535;
	sc_uint<16> b = 1;
	sc_uint<16> c = a+b;
	sc_uint<16> d = a+(b*10);

	// Some tests with unsigned int (16-bits)
	cout << "c=a(65535)+b(1)=" << c << endl;
	cout << "d=a+(b*1000)=" << d << endl;
	cout << "a+(b*1000)=" << a+(b*1000) << endl;

	EXPECT_EQ(0,c);
	EXPECT_EQ(9,d);
	EXPECT_EQ(66535,a+(b*1000));
}

int sc_main(int argc, char* argv[]){
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
