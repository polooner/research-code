#include <cmath>
#include <complex>
#include <iostream>
#include <vector>

// Define pi for portability
const double PI = 3.14159265358979323846;

// Calculate the 1D DFT of a sequence of complex numbers
std::vector<std::complex<double>>
calculateDFT(const std::vector<std::complex<double>> &input) {
  int N = input.size();
  std::vector<std::complex<double>> output(N);

  for (int k = 0; k < N; ++k) {
    std::complex<double> sum(0.0, 0.0);
    for (int n = 0; n < N; ++n) {
      double angle = -2 * PI * k * n / N;
      // the Twiddle factor
      std::complex<double> w(cos(angle), sin(angle));
      sum += input[n] * w;
    }
    output[k] = sum;
  }

  return output;
}

int main() {
  // Example input (as complex numbers, with imaginary parts being zero)
  std::vector<std::complex<double>> input = {
      std::complex<double>(1.0, 0.0), std::complex<double>(2.0, 0.0),
      std::complex<double>(3.0, 0.0), std::complex<double>(4.0, 0.0)};

  std::vector<std::complex<double>> output = calculateDFT(input);

  std::cout << "DFT Result:" << std::endl;
  for (const auto &value : output) {
    std::cout << "(" << value.real() << ", " << value.imag() << ")"
              << std::endl;
  }

  return 0;
}
