#pragma once
namespace Invaders {
    class GameUI {
    private:
        size_t _count_lives;
        size_t _player_score;
        size_t _level;
    public:
        GameUI() = default;
        GameUI(size_t lives, size_t score, size_t level) :
            _count_lives(lives), _player_score(score), _level(level) {}
        GameUI(const GameUI&) = default;
        size_t getLives() const {
            return _count_lives;
        }
        size_t getScore() const {
            return _player_score;
        }
        size_t getLevel() const {
            return _level;
        }
        void setLives(size_t lives) {
            _count_lives = lives;
        }
        void setScore(size_t score) {
            _player_score = score;
        }
        void setLevel(size_t level) {
            _level = level;
        }
        void ShowPanel();
        void UpdateLives();
        void UpdateScore();
        void UpdateLevel();
    };
}

