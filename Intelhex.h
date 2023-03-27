#ifndef _INTELHEX_H_
#define _INTELHEX_H_
#include <stdint.h>

/* 
*   Intel4004 Emulator
*   Gruppe: Tobias Traiser, Kilian Wachter, Pascal Wildermuth, Shaig Rustamov
*   Projektabgabe C 2.Semester - 18.07.2021
*/

/**
 * Dient zum lesen einer Intel HEX Datei
 * @param path Pfadangabe Hex-Datei
 * @param destination Array von Binärdaten
 * @param max_length Größe des Array von Binärdaten
 * @return Anzahl der gelesenen Binär Bytes (im Fehlerfall -1)
 */
extern int readHexFile(const char *path, uint8_t *destination, int max_length);

#endif
