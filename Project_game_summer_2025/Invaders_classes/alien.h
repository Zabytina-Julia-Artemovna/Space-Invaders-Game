#pragma once
#include "game_object.h"
namespace Invaders {
    enum class AlienType {
        SMALL,
        MEDIUM,
        LARGE
    };
    class Alien : public GameObject {
    private:
        AlienType _type;
        char _alien_appearance;
        size_t _cost;
    public:
        Alien(int x, int y, AlienType type) :
            GameObject(x, y), _type(type) {
            switch (_type) {
            case AlienType::SMALL:
                _alien_appearance = 's';
                _cost = 10;
                break;
            case AlienType::MEDIUM:
                _alien_appearance = 'm';
                _cost = 20;
                break;
            case AlienType::LARGE:
                _alien_appearance = 'l';
                _cost = 30;
                break;
            }
        }
        AlienType getType() const {
            return _type;
        }
        char getAppearance() const {
            return _alien_appearance;
        }
        size_t getCost() const {
            return _cost;
        }
        void Shoot();
        //void OnCollision(GameObject* other) override;
        //void Draw() const override;
        void Update() override;
    };
}
