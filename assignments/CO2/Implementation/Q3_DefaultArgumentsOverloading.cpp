#include <iostream>
#include <string>

struct Parcel {
    double kilograms;
    bool express;
    bool insured;
};

double charge(double kilograms, bool express = false, bool insured = false) {
    double amount = kilograms * 50.0;
    if (express) {
        amount += 20.0;
    }
    if (insured) {
        amount += 10.0;
    }
    return amount;
}

double charge(int grams) {
    return charge(static_cast<double>(grams) / 1000.0);
}

double charge(const Parcel& parcel) {
    return charge(parcel.kilograms, parcel.express, parcel.insured);
}

int main() {
    std::cout << "charge(2): " << charge(2) << '\n';
    std::cout << "charge(2.0): " << charge(2.0) << '\n';
    std::cout << "charge(2.0f): " << charge(2.0f) << '\n';
    std::cout << "charge(2.0, true): " << charge(2.0, true) << '\n';
    std::cout << "charge(2.0, false, true): " << charge(2.0, false, true) << '\n';
    std::cout << "charge(Parcel{3.0, true, true}): "
              << charge(Parcel{3.0, true, true}) << '\n';
}