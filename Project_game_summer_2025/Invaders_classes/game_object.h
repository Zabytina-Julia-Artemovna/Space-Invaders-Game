#pragma once
#include <windows.h>
#include <vector>     
#include <iostream>   
#include <memory>     
#include <algorithm>  
namespace Invaders {
    struct Coordinates {
        int x;
        int y;
    };
    struct IDisplay {
        virtual void print(int x, int y, char c) = 0;
        virtual void clear(int x, int y) = 0;
        virtual ~IDisplay() = default;
    };
    struct IDrawable {
        virtual void DrawOn(IDisplay& out) const = 0;
        virtual void ClearOn(IDisplay& out) const = 0;
        virtual ~IDrawable() = default;
    };
    enum class Event {
        KeyPress,
        Timer,
        AlienShoot
    };
    class ConsoleDisplay : public IDisplay {
    private:
        std::vector<CHAR_INFO> buffer;
        COORD bufferSize;
        COORD bufferCoord;
        SMALL_RECT writeRegion;
        HANDLE hConsole;
    public:
        ConsoleDisplay(int width, int height) : hConsole(GetStdHandle(STD_OUTPUT_HANDLE)) {
            bufferSize.X = width;
            bufferSize.Y = height;
            bufferCoord.X = 0;
            bufferCoord.Y = 0;
            writeRegion = { 0, 0, static_cast<SHORT>(width - 1), 
                static_cast<SHORT>(height - 1) };
            buffer.resize(width * height);
            clearAll();
        }
        void clearAll() {
            for (auto& cell : buffer) {
                cell.Char.AsciiChar = ' ';
                cell.Attributes = 7;
            }
            flush();
        }
        void print(int x, int y, char c) override {
            if (x >= 0 && x < bufferSize.X && y >= 0 && y < bufferSize.Y) {
                buffer[y * bufferSize.X + x].Char.AsciiChar = c;
            }
        }
        void clear(int x, int y) override {
            if (x >= 0 && x < bufferSize.X && y >= 0 && y < bufferSize.Y) {
                buffer[y * bufferSize.X + x].Char.AsciiChar = ' ';
            }
        }
        void flush() {
            WriteConsoleOutputA(hConsole, buffer.data(), bufferSize, bufferCoord, &writeRegion);
        }
    };
    class GameObject : public IDrawable {
    protected:
        Coordinates _position;
        Coordinates _previous_position;
        bool _is_active;
        char _appearance;
    public:
        GameObject(int x, int y, char appearance) :
            _position{ x, y },
            _previous_position{ x, y},
            _is_active(true),
            _appearance(appearance){}
        virtual void OnEvent(Event e, char c) = 0;
        void DrawOn(IDisplay& out) const override {
            out.print(_position.x, _position.y, _appearance);
        }
        void ClearOn(IDisplay& out) const override {
            out.clear(_previous_position.x, _previous_position.y);
        }
        void UpdatePosition(int newX, int newY) {
            _previous_position = _position;  
            _position = { newX, newY };  
        }
        Coordinates getPosition() {
            return _position;
        }
      
    };
}
