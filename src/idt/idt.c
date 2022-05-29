#include "idt.h"
#include "config.h"
#include "memory/memory.h"
#include "text/text.h"

struct idt_desc idt_descriptors[TOYOS_TOTAL_INTERRUPTS];
struct idtr_desc idtr_descriptor;

void idt_zero()
{
    print("Divide by zero error\n");
}

void idt_set(int i, void* address)
{
    struct idt_desc* desc = &idt_descriptors[i];
    desc->offset_1 = (uint32_t) address & 0x0000ffff;
    desc->selector = KERNEL_CODE_SELECTOR;
    desc->zeroed = 0x00;
    desc->type_attr = 0xEE;
    desc->offset_2 = (uint32_t) address >> 16;
}

void load_idt(struct idtr_desc* idtr_address) {
    print("This works");
    __asm__ (
             "lidt %0" :: "m"(*idtr_address)
        );
}

void idt_init() {
    memset(idt_descriptors, 0, sizeof(idt_descriptors));
    idtr_descriptor.limit = sizeof(idt_descriptors) - 1;
    idtr_descriptor.base = (uint32_t)idt_descriptors;

    idt_set(0, idt_zero);
    load_idt(&idtr_descriptor);
}
