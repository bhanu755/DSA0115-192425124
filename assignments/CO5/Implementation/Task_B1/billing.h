#ifndef CO5_BILLING_H
#define CO5_BILLING_H

#include <iomanip>
#include <iostream>
#include <string>

class Bill {
protected:
    std::string patientName_;

    explicit Bill(const std::string& patientName)
        : patientName_(patientName) {}

public:
    virtual ~Bill() {
        std::cout << "~Bill()\n";
    }

    virtual double total() const = 0;

    virtual std::string type() const {
        return "UNKNOWN";
    }

    virtual void print(std::ostream& output) const {
        output << type() << " bill - " << patientName_
               << ": Rs " << std::fixed << std::setprecision(2) << total();
    }

    const std::string& patientName() const {
        return patientName_;
    }
};

inline std::ostream& operator<<(std::ostream& output, const Bill& bill) {
    bill.print(output);
    return output;
}

class OutPatient : public Bill {
    double consultation_;
    double tests_;

public:
    OutPatient(const std::string& name, double consultation, double tests)
        : Bill(name), consultation_(consultation), tests_(tests) {}

    double total() const override {
        return consultation_ + tests_;
    }

    std::string type() const override {
        return "OP";
    }

    ~OutPatient() override {
        std::cout << "~OutPatient()\n";
    }
};

class InPatient : public Bill {
    int days_;
    double perDay_;
    double surgery_;

public:
    InPatient(const std::string& name, int days, double perDay, double surgery)
        : Bill(name), days_(days), perDay_(perDay), surgery_(surgery) {}

    double total() const override {
        return days_ * perDay_ + surgery_;
    }

    std::string type() const override {
        return "IP";
    }
};

class DayCareBill : public Bill {
    double packagePrice_;

public:
    DayCareBill(const std::string& name, double packagePrice)
        : Bill(name), packagePrice_(packagePrice) {}

    double total() const override {
        return packagePrice_;
    }

    std::string type() const override {
        return "DAYCARE";
    }
};

class EmergencyBill : public Bill {
    double baseCharge_;
    double timeCharge_;

public:
    EmergencyBill(const std::string& name, double baseCharge, double timeCharge)
        : Bill(name), baseCharge_(baseCharge), timeCharge_(timeCharge) {}

    double total() const override {
        return baseCharge_ + timeCharge_;
    }

    std::string type() const override {
        return "EMERGENCY";
    }
};

class DiagnosticBill : public Bill {
    double scanCharge_;
    double laboratoryCharge_;

public:
    DiagnosticBill(const std::string& name,
                   double scanCharge, double laboratoryCharge)
        : Bill(name),
          scanCharge_(scanCharge),
          laboratoryCharge_(laboratoryCharge) {}

    double total() const override {
        return scanCharge_ + laboratoryCharge_;
    }

    std::string type() const override {
        return "DIAGNOSTIC";
    }
};

class Payer {
public:
    virtual ~Payer() = default;
    virtual double amountCovered(const Bill& bill) const = 0;
};

class SelfPay : public Payer {
public:
    double amountCovered(const Bill&) const override {
        return 0.0;
    }
};

class Insurance : public Payer {
    double coverLimit_;
    double coPaymentPercent_;

public:
    Insurance(double coverLimit, double coPaymentPercent)
        : coverLimit_(coverLimit), coPaymentPercent_(coPaymentPercent) {}

    double amountCovered(const Bill& bill) const override {
        const double limitedAmount =
            bill.total() < coverLimit_ ? bill.total() : coverLimit_;
        return limitedAmount * (100.0 - coPaymentPercent_) / 100.0;
    }
};

class GovernmentScheme : public Payer {
    double fixedPackageRate_;

public:
    explicit GovernmentScheme(double fixedPackageRate)
        : fixedPackageRate_(fixedPackageRate) {}

    double amountCovered(const Bill& bill) const override {
        return bill.total() < fixedPackageRate_ ? bill.total()
                                                : fixedPackageRate_;
    }
};

class CorporateTieUp : public Payer {
    double coveragePercent_;

public:
    explicit CorporateTieUp(double coveragePercent)
        : coveragePercent_(coveragePercent) {}

    double amountCovered(const Bill& bill) const override {
        return bill.total() * coveragePercent_ / 100.0;
    }
};

#endif
