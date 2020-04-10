#include <iostream>
#include <stdexcept>




#include <cmath>
#include <limits>



bool almost_equal(float x, float y, int ulp) {

     return std::fabs(x-y) <= std::numeric_limits<float>::epsilon() * std::fabs(x+y) * ulp ||  std::fabs(x-y) < std::numeric_limits<float>::min();

}

void test_target_teams__distribute(){

 // Input and Outputs
 
 const int L = 5;

float counter{};

// Main program

#pragma omp target teams  map(tofrom:counter) 

{


#pragma omp distribute 

    for (int i = 0 ; i < L ; i++ )

{



#pragma omp atomic update

counter += float { 1 };



}

}


// Validation
if ( !almost_equal(counter,float { L }, 10)  ) {
    std::cerr << "Expected: " << L << " Get: " << counter << std::endl;
    throw std::runtime_error( "target_teams__distribute give incorect value when offloaded");
}

}
int main()
{
    test_target_teams__distribute();
}