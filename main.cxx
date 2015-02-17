#include <algorithm>
#include <iostream>
#include <iterator>

#include <cmath>

#include "dft.hxx"
#include "signals.hxx"

int main()
{
    sinus_signal_generator sin1(10u, 200.0);
    sinus_signal_generator sin2(100u, 100.0);
    sinus_signal_generator sin3(300u, 80.0);
    
    adding_signal_generator combined;
    combined.add_signal(&sin1);
    combined.add_signal(&sin2);
    combined.add_signal(&sin3);
    
    std::vector<double> combined_signal(8192);
    combined.values(8192, combined_signal);
    
    auto transformed = fft(combined_signal);
    
    std::vector<double> result(combined_signal.size() / 2);
    std::transform(std::begin(transformed), std::begin(transformed) + result.size(), std::begin(result), [&result](std::complex<double> const & val){
        return std::abs(val) / static_cast<double>(result.size());
    });
    
    std::vector<double> sin1_signal(8192);
    sin1.values(8192, sin1_signal);
    std::vector<double> sin2_signal(8192);
    sin2.values(8192, sin2_signal);
    std::vector<double> sin3_signal(8192);
    sin3.values(8192, sin3_signal);
    
    for (unsigned k = 0; k < 8192; ++k)
        std::cout << k << " " << sin1_signal[k] << " " << sin2_signal[k] << " " << sin3_signal[k] << " " << combined_signal[k] << "\n";
    
    return 0;
}
