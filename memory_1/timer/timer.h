#include <cassert>
#include <chrono>
#include <cmath>
#include <sstream>
#include <string>
#include <thread>

class Timer {
public:
    explicit Timer(std::chrono::duration<float> time_) : time(time_) {
        start = std::chrono::steady_clock::now();
    }
    bool Expired() {
        end = std::chrono::steady_clock::now();
        std::chrono::duration<float> duration = end - start;
        if (duration >= time) {
            return true;
        }
        return false;
    }
private:
    std::chrono::duration<float> time;
    std::chrono::time_point<std::chrono::steady_clock> start, end;
};

class TimeMeasurer {
public:
    explicit TimeMeasurer(std::ostream& ostream_) : Ostream(ostream_) {
        start = std::chrono::steady_clock::now();
    }
    ~TimeMeasurer() {
        end = std::chrono::steady_clock::now();
        std::chrono::duration<float, std::milli> time = end - start;
        long int s = static_cast<int>((time).count());
        Ostream << "Elapsed time: " << s << std::endl;
    }
private:
    std::chrono::time_point<std::chrono::steady_clock> start, end;
    std::ostream& Ostream;
};