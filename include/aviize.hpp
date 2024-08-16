#include <cassert>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

namespace aviize {

const std::string ASCII_ESC_CLEAR_LINE = "\033[K";
const std::string ASCII_ESC_MOVE_UP    = "\033[F";

static std::ostream& out_stream = std::cerr;

void erase_line(std::ostream& os = out_stream)
{
    // move the cursor to the beginning of the current line and clear it
    os << ASCII_ESC_CLEAR_LINE;
    os << std::flush;
}

void erase_lines(size_t n_lines, std::ostream& os = out_stream)
{
    for (size_t i = 0; i < n_lines; i++) {
        os << ASCII_ESC_MOVE_UP;
        erase_line(os);
    }
}

std::string seconds_to_hhmmss_string(const double seconds)
{
    std::stringstream ss{};
    ss << std::setw(2) << std::setfill('0') << ((int)seconds / 60 / 60) % 60;
    ss << ":" << std::setw(2) << std::setfill('0') << ((int)seconds / 60) % 60;
    ss << ":" << std::setw(2) << std::setfill('0') << (int)seconds % 60;
    return ss.str();
}

class Progress {
private:
    std::chrono::time_point<std::chrono::steady_clock> last_update_time =
            std::chrono::steady_clock::now();

    double _get_eta_s(size_t n, const size_t update_period)
    {
        const std::chrono::time_point<std::chrono::steady_clock> now =
                std::chrono::steady_clock::now();
        const double us_per_update_period =
                std::chrono::duration_cast<std::chrono::microseconds>(
                        now - last_update_time)
                        .count();
        last_update_time         = now;
        const size_t remaining_n = n_max - n;
        const double eta_s =
                us_per_update_period / update_period * remaining_n / 1000000;
        return eta_s;
    }

public:
    char c_opening_bracket = '[';
    char c_closing_bracket = ']';
    char c_fill            = '.';
    char c_no_fill         = ' ';
    size_t c_bar_len       = 10;
    size_t update_period;
    size_t current_n;
    size_t n_min;
    size_t n_max;
    std::string text;

    Progress(size_t in_n_min, size_t in_n_max, size_t in_update_period = 1) :
        update_period(in_update_period),
        n_min(in_n_min),
        n_max(in_n_max)
    {
        assert(update_period > 0);
    }

    Progress() :
        Progress(0, 0)
    {
    }

    std::string str_progress_bar(size_t n)
    {
        assert(n >= n_min);
        assert(n <= n_max);

        // generate a string first and then write the whole string to `os`
        // to prevent blinking cursor from jumping all over the place
        std::stringstream ss;

        ss << c_opening_bracket;
        size_t n_fill = n / (double)(n_max - n_min) * c_bar_len;
        for (size_t i = 0; i < c_bar_len; i++) {
            if (i < n_fill) {
                ss << c_fill;
            }
            else {
                ss << c_no_fill;
            }
        }
        ss << c_closing_bracket;
        return ss.str();
    }

    std::string str_total(size_t n)
    {
        assert(n >= n_min);
        assert(n <= n_max);

        std::stringstream ss;
        const size_t n_max_strlen = std::to_string(n_max).length();
        ss << " " << std::setfill('0') << std::setw(n_max_strlen) << n;
        ss << "/" << n_max;
        return ss.str();
    }

    std::string str_pct(size_t n)
    {
        assert(n >= n_min);
        assert(n <= n_max);

        std::stringstream ss;
        ss << std::fixed << std::setprecision(1) << (double)n / n_max * 100
           << "%";
        return ss.str();
    }

    std::string str_eta(size_t n)
    {
        assert(n >= n_min);
        assert(n <= n_max);

        double eta_s = _get_eta_s(n, update_period);
        return seconds_to_hhmmss_string(eta_s);
    }

    void print()
    {
        std::stringstream ss;

        // if update_period specified:
        // to not overload the console - update only at update_period
        if (update_period > 1) {
            static size_t next_update_in = 0;

            if (next_update_in == 0) {
                next_update_in = update_period;
            }
            else {
                next_update_in--;
                return;
            }
        }

        // overwrite remalining command line with ' '
        const size_t n_chars = 5;
        for (size_t i = 0; i < n_chars; i++) {
            text += " ";
        }
        text += "\r";
        out_stream << text;
    }
};

}  // namespace aviize
