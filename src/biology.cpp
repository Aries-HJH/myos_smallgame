#include "../include/biology.h"
#include "../include/types.h"

void printf(const char*);
void printfHex(uint8_t key);

Biology::Biology(Sence* sence) : p_x(-1), p_y(-1), x(10), y(5), isrun(true), isJumpping(false), sence(sence) {
}

void Biology::DrawBiology() {
	uint16_t* VideoMemory = (uint16_t*)0xb8000;
	if (p_x != -1 && p_y != -1) {
		// Head
		VideoMemory[p_y * 80 + p_x] = ((VideoMemory[p_y * 80 + p_x] & 0xf000) >> 4) |
			                ((VideoMemory[p_y * 80 + p_x] & 0x0f00) << 4) |
			                (VideoMemory[p_y * 80 + p_x] & 0x00ff);
		VideoMemory[p_y * 80 + p_x + 1] = ((VideoMemory[p_y * 80 + p_x + 1] & 0xf000) >> 4) |
			                ((VideoMemory[p_y * 80 + p_x + 1] & 0x0f00) << 4) |
			                (VideoMemory[p_y * 80 + p_x + 1] & 0x00ff);
		
		// body
		VideoMemory[(p_y + 1) * 80 + p_x] = ((VideoMemory[(p_y + 1) * 80 + p_x] & 0xf000) >> 4) |
			                ((VideoMemory[(p_y + 1) * 80 + p_x] & 0x0f00) << 4) |
			                (VideoMemory[(p_y + 1) * 80 + p_x] & 0x00ff);
		VideoMemory[(p_y + 1) * 80 + p_x + 1] = ((VideoMemory[(p_y + 1) * 80 + p_x + 1] & 0xf000) >> 4) |
			                ((VideoMemory[(p_y + 1) * 80 + p_x + 1] & 0x0f00) << 4) |
			                (VideoMemory[(p_y + 1) * 80 + p_x + 1] & 0x00ff);
		VideoMemory[(p_y + 1) * 80 + p_x + 2] = ((VideoMemory[(p_y + 1) * 80 + p_x + 2] & 0xf000) >> 4) |
			                ((VideoMemory[(p_y + 1) * 80 + p_x + 2] & 0x0f00) << 4) |
			                (VideoMemory[(p_y + 1) * 80 + p_x + 2] & 0x00ff);
		VideoMemory[(p_y + 1) * 80 + p_x - 1] = ((VideoMemory[(p_y + 1) * 80 + p_x - 1] & 0xf000) >> 4) |
			                ((VideoMemory[(p_y + 1) * 80 + p_x - 1] & 0x0f00) << 4) |
			                (VideoMemory[(p_y + 1) * 80 + p_x - 1] & 0x00ff);
		
		// leg
		VideoMemory[(p_y + 2) * 80 + p_x + 2] = ((VideoMemory[(p_y + 2) * 80 + p_x + 2] & 0xf000) >> 4) |
			                ((VideoMemory[(p_y + 2) * 80 + p_x + 2] & 0x0f00) << 4) |
			                (VideoMemory[(p_y + 2) * 80 + p_x + 2] & 0x00ff);
		VideoMemory[(p_y + 2) * 80 + p_x - 1] = ((VideoMemory[(p_y + 2) * 80 + p_x - 1] & 0xf000) >> 4) |
			                ((VideoMemory[(p_y + 2) * 80 + p_x - 1] & 0x0f00) << 4) |
			                (VideoMemory[(p_y + 2) * 80 + p_x - 1] & 0x00ff);
	}
	p_x = x;
	p_y = y;
	// Head
	VideoMemory[y * 80 + x] = ((VideoMemory[y * 80 + x] & 0xf000) >> 4) |
	                        ((VideoMemory[y * 80 + x] & 0x0f00) << 4) |
	                        (VideoMemory[y * 80 + x] & 0x00ff);
	VideoMemory[y * 80 + x + 1] = ((VideoMemory[y * 80 + x + 1] & 0xf000) >> 4) |
	                        ((VideoMemory[y * 80 + x + 1] & 0x0f00) << 4) |
	                        (VideoMemory[y * 80 + x + 1] & 0x00ff);
	
	// body
	VideoMemory[(y + 1) * 80 + x] = ((VideoMemory[(y + 1) * 80 + x] & 0xf000) >> 4) |
	                        ((VideoMemory[(y + 1) * 80 + x] & 0x0f00) << 4) |
	                        (VideoMemory[(y + 1) * 80 + x] & 0x00ff);
	VideoMemory[(y + 1) * 80 + x + 1] = ((VideoMemory[(y + 1) * 80 + x + 1] & 0xf000) >> 4) |
	                        ((VideoMemory[(y + 1) * 80 + x + 1] & 0x0f00) << 4) |
	                        (VideoMemory[(y + 1) * 80 + x + 1] & 0x00ff);
	VideoMemory[(y + 1) * 80 + x + 2] = ((VideoMemory[(y + 1) * 80 + x + 2] & 0xf000) >> 4) |
	                        ((VideoMemory[(y + 1) * 80 + x + 2] & 0x0f00) << 4) |
	                        (VideoMemory[(y + 1) * 80 + x + 2] & 0x00ff);
	VideoMemory[(y + 1) * 80 + x - 1] = ((VideoMemory[(y + 1) * 80 + x - 1] & 0xf000) >> 4) |
	                        ((VideoMemory[(y + 1) * 80 + x - 1] & 0x0f00) << 4) |
	                        (VideoMemory[(y + 1) * 80 + x - 1] & 0x00ff);
	
	// leg
	VideoMemory[(y + 2) * 80 + x + 2] = ((VideoMemory[(y + 2) * 80 + x + 2] & 0xf000) >> 4) |
	                        ((VideoMemory[(y + 2) * 80 + x + 2] & 0x0f00) << 4) |
	                        (VideoMemory[(y + 2) * 80 + x + 2] & 0x00ff);
	VideoMemory[(y + 2) * 80 + x - 1] = ((VideoMemory[(y + 2) * 80 + x - 1] & 0xf000) >> 4) |
	                        ((VideoMemory[(y + 2) * 80 + x - 1] & 0x0f00) << 4) |
	                        (VideoMemory[(y + 2) * 80 + x - 1] & 0x00ff);
}

