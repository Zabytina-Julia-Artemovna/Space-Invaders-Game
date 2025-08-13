#pragma once
#include "game_object.h"
namespace Invaders {
    class Player : public GameObject {
    private:
        char _player_appearance = '^';
    public:
        Player(int x, int y) : GameObject(x, y) {}
        char getAppearance() const {
            return _player_appearance;
        }
        void Shoot(); // возвращает void или Bullet* ?
        void MoveLeft();
        void MoveRight();
        //void OnCollision(GameObject* other) override;
        //void DrawOn() const override;
        void Update() override;
    };
}

