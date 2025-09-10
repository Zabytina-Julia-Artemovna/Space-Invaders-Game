#pragma once
#include "alien.h"
namespace Invaders {
    class RedAlien : public Alien {
    public:
        RedAlien(int x, int y, int right_border,
            int left_border) :
            Alien(x, y, 'R', 100, right_border, left_border) {}
        
        
        };
        
    };

