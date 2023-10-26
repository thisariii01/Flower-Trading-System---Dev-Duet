#include <chrono>
#include <iomanip>
#include <sstream>
#include <string>

using namespace std;
using namespace std::chrono;

class TimestampGenerator {
public:
    static string GenerateTimestamp() {
        auto now = system_clock::now();
        time_t time = system_clock::to_time_t(now);
        auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;
        struct tm timeInfo;
        localtime_s(&timeInfo, &time);

        ostringstream formattedDateTime;
        formattedDateTime << put_time(&timeInfo, "%Y-%m-%d %H:%M:%S:") << setfill('0') << setw(3) << ms.count();
        return formattedDateTime.str();
    }
};