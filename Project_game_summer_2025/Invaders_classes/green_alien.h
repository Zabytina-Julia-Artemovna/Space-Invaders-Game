#pragma once
#include "alien.h"
namespace Invaders {
    class GreenAlien : public Alien {
    public:
        GreenAlien(int x, int y, int right_border,
            int left_border) :
            Alien(x, y, 'G', 25, right_border, left_border) {}
       

        
    };
}
