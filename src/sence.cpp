#include "../include/sence.h"

Sence::Sence() : x(30), y_up(12), y_down(5) {}

void Sence::LoadSence() {
	DrawSence(30, 12, 5);
	DrawSence(50, 12, 5);
	
}

void Sence::DrawSence(uint8_t x, uint8_t y_up, uint8_t y_down) {
	uint16_t* VideoMemory = (uint16_t*)0xb8000;
	for (int i = 0; i <= 24; i++) {
		for (int j = 0; j < 5; j++) {
			VideoMemory[(y_up + i) * 80 + x + j] = ((VideoMemory[(y_up + i) * 80 + x + j] & 0xf000) >> 4) |
	                        ((VideoMemory[(y_up + i) * 80 + x + j] & 0x0f00) << 4) |
	                        (VideoMemory[(y_up + i) * 80 + x + j] & 0x00ff);
		}
	}
	for (int i = y_down; i >= 0; i--) {
		for (int j = 0; j < 5; j++) {
	               VideoMemory[i * 80 + x + j] = ((VideoMemory[i * 80 + x + j] & 0xf000) >> 4) |
	                        ((VideoMemory[i * 80 + x + j] & 0x0f00) << 4) |
	                        (VideoMemory[i * 80 + x + j] & 0x00ff);
		}
	}
}

void Sence::ShowInformation(const char* str) {
	uint16_t* VideoMemory = (uint16_t*)0xb8000;
	int g = 35;
	for (int i = 0; str[i]; i++) {
	    VideoMemory[80 * 10 + g] = (VideoMemory[80 * 10 + g] & 0xFF00) | str[i];
	    g++;
	}
}

void Sence::GameOverSence() {
	uint16_t* VideoMemory = (uint16_t*)0xb8000;
	for (int i = 20; i<=60; i++) {
		for (int j = 5; j<=15; j++) {
	               VideoMemory[j * 80 + i] = 0x7020;
	               ShowInformation("Game Over.");
		}
	}
	
}

void Sence::GamePassSence() {
	uint16_t* VideoMemory = (uint16_t*)0xb8000;
	for (int i = 20; i<=60; i++) {
		for (int j = 5; j<=15; j++) {
	               VideoMemory[j * 80 + i] = 0x7020;
	               ShowInformation("Good Game.");
		}
	}
}
