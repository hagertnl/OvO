#include <iostream>
#include <cmath>
#include <stdexcept>
#
bool almost_equal(float x, float gold, float tol) {
        return gold * (1-tol) <= x && x <= gold * ( 1+tol );
}
void test_target_teams_loop__parallel_loop(){
 // Input and Outputs
 const int L = 5;
 const int M = 6;
float counter{};
// Main program
#pragma omp target teams loop  map(tofrom:counter) 
    for (int i = 0 ; i < L ; i++ )
{
#pragma omp parallel loop 
    for (int j = 0 ; j < M ; j++ )
{
#pragma omp atomic update
counter += float { 1 };
    } 
    } 
// Validation
if ( !almost_equal(counter,float { L*M }, 0.1)  ) {
    std::cerr << "Expected: " << L*M << " Got: " << counter << std::endl;
    throw std::runtime_error( "target_teams_loop__parallel_loop give incorect value when offloaded");
}
}
int main()
{
    test_target_teams_loop__parallel_loop();
}