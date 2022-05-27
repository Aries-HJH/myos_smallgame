#ifndef __KEYBOARD_H
#define __KEYBOARD_H
#include "types.h"
#include "port.h"
#include "interrupts.h"
#include "driver.h"
/* 一个是 intel 8042 芯片，位于主板上，CPU 通过 I/O 端口直接和这个芯片通信，获得按键的扫描码或者发送各种键盘命令。
另一个是 intel 8048 芯片或者其兼容芯片，位于键盘中，这个芯片主要作用是从键盘的硬件中得到被按的键所产生的扫描码，
与 8042 通信，控制键盘本身。8042有两个端口，驱动中0x60叫数据端口，0x64命令端口。*/

class KeyboardEventHandler {
public:
    KeyboardEventHandler();

    virtual void OnKeyDown(char);
    virtual void OnKeyUp(char);
};

class KeyBoardDrive : public InterruptHandle, public Driver {
public:
	KeyBoardDrive(InterruptManager* manager, KeyboardEventHandler* handler);
	~KeyBoardDrive();
	virtual void Activate();
	virtual uint32_t HandleInterrrupt(uint32_t esp);
private:
	Port8Bit dataport;
	Port8Bit commandport;
	KeyboardEventHandler* handler;
};

#endif
