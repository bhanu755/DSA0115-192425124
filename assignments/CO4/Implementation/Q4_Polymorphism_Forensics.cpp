#include <iostream>
#include <memory>
#include <vector>

/*
Defect demonstration:
rate() is non-virtual, the base destructor is non-virtual, and Account copy
construction slices a SeniorAccount derived object.
*/

class AccountDefective {
public:
    double rate() const { return 3.5; }
    ~AccountDefective() { std::cout << "~AccountDefective\n"; }
};

class SeniorAccountDefective : public AccountDefective {
private:
    double* history_;

public:
    SeniorAccountDefective() : history_(new double[100]) {}

    double rate() const { return 4.0; }

    ~SeniorAccountDefective() {
        std::cout << "~SeniorAccountDefective\n";
        delete[] history_;
    }
};

class Account {
public:
    virtual double rate() const { return 3.5; }
    virtual ~Account() { std::cout << "~Account\n"; }
};

class SeniorAccount : public Account {
private:
    std::unique_ptr<double[]> history_;

public:
    SeniorAccount() : history_(std::make_unique<double[]>(100)) {}

    double rate() const override { return 4.0; }

    ~SeniorAccount() override {
        std::cout << "~SeniorAccount\n";
    }
};

int main() {
    AccountDefective* defectiveAccounts[2] = {
        new AccountDefective,
        new SeniorAccountDefective
    };

    std::cout << "Defective non-virtual rates:\n";
    for (AccountDefective* account : defectiveAccounts) {
        std::cout << account->rate() << '\n';
    }
    for (AccountDefective* account : defectiveAccounts) {
        delete account;
    }

    /*
    This next line demonstrates slicing. If a temporary SeniorAccount could
    convert to Account, only the Account part would remain.
    */
    AccountDefective copy = SeniorAccountDefective();
    (void)copy;

    std::cout << "Repaired virtual rates:\n";
    std::vector<std::unique_ptr<Account>> accounts;
    accounts.push_back(std::make_unique<Account>());
    accounts.push_back(std::make_unique<SeniorAccount>());

    for (const auto& account : accounts) {
        std::cout << account->rate() << '\n';
    }

    /*
    Run defective and repaired programs under AddressSanitizer if required:
    g++ -std=c++17 -Wall -Wextra -fsanitize=address -g
        Q4_Polymorphism_Forensics.cpp -o main

    Do not expect a fabricated ASan report. Capture actual local output only.
    */
}
