#include <complex>
#include <cmath>
#include <limits>
#include <iostream>
#include <stdexcept>
#
using namespace std;
bool almost_equal(complex<long double> x, complex<long double> y, int ulp) {
    return std::abs(x-y) <= std::numeric_limits<long double>::epsilon() * std::abs(x+y) * ulp ||  std::abs(x-y) < std::numeric_limits<long double>::min();
}
void test_log10(){
   complex<long double> in0 {  0.42, 0.0 };
   complex<long double> out1_host;
   complex<long double> out1_device;
    out1_host =  log10( in0);
   #pragma omp target map(from: out1_device )
   {
     out1_device =  log10( in0);
   }
   if ( !almost_equal(out1_host,out1_device,4) ) {
        std::cerr << "Host: " << out1_host << " GPU: " << out1_device << std::endl;
        throw std::runtime_error( "log10 give incorect value when offloaded");
    }
}
int main()
{
    test_log10();
}