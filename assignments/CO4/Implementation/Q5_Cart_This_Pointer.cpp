#include <iomanip>
#include <iostream>
#include <string>

class Cart {
private:
    static const int capacity = 10;
    std::string items_[capacity];
    double prices_[capacity];
    int itemCount_;
    double discountPercent_;

public:
    Cart()
        : itemCount_(0), discountPercent_(0.0) {}

    Cart& add(const std::string& item, double price) {
        if (itemCount_ < capacity) {
            items_[itemCount_] = item;
            prices_[itemCount_] = price;
            ++itemCount_;
        }
        return *this;
    }

    Cart& setDiscount(double discountPercent) {
        this->discountPercent_ = discountPercent;
        return *this;
    }

    double total() const {
        double sum = 0.0;
        for (int i = 0; i < itemCount_; ++i) {
            sum += prices_[i];
        }
        return sum * (1.0 - discountPercent_ / 100.0);
    }
};

int main() {
    Cart directCart;
    directCart.add("Rice", 60.0);

    Cart* pointer = &directCart;
    pointer->add("Dal", 120.0);

    Cart& reference = directCart;
    reference.add("Oil", 180.0);

    directCart.setDiscount(10.0);

    Cart* dynamicCart = new Cart;
    dynamicCart->add("Milk", 50.0);
    delete dynamicCart;

    Cart first;
    first.add("Rice", 60.0).add("Dal", 120.0).add("Oil", 180.0)
         .setDiscount(10.0);

    Cart second;
    second.add("Bread", 75.0);

    Cart third;
    third.add("Vegetables", 200.0);

    Cart* carts[3] = { &first, &second, &third };
    Cart* highest = carts[0];
    for (int i = 1; i < 3; ++i) {
        if (carts[i]->total() > highest->total()) {
            highest = carts[i];
        }
    }

    std::cout << std::fixed << std::setprecision(2)
              << highest->total() << '\n';
}
