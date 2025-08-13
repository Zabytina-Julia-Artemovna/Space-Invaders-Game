#pragma once
namespace Invaders {
    struct IDisplay {
        virtual void print(int x, int y, char c) = 0;
        virtual ~IDisplay() = default;
    };

    class ConsoleDisplay : public IDisplay {
    public:
        void print(int x, int y, char c) override;
    };

    struct IDrawable {
        virtual void DrawOn(IDisplay& out) const = 0;
        virtual void Update() = 0; // перемещение и обновление состояния
        virtual ~IDrawable() = default;
    };

    enum Event {
        KeyPress = 0
    };
    struct Coordinates {
        int x;
        int y;
    };
    class GameObject : public IDrawable {
    protected:
        Coordinates _position;
        bool _is_active;

    public:
        GameObject(int x, int y) :
            _position{ x, y },
            _is_active(true) {}

        virtual void OnEvent(Event e, char c) = 0;
        //virtual void OnCollision(GameObject* other) = 0;
        void DrawOn(IDisplay& out) const override;
        void Update() override;
    };
}
