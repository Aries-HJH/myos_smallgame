#include "../include/types.h"
#include "../include/gdt.h"
#include "../include/interrupts.h"
#include "../include/keyboard.h"
#include "../include/driver.h"
#include "../include/biology.h"
#include "../include/sence.h"

void printf(const char* str){
	static uint16_t* VideoMemory = (uint16_t*)0xb8000;
	static uint8_t x = 0, y = 0;
	for (int i = 0; str[i]; i++) {
	switch(str[i]) {
	case '\n':
	    y++;
	    x = 0;
	    break;
	default:
	    VideoMemory[80 * y + x] = (VideoMemory[80 * y + x] & 0xFF00) | str[i];
	    x++;
	    break;
	}


	if (x >= 80) {
	    x = 0;
	    y++;
	}

	if (y >= 25) {
	    for (y = 0; y < 25; y++) {
		for (x = 0; x < 80; x++) {
		    VideoMemory[80 * y + x] = (VideoMemory[80 * y + x] & 0xFF00) | ' ';
		}
	    }
	    x = 0, y = 0;
	}
	}
}

void printfHex(uint8_t key) {
    char* foo = (char*)"00";
    const char* hex = "0123456789ABCDEF";
    foo[0] = hex[(key >> 4) & 0x0f];
    foo[1] = hex[key & 0x0f];
    printf((const char*)foo);
}

class PrintKeyboardEventHandler : public KeyboardEventHandler {
public:
	
	PrintKeyboardEventHandler(Biology* biology);
	void OnKeyDown(char c) {
		if (c == 'q')
			biology->Deactivate();
		else if ((c == 'j') && (!biology->GetIsjump())) {
			biology->Jump();
			
		}// && !biology->GetIsjump())
			
			
		/*
		char* foo = (char*)" ";
		foo[0] = c;
		printf(foo);
		*/
	}
private:
	Biology* biology;
};

PrintKeyboardEventHandler::PrintKeyboardEventHandler(Biology* biology) : biology(biology) {}

typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;

extern "C" void callConstructors() {
	for (constructor* i = &start_ctors; i != &end_ctors; i++) {
		(*i)();
	}
}

/*
__GLOBAL_OFFSET_TABLE_ 
A kernel that can be booted by GRUB meets two conditions.
	The standard multiboot header.
		magic: 0x1BADB002
		flag
		check
	The kernel is to be loaded at more than 1MB of memory address.
*/
extern "C" void kernelMain(void* multiboot_structure, uint32_t magicnumber){
	Sence sence;
	sence.LoadSence();
	// init GDT
	GlobalDescriptorTable gdt;
	// init IDT
	InterruptManager interrupt(0x20, &gdt);
	
	DriverManager driverManager;
	Biology biology(&sence);
	PrintKeyboardEventHandler kbhandler(&biology);
	KeyBoardDrive keyboard(&interrupt, &kbhandler);
	driverManager.AddDriver(&keyboard);

	driverManager.ActivateAll();
	interrupt.Activate();
	biology.Move();
	while(1);
}
