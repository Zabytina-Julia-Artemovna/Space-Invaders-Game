#pragma once
#include <vector>
#include "player.h"
#include "alien_manager.h"
namespace Invaders {
    class CollisionManager {
    private:
        CollisionManager() = default;
    public:
        CollisionManager(const CollisionManager&) = delete;
        CollisionManager& operator=(const CollisionManager&) = delete;

        static CollisionManager& getInstance() {
            static CollisionManager instance;
            return instance;
        }
        bool checkCollisions(Player& player, Alien& alien) {
            if (checkPlayerVsAlien()) {
                return true;
            }
            if (checkPlayerVsBullet()) {
                return true;
            }
            if (checkAlienVsBullet()) {
                return true;
            }
            return false;
        }
        bool checkPlayerVsAlien() {

        }
        bool checkPlayerVsBullet() {

        }
        bool checkAlienVsBullet() {

        }
    };
}
