#ifndef __INTERRUPTS_H
#define __INTERRUPTS_H
#include "types.h"
#include "port.h"
#include "gdt.h"

class InterruptManager;

class InterruptHandle {
public:
	virtual uint32_t HandleInterrrupt(uint32_t esp);
protected:
	InterruptHandle(uint8_t interruptNumber, InterruptManager* interruptManager);
	~InterruptHandle();
	
	uint8_t interruptNumber;
	InterruptManager* interruptManager;
};


class InterruptManager {
	friend class InterruptHandle;
public:
	InterruptManager(uint16_t hardwareInterruptOffset, GlobalDescriptorTable* gdt);
	~InterruptManager();
	
	uint16_t HardwareInterruptOffset() { return hardwareInterruptOffset; }
	
	void Activate();
	
	void Deactivate();
	
protected:
	static InterruptManager* interruptPoint;

	InterruptHandle* handle[256];
	
	static void InterruptIgnore(){}
	//门描述符，中断门
	//一个中断源就会产生一个中断向量，一个中断向量对应IDT中的一个门描述符，通过门描述符可以找到对应的中断处理程序
	struct GateDescriptor {
		uint16_t handlerAddressLowBits;
		uint16_t gdt_codeSegmentSelector;
		uint8_t reserved;
		uint8_t access;
		uint16_t handlerAddressHighBits;
	} __attribute__((packed));
	
	static GateDescriptor interruptDescriptorTable[256];
	
	struct InterruptDescriptorTablePointer {
		uint16_t size;
		uint32_t base;
	} __attribute__((packed));
	
	static void SetInterruptDescriptorTableEntry(
	uint8_t interruptNumber,
	uint16_t codeSegmentSelectorOffset,
	void (*handler)(),
	uint8_t descriptorPrivilegeLevel,
	uint8_t descriptorType
	);	
	uint16_t hardwareInterruptOffset;
	
	static uint32_t handleInterrupts(uint8_t interruptsNumber, uint32_t esp);
	
	uint32_t DoHandleInterrupts(uint8_t interruptsNumber, uint32_t esp);
	
	static void HandleInterruptRequest0x00();
	static void HandleInterruptRequest0x01();
	static void HandleInterruptRequest0x02();
	static void HandleInterruptRequest0x03();
	static void HandleInterruptRequest0x04();
	static void HandleInterruptRequest0x05();
	static void HandleInterruptRequest0x06();
	static void HandleInterruptRequest0x07();
	static void HandleInterruptRequest0x08();
	static void HandleInterruptRequest0x09();
	static void HandleInterruptRequest0x0A();
	static void HandleInterruptRequest0x0B();
	static void HandleInterruptRequest0x0C();
	static void HandleInterruptRequest0x0D();
	static void HandleInterruptRequest0x0E();
	static void HandleInterruptRequest0x0F();
	static void HandleInterruptRequest0x31();
	
	static void HandleException0x00();
	static void HandleException0x01();
	static void HandleException0x02();
	static void HandleException0x03();
	static void HandleException0x04();
	static void HandleException0x05();
	static void HandleException0x06();
	static void HandleException0x07();
	static void HandleException0x08();
	static void HandleException0x09();
	static void HandleException0x0A();
	static void HandleException0x0B();
	static void HandleException0x0C();
	static void HandleException0x0D();
	static void HandleException0x0E();
	static void HandleException0x0F();
	static void HandleException0x10();
	static void HandleException0x11();
	static void HandleException0x12();
	static void HandleException0x13();
	
	Port8BitSlow picMasterCommand;
	Port8BitSlow picMasterData;
	Port8BitSlow picSlaveCommand;
	Port8BitSlow picSlaveData;
};


#endif
