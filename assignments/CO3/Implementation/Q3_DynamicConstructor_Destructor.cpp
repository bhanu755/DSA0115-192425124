#include <iostream>
#include <stdexcept>

class Auditorium {
public:
    Auditorium(int rows, int columns)
        : rows_(rows > 0 && columns > 0 ? rows : 0),
          columns_(rows > 0 && columns > 0 ? columns : 0),
          seats_(nullptr),
          bookedCount_(0) {
        if (rows_ == 0) {
            std::cout << "Created an empty auditorium.\n";
            return;
        }

        seats_ = new bool*[rows_]{};
        try {
            for (int row = 0; row < rows_; ++row) {
                seats_[row] = new bool[columns_]{};
            }
        } catch (...) {
            for (int row = 0; row < rows_; ++row) {
                delete[] seats_[row];
            }
            delete[] seats_;
            seats_ = nullptr;
            throw;
        }
        std::cout << "Created an auditorium with " << rows_ << " rows and "
                  << columns_ << " seats per row.\n";
    }

    Auditorium(const Auditorium&) = delete;
    Auditorium& operator=(const Auditorium&) = delete;

    ~Auditorium() {
        for (int row = 0; row < rows_; ++row) {
            delete[] seats_[row];
        }
        delete[] seats_;
        std::cout << "Auditorium cleanup: " << bookedCount_
                  << " seat(s) still booked.\n";
    }

    bool bookSeat(int row, int column) {
        if (!isValidSeat(row, column) || seats_[row][column]) {
            return false;
        }
        seats_[row][column] = true;
        ++bookedCount_;
        return true;
    }

    bool cancelSeat(int row, int column) {
        if (!isValidSeat(row, column) || !seats_[row][column]) {
            return false;
        }
        seats_[row][column] = false;
        --bookedCount_;
        return true;
    }

private:
    bool isValidSeat(int row, int column) const {
        return row >= 0 && row < rows_ && column >= 0 && column < columns_;
    }

    int rows_;
    int columns_;
    bool** seats_;
    int bookedCount_;
};

int main() {
    Auditorium mainHall(3, 5);
    std::cout << "Book seat (0, 1): "
              << (mainHall.bookSeat(0, 1) ? "success" : "failed") << '\n';
    std::cout << "Cancel seat (0, 1): "
              << (mainHall.cancelSeat(0, 1) ? "success" : "failed") << '\n';

    {
        Auditorium smallHall(1, 2);
        smallHall.bookSeat(0, 0);
    }

    Auditorium emptyHall(0, 5);
    Auditorium* heapHall = new Auditorium(2, 2);
    heapHall->bookSeat(1, 1);
    delete heapHall;
}
