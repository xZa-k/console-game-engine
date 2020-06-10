#include "consoleEngine.h"
#include <iostream>
#include <string>
#include <math.h>
#include <bitset>

using namespace consoleEngine;

Console::Console(int width, int height) {
	
	// Initialise variables
	m_width = width;
	m_height = height;

	m_consoleTitle = L"Console game";
	
	// Get console handles
	m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	m_hConsoleIn = GetStdHandle(STD_INPUT_HANDLE);


	// To shrink screenbuffer to remove scroll bars
	m_rectWindow = { 0, 0, 1, 1 };

	SetConsoleWindowInfo(m_hConsole, TRUE, &m_rectWindow);
	m_rectWindow = { 0, 0, (short)m_width, (short)m_height };

	COORD coord = { (short)m_width, (short)m_height };
	SetConsoleScreenBufferSize(m_hConsole, coord);

	SetConsoleActiveScreenBuffer(m_hConsole);

	m_rectWindow = { 0, 0, (short)m_width - 1, (short)m_height - 1 };
	SetConsoleWindowInfo(m_hConsole, TRUE, &m_rectWindow);

	SetConsoleMode(m_hConsoleIn, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);

	m_screen = new CHAR_INFO[m_width * m_height];
	memset(m_screen, 0, sizeof(CHAR_INFO) * m_width * m_height);

}

void Console::draw(int x, int y, short c, short col) {
	drawBuffer(x, y, c, col);
	writeConsole();
}

void Console::draw(Vector2& pos, short c, short col) {
	drawBuffer(pos, c, col);
	writeConsole();
}

void Console::writeConsole() {
	WriteConsoleOutput(m_hConsole, m_screen, { (short)m_width, (short)m_height }, { 0, 0 }, &m_rectWindow);
}

void Console::fillBackground(short c, short col){
	for (size_t y = 0; y < m_width; y++)
	{
		for (size_t x = 0; x < m_height; x++)
		{
			m_screen[x * 80 + y].Char.UnicodeChar = c;
			m_screen[x * 80 + y].Attributes = col;
		}
	}
	writeConsole();
}

void Console::drawBuffer(int x, int y, short c, short col) {
	m_screen[x * 80 + y].Char.UnicodeChar = c;
	m_screen[x * 80 + y].Attributes = col;
}

void Console::drawBuffer(Vector2& pos, short c, short col) {
	m_screen[pos.x * 80 + pos.y].Char.UnicodeChar = c;
	m_screen[pos.x * 80 + pos.y].Attributes = col;
}

void Console::drawRect(int x1, int y1, int x2, int y2, short col, short c, bool fill = true) {
	int startX = (x1 < x2) ? x1 : x2;
	int startY = (y1 < y2) ? y1 : y2;

	int endX = (x1 > x2) ? x1 : x2;
	int endY = (y1 > y2) ? y1 : y2;

	for (size_t y = startY; y < endY; y++) {
		for (size_t x = startX; x < endX; x++) {
			if (fill || (y == startY || y == endY-1 || x == startX || x == endX-1))
				drawBuffer(x, y, c, col);
		}
	}
	writeConsole();
}

// Blantly copied and pasted from javidx9 though he just copied it from wikipedia
void Console::drawLine(int x1, int y1, int x2, int y2, short col, short c) {

	int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
	dx = x2 - x1; dy = y2 - y1;
	dx1 = abs(dx); dy1 = abs(dy);
	px = 2 * dy1 - dx1;	py = 2 * dx1 - dy1;
	if (dy1 <= dx1)
	{
		if (dx >= 0)
		{
			x = x1; y = y1; xe = x2;
		}
		else
		{
			x = x2; y = y2; xe = x1;
		}

		draw(x, y, c, col);

		for (i = 0; x < xe; i++)
		{
			x = x + 1;
			if (px < 0)
				px = px + 2 * dy1;
			else
			{
				if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) y = y + 1; else y = y - 1;
				px = px + 2 * (dy1 - dx1);
			}
			draw(x, y, c, col);
		}
	}
	else
	{
		if (dy >= 0)
		{
			x = x1; y = y1; ye = y2;
		}
		else
		{
			x = x2; y = y2; ye = y1;
		}

		draw(x, y, c, col);

		for (i = 0; y < ye; i++)
		{
			y = y + 1;
			if (py <= 0)
				py = py + 2 * dx1;
			else
			{
				if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) x = x + 1; else x = x - 1;
				py = py + 2 * (dx1 - dy1);
			}
			draw(x, y, c, col);
		}
	}
}

Console::~Console() { 
	delete this->m_screen;
}



void Vector2::print() {
	std::cout << toString() << "\n";
}

std::string Vector2::toString() {
	return "Vector2{ " + std::to_string(this->x) + ", " + std::to_string(this->y) + " }";
}

#pragma region Vector2Operators

Vector2 Vector2::operator+(const Vector2& other) {
	return Vector2(other.x + this->x, other.y + this->y);
}

Vector2 Vector2::operator*(const Vector2& other) {
	return Vector2(other.x * this->x, other.y * this->y);
}

Vector2 Vector2::operator-(const Vector2& other) {
	return Vector2(other.x - this->x, other.y - this->y);
}

Vector2 Vector2::operator/(const Vector2& other) {
	return Vector2(other.x / this->x, other.y / this->y);
}

Vector2 Vector2::operator%(const Vector2& other) {
	return Vector2(other.x % this->x, other.y % this->y);
}

Vector2 Vector2::operator+=(const Vector2& other) {
	this->x += other.x;
	this->y += other.y;
	return *this;
}

Vector2 Vector2::operator*=(const Vector2& other) {
	this->x *= other.x;
	this->y *= other.y;
	return *this;
}

Vector2 Vector2::operator-=(const Vector2& other) {
	this->x -= other.x;
	this->y -= other.y;
	return *this;
}

Vector2 Vector2::operator/=(const Vector2& other) {
	this->x /= other.x;
	this->y /= other.y;
	return *this;
}

Vector2 Vector2::operator%=(const Vector2& other) {
	this->x %= other.x;
	this->y %= other.y;
	return *this;
}

bool Vector2::operator==(const Vector2& other) {
	return (other.x == this->x && other.y == this->y);
}

bool Vector2::operator!=(const Vector2& other) {
	return !(other.x == this->x && other.y == this->y);
}

#pragma endregion


Game::Game() {
	m_consoleInstance = &Console(80, 30);
}

Game::Game(int width, int height) {
	m_consoleInstance = &Console(width, height);
}

Game::Game(Console* consoleInstance) {
	m_consoleInstance = consoleInstance;
}

void Game::start() {
	std::thread t = std::thread(&Game::gameLoop, this);
	t.join();
}

void Game::gameLoop() {
	
	while (m_gameLoopActive) {
		for (size_t i = 0; i < 256; i++)
		{
			sKeyState key = sKeyState{0,0,0};

			short byte = GetAsyncKeyState(i);
			
			if (byte & 0x8000) {
				if (m_keys[i].bHeld == false)
					key.bPressed = true;
				else
					key.bPressed = false;
				

				key.bHeld = true;
			}
			else {
				if (m_keys[i].bHeld == true)
					key.bReleased = true;
				key.bHeld = false;
			}


			if (i == 0x52) {
				std::cout << "Held: " << key.bHeld << "\n";
				std::cout << "Pressed: " << key.bPressed << "\n";
				std::cout << "Released: " << key.bReleased << "\n";
			}
			m_keys[i] = key;
		}
		using namespace std::chrono_literals;
		std::this_thread::sleep_for(0.1s);
	}
}
