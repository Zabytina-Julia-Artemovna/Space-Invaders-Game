#pragma once
#include "game_object.h"
namespace Invaders {
    class Bullet : public GameObject {
    private:
        bool _is_player_bullet;
        // �������� _direction = -1/1 ��� ����������� ����������� ����/�����
        //���������!
    public:
        Bullet(int x, int y, bool is_player_bullet) :
            GameObject(x, y), _is_player_bullet(is_player_bullet) {}
        bool isPlayerBullet() const {
            return _is_player_bullet;
        }
        //void Draw() const override;
        void Update() override;
        //void OnCollision(GameObject* other) override;
    };
}
