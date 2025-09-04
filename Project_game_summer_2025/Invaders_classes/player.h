#pragma once
#include "bullet.h"
#include "game_object.h"
#include <vector>
#include <windows.h>
namespace Invaders {
    class Player : public GameObject {
    private:
        std::vector<Bullet> _player_bullets;
        std::chrono::steady_clock::time_point _lastShotTime;
        bool _canShoot = false;
        const int _shootCooldown = 1000; 
    public:
        Player(int x, int y) : GameObject(x, y, 'O') {}
        void OnEvent(Event e, char c) override {
            if (e == Event::KeyPress) {
                int newX = _position.x;
                int newY = _position.y;
                if ((c == 'D' || c == 'd') && newX + 1 < 200) {
                    newX += 2;
                }
                else if ((c == 'A' || c == 'a') && newX - 1 > 0) {
                    newX -= 2;
                }
                else if (c == ' ') {
                    TryShoot(_position.x, _position.y);
                }
                UpdatePosition(newX, newY);
            }
            
        }
        void TryShoot(int x, int y) {
            auto currentTime = std::chrono::steady_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>
                (currentTime - _lastShotTime).count();

            if (duration > _shootCooldown) {
                _canShoot = true;
            }
            if (_canShoot) {
                Bullet bullet(x, y-1, true);
                _player_bullets.push_back(bullet);
            } 
            
        }
        size_t getBulletsCount() const {
            return _player_bullets.size();
        }
        std::vector<Bullet>& getBullets() {
            return _player_bullets;
        }
    };
}
