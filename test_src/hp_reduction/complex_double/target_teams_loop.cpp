#include <iostream>
#include <stdexcept>


#include <cmath>
#include <limits>


#include <complex>
using namespace std;


bool almost_equal(complex<double> x, complex<double> y, int ulp) {

    bool r = std::fabs(x.real()-y.real()) <= std::numeric_limits<double>::epsilon() * std::fabs(x.real()+y.real()) * ulp ||  std::fabs(x.real()-y.real()) < std::numeric_limits<double>::min();
    bool i = std::fabs(x.imag()-y.imag()) <= std::numeric_limits<double>::epsilon() * std::fabs(x.imag()+y.imag()) * ulp ||  std::fabs(x.imag()-y.imag()) < std::numeric_limits<double>::min();
    return r && i;

}


#pragma omp declare reduction(ComplexReduction: complex<double>:   omp_out += omp_in) 


void test_target_teams_loop(){

 // Input and Outputs
 
 const int L = 5;

complex<double> counter{};

// Main program

#pragma omp target teams loop  reduction(  ComplexReduction  :counter)   map(tofrom:counter) 

    for (int i = 0 ; i < L ; i++ )

{




counter += complex<double> { 1 };



}


// Validation
if ( !almost_equal(counter,complex<double> { L }, 1)  ) {
    std::cerr << "Expected: " << L << " Get: " << counter << std::endl;
    throw std::runtime_error( "target_teams_loop give incorect value when offloaded");
}

}
int main()
{
    test_target_teams_loop();
}