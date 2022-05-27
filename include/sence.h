#ifndef __SENCE_H
#define __SENCE_H
#include "types.h"

class Sence {
public:
	Sence();
	void LoadSence();
	void GameOverSence();
	void GamePassSence();
private:
	void DrawSence(uint8_t x, uint8_t y_up, uint8_t y_down);
	void ShowInformation(const char* str);
	int8_t x;
	int8_t y_up;
	int8_t y_down;
};

#endif
