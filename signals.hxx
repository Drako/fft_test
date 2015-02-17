#ifndef SIGNALS_HXX
#define SIGNALS_HXX

#include <vector>

struct signal_generator
{
    virtual ~signal_generator() {}
    virtual double value(double t) const = 0;
    virtual void values(unsigned sample_rate, std::vector<double> & buffer) const = 0;
};

struct abstract_signal_generator
    : public signal_generator
{
    virtual ~abstract_signal_generator() {}
    virtual void values(unsigned sample_rate, std::vector<double> & buffer) const;
};

class sinus_signal_generator
    : public abstract_signal_generator
{
public:
    sinus_signal_generator();
    sinus_signal_generator(unsigned frequency, double amplitude);
    virtual ~sinus_signal_generator() {}
    
    virtual double value(double t) const;
    
protected:
    unsigned frequency_;
    double amplitude_;
};

class combining_signal_generator
    : public abstract_signal_generator
{
public:
    combining_signal_generator();
    virtual ~combining_signal_generator() {}
    
    void add_signal(signal_generator * generator);
    
    virtual double value(double t) const;
    virtual double merge(std::vector<double> const & numbers) const = 0;
    
private:
    std::vector<signal_generator *> generators_;
};

class adding_signal_generator
    : public combining_signal_generator
{
public:
    adding_signal_generator();
    virtual ~adding_signal_generator() {}
    
    virtual double merge(std::vector<double> const & numbers) const;
};

#endif // SIGNALS_HXX
