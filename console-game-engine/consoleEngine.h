#pragma once
#include <Windows.h>
#include <iostream>
#include <chrono>
#include <vector>
#include <list>
#include <thread>
#include <atomic>
#include <condition_variable>


namespace consoleEngine {
	enum COLOUR
	{
		FG_BLACK = 0x0000,
		FG_DARK_BLUE = 0x0001,
		FG_DARK_GREEN = 0x0002,
		FG_DARK_CYAN = 0x0003,
		FG_DARK_RED = 0x0004,
		FG_DARK_MAGENTA = 0x0005,
		FG_DARK_YELLOW = 0x0006,
		FG_GREY = 0x0007, 
		FG_DARK_GREY = 0x0008,
		FG_BLUE = 0x0009,
		FG_GREEN = 0x000A,
		FG_CYAN = 0x000B,
		FG_RED = 0x000C,
		FG_MAGENTA = 0x000D,
		FG_YELLOW = 0x000E,
		FG_WHITE = 0x000F,
		BG_BLACK = 0x0000,
		BG_DARK_BLUE = 0x0010,
		BG_DARK_GREEN = 0x0020,
		BG_DARK_CYAN = 0x0030,
		BG_DARK_RED = 0x0040,
		BG_DARK_MAGENTA = 0x0050,
		BG_DARK_YELLOW = 0x0060,
		BG_GREY = 0x0070,
		BG_DARK_GREY = 0x0080,
		BG_BLUE = 0x0090,
		BG_GREEN = 0x00A0,
		BG_CYAN = 0x00B0,
		BG_RED = 0x00C0,
		BG_MAGENTA = 0x00D0,
		BG_YELLOW = 0x00E0,
		BG_WHITE = 0x00F0,
	};

	struct Vector2 {
		int x;
		int y;
		Vector2(int x, int y) :x(x), y(y) {};
		std::string toString();
		void print();
		Vector2 operator+(const Vector2& other);
		Vector2 operator*(const Vector2& other);
		Vector2 operator-(const Vector2& other);
		Vector2 operator/(const Vector2& other);
		Vector2 operator%(const Vector2& other);

		Vector2 operator+=(const Vector2& other);
		Vector2 operator*=(const Vector2& other);
		Vector2 operator-=(const Vector2& other);
		Vector2 operator/=(const Vector2& other);
		Vector2 operator%=(const Vector2& other);

		bool operator!=(const Vector2& other);
		bool operator==(const Vector2& other);

	};

	class Console
	{
	public:

		Console(int width, int height);

		~Console();

		void fillBackground(short c, short col);
		void draw(int x, int y, short c, short col);
		void draw(Vector2& pos, short c, short col);

		void writeConsole();
		void drawBuffer(int x, int y, short c, short col);
		void drawBuffer(Vector2& pos, short c, short col);

		void drawRect(int x1, int y1, int x2, int y2, short col, short c, bool fill);

		void drawLine(int x1, int y1, int x2, int y2, short col, short c);


	protected:
		uint16_t m_width;
		uint16_t m_height;
		HANDLE m_hConsole;
		HANDLE m_hConsoleIn;
		SMALL_RECT m_rectWindow;
		CHAR_INFO* m_screen;
		std::wstring m_consoleTitle;
	};

	class Game {

	public:
		bool m_gameLoopActive = true;

		Game();
		Game(int width, int height);
		Game(Console* console);
		void gameLoop();
		void start();

	protected:
		Console* m_consoleInstance;
		struct sKeyState
		{
			bool bPressed;
			bool bReleased;
			bool bHeld;
		} m_keys[256], m_mouse[5];

		int m_mousePosX = 0;
		int m_mousePosY = 0;
	};
}