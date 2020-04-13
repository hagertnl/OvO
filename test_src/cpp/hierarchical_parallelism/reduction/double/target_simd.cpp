#include <iostream>
#include <limits>





bool almost_equal(double x, double y, int ulp) {

     return std::fabs(x-y) <= std::numeric_limits<double>::epsilon() * std::fabs(x+y) * ulp ||  std::fabs(x-y) < std::numeric_limits<double>::min();

}



void test_target_simd(){

 // Input and Outputs
 
 const int L = 5;

double counter{};

// Main program

#pragma omp target simd  reduction(  +  :counter)   map(tofrom:counter) 

    for (int i = 0 ; i < L ; i++ )

{




counter += double { 1.0f };



}


// Validation
if ( !almost_equal(counter,double { L }, 10)  ) {
    std::cerr << "Expected: " << L << " Got: " << counter << std::endl;
    throw std::runtime_error( "target_simd give incorect value when offloaded");
}

}
int main()
{
    test_target_simd();
}