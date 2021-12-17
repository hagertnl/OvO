#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <complex>
using std::complex;
#ifdef _OPENMP
#include <omp.h>
#else
int omp_get_num_teams() {return 1;}
void omp_set_num_teams(int _) { (void)_;}
int omp_get_num_threads() {return 1;}
#endif
bool almost_equal(complex<double> x, complex<double> gold, double rel_tol=1e-09, double abs_tol=0.0) {
  return std::abs(x-gold) <= std::max(rel_tol * std::max(std::abs(x), std::abs(gold)), abs_tol);
}
#pragma omp declare reduction(+: complex<double>: omp_out += omp_in)
void test_target_teams__parallel() {
  const complex<double> expected_value { 1 };
  omp_set_num_teams(182);
  complex<double> counter_teams{};
  #pragma omp target teams reduction(+: counter_teams)
  {
    #pragma omp parallel num_threads(182) reduction(+: counter_teams)
    {
      counter_teams = counter_teams + complex<double> { double { 1. } / ( omp_get_num_teams() * omp_get_num_threads() ) };
    }
  }
  if (!almost_equal(counter_teams, expected_value, 0.01)) {
    std::cerr << "Expected: " << expected_value << " Got: " << counter_teams << std::endl;
    std::exit(112);
  }
}
int main()
{
    test_target_teams__parallel();
}
