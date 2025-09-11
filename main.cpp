#include "PRCPP.hpp"

uint16_t sizeX = 10;
uint16_t sizeY = 10;
uint16_t size = sizeX * sizeY;
PrisonersRiddle::Array array = PrisonersRiddle::array_generate(sizeX, sizeY);
std::vector<PrisonersRiddle::Prisoner> prisoners(size);

int main(int argc, char **argv) {
    //PrisonersRiddle::render_array(array);

    for(int c = 0; c < 10; c++) {
        std::cout << std::endl << "Попытка " << (c + 1) << std::endl;
        PrisonersRiddle::Array array = PrisonersRiddle::array_generate(sizeX, sizeY);
        int founds = 0;
        for(int i = 0; i < size; i++) {
            prisoners[i].number = i;
            PrisonersRiddle::step(array, prisoners[i]);
            if(prisoners[i].found) {
                founds++;
            }
        }

        std::cout << "Из всех " << size << " заключенных, только " << founds << " нашли свой номер, используя цикл" << std::endl;
        if(founds == size) {
            std::cout << "Молодцы, всех отпускаем" << std::endl;
        } else {
            std::cout << (size - founds) << " не нашли свой номер, и из-за них все пойдут на смертную казнь" << std::endl;
        }
    }

    return 0;
}
