# Learning SystemC
Learn basics of [SystemC](http://www.accellera.org/downloads/standards/systemc)

### SystemC Tutorials and References
* [Wikipedia](https://en.wikipedia.org/wiki/SystemC)
* [Tutorial](http://www.es.ele.tue.nl/~heco/courses/ProcDesign/systemc_1_tutorial.pdf)
* [Doulos SystemC tutorial](https://www.doulos.com/knowhow/systemc/tutorial/)
* [Counter with Testbench](http://www.asic-world.com/systemc/first1.html)
* [Asic World tutorial](http://www.asic-world.com/systemc/tutorial.html)
* [Getting Started](http://www.electrobucket.com/systemc/getting-started-with-systemc)
* [Video tutorials](https://www.youtube.com/watch?v=NCFxBGLB5xs)
* [Portuguese presentation](http://slideplayer.com.br/slide/359173/)

### Some other references
* [Cmake](https://mirkokiefer.com/cmake-by-example-f95eb47d45b1)
* [Using Cmake libraries](https://coderwall.com/p/y3zzbq/use-cmake-enabled-libraries-in-your-cmake-project)
* [Cmake third party libraries](https://www.selectiveintellect.net/blog/2016/7/29/using-cmake-to-add-third-party-libraries-to-your-project-1)
* [Typical Linux CMake](http://kaizou.org/2014/11/typical-cmake-project/)
* [Google Test I](http://www.yolinux.com/TUTORIALS/Cpp-GoogleTest.html)
* [Google Test II](https://www.eriksmistad.no/getting-started-with-google-test-on-ubuntu/)
* [Installing Jenkins](https://www.digitalocean.com/community/tutorials/how-to-install-jenkins-on-ubuntu-16-04)
* [Jenkins long video tutorial](https://www.youtube.com/watch?v=Lxd6JMMxuwo)
* [Another Jenkins Tutorial](http://www.vogella.com/tutorials/Jenkins/article.html)
* [Building C++ Tensorflow API](https://github.com/cjweeks/tensorflow-cmake)
* [Catch framework and Jenkins](https://github.com/philsquared/Catch/blob/e0aaba6cf84c2e932c9a87dd26263875628c4c4f/docs/reporters.md)
* [CMake, Google test and Jenkins](https://schneide.wordpress.com/2014/01/27/integrating-googletest-in-cmake-projects-and-jenkins/)
* [Jenkins start after github commit](https://www.youtube.com/watch?v=Z3S2gMBUkBo)

## First things
* It's not a language it's a C++ library
* Attempt to make HW/SW/Algo engineers to use the same language (C++)
* Not supported by much FPGA vendors

## Hello World
```C++
// All systemc modules should include systemc.h header file
#include "systemc.h"
// Hello_world is module name
SC_MODULE (hello_world) {
  SC_CTOR (hello_world) {
    // Nothing in constructor 
  }
  void say_hello() {
    //Print "Hello World" to the console.
    cout << "Hello World.\n";
  }
};

// sc_main in top level function like in C++ main
int sc_main(int argc, char* argv[]) {
  hello_world hello("HELLO");
  // Print the hello world
  hello.say_hello();
  return(0);
}
```

## Combinational Circuit
```C++
#include "systemc.h"
SC_MODULE (half_add) {
  // Input and Output ports
  sc_out<sc_logic> s,c;
  sc_in<sc_logic> a,b;
  
  // Pure C++ coder here (For synthesis depends on HLS power...)
  void compute(){
    s = a ^ b; // a XOR b
    c = a & b; // a AND b
  }
  
  SC_CTOR (half_add) {
    // Kind of always_comb block (Sensitive to a and b)
    SC_METHOD(compute);
    sensitive << a << b;
  }  
};
```

## Compiling (by hand)
```bash
g++ adder.cpp -I/systemc-2.3.2/include -L/systemc-2.3.2/lib-linux64 -lsystemc -o adder
g++ test_adder.cpp -I/systemc-2.3.2/include -L/systemc-2.3.2/lib-linux64 -lsystemc -lgtest -lgtest_main -lpthread -o test_adder 
```
## Compiling with CMake
```bash
mkdir build; cd build
cmake ..
make
```
