
#include <cmath>

#include <limits>
#include <iostream>
#include <stdexcept>

using namespace std;

 
bool almost_equal(long double x, long double y, int ulp) {

     return std::fabs(x-y) <= std::numeric_limits<long double>::epsilon() * std::fabs(x+y) * ulp ||  std::fabs(x-y) < std::numeric_limits<long double>::min();

}


void test_fabs(){
   
   long double in0 {  0.42 };
   

   
   long double out1_host ;
   long double out1_gpu ;
   

   out1_host = fabs( in0, &out1_host);

   #pragma omp target map(from: out1_gpu )
   {
   out1_gpu = fabs( in0, &out1_gpu);
   }

   
   if ( !almost_equal(out1_host,out1_gpu,1) ) {
        std::cerr << "Host: " << out1_host << " GPU: " << out1_gpu << std::endl;
        throw std::runtime_error( "fabs give incorect value when offloaded");
    }
    
}

int main()
{
    test_fabs();
}
