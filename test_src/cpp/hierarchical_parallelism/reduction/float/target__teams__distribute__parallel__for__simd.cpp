#include <iostream>
#include <cstdlib>
bool almost_equal(float x, float gold, float tol) {
        return gold * (1-tol) <= x && x <= gold * (1 + tol);
}
void test_target__teams__distribute__parallel__for__simd(){
 const int L = 64;
 const int M = 64;
 const int N = 64;
 float counter{};
#pragma omp target   map(tofrom:counter) 
{
#pragma omp teams  reduction(+: counter)  
{
#pragma omp distribute  
    for (int i = 0 ; i < L ; i++ )
{
#pragma omp parallel  reduction(+: counter)  
{
#pragma omp for  
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
    }
if ( !almost_equal(counter,float { L*M*N }, 0.1)  ) {
    std::cerr << "Expected: " << L*M*N << " Got: " << counter << std::endl;
    std::exit(112);
}
}
int main()
{
    test_target__teams__distribute__parallel__for__simd();
}