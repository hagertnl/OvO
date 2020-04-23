#include <iostream>
#include <cmath>
#include <stdexcept>
#ifdef _OPENMP
#include <omp.h>
#else
int omp_get_num_teams() {return 1;}
int omp_get_num_threads() {return 1;}
#endif
bool almost_equal(double x, double gold, float tol) {
        return gold * (1-tol) <= x && x <= gold * ( 1+tol );
}
void test_target_teams__parallel_loop(){
 // Input and Outputs
 const int L = 5;
double counter{};
// Main program
#pragma omp target teams  reduction(+: counter)   map(tofrom:counter) 
{
const int num_teams = omp_get_num_teams();
#pragma omp parallel loop  reduction(+: counter)  
    for (int i = 0 ; i < L ; i++ )
{
counter += double { 1.0f/num_teams } ;
    }
    }
// Validation
if ( !almost_equal(counter,double { L }, 0.1)  ) {
    std::cerr << "Expected: " << L << " Got: " << counter << std::endl;
    throw std::runtime_error( "target_teams__parallel_loop give incorect value when offloaded");
}
}
int main()
{
    test_target_teams__parallel_loop();
}