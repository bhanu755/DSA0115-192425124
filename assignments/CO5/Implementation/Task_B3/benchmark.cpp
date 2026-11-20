#include "benchmark.h"

#include <chrono>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <type_traits>
#include <vector>

bool validateReturnCode(double amount) {
    return amount >= 0.0;
}

void validateException(double amount) {
    if (amount < 0.0) {
        throw std::invalid_argument("invalid bill");
    }
}

int main() {
    constexpr std::size_t count = 1000000;
    const int invalidRates[] = {0, 1, 50};

    for (int percent : invalidRates) {
        std::vector<double> amounts(count);
        for (std::size_t i = 0; i < count; ++i) {
            const int indexPercent =
                static_cast<int>((i * 100) / count);
            amounts[i] = indexPercent < percent ? -1.0 : 100.0;
        }

        const auto returnStart = std::chrono::steady_clock::now();
        std::size_t returnErrors = 0;
        for (double amount : amounts) {
            if (!validateReturnCode(amount)) {
                ++returnErrors;
            }
        }
        const auto returnEnd = std::chrono::steady_clock::now();

        const auto exceptionStart = std::chrono::steady_clock::now();
        std::size_t exceptionErrors = 0;
        for (double amount : amounts) {
            try {
                validateException(amount);
            } catch (const std::invalid_argument&) {
                ++exceptionErrors;
            }
        }
        const auto exceptionEnd = std::chrono::steady_clock::now();

        const double returnMilliseconds =
            std::chrono::duration<double, std::milli>(
                returnEnd - returnStart).count();
        const double exceptionMilliseconds =
            std::chrono::duration<double, std::milli>(
                exceptionEnd - exceptionStart).count();

        std::cout << "Error rate: " << percent << "%\n";
        std::cout << "Return-code time: " << returnMilliseconds << " ms\n";
        std::cout << "Exception time: " << exceptionMilliseconds << " ms\n";
        std::cout << "Measured errors: " << returnErrors
                  << " / " << exceptionErrors << '\n';
    }
}
