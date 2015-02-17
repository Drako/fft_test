#ifndef DFT_HXX
#define DFT_HXX

#include <complex>
#include <vector>

static std::size_t const DFT_ALL = 0;
std::vector<std::complex<double>> dft(std::vector<double> const & source_signal, std::size_t count = DFT_ALL);
std::vector<std::complex<double>> dft(std::vector<std::complex<double>> const & source_signal, std::size_t count = DFT_ALL);
std::vector<std::complex<double>> fft(std::vector<double> const & source_signal);
std::vector<std::complex<double>> fft(std::vector<std::complex<double>> const & source_signal);

#endif // DFT_HXX
