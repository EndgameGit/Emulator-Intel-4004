#include <Get4004.h>
#include <stdio.h>

int main() {
    Intel4004Base *processor = { get4004Instance(0xFFFF, 0xFFFFFFFF) };

    Intel4001Base * ROMPtr = processor->getPtrToROM();

    printf("%i", ROMPtr->readFromPort(ROMCHIP0));

    return 0;
}