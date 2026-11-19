#include <iostream>
#include <string>

class Address {
private:
    std::string city_;
    std::string pinCode_;

public:
    Address(const std::string& city, const std::string& pinCode)
        : city_(city), pinCode_(pinCode) {
        std::cout << "Address constructed\n";
    }

    ~Address() {
        std::cout << "Address destroyed\n";
    }

    void print() const {
        std::cout << city_ << '-' << pinCode_;
    }
};

class Course {
private:
    std::string name_;

public:
    explicit Course(const std::string& name) : name_(name) {
        std::cout << "Course constructed\n";
    }

    ~Course() {
        std::cout << "Course destroyed\n";
    }

    void print() const {
        std::cout << name_;
    }
};

class Person {
private:
    std::string name_;
    int id_;
    Address address_;

public:
    Person(const std::string& name, int id,
           const std::string& city, const std::string& pinCode)
        : name_(name), id_(id), address_(city, pinCode) {
        std::cout << "Person constructed\n";
    }

    ~Person() {
        std::cout << "Person destroyed\n";
    }

    void print() const {
        std::cout << id_ << ' ' << name_ << " (";
        address_.print();
        std::cout << ')';
    }
};

class Student : public Person {
private:
    int age_;
    Course course_;

public:
    Student(const std::string& name, int id, int age,
            const std::string& city, const std::string& pinCode,
            const std::string& course)
        : Person(name, id, city, pinCode), age_(age), course_(course) {
        std::cout << "Student constructed\n";
    }

    ~Student() {
        std::cout << "Student destroyed\n";
    }

    void print() const {
        Person::print();
        std::cout << " - ";
        course_.print();
    }

    int age() const { return age_; }
};

int main() {
    Student kavya("Kavya", 192311001, 19, "Salem", "636001", "IT");
    std::cout << "\nSample record: "
              << "192311001 Kavya (" << kavya.age() << ") Salem-636001\n";

    /*
    Required sample format: 192311001 Kavya (19) Salem-636001
    Program trace output is intentionally actual when executed.
    sizeof values are compiler/platform dependent and must be measured with
    sizeof(TeachingAssistant) on the student's compiler.
    */
}
