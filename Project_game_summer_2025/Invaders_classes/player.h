#pragma once
#include "game_object.h"
#include <windows.h>
namespace Invaders {
    class Player : public GameObject {
    public:
        Player(int x, int y) : GameObject(x, y) {
            _appearance = 'W';
        }
        void OnEvent(Event e, char c) override {
            int newX =  _position.x;
            int newY =  _position.y;
            if ( (c == 'D' || c == 'd') && newX+1 < 208) {
                newX++;
            }
            else if ( (c == 'A' || c == 'a') && newX-1 > 0) {
                newX--;
            }
            UpdatePosition(newX, newY);
        }
        //void OnCollision(GameObject* other) override;
    };
}
