#include "billing.h"

#include <memory>
#include <vector>

int main() {
    std::vector<std::unique_ptr<Bill>> bills;
    bills.push_back(std::make_unique<OutPatient>("Ravi", 500.0, 1200.0));
    bills.push_back(std::make_unique<InPatient>("Meena", 3, 2500.0, 40000.0));
    bills.push_back(std::make_unique<DayCareBill>("Suresh", 18000.0));
    bills.push_back(std::make_unique<EmergencyBill>("Kavya", 3000.0, 2500.0));

    std::vector<std::unique_ptr<Payer>> payers;
    payers.push_back(std::make_unique<SelfPay>());
    payers.push_back(std::make_unique<Insurance>(50000.0, 10.0));
    payers.push_back(std::make_unique<GovernmentScheme>(40000.0));
    payers.push_back(std::make_unique<CorporateTieUp>(80.0));

    double dayTotal = 0.0;
    for (const auto& bill : bills) {
        std::cout << *bill << '\n';
        dayTotal += bill->total();
    }
    std::cout << "Complete day's total: Rs " << dayTotal << '\n';

    std::cout << "Payer coverage tests:\n";
    for (const auto& bill : bills) {
        std::cout << bill->patientName() << ": ";
        for (std::size_t i = 0; i < payers.size(); ++i) {
            if (i != 0) {
                std::cout << ", ";
            }
            std::cout << payers[i]->amountCovered(*bill);
        }
        std::cout << '\n';
    }
}
