#pragma once
#include <windows.h>
namespace Invaders {
    struct Coordinates {
        int x;
        int y;
    };
    struct IDisplay {
        virtual void print(int x, int y, char c) = 0;
        virtual ~IDisplay() = default;
    };
    struct IDrawable {
        virtual void DrawOn(IDisplay& out) const = 0;
        virtual void Update() = 0;
        virtual ~IDrawable() = default;
    };
    enum Event {
        KeyPress = 0
    };
    class ConsoleDisplay : public IDisplay {
    public:
        void print(int x, int y, char c) override {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            COORD coordinates = { 
                static_cast<SHORT>(x - 1), static_cast<SHORT>(y - 1) 
            };
            SetConsoleCursorPosition(hConsole, coordinates);
            WriteConsoleOutputCharacterA(hConsole, &c, 1, coordinates, nullptr);
        }
    };
    class GameObject : public IDrawable {
    protected:
        Coordinates _position;
        bool _is_active;
        char _appearance;
    public:
        GameObject(int x, int y) :
            _position{ x, y },
            _is_active(true) {}

        virtual void OnEvent(Event e, char c) = 0;
        void DrawOn(IDisplay& out) const override {
            out.print(_position.x, _position.y, _appearance);
        }
    };
}
