#include "test_framework/generic_test.h"

static bool impl(int x) {
    if (x <= 0)
        return x == 0;
    const unsigned int ndigits = std::floor(std::log10(x)) + 1;
    int div = std::pow(10, ndigits - 1);
    while (div > 1) {
        int lsd = x % 10;
        int msd = x / div;
        if (lsd != msd)
            return false;
        x = x % div / 10;
        div = div / 100;
    }
    return true;
}

bool IsPalindromeNumber(int x) {
    return impl(x);
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"x"};
    return GenericTestMain(args, "is_number_palindromic.cc", "is_number_palindromic.tsv", &IsPalindromeNumber, DefaultComparator{}, param_names);
}
