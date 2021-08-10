#include "test_framework/generic_test.h"

static long long impl_naive(int x) {
    auto str = std::to_string(x);
    auto s = str.begin();
    auto e = str.end() - 1;
    if (*s == '-')
        ++s;
    while (s < e) {
        std::swap(*s, *e);
        ++s, --e;
    }
    return std::stoll(str);
}

static long long impl_improved(int x) {
    long long y = 0;
    while (x) {
        y = y * 10 + x % 10;
        x /= 10;
    }
    return y;
}

long long Reverse(int x) {
    // return impl_naive(x);
    return impl_improved(x);
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"x"};
    return GenericTestMain(args, "reverse_digits.cc", "reverse_digits.tsv", &Reverse, DefaultComparator{}, param_names);
}
