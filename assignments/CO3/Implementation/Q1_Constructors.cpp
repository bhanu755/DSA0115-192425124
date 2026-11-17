#include <iostream>
#include <stdexcept>
#include <string>

class Book {
public:
    Book() : Book("Untitled", "Unknown", 0) {}

    explicit Book(const std::string& title)
        : Book(title, "Donated", 1) {}

    Book(const std::string& title, const std::string& author, int copies)
        : title_(title), author_(author), copies_(copies) {
        if (copies < 0) {
            throw std::invalid_argument("The number of copies cannot be negative.");
        }
    }

    friend std::ostream& operator<<(std::ostream& output, const Book& book) {
        output << "Title: " << book.title_
               << ", Author: " << book.author_
               << ", Copies: " << book.copies_;
        return output;
    }

private:
    std::string title_;
    std::string author_;
    int copies_;
};

int main() {
    const Book defaultBook;
    const Book donatedBook("The Little Prince");
    const Book libraryBook("Clean Code", "Robert C. Martin", 4);

    std::cout << "Default book: " << defaultBook << '\n'
              << "Donated book: " << donatedBook << '\n'
              << "Library book: " << libraryBook << '\n';

    try {
        const Book invalidBook("Invalid", "Unknown", -2);
        std::cout << invalidBook << '\n';
    } catch (const std::invalid_argument& error) {
        std::cout << "Invalid book rejected: " << error.what() << '\n';
    }
}
