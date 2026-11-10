#include <array>
#include <charconv>
#include <cstdint>
#include <iostream>
#include <limits>
#include <optional>
#include <string>
#include <string_view>
#include <system_error>

using MoneyPaise = std::int64_t;

constexpr MoneyPaise kMinimumBalancePaise = 5000;
constexpr MoneyPaise kPeakSurchargePaise = 1000;
constexpr int kConcessionPercent = 50;

enum class Zone : int { One = 1, Two = 2, Three = 3 };
enum class PassengerType { Adult, Student, Senior };

struct Passenger {
    PassengerType type;
};

struct Journey {
    Zone origin;
    Zone destination;
    int departureMinutes;
};

struct FareQuote {
    MoneyPaise baseFarePaise;
    MoneyPaise peakSurchargePaise;
    MoneyPaise concessionPaise;
    MoneyPaise totalPaise;
};

std::optional<MoneyPaise> parseMoney(std::string_view input) {
    if (input.empty()) {
        return std::nullopt;
    }

    const std::size_t decimalPoint = input.find('.');
    const std::string_view rupeesText = input.substr(0, decimalPoint);
    const std::string_view paiseText = decimalPoint == std::string_view::npos
        ? std::string_view{}
        : input.substr(decimalPoint + 1);

    if (rupeesText.empty() || (decimalPoint != std::string_view::npos &&
        (paiseText.empty() || paiseText.size() > 2))) {
        return std::nullopt;
    }

    std::uint64_t rupees = 0;
    const auto rupeeResult = std::from_chars(
        rupeesText.data(), rupeesText.data() + rupeesText.size(), rupees);
    if (rupeeResult.ec != std::errc{} ||
        rupeeResult.ptr != rupeesText.data() + rupeesText.size()) {
        return std::nullopt;
    }

    std::uint64_t paise = 0;
    if (!paiseText.empty()) {
        const auto paiseResult = std::from_chars(
            paiseText.data(), paiseText.data() + paiseText.size(), paise);
        if (paiseResult.ec != std::errc{} ||
            paiseResult.ptr != paiseText.data() + paiseText.size()) {
            return std::nullopt;
        }
        if (paiseText.size() == 1) {
            paise *= 10;
        }
    }

    const auto maxPaise = static_cast<std::uint64_t>(
        std::numeric_limits<MoneyPaise>::max());
    if (paise > 99 || rupees > (maxPaise - paise) / 100) {
        return std::nullopt;
    }
    return static_cast<MoneyPaise>(rupees * 100 + paise);
}

std::optional<int> parseTime(std::string_view input) {
    if (input.size() != 5 || input[2] != ':') {
        return std::nullopt;
    }
    for (std::size_t index : {0U, 1U, 3U, 4U}) {
        if (input[index] < '0' || input[index] > '9') {
            return std::nullopt;
        }
    }

    const int hours = (input[0] - '0') * 10 + (input[1] - '0');
    const int minutes = (input[3] - '0') * 10 + (input[4] - '0');
    if (hours > 23 || minutes > 59) {
        return std::nullopt;
    }
    return hours * 60 + minutes;
}

std::optional<Zone> parseZone(std::string_view input) {
    int value = 0;
    const auto result = std::from_chars(input.data(), input.data() + input.size(), value);
    if (result.ec != std::errc{} || result.ptr != input.data() + input.size() ||
        value < static_cast<int>(Zone::One) || value > static_cast<int>(Zone::Three)) {
        return std::nullopt;
    }
    return static_cast<Zone>(value);
}

std::optional<PassengerType> parsePassengerType(std::string_view input) {
    if (input == "adult") {
        return PassengerType::Adult;
    }
    if (input == "student") {
        return PassengerType::Student;
    }
    if (input == "senior") {
        return PassengerType::Senior;
    }
    return std::nullopt;
}

bool isPeakTime(int minutesAfterMidnight) {
    const bool morningPeak = minutesAfterMidnight >= 7 * 60 &&
        minutesAfterMidnight < 10 * 60;
    const bool eveningPeak = minutesAfterMidnight >= 17 * 60 &&
        minutesAfterMidnight < 20 * 60;
    return morningPeak || eveningPeak;
}

