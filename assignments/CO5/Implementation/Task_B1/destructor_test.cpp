#include "billing.h"

#include <memory>

int main() {
    // With a virtual base destructor, deleting through Bill* also destroys
    // the most-derived OutPatient object.
    Bill* bill = new OutPatient("Ravi", 500.0, 1200.0);
    delete bill;

    /*
    Controlled non-virtual experiment:

    Repeat this file after changing Bill::~Bill() to non-virtual and
    compiling with AddressSanitizer. The derived destructor may not run,
    and a resource-owning derived class may leak or trigger ASan findings.
    The original implementation must remain virtual.
    */
}
