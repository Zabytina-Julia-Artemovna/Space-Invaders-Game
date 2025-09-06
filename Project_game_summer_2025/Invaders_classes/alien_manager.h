#pragma once
#include "alien.h"
#include "red_alien.h"
#include "green_alien.h"
#include "white_alien.h"
#include "game_object.h"
#include <vector>
#include <algorithm>
#include <random>
namespace Invaders {
    class AlienManager {
    private:
        std::vector<Invaders::RedAlien> _redAliens;
        std::vector<Invaders::GreenAlien> _greenAliens;
        std::vector<Invaders::WhiteAlien> _whiteAliens;
        int getRandomNumber(int min, int max) {
            static std::random_device rd;
            static std::mt19937 gen(rd());
            std::uniform_int_distribution<> distrib(min, max);
            return distrib(gen);
        }
    public:
        void CreateAlienSwarm() {
            int countRed = 0;
            int coordXred = 10;
            while (countRed < 10) {
                _redAliens.push_back(Invaders::RedAlien(coordXred, 0, 150, 0));
                countRed++;
                coordXred--;
            }
            int countGreen = 0;
            int coordXgreen = 10;
            while (countGreen < 10) {
                _greenAliens.push_back(Invaders::GreenAlien(coordXgreen, 1, 150, 0));
                countGreen++;
                coordXgreen--;
            }
            int countWhite = 0;
            int coordXwhite = 10;
            while (countWhite < 10) {
                _whiteAliens.push_back(Invaders::WhiteAlien(coordXwhite, 2, 150, 0));
                countWhite++;
                coordXwhite--;
            }
        }
        std::vector<Invaders::RedAlien>& getRedAliens() {
            return _redAliens;
        }
        std::vector<Invaders::GreenAlien>& getGreenAliens() {
            return _greenAliens;
        }
        std::vector<Invaders::WhiteAlien>& getWhiteAliens() {
            return _whiteAliens;
        }
    };
}
