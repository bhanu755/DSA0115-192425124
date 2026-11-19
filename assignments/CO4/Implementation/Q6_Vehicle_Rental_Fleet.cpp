#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Vehicle {
private:
    std::string registrationNumber_;
    double dailyRate_;
    bool rented_;

protected:
    Vehicle(const std::string& registrationNumber, double dailyRate)
        : registrationNumber_(registrationNumber),
          dailyRate_(dailyRate),
          rented_(false) {}

    const std::string& registrationNumber() const {
        return registrationNumber_;
    }

    double dailyRate() const {
        return dailyRate_;
    }

public:
    virtual ~Vehicle() = default;
    virtual std::string registrationNumberString() const = 0;

    bool rent() {
        if (rented_) {
            return false;
        }
        rented_ = true;
        return true;
    }

    double returnVehicle(int lateDays) {
        rented_ = false;
        return std::max(0, lateDays) * dailyRate_ * 0.25;
    }

    virtual double charge(int days) const = 0;
    virtual void display() const = 0;

    bool isRented() const {
        return rented_;
    }
};

class Bicycle : public Vehicle {
public:
    Bicycle(const std::string& registrationNumber, double dailyRate)
        : Vehicle(registrationNumber, dailyRate) {}

    double charge(int days) const override {
        return std::max(0, days) * dailyRate();
    }

    void display() const override {
        std::cout << "Bicycle " << registrationNumber()
                  << ", Rate: " << dailyRate()
                  << ", Rented: " << std::boolalpha << isRented() << '\n';
    }

    std::string registrationNumberString() const override {
        return registrationNumber();
    }
};

class MotorVehicle : public Vehicle {
private:
    double fuelOrChargeLevel_;
    std::string serviceDueDate_;

protected:
    MotorVehicle(const std::string& registrationNumber, double dailyRate,
                 double fuelOrChargeLevel, const std::string& serviceDueDate)
        : Vehicle(registrationNumber, dailyRate),
          fuelOrChargeLevel_(fuelOrChargeLevel),
          serviceDueDate_(serviceDueDate) {}

    double fuelOrChargeLevel() const {
        return fuelOrChargeLevel_;
    }

    const std::string& serviceDueDate() const {
        return serviceDueDate_;
    }
};

class TwoWheeler : public MotorVehicle {
public:
    TwoWheeler(const std::string& registrationNumber, double dailyRate,
               double fuelLevel, const std::string& serviceDueDate)
        : MotorVehicle(registrationNumber, dailyRate,
                       fuelLevel, serviceDueDate) {}

    double charge(int days) const override {
        return std::max(0, days) * dailyRate() + 50.0;
    }

    void display() const override {
        std::cout << "TwoWheeler " << registrationNumber()
                  << ", Fuel: " << fuelOrChargeLevel()
                  << ", Service: " << serviceDueDate()
                  << ", Rented: " << std::boolalpha << isRented() << '\n';
    }

    std::string registrationNumberString() const override {
        return registrationNumber();
    }
};

class Car : public MotorVehicle {
private:
    int seatingCapacity_;

public:
    Car(const std::string& registrationNumber, double dailyRate,
        double fuelLevel, const std::string& serviceDueDate, int seatingCapacity)
        : MotorVehicle(registrationNumber, dailyRate,
                       fuelLevel, serviceDueDate),
          seatingCapacity_(seatingCapacity) {}

    double charge(int days) const override {
        return std::max(0, days) * dailyRate()
             + static_cast<double>(seatingCapacity_) * 20.0;
    }

    void display() const override {
        std::cout << "Car " << registrationNumber()
                  << ", Seats: " << seatingCapacity_
                  << ", Rented: " << std::boolalpha << isRented() << '\n';
    }

    std::string registrationNumberString() const override {
        return registrationNumber();
    }
};

class ElectricCar : public MotorVehicle {
private:
    double batteryCapacity_;
    double costPerKWh_;

public:
    ElectricCar(const std::string& registrationNumber, double dailyRate,
                double chargeLevel, const std::string& serviceDueDate,
                double batteryCapacity, double costPerKWh)
        : MotorVehicle(registrationNumber, dailyRate,
                       chargeLevel, serviceDueDate),
          batteryCapacity_(batteryCapacity),
          costPerKWh_(costPerKWh) {}

