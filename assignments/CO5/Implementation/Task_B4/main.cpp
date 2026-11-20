#include "../Task_B1/billing.h"

#include <cassert>
#include <memory>
#include <vector>

int main() {
    bool earlierTestsPass =
        OutPatient("Ravi", 500.0, 1200.0).total() == 1700.0 &&
        InPatient("Meena", 3, 2500.0, 40000.0).total() == 47500.0 &&
        DayCareBill("Suresh", 18000.0).total() == 18000.0 &&
        EmergencyBill("Kavya", 3000.0, 2500.0).total() == 5500.0;

    if (earlierTestsPass) {
        std::cout << "Earlier tests: PASS\n";
    } else {
        std::cout << "Earlier tests: FAIL\n";
        return 1;
    }

    DiagnosticBill diagnostic("Ravi", 2200.0, 1800.0);
    const bool newBillPass = diagnostic.total() == 4000.0;
    std::cout << "New bill test: "
              << (newBillPass ? "PASS" : "FAIL") << '\n';
    if (!newBillPass) {
        return 1;
    }

    CorporateTieUp corporate(80.0);
    const bool newPayerPass =
        corporate.amountCovered(diagnostic) == 3200.0;
    std::cout << "New payer test: "
              << (newPayerPass ? "PASS" : "FAIL") << '\n';

    std::vector<std::unique_ptr<Bill>> bills;
    bills.push_back(std::make_unique<OutPatient>("Ravi", 500.0, 1200.0));
    bills.push_back(std::make_unique<InPatient>("Meena", 3, 2500.0, 40000.0));
    bills.push_back(std::make_unique<DiagnosticBill>("Ravi", 2200.0, 1800.0));

    std::cout << "Polymorphic final fleet:\n";
    for (const auto& bill : bills) {
        std::cout << *bill << '\n';
    }

    if (!newPayerPass) {
        return 1;
    }
}
