#include <iostream>
#include <string>

class Person {
protected:
    std::string name_;
    int id_;
    std::string phone_;

public:
    Person(const std::string& name, int id, const std::string& phone)
        : name_(name), id_(id), phone_(phone) {}

    virtual ~Person() = default;

    const std::string& name() const { return name_; }
};

class Student : virtual public Person {
protected:
    std::string programme_;
    double cgpa_;

public:
    Student(const std::string& name, int id, const std::string& phone,
            const std::string& programme, double cgpa)
        : Person(name, id, phone), programme_(programme), cgpa_(cgpa) {}
};

class Staff : virtual public Person {
protected:
    std::string department_;
    double salary_;

public:
    Staff(const std::string& name, int id, const std::string& phone,
          const std::string& department, double salary)
        : Person(name, id, phone), department_(department), salary_(salary) {}
};

class TeachingAssistant : public Student, public Staff {
public:
    TeachingAssistant(const std::string& name, int id, const std::string& phone,
                      const std::string& programme, double cgpa,
                      const std::string& department, double salary)
        : Person(name, id, phone),
          Student(name, id, phone, programme, cgpa),
          Staff(name, id, phone, department, salary) {}
};

namespace non_virtual_inheritance {
    struct Person {
        Person() { std::cout << "Person "; }
    };

    struct Student : Person {
        Student() { std::cout << "Student "; }
    };

    struct Staff : Person {
        Staff() { std::cout << "Staff "; }
    };

    struct TeachingAssistant : Student, Staff {
        TeachingAssistant() { std::cout << "TA "; }
    };
}

namespace virtual_inheritance_trace {
    struct Person {
        Person() { std::cout << "Person "; }
    };

    struct Student : virtual Person {
        Student() { std::cout << "Student "; }
    };

    struct Staff : virtual Person {
        Staff() { std::cout << "Staff "; }
    };

    struct TeachingAssistant : Student, Staff {
        TeachingAssistant() { std::cout << "TA "; }
    };
}

class ResearchScholar : public Student {
private:
    double fellowship_;

public:
    ResearchScholar(const std::string& name, int id, const std::string& phone,
                    const std::string& programme, double cgpa, double fellowship)
        : Person(name, id, phone),
          Student(name, id, phone, programme, cgpa),
          fellowship_(fellowship) {}
};

int main() {
    TeachingAssistant ta("Kavya", 192311001, "9876543210",
                         "Information Technology", 9.1,
                         "IT", 35000.0);
    ResearchScholar rs("Arun", 192311002, "9123456780",
                       "Computer Science", 8.7, 25000.0);

    std::cout << "Virtual inheritance: " << ta.name() << '\n';
    std::cout << "Research scholar: " << rs.name() << '\n';
    std::cout << "TeachingAssistant has one shared Person subobject.\n";
    std::cout << "Virtual construction: ";
    virtual_inheritance_trace::TeachingAssistant virtualTa;
    std::cout << '\n';

    non_virtual_inheritance::TeachingAssistant nonVirtualTa;
    std::cout << "\nNon-virtual construction order is Person, Student, Person, Staff, TA.\n";

    /*
    Access table:
    Person public member: public Student -> public, protected Student ->
    protected, private Student -> private.
    Person protected member: protected in public/protected/private
    inheritance depending on the derived access level.
    Person private member: not accessible directly from derived classes.

    With virtual inheritance, constructors print:
    Person Student Staff TeachingAssistant
    Without virtual inheritance:
    Person Student Person Staff TeachingAssistant

    Multiple inheritance creates a diamond when both branches are separate.
    Composition avoids ambiguity, but uses has-a and keeps two separate
    Student/Staff objects. sizeof() is compiler and platform dependent.
    */
}
