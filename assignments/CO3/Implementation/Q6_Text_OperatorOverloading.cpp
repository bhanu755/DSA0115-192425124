#include <cstring>
#include <iostream>
#include <string>
#include <utility>

class Text {
public:
    Text(const char* value = "")
        : length_(std::strlen(value == nullptr ? "" : value)),
          data_(new char[length_ + 1]) {
        std::strcpy(data_, value == nullptr ? "" : value);
    }

    Text(const Text& other)
        : length_(other.length_), data_(new char[other.length_ + 1]) {
        std::strcpy(data_, other.data_);
    }

    Text& operator=(const Text& other) {
        if (this != &other) {
            Text copy(other);
            swap(copy);
        }
        return *this;
    }

    ~Text() {
        delete[] data_;
    }

    Text operator+(const Text& other) const {
        std::string combined(data_);
        combined += other.data_;
        return Text(combined.c_str());
    }

    bool operator==(const Text& other) const {
        return std::strcmp(data_, other.data_) == 0;
    }

    bool operator!=(const Text& other) const {
        return !(*this == other);
    }

    friend std::ostream& operator<<(std::ostream& output, const Text& text) {
        output << text.data_;
        return output;
    }

private:
    void swap(Text& other) noexcept {
        std::swap(length_, other.length_);
        std::swap(data_, other.data_);
    }

    std::size_t length_;
    char* data_;
};

int main() {
    Text greeting("Hello, ");
    Text message("the appointment is confirmed.");
    Text fullMessage = greeting + message;
    std::cout << "Combined message: " << fullMessage << '\n';

    Text copiedMessage(fullMessage);
    copiedMessage = copiedMessage;
    std::cout << "Copied message: " << copiedMessage << '\n';
    std::cout << "Messages equal: " << std::boolalpha
              << (fullMessage == copiedMessage) << '\n';
    std::cout << "Different from greeting: " << (fullMessage != greeting) << '\n';

    Text empty;
    Text longMessage(
        "This is a longer SMS message demonstrating that Text can store "
        "messages beyond a short fixed-size character buffer.");
    std::cout << "Empty message: [" << empty << "]\n";
    std::cout << "Long message: " << longMessage << '\n';
}
