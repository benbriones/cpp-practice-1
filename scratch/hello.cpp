#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> nums{5, 3, 9, 1, 7};
    std::ranges::sort(nums);

    for (int n : nums) {
        std::cout << n << ' ';
    }
    std::cout << '\n';
}