class FareTable {
public:
    static MoneyPaise fare(Zone origin, Zone destination) {
        constexpr std::array<std::array<MoneyPaise, 3>, 3> fares{{
            {{2000, 3000, 4000}},
            {{3000, 2000, 3000}},
            {{4000, 3000, 2000}},
        }};
        const auto originIndex = static_cast<std::size_t>(
            static_cast<int>(origin) - 1);
        const auto destinationIndex = static_cast<std::size_t>(
            static_cast<int>(destination) - 1);
        return fares[originIndex][destinationIndex];
    }
};

FareQuote calculateFare(const Passenger& passenger, const Journey& journey) {
    const MoneyPaise base = FareTable::fare(journey.origin, journey.destination);
    const MoneyPaise surcharge = isPeakTime(journey.departureMinutes)
        ? kPeakSurchargePaise
        : 0;
    const MoneyPaise grossFare = base + surcharge;
    const bool eligibleForConcession = passenger.type == PassengerType::Student ||
        passenger.type == PassengerType::Senior;
    const MoneyPaise concession = eligibleForConcession
        ? grossFare * kConcessionPercent / 100
        : 0;
    return {base, surcharge, concession, grossFare - concession};
}

class SmartCard {
public:
    explicit SmartCard(MoneyPaise initialBalancePaise)
        : balancePaise_(initialBalancePaise) {}

    MoneyPaise balancePaise() const {
        return balancePaise_;
    }

    bool payFare(MoneyPaise farePaise) {
        if (farePaise < 0 || balancePaise_ < kMinimumBalancePaise ||
            farePaise > balancePaise_ - kMinimumBalancePaise) {
            return false;
        }
        balancePaise_ -= farePaise;
        return true;
    }

private:
    MoneyPaise balancePaise_;
};

std::string formatMoney(MoneyPaise amountPaise) {
    const MoneyPaise rupees = amountPaise / 100;
    const MoneyPaise paise = amountPaise % 100;
    std::string result = "Rs." + std::to_string(rupees) + ".";
    if (paise < 10) {
        result += '0';
    }
    result += std::to_string(paise);
    return result;
}

bool expectTest(std::string_view name, bool passed) {
    std::cout << (passed ? "[PASS] " : "[FAIL] ") << name << '\n';
    return passed;
}

int runTests() {
    int failures = 0;
    const auto check = [&failures](std::string_view name, bool passed) {
        if (!expectTest(name, passed)) {
            ++failures;
        }
    };

    const Passenger adult{PassengerType::Adult};
    const Passenger student{PassengerType::Student};
    const Passenger senior{PassengerType::Senior};
    const auto quote = [](Passenger passenger, Zone origin, Zone destination,
                          std::string_view time) {
        return calculateFare(passenger, Journey{origin, destination, *parseTime(time)});
    };

    check("normal adult fare", quote(adult, Zone::One, Zone::Two, "10:00").totalPaise == 3000);
    check("all three zones fare table", FareTable::fare(Zone::One, Zone::Three) == 4000 &&
        FareTable::fare(Zone::Two, Zone::Two) == 2000 &&
        FareTable::fare(Zone::Three, Zone::One) == 4000);
    check("peak surcharge", quote(adult, Zone::One, Zone::One, "07:00").totalPaise == 3000);
    check("student concession", quote(student, Zone::One, Zone::Two, "10:00").totalPaise == 1500);
    check("senior concession", quote(senior, Zone::One, Zone::One, "10:00").totalPaise == 1000);

    SmartCard exactMinimumCard(8000);
    check("journey leaves exact Rs.50 minimum", exactMinimumCard.payFare(3000) &&
        exactMinimumCard.balancePaise() == kMinimumBalancePaise);
    SmartCard lowBalanceCard(7999);
    check("low balance is rejected without debit", !lowBalanceCard.payFare(3000) &&
        lowBalanceCard.balancePaise() == 7999);

    check("06:59 is outside peak", !isPeakTime(*parseTime("06:59")));
    check("07:00 starts morning peak", isPeakTime(*parseTime("07:00")));
    check("09:59 is inside morning peak", isPeakTime(*parseTime("09:59")));
    check("10:00 ends morning peak", !isPeakTime(*parseTime("10:00")));
    check("16:59 is outside evening peak", !isPeakTime(*parseTime("16:59")));
    check("17:00 starts evening peak", isPeakTime(*parseTime("17:00")));
    check("19:59 is inside evening peak", isPeakTime(*parseTime("19:59")));
    check("20:00 ends evening peak", !isPeakTime(*parseTime("20:00")));

    check("invalid time is rejected", !parseTime("24:00") && !parseTime("12:60"));
    check("invalid zone is rejected", !parseZone("0") && !parseZone("4") &&
        !parseZone("2x"));
    check("invalid money is rejected", !parseMoney("1.234") && !parseMoney("-1.00") &&
        !parseMoney("abc"));
    check("money uses exact paise", parseMoney("12.5") == 1250 &&
        parseMoney("12.05") == 1205);

    if (failures == 0) {
        std::cout << "All tests passed.\n";
        return 0;
    }
    std::cout << failures << " test(s) failed.\n";
    return 1;
}

