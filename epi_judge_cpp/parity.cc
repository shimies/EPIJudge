#include "test_framework/generic_test.h"

static short impl_naive(unsigned long long);
static short impl_clear_lowest_set_bit(unsigned long long);
static short impl_reduced(unsigned long long);

class ParityCache {
    const std::unique_ptr<short[]> table_;
public:
    ParityCache(int bits) : ParityCache(1ull << bits) { }
    short operator[](int index) const {
        return table_[index];
    }
private:
    ParityCache(unsigned long long npatterns) : table_(new short[npatterns]) {
        for (unsigned long long i = 0; i < npatterns; ++i) {
            table_[i] = ::impl_clear_lowest_set_bit(i);
        }
    }
};

static short impl_naive(unsigned long long x) {
    short result = 0;
    while (x) {
        result ^= (x & 1);
        x >>= 1;
    }
    return result;
}

static short impl_clear_lowest_set_bit(unsigned long long x) {
    short result = 0;
    while (x) {
        result ^= 1;
        x &= x - 1;
    }
    return result;
}

static short impl_cached(unsigned long long x) {
    static constexpr int bits = 16;
    static constexpr unsigned long long bitmask = (1ull << bits) - 1;
    static const ParityCache pc(bits);
    short result = 0;
    while (x) {
        result ^= pc[x & bitmask];
        x >>= bits;
    }
    return result;
}

static short impl_reduced(unsigned long long x) {
    x ^= x >> 32;
    x ^= x >> 16;
    x ^= x >> 8;
    x ^= x >> 4;
    x ^= x >> 2;
    x ^= x >> 1;
    return x & 0x1;
}

short Parity(unsigned long long x) {
    // return impl_cached(x);
    return impl_reduced(x);
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"x"};
    return GenericTestMain(args, "parity.cc", "parity.tsv", &Parity, DefaultComparator{}, param_names);
}
