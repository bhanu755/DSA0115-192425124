#include <iostream>

int& highest(int marks[], int count) {
    int position = 0;
    for (int index = 1; index < count; ++index) {
        if (marks[index] > marks[position]) {
            position = index;
        }
    }
    return marks[position];
}

int& bad() {
    int local = 10;
    return local;
}

int main() {
    int marks[] = {72, 91, 85, 88, 90};
    const int count = static_cast<int>(sizeof(marks) / sizeof(marks[0]));

    std::cout << "Highest mark: " << highest(marks, count) << '\n';
    highest(marks, count) += 2;
    std::cout << "Moderated highest mark: " << highest(marks, count) << '\n';
}