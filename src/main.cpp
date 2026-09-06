#include <print>
#include <string>
#include <vector>

int main() {
    std::vector<std::string> langs{"C", "C++", "Rust"};

    for (const auto& lang : langs) {
        std::println("Hello from {}!", lang);
    }

    return 0;
}
