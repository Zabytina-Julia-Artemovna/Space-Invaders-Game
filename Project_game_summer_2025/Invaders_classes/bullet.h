#pragma once
#include "game_object.h"
#include <chrono>

namespace Invaders {
    class Bullet : public GameObject {
    private:
        int _speed = 1;
        bool _is_player_bullet;
        std::chrono::steady_clock::time_point lastTime;

    public:
        Bullet(int x, int y, bool is_player_bullet) :
            GameObject(x, y, 'O'), _is_player_bullet(is_player_bullet), 
            lastTime(std::chrono::steady_clock::now()) {}
        void OnEvent(Event e, char c) override {
            if (e == Event::Timer) {
                auto currentTime = std::chrono::steady_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>
                    (currentTime - lastTime).count();

                if (duration > 50) { 
                    lastTime = currentTime;

                    int newX = _position.x;
                    int newY = _position.y + (_is_player_bullet ? -_speed : _speed);

                    if (newY < -1 || newY > 100) {
                        _is_active = false;
                    }
                    else {
                        UpdatePosition(newX, newY);
                    }
                }
            }
        }
        bool isActive()  {
            return _is_active;
        }
    };
}
