#include "exceptions.h"

#include <iostream>
#include <stdexcept>

double chargeFromPackage(const std::string& code) {
    if (code == "STANDARD") {
        return 10000.0;
    }
    if (code == "PREMIUM") {
        return 25000.0;
    }
    throw BillingError("unknown package code");
}

double parseBillAmount(const std::string& text) {
    if (text.empty()) {
        throw std::invalid_argument("invalid numeric text");
    }
    if (text[0] == '-') {
        throw std::invalid_argument("negative billing amount");
    }

    try {
        std::size_t used = 0;
        const double amount = std::stod(text, &used);
        if (used != text.size()) {
            throw std::invalid_argument("invalid numeric text");
        }
        if (amount < 0.0) {
            throw std::invalid_argument("negative billing amount");
        }
        return amount;
    } catch (const std::invalid_argument&) {
        throw std::invalid_argument("invalid numeric text");
    }
}

const std::string& findPatient(const std::string& id) {
    static const std::string knownPatient = "Ravi";
    if (id != "P001") {
        throw BillingError("missing patient record");
    }
    return knownPatient;
}

int main() {
    try {
        parseBillAmount("-100");
    } catch (const std::invalid_argument& error) {
        std::cout << "Negative billing amount: " << error.what() << '\n';
    }

    try {
        throw ClaimError("exceeds cover");
    } catch (const ClaimError& error) {
        std::cout << "Claim above cover: " << error.what() << '\n';
    }

    try {
        chargeFromPackage("UNKNOWN");
    } catch (const BillingError& error) {
        std::cout << "Unknown package: " << error.what() << '\n';
    }

    try {
        findPatient("P999");
    } catch (const BillingError& error) {
        std::cout << "Missing patient: " << error.what() << '\n';
    }

    try {
        parseBillAmount("abc");
    } catch (const std::invalid_argument& error) {
        std::cout << "Invalid numeric text: " << error.what() << '\n';
    }

    try {
        throw std::bad_alloc();
    } catch (const std::bad_alloc& error) {
        std::cout << "Memory allocation failure: " << error.what() << '\n';
    }
}
