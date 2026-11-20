#include "billing.h"

#include <memory>

int main() {
    std::unique_ptr<Bill> bill =
        std::make_unique<InPatient>("Meena", 3, 2500.0, 40000.0);
    Bill* basePointer = bill.get();

    // Because total() is virtual, this call dispatches to InPatient::total().
    std::cout << "Runtime total: " << basePointer->total() << '\n';

    /*
    Controlled non-virtual experiment:

    If Bill::total() were changed to non-virtual, the call through Bill*
    would use Bill::total(), but Bill is abstract and cannot provide that
    implementation. In a controlled concrete base, it would use the base
    function and produce base-type behavior instead of the derived result.
    This implementation intentionally keeps total() virtual.
    */
}
