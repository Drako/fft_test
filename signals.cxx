#include "signals.hxx"

#include <algorithm>
#include <iterator>
#include <utility>

#include <cmath>

using namespace std;

void abstract_signal_generator::values(unsigned sample_rate, vector<double> & buffer) const
{
    for (auto n = buffer.size(); n--;)
        buffer[n] = value(n * 1.0 / sample_rate);
}

sinus_signal_generator::sinus_signal_generator()
    : frequency_(1)
    , amplitude_(1.0)
{
}

sinus_signal_generator::sinus_signal_generator(unsigned int frequency, double amplitude)
    : frequency_(frequency)
    , amplitude_(amplitude)
{
}

double sinus_signal_generator::value(double t) const
{
    return amplitude_ * sin(M_PI * 2.0 * frequency_ * t);
}

combining_signal_generator::combining_signal_generator()
{
}

void combining_signal_generator::add_signal(signal_generator * generator)
{
    generators_.emplace_back(generator);
}

double combining_signal_generator::value(double t) const
{
    std::vector<double> numbers(generators_.size());
    for (auto n = generators_.size(); n--;)
        numbers[n] = generators_[n]->value(t);
    return merge(numbers);
}

adding_signal_generator::adding_signal_generator()
{
}

double adding_signal_generator::merge(vector<double> const & numbers) const
{
    return accumulate(begin(numbers), end(numbers), 0.0);
}
