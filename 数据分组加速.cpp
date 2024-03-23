#include <array>
#include <cstddef>
#include <iostream>
#include <stdint.h>
#include <vector>

template <std::size_t mod>
void mod_func(std::vector<int> &v) {
    if constexpr (mod == 0) {
        return;
    }
    for (auto &x : v) {
        x = x % mod;
    }
}

template <typename>
struct ModFunc;

template <std::size_t... idxs>
struct ModFunc<std::index_sequence<idxs...>> {
    static void impl(std::vector<int> &v, std::size_t mod) {
        if (mod < func_map.size()) {
            func_map[mod](v);
        } else {
            for (auto &x : v) {
                x = x % mod;
            }
        }
    }

    constexpr static std::array func_map = {mod_func<idxs>...};
};

template <std::size_t size>
using Mod = ModFunc<std::make_index_sequence<size>>;

int main() {
    {
        std::vector v{1, 2, 3, 4};
        Mod<5>::impl(v, 2);
        for (auto x : v) std::cout << x << " ";
        std::cout << "\n";
    }

    {
        std::vector v{1, 2, 3, 4};
        Mod<5>::impl(v, 3);
        for (auto x : v) std::cout << x << " ";
        std::cout << "\n";
    }
}
///此外有一个小trick，在hash函数是int32_t时候，https://lemire.me/blog/2016/06/27/a-fast-alternative-to-the-modulo-reduction/
