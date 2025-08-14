#pragma once
#include "alien.h"
namespace Invaders {
    class GreenAlien : public Alien {
    public:
        GreenAlien(int x, int y, int right_border,
            int left_border) :
            Alien(x, y, 'G', 10, right_border, left_border) {}
        void Shoot() override {

        }

    };
}