std::optional<std::string> readLine(std::string_view prompt) {
    std::cout << prompt;
    std::string input;
    if (!std::getline(std::cin, input)) {
        return std::nullopt;
    }
    return input;
}

int runApplication() {
    const auto balanceInput = readLine("Card balance (Rs.): ");
    const auto balance = balanceInput ? parseMoney(*balanceInput) : std::nullopt;
    if (!balance || *balance < kMinimumBalancePaise) {
        std::cerr << "Invalid balance. Enter a non-negative amount with up to 2 decimals; "
                     "the card must have at least Rs.50.00.\n";
        return 1;
    }

    const auto passengerInput = readLine("Passenger type (adult/student/senior): ");
    const auto passengerType = passengerInput
        ? parsePassengerType(*passengerInput)
        : std::nullopt;
    if (!passengerType) {
        std::cerr << "Invalid passenger type.\n";
        return 1;
    }

    const auto originInput = readLine("Origin zone (1-3): ");
    const auto origin = originInput ? parseZone(*originInput) : std::nullopt;
    const auto destinationInput = readLine("Destination zone (1-3): ");
    const auto destination = destinationInput ? parseZone(*destinationInput) : std::nullopt;
    if (!origin || !destination) {
        std::cerr << "Invalid zone. Enter 1, 2, or 3.\n";
        return 1;
    }

    const auto timeInput = readLine("Departure time (HH:MM, 24-hour): ");
    const auto departureMinutes = timeInput ? parseTime(*timeInput) : std::nullopt;
    if (!departureMinutes) {
        std::cerr << "Invalid time. Use a valid 24-hour HH:MM time.\n";
        return 1;
    }

    const Passenger passenger{*passengerType};
    const Journey journey{*origin, *destination, *departureMinutes};
    const FareQuote quote = calculateFare(passenger, journey);
    SmartCard card(*balance);

    std::cout << "Base fare: " << formatMoney(quote.baseFarePaise) << '\n'
              << "Peak surcharge: " << formatMoney(quote.peakSurchargePaise) << '\n'
              << "Concession: " << formatMoney(quote.concessionPaise) << '\n'
              << "Fare due: " << formatMoney(quote.totalPaise) << '\n';

    if (!card.payFare(quote.totalPaise)) {
        std::cout << "Journey declined: at least Rs.50.00 must remain on the card.\n"
                  << "Card balance: " << formatMoney(card.balancePaise()) << '\n';
        return 2;
    }

    std::cout << "Journey approved.\n"
              << "Remaining balance: " << formatMoney(card.balancePaise()) << '\n';
    return 0;
}

int main(int argc, char* argv[]) {
    if (argc == 2 && std::string_view(argv[1]) == "--test") {
        return runTests();
    }
    if (argc != 1) {
        std::cerr << "Usage: metro_fare_system [--test]\n";
        return 1;
    }
    return runApplication();
}