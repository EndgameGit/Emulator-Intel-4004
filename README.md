# Emulator-Intel-4004
/* 
*   Intel4004 Emulator
*   Gruppe: Tobias Traiser, Kilian Wachter, Pascal Wildermuth, Shaig Rustamov
*   Projektabgabe C 2.Semester - 18.07.2021
*/

**Benötigte Dateien:**

*Header:*

Intel4002.h Intel4001.h Intel4004.h Intel4004Stack.h CommandsPW.h Intelhex.h Get4004.h 400x_GlobalDefines.h MCS4BaseClasses.h catch.hpp

*CPP-Files:*

Intel4002.cpp Intel4001.cpp Intel4004.cpp Intel4004Stack.cpp CommandsPW.cpp Intelhex.cpp Get4004.cpp

**Get started:**

main function linken und Befehl "Intel4004Base *get4004Instance(const uint16_t installed_ROM_Chips = 0xFFFF, const uint32_t installed_RAM_Chips = 0xFFFFFFFF);"
nutzen, um Instance von Prozessor zu ziehen.

Ein Makefile zum compilieren ist beigelegt. Alle .cpp Dateien müssen als .o gelinkt werden. 
Fügen Sie ihren Unittest in den Ordner und kompilieren Sie ihn zu den restlichen Dateien.
Wenn Sie das Makefile nutzen: Ergänzen Sie den Namen des Unittestfiles hinter die Dateinamen in der ersten Zeile mit Dateiendung .o