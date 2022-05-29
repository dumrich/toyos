#include "kernel.h"
#include "text/text.h"
#include "idt/idt.h"

void kernel_main() {
    /* Initialize Interrupt Descriptor Table */
    idt_init();

    int x = 10;
    int y = 1;
    x /= y - 1;

    print("Ayyo");
}
