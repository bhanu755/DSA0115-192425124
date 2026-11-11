#include <chrono>
#include <iostream>
#include <string>

class Time {
public:
    Time(int hours, int minutes) : hours_(hours), minutes_(minutes) {}

    friend inline int minutesBetween(const Time& first, const Time& second);
    friend inline bool earlier(const Time& first, const Time& second);
    friend int minutesBetweenWithoutInline(const Time& first, const Time& second);

private:
    int hours_;
    int minutes_;
};

inline int minutesBetween(const Time& first, const Time& second) {
    const int firstTotal = first.hours_ * 60 + first.minutes_;
    const int secondTotal = second.hours_ * 60 + second.minutes_;
    return firstTotal > secondTotal
        ? firstTotal - secondTotal
        : secondTotal - firstTotal;
}

inline bool earlier(const Time& first, const Time& second) {
    return first.hours_ * 60 + first.minutes_ < second.hours_ * 60 + second.minutes_;
}

int minutesBetweenWithoutInline(const Time& first, const Time& second) {
    const int firstTotal = first.hours_ * 60 + first.minutes_;
    const int secondTotal = second.hours_ * 60 + second.minutes_;
    return firstTotal > secondTotal
        ? firstTotal - secondTotal
        : secondTotal - firstTotal;
}

void runBenchmark() {
    const Time first(9, 45);
    const Time second(13, 10);
    constexpr int repetitions = 10000000;
    volatile int result = 0;

    const auto inlineStart = std::chrono::steady_clock::now();
    for (int index = 0; index < repetitions; ++index) {
        result = minutesBetween(first, second);
    }
    const auto inlineEnd = std::chrono::steady_clock::now();

    const auto regularStart = std::chrono::steady_clock::now();
    for (int index = 0; index < repetitions; ++index) {
        result = minutesBetweenWithoutInline(first, second);
    }
    const auto regularEnd = std::chrono::steady_clock::now();

    const auto inlineNanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(
        inlineEnd - inlineStart).count();
    const auto regularNanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(
        regularEnd - regularStart).count();
    std::cout << "10,000,000 inline calls: " << inlineNanoseconds << " ns\n"
              << "10,000,000 non-inline calls: " << regularNanoseconds << " ns\n"
              << "Result guard: " << result << '\n';
}

int main(int argc, char* argv[]) {
    if (argc == 2 && std::string(argv[1]) == "--benchmark") {
        runBenchmark();
        return 0;
    }
    if (argc != 1) {
        std::cerr << "Usage: Q6_FriendInlineTime [--benchmark]\n";
        return 1;
    }

    const Time departure(9, 45);
    const Time arrival(13, 10);
    std::cout << minutesBetween(departure, arrival) << ' '
              << std::boolalpha << earlier(arrival, departure) << '\n';

    const Time sameTime(12, 0);
    const Time beforeNoon(11, 55);
    const Time afterNoon(12, 5);
    std::cout << "same time difference: " << minutesBetween(sameTime, sameTime) << '\n'
              << "before noon is earlier: " << earlier(beforeNoon, afterNoon) << '\n';
}