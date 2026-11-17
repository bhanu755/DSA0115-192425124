#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

class Time {
public:
    Time() : totalSeconds_(0) {}

    Time(int hours, int minutes, int seconds) {
        if (hours < 0 || minutes < 0 || minutes > 59 ||
            seconds < 0 || seconds > 59) {
            throw std::invalid_argument("Invalid time value.");
        }
        totalSeconds_ = static_cast<long long>(hours) * 3600 +
                        minutes * 60 + seconds;
    }

    Time& operator++() {
        ++totalSeconds_;
        return *this;
    }

    Time operator++(int) {
        Time previous(*this);
        ++(*this);
        return previous;
    }

    bool operator==(const Time& other) const {
        return totalSeconds_ == other.totalSeconds_;
    }

    bool operator<(const Time& other) const {
        return totalSeconds_ < other.totalSeconds_;
    }

    friend std::ostream& operator<<(std::ostream& output, const Time& time) {
        const long long hours = time.totalSeconds_ / 3600;
        const int minutes = static_cast<int>((time.totalSeconds_ / 60) % 60);
        const int seconds = static_cast<int>(time.totalSeconds_ % 60);
        output << hours << ':' << std::setfill('0') << std::setw(2) << minutes
               << ':' << std::setw(2) << seconds << std::setfill(' ');
        return output;
    }

private:
    long long totalSeconds_;
};

class Playlist {
public:
    Playlist(std::initializer_list<std::string> tracks) : tracks_(tracks) {}

    std::string& operator[](std::size_t index) {
        return tracks_.at(index);
    }

    const std::string& operator[](std::size_t index) const {
        return tracks_.at(index);
    }

    std::size_t size() const {
        return tracks_.size();
    }

private:
    std::vector<std::string> tracks_;
};

int main() {
    Time timer(0, 0, 5);
    const Time previous = timer++;
    std::cout << "Postfix: old value " << previous << ", current value " << timer << '\n';
    const Time prefix = ++timer;
    std::cout << "Prefix: returned value " << prefix << ", current value " << timer << '\n';

    Time almostOneHour(0, 59, 59);
    std::cout << "Before rollover: " << almostOneHour << '\n';
    ++almostOneHour;
    std::cout << "After rollover: " << almostOneHour << '\n';
    std::cout << "Timer < 01:00:00: "
              << (timer < almostOneHour) << '\n';
    std::cout << "Equal times: " << (timer == Time(0, 0, 7)) << '\n';

    Playlist playlist{"Opening Track", "Interlude", "Final Track"};
    playlist[1] = "Updated Interlude";
    std::cout << "Playlist track 2: " << playlist[1] << '\n';
    const Playlist& readOnlyPlaylist = playlist;
    std::cout << "Playlist contains " << readOnlyPlaylist.size()
              << " tracks; track 1: " << readOnlyPlaylist[0] << '\n';

    try {
        std::cout << playlist[playlist.size()] << '\n';
    } catch (const std::out_of_range& error) {
        std::cout << "Invalid playlist index: " << error.what() << '\n';
    }
}
