#pragma once
#include <chrono>
#include "game_object.h"
namespace Invaders {
    class Alien : public GameObject {
    protected:
        size_t _cost;
        int _speed = 1;
        int _right_border;
        int _left_border;
        std::chrono::steady_clock::time_point lastTime;
    public:
        virtual ~Alien() = default;
        Alien(int x, int y, char appearance, size_t cost,
            int right_border, int left_border)
            : GameObject(x, y, appearance),
            _cost(cost), _right_border(right_border),
            _left_border(left_border),
            lastTime(std::chrono::steady_clock::now()) {}
        void OnEvent(Event e, char c) override {
            auto currentTime = std::chrono::steady_clock::now();
            int durationTime = std::chrono::duration_cast<std::chrono::milliseconds>
                (currentTime - lastTime).count();
            durationTime = std::min<int>(durationTime, 100);
            lastTime = currentTime;
            int distance = (_speed * durationTime) / 64;
            if (distance == 0 && durationTime > 0) {
                distance = _speed > 0 ? 1 : -1;
            }
            int newX = _position.x;
            int newY = _position.y;
            if (_speed > 0) {
                if (newX + distance < _right_border) {
                    newX += distance;
                }
                else {
                    newY = _position.y + 1;
                    _speed *= -1;
                    newX = _right_border - 1;  
                }
            } else {
                if (newX + distance > _left_border) {
                    newX += distance;  
                }
                else {
                    newY = _position.y + 1;
                    _speed *= -1;
                    newX = _left_border + 1; 
                }
            }
            UpdatePosition(newX, newY);
        }
        virtual void Shoot() = 0;
    };
}
