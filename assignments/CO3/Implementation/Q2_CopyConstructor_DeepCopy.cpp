#include <cstddef>
#include <iostream>
#include <initializer_list>
#include <string>
#include <utility>

class Prescription {
public:
    Prescription(std::initializer_list<std::string> medicines)
        : count_(medicines.size()), medicines_(new std::string[count_]) {
        std::size_t index = 0;
        for (const std::string& medicine : medicines) {
            medicines_[index++] = medicine;
        }
    }

    Prescription(const Prescription& other)
        : count_(other.count_), medicines_(new std::string[count_]) {
        for (std::size_t i = 0; i < count_; ++i) {
            medicines_[i] = other.medicines_[i];
        }
    }

    Prescription& operator=(const Prescription& other) {
        if (this != &other) {
            Prescription copy(other);
            swap(copy);
        }
        return *this;
    }

    ~Prescription() {
        delete[] medicines_;
    }

    void setMedicine(std::size_t index, const std::string& medicine) {
        if (index < count_) {
            medicines_[index] = medicine;
        }
    }

    void print(const std::string& label) const {
        std::cout << label << ": ";
        for (std::size_t i = 0; i < count_; ++i) {
            if (i != 0) {
                std::cout << ", ";
            }
            std::cout << medicines_[i];
        }
        std::cout << '\n';
    }

private:
    void swap(Prescription& other) noexcept {
        std::swap(count_, other.count_);
        std::swap(medicines_, other.medicines_);
    }

    std::size_t count_;
    std::string* medicines_;
};

int main() {
    Prescription original{"Paracetamol", "Vitamin C"};
    Prescription copied(original);
    original.setMedicine(0, "Ibuprofen");

    original.print("Original prescription");
    copied.print("Deep copy");

    Prescription assigned{"Antacid"};
    assigned = original;
    assigned.setMedicine(1, "Cough syrup");
    assigned.print("Assigned prescription");
    original.print("Original remains independent");

    assigned = assigned;
    assigned.print("After self-assignment");
}