    double charge(int days) const override {
        return std::max(0, days) * dailyRate()
             + batteryCapacity_ * costPerKWh_;
    }

    void display() const override {
        std::cout << "ElectricCar " << registrationNumber()
                  << ", Battery: " << batteryCapacity_ << " kWh"
                  << ", Rented: " << std::boolalpha << isRented() << '\n';
    }

    std::string registrationNumberString() const override {
        return registrationNumber();
    }
};

class ElectricBus : public MotorVehicle {
private:
    int seatingCapacity_;

public:
    ElectricBus(const std::string& registrationNumber, double dailyRate,
                double chargeLevel, const std::string& serviceDueDate,
                int seatingCapacity)
        : MotorVehicle(registrationNumber, dailyRate,
                       chargeLevel, serviceDueDate),
          seatingCapacity_(seatingCapacity) {}

    double charge(int days) const override {
        return std::max(0, days) * dailyRate()
             + static_cast<double>(seatingCapacity_) * 10.0;
    }

    void display() const override {
        std::cout << "ElectricBus " << registrationNumber()
                  << ", Seats: " << seatingCapacity_
                  << ", Rented: " << std::boolalpha << isRented() << '\n';
    }

    std::string registrationNumberString() const override {
        return registrationNumber();
    }
};

class RentalFleet {
private:
    std::vector<std::unique_ptr<Vehicle>> vehicles_;

    Vehicle* findVehicle(const std::string& registrationNumber) {
        for (const auto& vehicle : vehicles_) {
            if (vehicle->registrationNumberString() == registrationNumber) {
                return vehicle.get();
            }
        }
        return nullptr;
    }

public:
    void addVehicle(std::unique_ptr<Vehicle> vehicle) {
        vehicles_.push_back(std::move(vehicle));
    }

    void listVehicles() const {
        for (const auto& vehicle : vehicles_) {
            vehicle->display();
        }
    }

    void rentVehicle(Vehicle* vehicle) {
        std::cout << (vehicle != nullptr && vehicle->rent()
                          ? "Rental successful\n"
                          : "Vehicle unavailable\n");
    }

    void rentVehicle(const std::string& registrationNumber) {
        rentVehicle(findVehicle(registrationNumber));
    }

    double calculateCharge(const Vehicle& vehicle, int days) const {
        return vehicle.charge(days);
    }

    void returnVehicle(Vehicle* vehicle, int lateDays) {
        if (vehicle != nullptr) {
            std::cout << "Late charge: "
                      << vehicle->returnVehicle(lateDays) << '\n';
        }
    }

    Vehicle* at(std::size_t index) {
        if (index >= vehicles_.size()) {
            return nullptr;
        }
        return vehicles_[index].get();
    }
};

int main() {
    RentalFleet fleet;
    fleet.addVehicle(std::make_unique<Bicycle>("B101", 200.0));
    fleet.addVehicle(std::make_unique<TwoWheeler>(
        "T201", 500.0, 80.0, "2026-12-01"));
    fleet.addVehicle(std::make_unique<Car>(
        "C301", 1200.0, 60.0, "2026-12-10", 5));
    fleet.addVehicle(std::make_unique<ElectricCar>(
        "E401", 1500.0, 90.0, "2026-12-15", 50.0, 8.0));
    fleet.addVehicle(std::make_unique<ElectricBus>(
        "EB501", 2500.0, 85.0, "2026-12-20", 40));

    std::cout << "Vehicle fleet:\n";
    fleet.listVehicles();

    for (int i = 0; i < 5; ++i) {
        fleet.rentVehicle(fleet.at(static_cast<std::size_t>(i)));
    }

    Vehicle* bicycle = fleet.at(0);
    if (bicycle != nullptr) {
        std::cout << "Bicycle charge for 3 days: "
                  << fleet.calculateCharge(*bicycle, 3) << '\n';
        fleet.returnVehicle(bicycle, 1);
    }

    fleet.listVehicles();
}
