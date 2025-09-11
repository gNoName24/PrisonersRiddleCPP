#pragma once

#include <cstdint>
#include <vector>
#include <random>
#include <string>
#include <algorithm>

#include <iostream>

namespace PrisonersRiddle {
    inline std::random_device rd;
    inline std::mt19937 gen(rd());

    using ArrayInt = uint16_t;
    using Array = std::vector<std::vector<ArrayInt>>;

    Array array_generate(int sizeX, int sizeY) {
        int total = sizeX * sizeY;

        std::vector<ArrayInt> values(total);
        for (int i = 0; i < total; i++) values[i] = i;

        std::shuffle(values.begin(), values.end(), gen);

        Array result(sizeX, std::vector<ArrayInt>(sizeY));
        int k = 0;
        for (int x = 0; x < sizeX; x++) {
            for (int y = 0; y < sizeY; y++) {
                result[x][y] = values[k++];
            }
        }
        return result;
    }

    void render_array(Array& array) {
        ArrayInt sizeX = array.size();
        ArrayInt sizeY = array[0].size();

        ArrayInt min = 0;
        ArrayInt max = sizeX * sizeY - 1;

        ArrayInt max_size = std::to_string(max).size(); // Длина max в плане символов

        std::string strf((sizeX * max_size) + sizeX + 1, '-');
        std::cout << strf << std::endl;
        for(int y = 0; y < sizeY; y++) {
            std::string str((sizeX * max_size) + sizeX, ' ');
            for(int x = 0; x < sizeX; x++) {
                str[x * (max_size + 1)] = '|';
                ArrayInt array_value = array[x][y] + 1;
                for(int i = 0; i < std::to_string(array_value).size(); i++) {
                    str[(x * (max_size + 1)) + i + 1] = std::to_string(array_value)[i];
                }
            }
            std::cout << str << "|" << std::endl;
            std::cout << strf << std::endl;
        }
    }

    struct Prisoner {
        ArrayInt number;
        bool found = false;
    };

    void step_array(Array& array, Prisoner& prisoner, bool start, int step_index, int& step_count) {
        ArrayInt sizeX = array.size();
        ArrayInt sizeY = array[0].size();
        ArrayInt min = 0;
        ArrayInt max = sizeX * sizeY - 1;
        step_count++;

        if(step_count >= 50) {
            return;
        }

        if(step_index < 0) return;
        if(step_index > max) {
            if(step_index - 1 >= 0 && step_index - 1 <= max) {
                step_index = step_index - 1;         // 1-based -> 0-based
            } else {
                step_index = step_index % (max + 1); // fallback: wrap
            }
        }

        ArrayInt x = step_index / sizeY; // x = index / cols
        ArrayInt y = step_index % sizeY; // y = index % cols

        ArrayInt next = array[x][y];
        if(next == prisoner.number) {
            prisoner.found = true;
            return;
        }
        step_array(array, prisoner, false, next, step_count);
    }

    void step(Array& array, Prisoner& prisoner) {
        ArrayInt sizeX = array.size();
        ArrayInt sizeY = array[0].size();
        ArrayInt min = 0;
        ArrayInt max = sizeX * sizeY - 1;

        //std::cout << "Ход заключенного " << prisoner.number << " | ";

        int step_count = 0;
        step_array(array, prisoner, true, prisoner.number, step_count);

        if(!prisoner.found) {
            //std::cout << "не ";
        }
        //std::cout << "нашлось за " << step_count << " ходов" << std::endl;
    }
};
