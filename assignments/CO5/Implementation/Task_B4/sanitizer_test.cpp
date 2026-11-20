#include "../Task_B1/billing.h"
#include "../Task_B2/exceptions.h"

#include <memory>

int main() {
    {
        std::unique_ptr<Bill> bill =
            std::make_unique<OutPatient>("Ravi", 500.0, 1200.0);
        Bill* billPointer = bill.get();
        std::cout << "Sanitizer bill total: " << billPointer->total() << '\n';
    }

    try {
        throw ClaimError("exceeds cover");
    } catch (const ClaimError& error) {
        std::cout << "Caught in sanitizer test: " << error.what() << '\n';
    }

    std::unique_ptr<double[]> buffer =
        std::make_unique<double[]>(100);
    buffer[0] = 1700.0;
}
