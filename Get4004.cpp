#include <Get4004.h>

/* 
*   Intel4004 Emulator
*   Gruppe: Tobias Traiser, Kilian Wachter, Pascal Wildermuth, Shaig Rustamov
*   Projektabgabe C 2.Semester - 18.07.2021
*/

Intel4004Base *get4004Instance( const uint16_t installed_ROM_Chips, const uint32_t installed_RAM_Chips)
{
    return new Intel4004(installed_ROM_Chips, installed_RAM_Chips);
}