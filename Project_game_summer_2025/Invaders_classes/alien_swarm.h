#pragma once
#include <vector>
#include "alien.h"
#include "game_object.h"
namespace Invaders {
    class AlienSwarm {
    private:
        std::vector< std::vector<Alien> > _alien_swarm;
        int _direction; // -1/1 (движение влево/вправо) Структура!
        //Возможно класс избыточный 
        bool _should_move_down = false;
    public:
        AlienSwarm(int rows, int cols, int start_x, int start_y);
        void MoveHorizontal(int dx);
        void MoveDown();
        void UpdateSwarm();
        void RandomAlienShoot();
        bool isSwarmKilled() const;
        const std::vector<std::vector<Alien>>& getAliens() const {
            return _alien_swarm;
        }
        void DrawSwarm() const;
    };
}
