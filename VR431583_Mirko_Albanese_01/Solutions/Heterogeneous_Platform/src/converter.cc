#include <converter.h>
#include <systemc.h>

uint64_t double_to_uint(double d)
{
    double* ptr = &d;
    uint64_t* ptr2 = (uint64_t*)ptr;
    return *ptr2;
}

double uint_to_double(uint64_t u)
{
    uint64_t* ptr = &u;
    double* ptr2 = (double*)ptr;
    return *ptr2;
}

double uints_to_double(uint32_t a, uint32_t b)
{
    uint64_t temp = static_cast<uint64_t>(a) + (static_cast<uint64_t>(b) << 32);
    return uint_to_double(temp);
}

double sc_uints_to_double(sc_uint<32> a, sc_uint<32> b)
{
    sc_uint<64> y;
    y.range(31,  0) = a;
    y.range(63, 32) = b;
    uint64_t yy = y.to_uint64();
    return uint_to_double(yy);
}
