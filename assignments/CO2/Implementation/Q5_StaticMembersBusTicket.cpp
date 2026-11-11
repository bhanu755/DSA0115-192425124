#include <iostream>
#include <string>

class Token {
    static int next;
    int id;

public:
    Token() : id(++next) {}

    int get() const {
        return id;
    }

    static int issued() {
        return next - 100;
    }
};

int Token::next = 100;

class BusTicket {
    static int issued_;
    static const int capacity_ = 3;
    int seat_;
    std::string name_;

public:
    explicit BusTicket(const std::string& name) : seat_(0), name_(name) {
        if (issued_ < capacity_) {
            seat_ = ++issued_;
        }
    }

    static int count() {
        return issued_;
    }

    void print() const {
        std::cout << name_ << ": "
                  << (seat_ ? "Seat " + std::to_string(seat_) : std::string("Waiting"))
                  << '\n';
    }
};

int BusTicket::issued_ = 0;

void createTicketsInFunction(const std::string& name) {
    const BusTicket tickets[] = {BusTicket(name)};
    tickets[0].print();
    std::cout << "Issued: " << BusTicket::count() << '\n';
}

int main(int argc, char* argv[]) {
    if (argc == 2 && std::string(argv[1]) == "--tokens") {
        Token counter[3];
        Token extra;
        std::cout << counter[0].get() << ' ' << counter[2].get() << ' '
                  << extra.get() << ' ' << Token::issued() << '\n';
        return 0;
    }

    if (argc == 2 && std::string(argv[1]) == "--twice") {
        createTicketsInFunction("First trip");
        createTicketsInFunction("Second trip");
        return 0;
    }

    if (argc != 1) {
        std::cerr << "Usage: Q5_StaticMembersBusTicket [--tokens|--twice]\n";
        return 1;
    }

    BusTicket trip[] = {
        BusTicket("Asha"), BusTicket("Bala"), BusTicket("Chitra"), BusTicket("Dev")};
    for (const BusTicket& ticket : trip) {
        ticket.print();
    }
    std::cout << "Issued: " << BusTicket::count() << '\n';
}