#include "dft.hxx"

#include <algorithm>
#include <iterator>
#include <iostream>

#include <cassert>
#include <cmath>

using namespace std;

static complex<double> _1j(0.0, 1.0);

vector<complex<double>> dft_real(vector<double> const & source_signal, size_t count)
{
    if (!count)
        count = source_signal.size();
    auto n = (count / 2) + 1;
    auto o = 1 - count % 2;

    vector<complex<double>> complex_signal(n);
    transform(begin(source_signal), begin(source_signal) + n, begin(complex_signal), [](double value){
        return complex<double>(value, 0.0);
    });

    auto transformed = dft(complex_signal);
    for (auto k = n; k < count; ++k)
        transformed.push_back(conj(transformed[2 * n - k - o - 1]));

    return transformed;
}

vector<complex<double>> dft(vector<double> const & source_signal, size_t count)
{
    auto transformed = dft_real(source_signal, count);
    double length = transformed.size();
    assert(length != 0.0);
    
    /*transform(begin(transformed), end(transformed), begin(transformed), [length](complex<double> const & value){
        return value / length;
    });*/

    return transformed;
}

vector<complex<double>> dft(vector<complex<double>> const & source_signal, size_t count)
{
    if (count == 0)
        count = source_signal.size();

    vector<complex<double>> transformed(count);
    for (size_t k = 0; k < count; ++k)
    {
        unsigned j = 0;
        for (auto const & aj : source_signal)
            transformed[k] += exp(-2 * M_PI * _1j * static_cast<double>(j++) * static_cast<double>(k) * 1.0 / static_cast<double>(source_signal.size())) * aj;
    }

    return transformed;
}

vector<complex<double>> fft(vector<double> const & source_signal)
{
    if (source_signal.size() % 2)
        return dft(source_signal);

    auto half_count = source_signal.size() / 2;
    vector<double> halfs[2];
    halfs[0].resize(half_count);
    halfs[1].resize(half_count);

    for (auto sample = source_signal.size(); sample--;)
        halfs[sample % 2][sample / 2] = source_signal[sample];

    auto even = fft(halfs[0]);
    auto odd  = fft(halfs[1]);

    auto freqfac = -M_PI * _1j / static_cast<double>(half_count);

    vector<complex<double>> transformed(source_signal.size());
    for (auto k = source_signal.size(); k--;)
    {
        if (k < half_count)
            transformed[k] = even[k] + exp(freqfac * static_cast<double>(k)) * odd[k];
        else
            transformed[k] = even[k - half_count] - exp(freqfac * static_cast<double>(k - half_count)) * odd[k - half_count];
    }

    /*transform(begin(transformed), end(transformed), begin(transformed), [&source_signal](complex<double> const & val){
        return val / static_cast<double>(source_signal.size());
    });*/
    
    // simplify
    vector<double> result(transformed.size() / 2);
    transform(begin(transformed), begin(transformed) + result.size(), begin(result), [](std::complex<double> const & val){
        return abs(val);
    });

    return transformed;
}

vector<complex<double>> fft(vector<complex<double>> const & source_signal)
{
    if (source_signal.size() % 2)
        return dft(source_signal);

    auto half_count = source_signal.size() / 2;
    vector<complex<double>> halfs[2];
    halfs[0].resize(half_count);
    halfs[1].resize(half_count);

    for (auto sample = source_signal.size(); sample--;)
        halfs[sample % 2][sample / 2] = source_signal[sample];

    auto even = fft(halfs[0]);
    auto odd  = fft(halfs[1]);

    auto freqfac = -M_PI * _1j / static_cast<double>(half_count);

    vector<complex<double>> transformed(source_signal.size());
    for (auto k = source_signal.size(); k--;)
    {
        if (k < half_count)
            transformed[k] = even[k] + exp(freqfac * static_cast<double>(k)) * odd[k];
        else
            transformed[k] = even[k - half_count] - exp(freqfac * static_cast<double>(k - half_count)) * odd[k - half_count];
    }

    /*transform(begin(transformed), end(transformed), begin(transformed), [&source_signal](complex<double> const & val){
        return val / static_cast<double>(source_signal.size());
    });*/

    return transformed;
}
