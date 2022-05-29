#ifndef IDT_HEADER
#define IDT_HEADER

#include <stdint.h>

struct idt_desc {
    uint16_t offset_1;
    uint16_t selector;
    uint8_t zeroed;
    uint8_t type_attr;
    uint16_t offset_2;
} __attribute__((packed));

struct idtr_desc {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

void idt_set(int i, void* address);

void idt_zero();

void idt_set(int i, void* address);

void load_idt(struct idtr_desc* idtr_address);

void idt_init(); 

#endif
