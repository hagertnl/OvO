#include <iostream>
#include <cstdlib>
bool almost_equal(float x, float gold, float tol) {
        return gold * (1-tol) <= x && x <= gold * (1 + tol);
}
void test_target_parallel__for__simd(){
 const int L = 4096;
 const int M = 64;
 float counter{};
#pragma omp target parallel   map(tofrom:counter) 
    {
#pragma omp for  
    for (int i = 0 ; i < L ; i++ )
    {
float partial_counter{};
#pragma omp simd reduction(+: partial_counter)
    for (int j = 0 ; j < M ; j++ )
    {
partial_counter += float { 1.0f };
   } 
#pragma omp atomic update
counter += partial_counter;
   } 
   } 
if ( !almost_equal(counter,float { L*M }, 0.1)  ) {
    std::cerr << "Expected: " << L*M << " Got: " << counter << std::endl;
    std::exit(112);
}
}
int main()
{
    test_target_parallel__for__simd();
}