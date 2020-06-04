#include <iostream>
#include <limits>
#include <cmath>
#include <complex>
using namespace std;
#include <vector>
#include <algorithm>
bool almost_equal(complex<double> x, complex<double> y, int ulp) {
    return std::abs(x-y) <= std::numeric_limits<double>::epsilon() * std::abs(x+y) * ulp ||  std::abs(x-y) < std::numeric_limits<double>::min();
}
void test_target_teams_distribute__simd(){
  const int N_i = 64;
  const int N_j = 64;
  const int size = N_i*N_j;
  std::vector<complex<double>> A(size);
  std::vector<complex<double>> B(size);
  std::generate(B.begin(), B.end(), std::rand);
  complex<double> *pA = A.data();
  complex<double> *pB = B.data();
#pragma omp target teams distribute   map(from: pA[0:N_i*N_j]) map(to: pB[0:N_i*N_j]) 
    for (int i = 0 ; i < N_i ; i++ )
    {
#pragma omp simd 
    for (int j = 0 ; j < N_j ; j++ )
    {
pA[ j+i*N_j ] = pB [ j+i*N_j ];
    } 
    } 
for (int i = 0 ;  i < size ; i++) {
    if ( !almost_equal(A[i],B[i],1) ) {
         std::cerr << "Expected: " << B[i] << " Got: " << A[i] << std::endl;
        std::exit(112);
    }
}
}
int main()
{
    test_target_teams_distribute__simd();
}