#include <chrono>
#include <iostream>

class ShiftedHistory {
    static constexpr int capacity_ = 50;
    long long transactions_[capacity_]{};
    int count_ = 0;

public:
    void add(long long amount) {
        if (count_ < capacity_) {
            transactions_[count_++] = amount;
            return;
        }
        for (int index = 1; index < capacity_; ++index) {
            transactions_[index - 1] = transactions_[index];
        }
        transactions_[capacity_ - 1] = amount;
    }

    int size() const {
        return count_;
    }

    long long atOldestFirst(int index) const {
        return transactions_[index];
    }
};

class CircularHistory {
    static constexpr int capacity_ = 50;
    long long transactions_[capacity_]{};
    int next_ = 0;
    int count_ = 0;

public:
    void add(long long amount) {
        transactions_[next_] = amount;
        next_ = (next_ + 1) % capacity_;
        if (count_ < capacity_) {
            ++count_;
        }
    }

    int size() const {
        return count_;
    }

    long long atOldestFirst(int index) const {
        const int oldest = (next_ - count_ + capacity_) % capacity_;
        return transactions_[(oldest + index) % capacity_];
    }
};

template <typename History>
bool validateSequence(History& history) {
    for (int transaction = 1; transaction <= 20; ++transaction) {
        history.add(transaction);
    }
    if (history.size() != 20 || history.atOldestFirst(0) != 1 ||
        history.atOldestFirst(19) != 20) {
        return false;
    }

    for (int transaction = 21; transaction <= 50; ++transaction) {
        history.add(transaction);
    }
    if (history.size() != 50 || history.atOldestFirst(0) != 1 ||
        history.atOldestFirst(49) != 50) {
        return false;
    }

    history.add(51);
    if (history.atOldestFirst(0) != 2 || history.atOldestFirst(49) != 51) {
        return false;
    }

    for (int transaction = 52; transaction <= 57; ++transaction) {
        history.add(transaction);
    }
    if (history.atOldestFirst(0) != 8 || history.atOldestFirst(49) != 57) {
        return false;
    }
    for (int index = 0; index < history.size(); ++index) {
        if (history.atOldestFirst(index) != index + 8) {
            return false;
        }
    }
    return true;
}

template <typename History>
long long benchmarkInsertions() {
    History history;
    constexpr int insertionCount = 200000;
    const auto start = std::chrono::steady_clock::now();
    for (int index = 0; index < insertionCount; ++index) {
        history.add(index);
    }
    const auto end = std::chrono::steady_clock::now();
    volatile long long lastValue = history.atOldestFirst(history.size() - 1);
    const auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    return elapsed + lastValue * 0;
}

int main() {
    ShiftedHistory original;
    CircularHistory redesigned;
    const bool originalPassed = validateSequence(original);
    const bool redesignedPassed = validateSequence(redesigned);

    std::cout << (originalPassed ? "[PASS]" : "[FAIL]")
              << " shifted history retains the newest 50 transactions\n"
              << (redesignedPassed ? "[PASS]" : "[FAIL]")
              << " circular history retains the newest 50 transactions\n";
    if (!originalPassed || !redesignedPassed) {
        return 1;
    }

    std::cout << "Shifted insertion benchmark: "
              << benchmarkInsertions<ShiftedHistory>() << " ns\n"
              << "Circular insertion benchmark: "
              << benchmarkInsertions<CircularHistory>() << " ns\n";
}