
#include <cmath>

#include <limits>
#include <iostream>
#include <stdexcept>

using namespace std;

 
bool almost_equal(float x, float y, int ulp) {

     return std::fabs(x-y) <= std::numeric_limits<float>::epsilon() * std::fabs(x+y) * ulp ||  std::fabs(x-y) < std::numeric_limits<float>::min();

}


void test_hypot(){
   
   float in0 {  0.42 };
   
   float in1 {  0.42 };
   

   
   float out2_host ;
   float out2_gpu ;
   

   out2_host = hypot( in0, in1, &out2_host);

   #pragma omp target map(from: out2_gpu )
   {
   out2_gpu = hypot( in0, in1, &out2_gpu);
   }

   
   if ( !almost_equal(out2_host,out2_gpu,1) ) {
        std::cerr << "Host: " << out2_host << " GPU: " << out2_gpu << std::endl;
        throw std::runtime_error( "hypot give incorect value when offloaded");
    }
    
}

int main()
{
    test_hypot();
}
