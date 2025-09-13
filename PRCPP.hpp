#pragma once

#include <cstdint>
#include <vector>
#include <random>
#include <string>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <numeric>

namespace PrisonersRiddle {
    using index_t = uint32_t;
    using size_type = std::size_t;

    struct Grid {
        size_type width{};
        size_type height{};
        std::vector<index_t> data;

        Grid() = default;
        Grid(size_type w, size_type h) : width(w), height(h), data(w * h) {}

        size_type total() const noexcept { return width * height; }
        bool empty() const noexcept { return data.empty(); }

        index_t at_flat(index_t idx) const noexcept {
            return data[idx];
        }
        index_t at_xy(size_type x, size_type y) const noexcept {
            return data[y * width + x];
        }

        void set_xy(size_type x, size_type y, index_t v) noexcept {
            data[y * width + x] = v;
        }
    };

    // 0..total-1
    inline Grid grid_generate_random(size_type width, size_type height, std::mt19937 &gen) {
        Grid grid(width, height);
        std::iota(grid.data.begin(), grid.data.end(), 0u);
        std::shuffle(grid.data.begin(), grid.data.end(), gen);
        return grid;
    }
    inline Grid grid_generate_random(size_type width, size_type height) {
        static thread_local std::random_device rd;
        static thread_local std::mt19937 gen(rd());
        return grid_generate_random(width, height, gen);
    }

    inline void grid_render(const Grid& grid) {
        if(grid.empty()) {
            std::cout << "Grid пустой" << std::endl;
            return;
        }

        size_type total = grid.total();
        index_t max_value = static_cast<index_t>(total > 0 ? total - 1 : 0) + 1;
        size_type max_width = std::to_string(max_value).size();

        std::string line;
        line.reserve((max_width + 1) * grid.width + 1);
        for (size_type i = 0; i < grid.width; ++i) {
            line += '+'; line += std::string(max_width, '-');
        }
        line += '+';
        std::cout << line << '\n';

        for(size_type y = 0; y < grid.height; ++y) {
            for(size_type x = 0; x < grid.width; ++x) {
                index_t v = grid.at_xy(x, y) + 1;
                std::cout << '|' << std::setw(static_cast<int>(max_width)) << v;
            }
            std::cout << '|' << '\n' << line << '\n';
        }
    }

    inline bool grid_prisonerfind(const Grid &grid, index_t prisoner_number, size_type max_steps) {
        if(grid.empty()) {
            std::cout << "Grid пустой" << std::endl;
            return false;
        }
        const size_type total = grid.total();
        if(static_cast<size_type>(prisoner_number) >= total) {
            std::cout << "Число заключенного больше чем количество ячеек в grid" << std::endl;
            return false;
        }

        std::vector<char> visited(total, 0);
        index_t idx = prisoner_number;
        for(size_type step = 0; step < max_steps; ++step) {
            if(grid.at_flat(idx) == prisoner_number) { // Заключенный нашел свой номер
                return true;
            }
            if(visited[idx]) { // Заключенный не нашел свой номер
                return false;
            }
            visited[idx] = 1;
            idx = grid.at_flat(idx);
        }
        return false;
    }
};
