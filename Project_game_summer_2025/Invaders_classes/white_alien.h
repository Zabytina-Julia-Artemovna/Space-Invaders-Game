#pragma once
#include "alien.h"
namespace Invaders {
    class WhiteAlien : public Alien {
    public:
        WhiteAlien(int x, int y, int right_border,
            int left_border) :
            Alien(x, y, 'W', 50, right_border, left_border) {}
        WhiteAlien& operator=(const WhiteAlien& other) {
            if (this != &other) {
                _position = other._position;
                _is_active = other._is_active;
                _cost = other._cost;
                _speed = other._speed;
                _right_border = other._right_border;
                _left_border = other._left_border;
                _lastTime = other._lastTime;
                _lastShotTime = other._lastShotTime;
                _canShoot = other._canShoot;

                _invaders_bullets = other._invaders_bullets;
            }
            return *this;
        }

        
    };
}
