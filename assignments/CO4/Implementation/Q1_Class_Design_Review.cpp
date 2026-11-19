#include <iostream>
#include <memory>
#include <string>
#include <vector>

/*
Hierarchy:
                    <<abstract>> Staff
                          |
       +------------------+------------------+
       |                  |                  |
   Professor       LabAssistant       GuestFaculty

Staff is abstract and provides the common identity and polymorphic pay()
interface. Public inheritance preserves the is-a relationship.
*/

class Staff {
private:
    std::string name_;
    int id_;

protected:
    Staff(const std::string& name, int id) : name_(name), id_(id) {}

public:
    virtual ~Staff() = default;

    const std::string& name() const { return name_; }
    int id() const { return id_; }
    virtual double pay() const = 0;
};

class Professor : public Staff {
private:
    double basic_;
    double research_;

public:
    Professor(const std::string& name, int id, double basic, double research)
        : Staff(name, id), basic_(basic), research_(research) {}

    double pay() const override {
        constexpr double allowanceRate = 0.42;
        return basic_ + basic_ * allowanceRate + research_;
    }
};

class LabAssistant : public Staff {
private:
    double basic_;

public:
    LabAssistant(const std::string& name, int id, double basic)
        : Staff(name, id), basic_(basic) {}

    double pay() const override {
        constexpr double allowanceRate = 0.42;
        return basic_ + basic_ * allowanceRate;
    }
};

class GuestFaculty : public Staff {
private:
    double hours_;
    double rate_;

public:
    GuestFaculty(const std::string& name, int id, double hours, double rate)
        : Staff(name, id), hours_(hours), rate_(rate) {}

    double pay() const override {
        return hours_ * rate_;
    }
};

int main() {
    std::vector<std::unique_ptr<Staff>> staff;
    staff.push_back(std::make_unique<Professor>("Anita", 101, 50000.0, 5000.0));
    staff.push_back(std::make_unique<LabAssistant>("Ravi", 102, 30000.0));
    staff.push_back(std::make_unique<GuestFaculty>("Meera", 103, 20.0, 1000.0));

    for (const auto& member : staff) {
        std::cout << member->name() << " (" << member->id() << "): "
                  << member->pay() << '\n';
    }

    /*
    Alternative type-code design: one class with a type field and switch in
    pay(). It is O(1) for a call, but adding a staff type requires changing
    the enum, fields, switch and construction code. The hierarchy is more
    maintainable because a new class can be added without changing old ones.
    */
}