bool Biology::Collision_detection() {
	bool res = false;
	
	uint16_t* VideoMemory = (uint16_t*)0xb8000;
	
	if (VideoMemory[y * 80 + x] != 0x7020) res = true;
	else if (VideoMemory[y * 80 + x + 1] != 0x7020) res = true;
	else if (VideoMemory[(y + 1) * 80 + x] != 0x7020) res = true;
	else if (VideoMemory[(y + 1) * 80 + x + 1] != 0x7020) res = true;
	else if (VideoMemory[(y + 1) * 80 + x + 2] != 0x7020) res = true;
	else if (VideoMemory[(y + 1) * 80 + x - 1] != 0x7020) res = true;
	else if (VideoMemory[(y + 2) * 80 + x + 2] != 0x7020) res = true;
	else if (VideoMemory[(y + 2) * 80 + x - 1] != 0x7020) res = true;
	return res;
}

void Biology::Activate() {
	isrun = true;
}

void Biology::Deactivate() {
	isrun = false;
}

void Biology::time(uint16_t sec) {
	for (uint16_t i = 0; i < sec; i++)
		for (uint16_t j = 0; j < 10000; j++);
}

bool Biology::GetIsjump() { return isJumpping;}

void Biology::Jump() {
	// x->6 y->3
	uint8_t distance = 3;
	uint16_t t = 9000;
	isJumpping = true;
	while(distance != 0) {
		DrawBiology();
		
		// 碰撞检测
		if (Collision_detection()) {isrun = false; sence->GameOverSence(); break;}
		// 边缘检测
		if (x <= 1) break;//x = 1;
		else if (x >= 78) {isrun = false; sence->GamePassSence(); break;}//x = 77;
		if (y <= 2) break;//y = 0;
		else if (y >= 23) {isrun = false; sence->GameOverSence(); break;}//y = 22;
		if (distance > 0) {
			x+=2;
			y--;
			distance--;
			t -= 2000;
		}
		// 边缘检测
		if (x <= 1) break;//x = 1;
		else if (x >= 78) {isrun = false; sence->GamePassSence(); break;}//x = 77;
		if (y <= 2) break;//y = 0;
		else if (y >= 23) {isrun = false; sence->GameOverSence(); break;}//y = 22;
		time(t);
	}
	isJumpping = false;
}

void Biology::Move() {
	while(isrun) {
	
		// 绘制
		DrawBiology();
		
		// 碰撞检测
		if (Collision_detection()) {isrun = false; sence->GameOverSence(); break;}
		x++;
		y++;
		// 边缘检测
		if (x <= 1) break;//x = 1;
		else if (x >= 78) {isrun = false; sence->GamePassSence(); break;}//x = 77;
		if (y <= 2) break;//y = 0;
		else if (y >= 23) {isrun = false; sence->GameOverSence(); break;}//y = 22;
		
		time(9000);
		
	}
}
