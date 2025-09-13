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
        bool checkCollisions(Player& player, AlienManager& aliens) {
            if (checkPlayerVsAliens(player, aliens)) {
                return true;
            }
            if (checkPlayerVsAlienBullet(player, aliens)) {
                return true;
            }
            if (checkAlienVsPlayerBullet(player, aliens)) {
                return true;
            }
            return false;
        }
    private:
        bool checkPlayerVsAliens(Player& player, AlienManager& aliens) {
            for (size_t i = 0; i < aliens.getRedAliens().size(); ++i) {
                if (player.getPosition().x == aliens.getRedAliens()[i].getPosition().x
                    && player.getPosition().y == aliens.getRedAliens()[i].getPosition().y
                    && aliens.getRedAliens()[i].isActive()) {
                    player.setIsActive(false);
                    return true;
                }
            }
            for (size_t i = 0; i < aliens.getGreenAliens().size(); ++i) {
                if (player.getPosition().x == aliens.getGreenAliens()[i].getPosition().x
                    && player.getPosition().y == aliens.getGreenAliens()[i].getPosition().y
                    && aliens.getGreenAliens()[i].isActive()) {
                    player.setIsActive(false);
                    return true;
                }
            }
            for (size_t i = 0; i < aliens.getWhiteAliens().size(); ++i) {
                if (player.getPosition().x == aliens.getWhiteAliens()[i].getPosition().x
                    && player.getPosition().y == aliens.getWhiteAliens()[i].getPosition().y
                    && aliens.getWhiteAliens()[i].isActive()) {
                    player.setIsActive(false);
                    return true;
                }
            }
            return false;
        }
        bool checkPlayerVsAlienBullet(Player& player, AlienManager& aliens) {
            for (size_t i = 0; i < aliens.getRedAliens().size(); ++i) {
                for (size_t j = 0; j < aliens.getRedAliens()[i].getBulletsCount(); ++j) {
                    if (player.getPosition().x == aliens.getRedAliens()[i].getBullets()[j].getPosition().x
                        && player.getPosition().y == aliens.getRedAliens()[i].getBullets()[j].getPosition().y
                        && aliens.getRedAliens()[i].isActive()
                        && aliens.getRedAliens()[i].getBullets()[j].isActive()) {
                        player.setIsActive(false);
                        return true;
                    }
                }
            }
            for (size_t i = 0; i < aliens.getGreenAliens().size(); ++i) {
                for (size_t j = 0; j < aliens.getGreenAliens()[i].getBulletsCount(); ++j) {
                    if (player.getPosition().x == aliens.getGreenAliens()[i].getBullets()[j].getPosition().x
                        && player.getPosition().y == aliens.getGreenAliens()[i].getBullets()[j].getPosition().y
                        && aliens.getGreenAliens()[i].isActive()
                        && aliens.getGreenAliens()[i].getBullets()[j].isActive()) {
                        player.setIsActive(false);
                        return true;
                    }
                }

            }
            for (size_t i = 0; i < aliens.getWhiteAliens().size(); ++i) {
                for (size_t j = 0; j < aliens.getWhiteAliens()[i].getBulletsCount(); ++j) {
                    if (player.getPosition().x == aliens.getWhiteAliens()[i].getBullets()[j].getPosition().x
                        && player.getPosition().y == aliens.getWhiteAliens()[i].getBullets()[j].getPosition().y
                        && aliens.getWhiteAliens()[i].isActive()
                        && aliens.getWhiteAliens()[i].getBullets()[j].isActive()) {
                        player.setIsActive(false);
                        return true;
                    }
                }
            }
            return false;
        }
        bool checkAlienVsPlayerBullet(Player& player, AlienManager& aliens) {
            for (size_t i = 0; i < aliens.getRedAliens().size(); ++i) {
                for (size_t j = 0; j < player.getBulletsCount(); ++j) {
                    if (aliens.getRedAliens()[i].getPosition().x == player.getBullets()[j].getPosition().x
                        && aliens.getRedAliens()[i].getPosition().y == player.getBullets()[j].getPosition().y
                        && aliens.getRedAliens()[i].isActive()
                        && player.getBullets()[j].isActive()) {
                        aliens.getRedAliens()[i].setIsActive(false);
                        player.getBullets()[j].setIsActive(false); 
                        return true;
                    }
                }
            }
            for (size_t i = 0; i < aliens.getGreenAliens().size(); ++i) {
                for (size_t j = 0; j < player.getBulletsCount(); ++j) {
                    if (aliens.getGreenAliens()[i].getPosition().x == player.getBullets()[j].getPosition().x
                        && aliens.getGreenAliens()[i].getPosition().y == player.getBullets()[j].getPosition().y
                        && aliens.getGreenAliens()[i].isActive()
                        && player.getBullets()[j].isActive()) {
                        aliens.getGreenAliens()[i].setIsActive(false);
                        player.getBullets()[j].setIsActive(false);
                        return true;
                    }
                }
            }
            for (size_t i = 0; i < aliens.getWhiteAliens().size(); ++i) {
                for (size_t j = 0; j < player.getBulletsCount(); ++j) {
                    if (aliens.getWhiteAliens()[i].getPosition().x == player.getBullets()[j].getPosition().x
                        && aliens.getWhiteAliens()[i].getPosition().y == player.getBullets()[j].getPosition().y
                        && aliens.getWhiteAliens()[i].isActive()
                        && player.getBullets()[j].isActive()) {
                        aliens.getWhiteAliens()[i].setIsActive(false);
                        player.getBullets()[j].setIsActive(false);
                        return true;
                    }
                }
            }
            return false;
        }
    };
}
