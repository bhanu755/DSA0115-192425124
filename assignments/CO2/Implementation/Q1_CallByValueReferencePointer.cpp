#include <iostream>

void change(int value, int& reference, int* pointer);
int& bigger(int& first, int& second);
void show(int first, int second = 5, int third = 10);
void applyByValue(long long fee, int percent);
void applyConcession(long long& fee, int percent);

void change(int value, int& reference, int* pointer) {
    value += 10;
    reference += 10;
    *pointer += 10;
}

int& bigger(int& first, int& second) {
    return first > second ? first : second;
}

void show(int first, int second, int third) {
    std::cout << first + second + third << ' ';
}

void applyByValue(long long fee, int percent) {
    fee -= fee * percent / 100;
}

void applyConcession(long long& fee, int percent) {
    fee -= fee * percent / 100;
}

int main() {
    int first = 1;
    int second = 2;
    int third = 3;
    change(first, second, &third);
    std::cout << first << ' ' << second << ' ' << third << '\n';

    bigger(first, third) = 100;
    std::cout << first << ' ' << third << '\n';

    show(1);
    show(1, 2);
    show(1, 2, 3);
    std::cout << '\n';

    long long hostelFee = 45000;
    applyByValue(hostelFee, 10);
    std::cout << "after call by value : " << hostelFee << '\n';
    applyConcession(hostelFee, 10);
    std::cout << "after call by reference: " << hostelFee << '\n';
}