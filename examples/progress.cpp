#include <chrono>
#include <iomanip>
#include <iostream>
#include <thread>

#include "aviize.hpp"

const size_t MAX_I    = 50000;
const size_t SLEEP_US = 60;

void sleep(size_t us)
{
    std::this_thread::sleep_for(std::chrono::microseconds(us));
}

int main()
{
    aviize::Progress p(0, MAX_I);

    std::cout << "test: all" << std::endl;
    std::stringstream ss{};
    for (size_t i = 0; i < MAX_I; i++) {
        p.text.clear();
        p.text += p.str_progress_bar(i);
        p.text += " ";
        p.text += p.str_total(i);
        p.text += " ";
        p.text += p.str_pct(i);
        p.text += " ";
        p.text += p.str_eta(i);
        p.text += " ";
        p.text += "text string and current i=" + std::to_string(i);
        p.print();
        sleep(SLEEP_US);
    }
    aviize::erase_line(p.text);
    p.print();

    std::cout << "test: progress bar" << std::endl;
    for (size_t i = 0; i < MAX_I; i++) {
        p.text.clear();
        p.text += p.str_progress_bar(i);
        p.print();
        sleep(SLEEP_US);
    }
    aviize::erase_line(p.text);
    p.print();

    std::cout << "test: total" << std::endl;
    for (size_t i = 0; i < MAX_I; i++) {
        p.text.clear();
        p.text += p.str_total(i);
        p.print();
        sleep(SLEEP_US);
    }
    aviize::erase_line(p.text);
    p.print();

    std::cout << "test: pct" << std::endl;
    for (size_t i = 0; i < MAX_I; i++) {
        p.text.clear();
        p.text += p.str_pct(i);
        p.print();
        sleep(SLEEP_US);
    }
    aviize::erase_line(p.text);
    p.print();

    std::cout << "test: eta" << std::endl;
    for (size_t i = 0; i < MAX_I; i++) {
        p.text.clear();
        p.text += p.str_eta(i);
        p.print();
        sleep(SLEEP_US);
    }
    aviize::erase_line(p.text);
    p.print();

    std::cout << "test: custom text" << std::endl;
    for (size_t i = 0; i < MAX_I; i++) {
        p.text.clear();
        p.text = "text string and current i=" + std::to_string(i);
        p.print();
        sleep(SLEEP_US);
    }
    aviize::erase_line(p.text);
    p.print();

    // clean up all previously printed lines
    aviize::erase_lines(p.text, 6);
    p.print();
    return 0;
}
