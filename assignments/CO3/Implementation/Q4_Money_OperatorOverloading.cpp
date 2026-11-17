#include <iomanip>
#include <iostream>
#include <stdexcept>

class Money {
public:
    Money(long long rupees = 0, int paise = 0)
        : paiseTotal_(rupees * 100 + paise) {}

    Money operator+(const Money& other) const {
        return Money::fromPaise(paiseTotal_ + other.paiseTotal_);
    }

    Money operator-(const Money& other) const {
        if (paiseTotal_ < other.paiseTotal_) {
            throw std::underflow_error("Subtraction would make money negative.");
        }
        return Money::fromPaise(paiseTotal_ - other.paiseTotal_);
    }

    Money& operator+=(const Money& other) {
        paiseTotal_ += other.paiseTotal_;
        return *this;
    }

    bool operator==(const Money& other) const {
        return paiseTotal_ == other.paiseTotal_;
    }

    bool operator<(const Money& other) const {
        return paiseTotal_ < other.paiseTotal_;
    }

    friend std::ostream& operator<<(std::ostream& output, const Money& money) {
        const long long rupees = money.paiseTotal_ / 100;
        const long long paise = money.paiseTotal_ % 100;
        output << "Rs " << rupees << '.' << std::setfill('0') << std::setw(2)
               << paise << std::setfill(' ');
        return output;
    }

    friend std::istream& operator>>(std::istream& input, Money& money) {
        long long rupees;
        int paise;
        if (input >> rupees >> paise) {
            money.paiseTotal_ = rupees * 100 + paise;
        }
        return input;
    }

private:
    static Money fromPaise(long long paise) {
        Money result;
        result.paiseTotal_ = paise;
        return result;
    }

    long long paiseTotal_;
};

int main() {
    const Money a(120, 75);
    const Money b(79, 25);
    const Money c = a + b;

    std::cout << c << '\n';
    std::cout << std::boolalpha << (c == Money(200, 0)) << '\n';

    std::cout << "Addition with carry: " << Money(10, 90) + Money(2, 30) << '\n';
    std::cout << "Subtraction: " << c - Money(50, 50) << '\n';
    Money total = a;
    total += b;
    std::cout << "After +=: " << total << '\n';
    std::cout << "a < b: " << (a < b) << '\n';

    try {
        const Money invalid = b - c;
        std::cout << invalid << '\n';
    } catch (const std::underflow_error& error) {
        std::cout << "Negative subtraction rejected: " << error.what() << '\n';
    }

    Money entered;
    std::cout << "Enter rupees and paise (for example: 12 50): ";
    if (std::cin >> entered) {
        std::cout << "Entered amount: " << entered << '\n';
    } else {
        std::cout << "No valid amount entered.\n";
    }
}
