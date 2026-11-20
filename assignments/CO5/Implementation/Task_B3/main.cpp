#include "benchmark.h"

#include <chrono>
#include <cstddef>
#include <iostream>
#include <memory>
#include <vector>

double virtualBenchmark(std::size_t count) {
    double sum = 0.0;
    for (std::size_t i = 0; i < count; ++i) {
        std::unique_ptr<VirtualBill> bill;
        switch (i % 4) {
            case 0:
                bill = std::make_unique<OutPatientVirtual>(500.0, 1200.0);
                break;
            case 1:
                bill = std::make_unique<InPatientVirtual>(3, 2500.0, 40000.0);
                break;
            case 2:
                bill = std::make_unique<DayCareVirtual>(18000.0);
                break;
            default:
                bill = std::make_unique<EmergencyVirtual>(3000.0, 2500.0);
                break;
        }
        sum += bill->total();
    }
    return sum;
}

double switchBenchmark(std::size_t count) {
    double sum = 0.0;
    for (std::size_t i = 0; i < count; ++i) {
        SwitchBill bill;
        switch (i % 4) {
            case 0:
                bill = {BillKind::OutPatient, 500.0, 1200.0, 1};
                break;
            case 1:
                bill = {BillKind::InPatient, 2500.0, 40000.0, 3};
                break;
            case 2:
                bill = {BillKind::DayCare, 18000.0, 0.0, 1};
                break;
            default:
                bill = {BillKind::Emergency, 3000.0, 2500.0, 1};
                break;
        }
        sum += bill.total();
    }
    return sum;
}

int main() {
    const std::size_t sizes[] = {1000, 1000000, 10000000};

    std::unique_ptr<VirtualBill> virtualTen[10];
    virtualTen[0] = std::make_unique<OutPatientVirtual>(500.0, 1200.0);
    virtualTen[1] = std::make_unique<InPatientVirtual>(3, 2500.0, 40000.0);
    virtualTen[2] = std::make_unique<DayCareVirtual>(18000.0);
    virtualTen[3] = std::make_unique<EmergencyVirtual>(3000.0, 2500.0);
    virtualTen[4] = std::make_unique<OutPatientVirtual>(500.0, 1200.0);
    virtualTen[5] = std::make_unique<InPatientVirtual>(3, 2500.0, 40000.0);
    virtualTen[6] = std::make_unique<DayCareVirtual>(18000.0);
    virtualTen[7] = std::make_unique<EmergencyVirtual>(3000.0, 2500.0);
    virtualTen[8] = std::make_unique<OutPatientVirtual>(500.0, 1200.0);
    virtualTen[9] = std::make_unique<InPatientVirtual>(3, 2500.0, 40000.0);

    double virtualTenTotal = 0.0;
    for (const auto& bill : virtualTen) {
        virtualTenTotal += bill->total();
    }

    SwitchBill switchTen[10] = {
        {BillKind::OutPatient, 500.0, 1200.0, 1},
        {BillKind::InPatient, 2500.0, 40000.0, 3},
        {BillKind::DayCare, 18000.0, 0.0, 1},
        {BillKind::Emergency, 3000.0, 2500.0, 1},
        {BillKind::OutPatient, 500.0, 1200.0, 1},
        {BillKind::InPatient, 2500.0, 40000.0, 3},
        {BillKind::DayCare, 18000.0, 0.0, 1},
        {BillKind::Emergency, 3000.0, 2500.0, 1},
        {BillKind::OutPatient, 500.0, 1200.0, 1},
        {BillKind::InPatient, 2500.0, 40000.0, 3}
    };
    double switchTenTotal = 0.0;
    for (const SwitchBill& bill : switchTen) {
        switchTenTotal += bill.total();
    }
    std::cout << "Ten-bill virtual == switch: "
              << (virtualTenTotal == switchTenTotal ? "YES" : "NO")
              << '\n';

    for (std::size_t size : sizes) {
        std::cout << "\nNumber of bills: " << size << '\n';
        const auto virtualStart = std::chrono::steady_clock::now();
        const double virtualTotal = virtualBenchmark(size);
        const auto virtualEnd = std::chrono::steady_clock::now();

        const auto switchStart = std::chrono::steady_clock::now();
        const double switchTotal = switchBenchmark(size);
        const auto switchEnd = std::chrono::steady_clock::now();

        const double virtualMilliseconds =
            std::chrono::duration<double, std::milli>(
                virtualEnd - virtualStart).count();
        const double switchMilliseconds =
            std::chrono::duration<double, std::milli>(
                switchEnd - switchStart).count();

        std::cout << "Virtual time: " << virtualMilliseconds << " ms\n";
        std::cout << "Switch time: " << switchMilliseconds << " ms\n";
        std::cout << "Totals equal: "
                  << (virtualTotal == switchTotal ? "YES" : "NO") << '\n';
    }

    std::cout << "\nVariant benchmark for 10000000 bills\n";
    const auto variantStart = std::chrono::steady_clock::now();
    double variantSum = 0.0;
    for (std::size_t i = 0; i < 10000000; ++i) {
        VariantBill bill;
        switch (i % 4) {
            case 0:
                bill = OutPatientVariant{500.0, 1200.0};
                break;
            case 1:
                bill = InPatientVariant{3, 2500.0, 40000.0};
                break;
            case 2:
                bill = DayCareVariant{18000.0};
                break;
            default:
                bill = EmergencyVariant{3000.0, 2500.0};
                break;
        }
        variantSum += variantTotal(bill);
    }
    const auto variantEnd = std::chrono::steady_clock::now();
    std::cout << "Variant time: "
              << std::chrono::duration<double, std::milli>(
                     variantEnd - variantStart).count()
              << " ms\n";
    std::cout << "Variant total: " << variantSum << '\n';

    std::cout << "Virtual base/object size: "
              << sizeof(VirtualBill) << " bytes\n";
    std::cout << "SwitchBill size: "
              << sizeof(SwitchBill) << " bytes\n";
    std::cout << "VariantBill size: "
              << sizeof(VariantBill) << " bytes\n";
}
