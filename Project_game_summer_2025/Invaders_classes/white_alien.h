#pragma once
#include "alien.h"
namespace Invaders {
    class WhiteAlien : public Alien {
    public:
        WhiteAlien(int x, int y, int right_border,
            int left_border) :
            Alien(x, y, 'G', 10, right_border, left_border) {}
        void Shoot() override {

        }

    };
}
