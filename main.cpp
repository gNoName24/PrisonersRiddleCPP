#include "PRCPP.hpp"

#include <stdlib.h>
#include <thread>
#include <chrono>
PrisonersRiddle::Grid grid;

thread_local std::random_device rd;
thread_local std::mt19937 gen(rd());

int main(int argc, char **argv) {
    int grid_width = 10, grid_heigth = 10;
    int repetitions_total = 100;
    int repetitions_sleep_milliseconds = 5;
    bool grid_render = true;

    std::cout << "Введите ширину поля: ";
    std::cin >> grid_width;

    std::cout << "Введите высота поля: ";
    std::cin >> grid_heigth;

    std::cout << "Введите общее число повторений: ";
    std::cin >> repetitions_total;

    std::cout << "Введите задержку между повторениями в миллисекуднах: ";
    std::cin >> repetitions_sleep_milliseconds;

    std::cout << "Рендерить ли поля?: ";
    std::cin >> grid_render;

    typedef std::chrono::steady_clock clock;
    clock::time_point start = clock::now();
    std::chrono::duration<double> elapsed;

    int repetitions_success = 0;
    for(int i = 0; i < repetitions_total; i++) {
        system("clear");

        clock::time_point now = clock::now();
        elapsed = now - start;

        std::cout << "Прошло " << elapsed.count() << " секунд\n\n";

        grid = PrisonersRiddle::grid_generate_random(grid_width, grid_heigth, gen);
        if(grid_render) {
            PrisonersRiddle::grid_render(grid);
        }

        int founds = 0;
        PrisonersRiddle::Grid grid_founds(grid.width, grid.height);
        for(int pi = 0; pi < grid.total(); pi++) {
            grid_founds.set_xy(pi % grid.width, pi / grid.width, 0);
            if(PrisonersRiddle::grid_prisonerfind(grid, pi, grid.total() / 2)) {
                grid_founds.set_xy(pi % grid.width, pi / grid.width, 1);
                founds++;
            }
        }

        std::cout << std::endl;
        if(grid_render) {
            PrisonersRiddle::grid_render(grid_founds);
        }

        std::cout << "Из " << grid.total() << " заключенных, " << founds << " нашли свой номер" << std::endl;

        if(founds == grid.total()) {
            repetitions_success++;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(repetitions_sleep_milliseconds));
    }

    system("clear");
    std::cout << "Из " << repetitions_total << " повторений, " << repetitions_success << " полностью нашли свой номер" << std::endl;

    std::cout << repetitions_success << " / " << repetitions_total << " = " <<
        (static_cast<double>(repetitions_success) / repetitions_total * 100.0)
        << "%" << std::endl;

    std::cout << "Время выполнения: " << elapsed.count() << " секунд";

    return 0;
}
