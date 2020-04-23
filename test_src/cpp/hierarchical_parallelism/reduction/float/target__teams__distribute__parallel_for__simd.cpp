#include <iostream>
#include <cmath>
#include <stdexcept>
bool almost_equal(float x, float gold, float tol) {
        return gold * (1-tol) <= x && x <= gold * ( 1+tol );
}
void test_target__teams__distribute__parallel_for__simd(){
 // Input and Outputs
 const int L = 5;
 const int M = 6;
 const int N = 7;
float counter{};
// Main program
#pragma omp target   map(tofrom:counter) 
{
#pragma omp teams  reduction(+: counter)  
{
#pragma omp distribute  
    for (int i = 0 ; i < L ; i++ )
{
#pragma omp parallel for  reduction(+: counter)  
    for (int j = 0 ; j < M ; j++ )
{
#pragma omp simd  reduction(+: counter)  
    for (int k = 0 ; k < N ; k++ )
{
counter += float { 1.0f };
    }
    }
    }
    }
    }
// Validation
if ( !almost_equal(counter,float { L*M*N }, 0.1)  ) {
    std::cerr << "Expected: " << L*M*N << " Got: " << counter << std::endl;
    throw std::runtime_error( "target__teams__distribute__parallel_for__simd give incorect value when offloaded");
}
}
int main()
{
    test_target__teams__distribute__parallel_for__simd();
}