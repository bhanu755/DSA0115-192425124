#include <cmath>
#include <iostream>
#include <stdexcept>

class Complex {
public:
    Complex() : real(0.0), imag(0.0) {}
    Complex(double realValue) : real(realValue), imag(0.0) {}
    Complex(double realValue, double imagValue) : real(realValue), imag(imagValue) {}

    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }

    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imag - other.imag);
    }

    Complex operator*(const Complex& other) const {
        return Complex(real * other.real - imag * other.imag,
                       real * other.imag + imag * other.real);
    }

    Complex operator/(const Complex& other) const {
        const double denominator = other.real * other.real + other.imag * other.imag;
        if (denominator == 0.0) {
            throw std::domain_error("Cannot divide by a zero complex number.");
        }
        return Complex((real * other.real + imag * other.imag) / denominator,
                       (imag * other.real - real * other.imag) / denominator);
    }

    bool operator==(const Complex& other) const {
        return real == other.real && imag == other.imag;
    }

    double magnitude() const {
        return std::hypot(real, imag);
    }

    friend std::ostream& operator<<(std::ostream& output, const Complex& value) {
        output << value.real;
        if (value.imag >= 0.0) {
            output << " + " << value.imag << 'j';
        } else {
            output << " - " << -value.imag << 'j';
        }
        return output;
    }

    double real;
    double imag;
};

int main() {
    const double resistance = 10.0;
    const double inductance = 0.05;
    const double capacitance = 0.0001;
    const double frequency = 50.0;
    const double omega = 2.0 * std::acos(-1.0) * frequency;

    const Complex resistor(resistance, 0.0);
    const Complex inductor(0.0, omega * inductance);
    const Complex capacitor(0.0, -1.0 / (omega * capacitance));
    const Complex seriesImpedance = resistor + inductor + capacitor;

    std::cout << "Resistor impedance ZR: " << resistor << '\n'
              << "Inductor impedance ZL: " << inductor << '\n'
              << "Capacitor impedance ZC: " << capacitor << '\n'
              << "Series RLC impedance: " << seriesImpedance << '\n'
              << "Series magnitude: " << seriesImpedance.magnitude() << '\n';

    const Complex firstBranch(8.0, 3.0);
    const Complex secondBranch(12.0, -2.0);
    const Complex parallelImpedance =
        (firstBranch * secondBranch) / (firstBranch + secondBranch);
    std::cout << "Parallel impedance: " << parallelImpedance << '\n';
    std::cout << "Complex multiplication: " << firstBranch * secondBranch << '\n';
    std::cout << "Complex division: " << firstBranch / secondBranch << '\n';
    std::cout << "Complex equality: "
              << std::boolalpha << (Complex(2.0, 3.0) == Complex(2.0, 3.0)) << '\n';

    try {
        const Complex invalid = firstBranch / Complex();
        std::cout << invalid << '\n';
    } catch (const std::domain_error& error) {
        std::cout << "Division by zero rejected: " << error.what() << '\n';
    }
}
