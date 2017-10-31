# Learning SystemC
Learn basics of [SystemC](http://www.accellera.org/downloads/standards/systemc)

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
## Compiling (by hand)
```bash
g++ adder.cpp -I/home/laraujo/systemc-2.3.2/include -L/home/laraujo/systemc-2.3.2/lib-linux64 -lsystemc
```
We're adding cmake scrips to make life easier

### SystemC Tutorials and References
* [Wikipedia](https://en.wikipedia.org/wiki/SystemC)
* [Tutorial](http://www.es.ele.tue.nl/~heco/courses/ProcDesign/systemc_1_tutorial.pdf)
* [Doulos SystemC tutorial](https://www.doulos.com/knowhow/systemc/tutorial/)
* [Asic World tutorial](http://www.asic-world.com/systemc/tutorial.html)
* [Getting Started](http://www.electrobucket.com/systemc/getting-started-with-systemc)
* [Video tutorials](https://www.youtube.com/watch?v=NCFxBGLB5xs)

### Some other references
* [Cmake](https://mirkokiefer.com/cmake-by-example-f95eb47d45b1)
* [Using Cmake libraries](https://coderwall.com/p/y3zzbq/use-cmake-enabled-libraries-in-your-cmake-project)
* [Cmake third party libraries](https://www.selectiveintellect.net/blog/2016/7/29/using-cmake-to-add-third-party-libraries-to-your-project-1)
