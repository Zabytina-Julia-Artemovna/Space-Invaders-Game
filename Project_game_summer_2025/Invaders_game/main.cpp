#include "player.h"
#include "bullet.h"
#include "alien.h"
#include "red_alien.h"
#include "white_alien.h"
#include "green_alien.h"
#include "alien_manager.h"
#include "collision_manager.h"
#include <windows.h>
#include <vector>
#include <iostream>
#include <conio.h>
#include <cctype> 
#include <memory>   
#include <algorithm>
char getCharWithTimeout() {
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    if (hStdin == INVALID_HANDLE_VALUE) {
        std::cerr << "Error getting console input handle\n";
        return 0;
    }
    DWORD waitResult = WaitForSingleObject(hStdin, 100);
    if (waitResult == WAIT_OBJECT_0) {
        if (_kbhit()) {
            char ch = _getch();
            return ch;
        }
    }
    return 0;
}
void MaximizeConsoleWindow() {
    HWND hConsole = GetConsoleWindow();
    ShowWindow(hConsole, SW_MAXIMIZE);
}
void HideCursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}
int main() {
    while (true) {
        MaximizeConsoleWindow();
        HideCursor();
        system("cls");
        std::cout << "\n";
        std::cout << "============================== SPACE INVADERS ==============================\n";
        system("pause");
        system("cls");
        Invaders::Player player(100, 7);
        Invaders::ConsoleDisplay console(200, 200);
        Invaders::AlienManager alienSwarm;
        alienSwarm.CreateAlienSwarm();
        while (true) {
            for (size_t i = 0; i < alienSwarm.getRedAliens().size(); ++i) {
                alienSwarm.getRedAliens()[i].ClearOn(console);
            }
            for (size_t i = 0; i < alienSwarm.getGreenAliens().size(); ++i) {
                alienSwarm.getGreenAliens()[i].ClearOn(console);
            }
            for (size_t i = 0; i < alienSwarm.getWhiteAliens().size(); ++i) {
                alienSwarm.getWhiteAliens()[i].ClearOn(console);
            }
            if (Invaders::CollisionManager::getInstance().checkCollisions(player, alienSwarm)) {
                if (player.isActive() == false) {
                    system("cls");
                    std::cout << "GAME OVER! INVADERS IS WIN!\n";
                    system("pause");
                    break;
                }
            }
            alienSwarm.removeDeadAliens();
            if (alienSwarm.isAliensDead()) {
                std::cout << "GAME OVER! YOU ARE WIN!\n";
                break;
            }
            player.ClearOn(console);
            player.DrawOn(console);

            for (size_t i = 0; i < player.getBulletsCount(); ++i) {
                player.getBullets()[i].ClearOn(console);
                if (player.getBullets()[i].isActive()) {
                    player.getBullets()[i].DrawOn(console);
                }
            }
            for (size_t i = 0; i < alienSwarm.getRedAliens().size(); ++i) {
                for (size_t j = 0; j < alienSwarm.getRedAliens()[i].getBulletsCount(); ++j) {
                    if (alienSwarm.getRedAliens()[i].getBullets()[j].isActive()) {
                        alienSwarm.getRedAliens()[i].getBullets()[j].ClearOn(console);
                        alienSwarm.getRedAliens()[i].getBullets()[j].DrawOn(console);
                    }
                }
            }
            for (size_t i = 0; i < alienSwarm.getGreenAliens().size(); ++i) {
                for (size_t j = 0; j < alienSwarm.getGreenAliens()[i].getBulletsCount(); ++j) {
                    if (alienSwarm.getGreenAliens()[i].getBullets()[j].isActive()) {
                        alienSwarm.getGreenAliens()[i].getBullets()[j].ClearOn(console);
                        alienSwarm.getGreenAliens()[i].getBullets()[j].DrawOn(console);
                    }
                }
            }
            for (size_t i = 0; i < alienSwarm.getWhiteAliens().size(); ++i) {
                for (size_t j = 0; j < alienSwarm.getWhiteAliens()[i].getBulletsCount(); ++j) {
                    if (alienSwarm.getWhiteAliens()[i].getBullets()[j].isActive()) {
                        alienSwarm.getWhiteAliens()[i].getBullets()[j].ClearOn(console);
                        alienSwarm.getWhiteAliens()[i].getBullets()[j].DrawOn(console);
                    }
                }
            }
            for (size_t i = 0; i < alienSwarm.getRedAliens().size(); ++i) {
                if (alienSwarm.getRedAliens()[i].isActive()) {
                    alienSwarm.getRedAliens()[i].ClearOn(console);
                    alienSwarm.getRedAliens()[i].DrawOn(console);
                }

            }
            for (size_t i = 0; i < alienSwarm.getGreenAliens().size(); ++i) {
                if (alienSwarm.getGreenAliens()[i].isActive()) {
                    alienSwarm.getGreenAliens()[i].ClearOn(console);
                    alienSwarm.getGreenAliens()[i].DrawOn(console);
                }

            }
            for (size_t i = 0; i < alienSwarm.getWhiteAliens().size(); ++i) {
                if (alienSwarm.getWhiteAliens()[i].isActive()) {
                    alienSwarm.getWhiteAliens()[i].ClearOn(console);
                    alienSwarm.getWhiteAliens()[i].DrawOn(console);
                }
            }
            console.flush();
            char symbol = getCharWithTimeout();
            if (symbol != 0) {
                player.OnEvent(Invaders::Event::KeyPress, symbol);
                for (size_t i = 0; i < player.getBulletsCount(); ++i) {
                    player.getBullets()[i].OnEvent(Invaders::Event::KeyPress, symbol);
                }
            }
            for (size_t i = 0; i < player.getBulletsCount(); ++i) {
                player.getBullets()[i].OnEvent(Invaders::Event::Timer, 0);
            }
            if (alienSwarm.canShoot()) {
                alienSwarm.getShooterAlien().OnEvent(Invaders::Event::AlienShoot, 0);
            }
            for (size_t i = 0; i < alienSwarm.getRedAliens().size(); ++i) {
                if (alienSwarm.getRedAliens()[i].isActive()) {
                    alienSwarm.getRedAliens()[i].OnEvent(Invaders::Event::Timer, 0);
                }
            }
            for (size_t i = 0; i < alienSwarm.getGreenAliens().size(); ++i) {
                if (alienSwarm.getGreenAliens()[i].isActive()) {
                    alienSwarm.getGreenAliens()[i].OnEvent(Invaders::Event::Timer, 0);
                }
            }
            for (size_t i = 0; i < alienSwarm.getWhiteAliens().size(); ++i) {
                if (alienSwarm.getWhiteAliens()[i].isActive()) {
                    alienSwarm.getWhiteAliens()[i].OnEvent(Invaders::Event::Timer, 0);
                }
            }
            for (size_t i = 0; i < alienSwarm.getRedAliens().size(); ++i) {
                for (size_t j = 0; j < alienSwarm.getRedAliens()[i].getBulletsCount(); ++j) {

                    alienSwarm.getRedAliens()[i].getBullets()[j].OnEvent(Invaders::Event::Timer, 0);
                }
            }
            for (size_t i = 0; i < alienSwarm.getGreenAliens().size(); ++i) {
                for (size_t j = 0; j < alienSwarm.getGreenAliens()[i].getBulletsCount(); ++j) {
                    alienSwarm.getGreenAliens()[i].getBullets()[j].OnEvent(Invaders::Event::Timer, 0);
                }
            }
            for (size_t i = 0; i < alienSwarm.getWhiteAliens().size(); ++i) {
                for (size_t j = 0; j < alienSwarm.getWhiteAliens()[i].getBulletsCount(); ++j) {
                    alienSwarm.getWhiteAliens()[i].getBullets()[j].OnEvent(Invaders::Event::Timer, 0);
                }
            }
            Sleep(50);
        }
    }
    return 0;
}
