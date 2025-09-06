#pragma once
#include "alien.h"
#include "red_alien.h"
#include "green_alien.h"
#include "white_alien.h"
#include "game_object.h"
#include <vector>
#include <algorithm>
#include <random>
#include <stdexcept>

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
        int findLowestRow() {
            if (!_redAliens.empty()) {
                return 0;
            }
            if (!_greenAliens.empty()) {
                return 1;
            }
            if (!_whiteAliens.empty()) {
                return 2;
            }
            return -1;
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
        bool canShoot() {
            try {
                Alien& shooter = getShooterAlien();
                auto currentTime = std::chrono::steady_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>
                    (currentTime - shooter.getLastShotTime()).count();
                return duration > shooter.getShootCooldown();
            }
            catch (...) {
                return false;
            }
        }
        Alien& getShooterAlien() {
            int lowestRow = findLowestRow();
            if (lowestRow == -1) {
                throw std::runtime_error("No active aliens");
            }
            int randomNumber;
            switch (lowestRow) {
            case 0:
                randomNumber = getRandomNumber(0, _redAliens.size() - 1);
                return _redAliens[randomNumber];
            case 1:
                randomNumber = getRandomNumber(0, _greenAliens.size() - 1);
                return _greenAliens[randomNumber];
            case 2:
                randomNumber = getRandomNumber(0, _whiteAliens.size() - 1);
                return _whiteAliens[randomNumber];
            default:
                throw std::runtime_error("Invalid row");
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
