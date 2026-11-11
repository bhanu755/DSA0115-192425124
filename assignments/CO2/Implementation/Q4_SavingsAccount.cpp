#include <iostream>
#include <string>

class SavingsAccount {
    std::string accountNumber_;
    long long balance_;
    long long transactions_[10]{};
    int count_ = 0;

    void addTransaction(long long amount) {
        if (count_ < 10) {
            transactions_[count_++] = amount;
        } else {
            for (int index = 1; index < 10; ++index) {
                transactions_[index - 1] = transactions_[index];
            }
            transactions_[9] = amount;
        }
    }

public:
    SavingsAccount(const std::string& accountNumber, long long openingBalance)
        : accountNumber_(accountNumber), balance_(openingBalance >= 0 ? openingBalance : 0) {}

    void deposit(long long amount);
    bool withdraw(long long amount);
    void miniStatement() const;
};

void SavingsAccount::deposit(long long amount) {
    if (amount > 0) {
        balance_ += amount;
        addTransaction(amount);
    }
}

bool SavingsAccount::withdraw(long long amount) {
    if (amount <= 0 || amount > balance_) {
        return false;
    }

    balance_ -= amount;
    addTransaction(-amount);
    return true;
}

void SavingsAccount::miniStatement() const {
    std::cout << "Account: " << accountNumber_ << '\n'
              << "Balance: " << balance_ << '\n'
              << "Transactions:\n";
    for (int index = 0; index < count_; ++index) {
        std::cout << transactions_[index] << '\n';
    }
}

int main() {
    SavingsAccount account("SB1001", 10000);
    account.deposit(2000);
    account.withdraw(1500);
    account.miniStatement();

    SavingsAccount recentHistory("SB1002", 0);
    for (int transaction = 1; transaction <= 11; ++transaction) {
        recentHistory.deposit(transaction * 100);
    }
    recentHistory.miniStatement();
}