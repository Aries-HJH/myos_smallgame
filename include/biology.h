#ifndef __BIOLOGY_H
#define __BIOLOGY_H
#include "types.h"
#include "sence.h"

class Biology {
public:
	Biology(Sence* sence);
	
	// virtual void Move(uint8_t key);
	void Move();
	void Activate();
	void Deactivate();
	void Jump();
	bool GetIsjump();
private:
	bool Collision_detection();
	void DrawBiology();
	void time(uint16_t sec);
	int8_t p_x, p_y;
	int8_t x, y;
	bool isrun;
	bool isJumpping;
	Sence* sence;
};

#endif
