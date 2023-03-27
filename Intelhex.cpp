#include <stdio.h>
#include <string.h>
#include <Intelhex.h>

/* 
*   Intel4004 Emulator
*   Gruppe: Tobias Traiser, Kilian Wachter, Pascal Wildermuth, Shaig Rustamov
*   Projektabgabe C 2.Semester - 18.07.2021
*/

/*
    Wichtige Befehle für die main:
    const int max_length = ??;  // Maximale Zeilenlänge, von der ausgegangen wird
    uint8_t hex_array[max_length];  // Ein unsigned chars array, was anfangs leer ist und in der Routine gleich gefüllt wird
    int databytes_count = readHexFile(argv[2], hex_array, max_length);  
    if (databytes_count == -1) return 1;
 */
int parseHexLine(char line[], int line_databytes[], int *addr, int *line_databytes_count, int *status) {
	int sum, len, checksum;
	char *ptr;  
	*line_databytes_count = 0;  

	if (line[0] != ':') return 0;  
	if (strlen(line) < 11) return 0;  
	ptr = line+1;  
	if (!sscanf(ptr, "%02x", &len)) return 0;  
	ptr += 2;  
	if (strlen(line) < (11 + (len * 2)) ) return 0;  
	if (!sscanf(ptr, "%04x", addr)) return 0;  
	ptr += 4;  
	if (!sscanf(ptr, "%02x", status)) return 0;  
	ptr += 2;

	sum = (len & 255) + ((*addr >> 8) & 255) + (*addr & 255) + (*status & 255);  
	while(*line_databytes_count != len) {  
		if (!sscanf(ptr, "%02x", &line_databytes[*line_databytes_count])) return 0;
		
		ptr += 2; 
		sum += line_databytes[*line_databytes_count] & 255;  
		(*line_databytes_count)++;  
		if (*line_databytes_count >= 256) return 0;  
	}
	if (!sscanf(ptr, "%02x", &checksum)) return 0;  
	if (((sum & 255) + (checksum & 255)) & 255 ) return 0;  
	return 1;  
}

/**
 * Dient zum lesen einer Intel HEX Datei
 * @param path Pfadangabe Hex-Datei
 * @param destination Array von Binärdaten, zu Beginn leer aber wird dann befüllt
 * @param max_length Größe des Array von Binärdaten
 * @return Anzahl der gelesenen Binär Bytes (im Fehlerfall -1)
 */
int readHexFile(const char *path, uint8_t *destination, const int max_length) {
    if (strlen(path) == 0) { 
		printf("Error: No file path was given.\n");
		return -1;
	}
	
	FILE *file_ptr = fopen(path, "r");  
	                                           
	if (file_ptr == NULL) {  
		printf("Error: Can't open file '%s'.\n", path);
		return -1;
	}
	
	char line[max_length];  
	int line_databytes[max_length / 2];  
    int addr, status, line_databytes_count;
    int i, total=0, line_number=1;
    
	while (!feof(file_ptr) && !ferror(file_ptr)) {  
        line[0] = '\0';  
        fgets(line, max_length, file_ptr);  
        if (line[strlen(line)-1] == '\n' || line[strlen(line)-1] == '\r') {
            line[strlen(line)-1] = '\0';  
        }
        
        
        if (parseHexLine(line, line_databytes, &addr, &line_databytes_count, &status)) {
            
			if (status == 0) { 
				for(i=0; i<=(line_databytes_count - 1); i++) {
                    
					destination[addr] = line_databytes[i] & 255;
					total++;
					addr++;
				}
			}
			if (status == 1) break; 
		} else {
            
			printf("There was a parsing error in line %d.\n", line_number);
		}
		line_number++;  
    }
	
	fclose(file_ptr); 
    if (total == 0) total = -1; 
    return total;
}