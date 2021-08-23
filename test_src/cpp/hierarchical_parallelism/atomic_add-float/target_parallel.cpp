#include <iostream>
#include <cstdlib>
#include <cmath>
#ifdef _OPENMP
#include <omp.h>
#else
int omp_get_num_threads() {return 1;}
#endif
bool almost_equal(float x, float gold, float rel_tol=1e-09, float abs_tol=0.0) {
  return std::abs(x-gold) <= std::max(rel_tol * std::max(std::abs(x), std::abs(gold)), abs_tol);
}
void test_target_parallel() {
  const float expected_value { 1 };
  float counter_parallel{};
  #pragma omp target parallel num_threads(32768) map(tofrom: counter_parallel)
  {
    #pragma omp atomic update
    counter_parallel = counter_parallel + float { float{ 1. } / omp_get_num_threads() };
  }
  if (!almost_equal(counter_parallel, expected_value, 0.01)) {
    std::cerr << "Expected: " << expected_value << " Got: " << counter_parallel << std::endl;
    std::exit(112);
  }
}
int main()
{
    test_target_parallel();
}
