#pragma once
#include <chrono>
#include "game_object.h"
namespace Invaders {
    std::chrono::steady_clock::time_point lastTime;
    enum class AlienType {
        SMALL,
        MEDIUM,
        LARGE
    };
    class Alien : public GameObject {
    private:
        AlienType _type; 
        size_t _cost;
        int _speed = 2;
    public:
        Alien(int x, int y, AlienType type) :
            GameObject(x, y), _type(type) {
            switch (_type) {
            case AlienType::SMALL:
                _appearance = 'S';
                _cost = 10;
                break;
            case AlienType::MEDIUM:
                _appearance = 'M';
                _cost = 20;
                break;
            case AlienType::LARGE:
                _appearance = 'L';
                _cost = 30;
                break;
            }
        }
        void OnEvent(Event e, char c) override
        {
            static auto lastTime = std::chrono::steady_clock::now();
            auto currentTime = std::chrono::steady_clock::now();
            int durationTime =
                std::chrono::duration_cast<std::chrono::milliseconds>
                (currentTime - lastTime).count();
            lastTime = currentTime;
            int distance = (_speed * durationTime) / 16;  // Регулируйте делитель
            int newX = _position.x;
            int newY = _position.y;
            if (_speed > 0) {
                if (newX + distance < 208) {
                    newX += distance;
                } else {
                    newY++;
                    _speed *= -1;
                    newX = 207;  // Фиксация у правой границы
                }
            }
            else if (_speed < 0) {
                if (newX + distance > 0) {
                    newX += distance;
                }
                else {
                    newY++;
                    _speed *= -1;
                    newX = 1;  // Фиксация у левой границы
                }
            }
            UpdatePosition(newX, newY);
        }
        void Shoot();
        //void OnCollision(GameObject* other) override;
    };
}
