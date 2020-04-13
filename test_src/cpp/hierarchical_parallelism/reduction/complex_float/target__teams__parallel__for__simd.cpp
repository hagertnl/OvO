#include <iostream>
#include <limits>


#include <complex>
using namespace std;



#ifdef _OPENMP
#include <omp.h>
#else
int omp_get_num_teams() {return 1;}
int omp_get_num_threads() {return 1;}
#endif


bool almost_equal(complex<float> x, complex<float> y, int ulp) {

    bool r = std::fabs(x.real()-y.real()) <= std::numeric_limits<float>::epsilon() * std::fabs(x.real()+y.real()) * ulp ||  std::fabs(x.real()-y.real()) < std::numeric_limits<float>::min();
    bool i = std::fabs(x.imag()-y.imag()) <= std::numeric_limits<float>::epsilon() * std::fabs(x.imag()+y.imag()) * ulp ||  std::fabs(x.imag()-y.imag()) < std::numeric_limits<float>::min();
    return r && i;

}


#pragma omp declare reduction(ComplexReduction: complex<float>:   omp_out += omp_in) 


void test_target__teams__parallel__for__simd(){

 // Input and Outputs
 
 const int L = 5;
 const int M = 6;

complex<float> counter{};

// Main program

#pragma omp target   map(tofrom:counter) 

{


#pragma omp teams  reduction(  ComplexReduction  :counter)  

{

const int num_teams = omp_get_num_teams();


#pragma omp parallel  reduction(  ComplexReduction  :counter)  

{


#pragma omp for  

    for (int i = 0 ; i < L ; i++ )

{


#pragma omp simd  reduction(  ComplexReduction  :counter)  

    for (int j = 0 ; j < M ; j++ )

{




counter += complex<float> { 1.0f/num_teams } ;



}

}

}

}

}


// Validation
if ( !almost_equal(counter,complex<float> { L*M }, 10)  ) {
    std::cerr << "Expected: " << L*M << " Got: " << counter << std::endl;
    throw std::runtime_error( "target__teams__parallel__for__simd give incorect value when offloaded");
}

}
int main()
{
    test_target__teams__parallel__for__simd();
}