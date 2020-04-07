#include <cassert>
#include <iostream>
#
void test_target_teams__distribute__parallel__for__simd(){

 // Input and Outputs
 
 const int L = 5;
 const int M = 6;
 const int N = 7;

int counter = 0;

// Main program

#pragma omp target teams  reduction(+:counter)   defaultmap(tofrom:scalar) 

{

#pragma omp distribute  

    for (int i = 0 ; i < L ; i++ )

{

#pragma omp parallel  reduction(+:counter)  

{

#pragma omp for  

    for (int j = 0 ; j < M ; j++ )

{

#pragma omp simd  reduction(+:counter)  

    for (int k = 0 ; k < N ; k++ )

{


counter++;

 }  }  }  }  } 

// Validation
auto bo = ( counter == L*M*N ) ;
if ( bo != true) {
    std::cerr << "Expected: " << L*M*N << " Get: " << counter << std::endl;
    assert(bo);
}

}
int main()
{
    test_target_teams__distribute__parallel__for__simd();
}