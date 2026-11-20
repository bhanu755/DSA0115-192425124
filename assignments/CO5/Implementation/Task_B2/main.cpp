#include "exceptions.h"

#include <iostream>
#include <stdexcept>

void validate(double amount) {
    if (amount < 0.0) {
        throw std::invalid_argument("negative");
    }
    if (amount > 1000000.0) {
        throw std::out_of_range("too large");
    }
    std::cout << "ok ";
}

void process(double amount) {
    try {
        validate(amount);
        std::cout << "done ";
    } catch (const std::out_of_range&) {
        std::cout << "[log too large] ";
        throw;
    }
}

double approve(double billed, double cover) {
    if (billed < 0.0 || cover < 0.0) {
        throw std::invalid_argument("negative amount");
    }
    if (billed > cover) {
        throw ClaimError("exceeds cover");
    }
    return billed;
}

double settle(double billed, double cover) {
    try {
        return approve(billed, cover);
    } catch (const ClaimError& error) {
        std::cout << "audit: " << error.what() << '\n';
        throw;
    }
}

int main() {
    process(100.0);

    try {
        process(-5.0);
    } catch (const std::invalid_argument& error) {
        std::cout << "caught " << error.what() << ' ';
    }

    try {
        process(2000000.0);
    } catch (const std::out_of_range& error) {
        std::cout << "caught " << error.what() << '\n';
    }

    try {
        std::cout << "approved " << approve(40000.0, 50000.0) << '\n';
    } catch (const std::exception& error) {
        std::cout << "claim rejected: " << error.what() << '\n';
    }

    try {
        settle(60000.0, 50000.0);
    } catch (const ClaimError& error) {
        std::cout << "claim rejected: " << error.what() << '\n';
    }

    try {
        approve(-100.0, 50000.0);
    } catch (const std::invalid_argument& error) {
        std::cout << "error: " << error.what() << '\n';
    }
}
