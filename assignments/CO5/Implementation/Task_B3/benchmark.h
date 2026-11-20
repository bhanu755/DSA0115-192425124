#ifndef CO5_BENCHMARK_H
#define CO5_BENCHMARK_H

#include <variant>
#include <string>
#include <type_traits>

class VirtualBill {
public:
    virtual ~VirtualBill() = default;
    virtual double total() const = 0;
};

class OutPatientVirtual : public VirtualBill {
public:
    double consultation;
    double tests;
    OutPatientVirtual(double c, double t) : consultation(c), tests(t) {}
    double total() const override { return consultation + tests; }
};

class InPatientVirtual : public VirtualBill {
public:
    int days;
    double perDay;
    double surgery;
    InPatientVirtual(int d, double p, double s)
        : days(d), perDay(p), surgery(s) {}
    double total() const override { return days * perDay + surgery; }
};

class DayCareVirtual : public VirtualBill {
public:
    double packagePrice;
    explicit DayCareVirtual(double p) : packagePrice(p) {}
    double total() const override { return packagePrice; }
};

class EmergencyVirtual : public VirtualBill {
public:
    double baseCharge;
    double timeCharge;
    EmergencyVirtual(double b, double t) : baseCharge(b), timeCharge(t) {}
    double total() const override { return baseCharge + timeCharge; }
};

enum class BillKind {
    OutPatient,
    InPatient,
    DayCare,
    Emergency
};

struct SwitchBill {
    BillKind kind;
    double first;
    double second;
    int days = 1;

    double total() const {
        switch (kind) {
            case BillKind::OutPatient:
                return first + second;
            case BillKind::InPatient:
                return days * first + second;
            case BillKind::DayCare:
                return first;
            case BillKind::Emergency:
                return first + second;
        }
        return 0.0;
    }
};

struct OutPatientVariant {
    double consultation;
    double tests;
};

struct InPatientVariant {
    int days;
    double perDay;
    double surgery;
};

struct DayCareVariant {
    double packagePrice;
};

struct EmergencyVariant {
    double baseCharge;
    double timeCharge;
};

using VariantBill = std::variant<
    OutPatientVariant,
    InPatientVariant,
    DayCareVariant,
    EmergencyVariant>;

inline double variantTotal(const VariantBill& bill) {
    return std::visit([](const auto& value) {
        using T = std::decay_t<decltype(value)>;
        if constexpr (std::is_same_v<T, OutPatientVariant>) {
            return value.consultation + value.tests;
        } else if constexpr (std::is_same_v<T, InPatientVariant>) {
            return value.days * value.perDay + value.surgery;
        } else if constexpr (std::is_same_v<T, DayCareVariant>) {
            return value.packagePrice;
        } else {
            return value.baseCharge + value.timeCharge;
        }
    }, bill);
}

#endif
