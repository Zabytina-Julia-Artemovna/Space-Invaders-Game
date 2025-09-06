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
        std::chrono::steady_clock::time_point _lastTime;

        std::chrono::steady_clock::time_point _lastShotTime;
        std::vector<Bullet> _invaders_bullets;
        bool _canShoot = false;
        const int _shootCooldown = 10000;
    public:
        virtual ~Alien() = default;
        Alien(int x, int y, char appearance, size_t cost,
            int right_border, int left_border)
            : GameObject(x, y, appearance),
            _cost(cost), _right_border(right_border),
            _left_border(left_border),
            _lastTime(std::chrono::steady_clock::now()) {}
        Alien() : Alien(0, 0, ' ', 0, 0, 0) {};
        void OnEvent(Event e, char c) override {
            if (e == Event::Timer) {
                auto currentTime = std::chrono::steady_clock::now();
                int durationTime = std::chrono::duration_cast<std::chrono::milliseconds>
                    (currentTime - _lastTime).count();
                durationTime = std::min<int>(durationTime, 100);
                _lastTime = currentTime;
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
                }
                else {
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
            if (e == Event::AlienShoot) {
                TryShoot(_position.x, _position.y);
            }
        }
        void TryShoot(int x, int y) { 
            if (_is_active) {
                auto currentTime = std::chrono::steady_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>
                    (currentTime - _lastShotTime).count();
                if (duration > _shootCooldown) {
                    _canShoot = true;
                }
                if (_canShoot) {
                    Bullet bullet(x, y + 1, false);
                    _invaders_bullets.push_back(bullet);
                    _canShoot = false;
                    _lastShotTime = currentTime;
                }
            }
        }
        size_t getBulletsCount() const {
            return _invaders_bullets.size();
        }
        std::vector<Bullet>& getBullets() {
            return _invaders_bullets;
        }
        std::chrono::steady_clock::time_point getLastShotTime() const {
            return _lastShotTime;
        }

        int getShootCooldown() const {
            return _shootCooldown;
        }
    };
}
