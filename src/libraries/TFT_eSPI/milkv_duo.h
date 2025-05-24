#pragma once

// Определения для Milk-V Duo
#define digitalPinToPort(P) (0)
#define digitalPinToBitMask(P) (1UL << (P))
#define portOutputRegister(port) ((volatile uint32_t *)0x10000000) // Примерный адрес, нужно уточнить
#define portInputRegister(port) ((volatile uint32_t *)0x10000004)
#define portSetRegister(port) ((volatile uint32_t *)0x10000008)
#define portClearRegister(port) ((volatile uint32_t *)0x1000000C)
#define portToggleRegister(port) ((volatile uint32_t *)0x10000010)
