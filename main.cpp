#include "PRCPP.hpp"

#include <stdlib.h>
#include <thread>
#include <chrono>
PrisonersRiddle::Grid grid;

int main(int argc, char **argv) {
    int total_repetitions = 734;

    int total_repetitions_success = 0;
    for(int i = 0; i < total_repetitions; i++) {
        system("clear");
        grid = PrisonersRiddle::grid_generate_random(10, 10);
        PrisonersRiddle::grid_render(grid);

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
        PrisonersRiddle::grid_render(grid_founds);

        std::cout << "Из " << grid.total() << " заключенных, " << founds << " нашли свой номер" << std::endl;

        if(founds == grid.total()) {
            total_repetitions_success++;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(0));
    }

    system("clear");
    std::cout << "Из " << total_repetitions << " повторений, " << total_repetitions_success << " полностью нашли свой номер" << std::endl;

    std::cout << total_repetitions_success << " / " << total_repetitions << " = " <<
        (static_cast<double>(total_repetitions_success) / total_repetitions * 100.0)
        << "%" << std::endl;

    return 0;
}
