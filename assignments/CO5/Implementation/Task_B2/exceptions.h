#ifndef CO5_EXCEPTIONS_H
#define CO5_EXCEPTIONS_H

#include <stdexcept>
#include <string>

class BillingError : public std::runtime_error {
public:
    explicit BillingError(const std::string& message)
        : std::runtime_error(message) {}
};

class ClaimError : public BillingError {
public:
    explicit ClaimError(const std::string& message)
        : BillingError(message) {}
};

#endif
