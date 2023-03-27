#include "Intel4001.h"
#include "Intelhex.h"
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

/* 
*   Intel4004 Emulator
*   Gruppe: Tobias Traiser, Kilian Wachter, Pascal Wildermuth, Shaig Rustamov
*   Projektabgabe C 2.Semester - 18.07.2021
*/


Intel4001::~Intel4001()
{
}
/**
	 * Setzt die internen Register zurück (Datenzellen auf 0x00, Ports auch auf 0)
	 */
void Intel4001::reset()
{
	for (int i = 0; i < 256 * 16; i++)
	{
		this->rom_memory[i] = 0;
	}

	for (int i = 0; i < 16; i++)
	{
		this->ports[i] = 0;
	}
}
/**
	 * Welche Bänke sind in diesem System verbaut
	 * @return Bits der eingeschalteten Bänke
	 */
uint16_t Intel4001::getEnabledBank() const
{
	return this->installed_banks;
} 
/**
	 * Liest das Programm ein (Typ binär)
	 * @param path Quelldatei
	 */
void Intel4001::writeFromBinaryFile(const char *const path)
{
	ifstream file(path, ios::binary | ios::in);
	char oneByte;

	if (!file)
		cerr << "ROM konnte nicht aus Datei " << path << " beschrieben werden." << endl;

	int i = 0;
	while (file.get(oneByte))
	{
		this->rom_memory[i] = oneByte;
		i++;
	}
}
/**
	 * Liest das Programm ein (Typ Intel HEX)
	 * @param path Quelldatei
	 */
void Intel4001::writeFromIntelHexFile(const char *const path)
{
	int databytes_count = readHexFile(path, this->rom_memory, sizeof(this->rom_memory) / sizeof(uint8_t));
	if (databytes_count == -1)
		cerr << "ROM konnte nicht aus Datei " << path << " beschrieben werden." << endl;
}
/**
	 * Liest das Programm ein (Typ Bytes)
	 * @param data Datenquelle
	 * @param count Anzahl Bytes die geschrieben werden
	 * @return Anzahl
	 */
int Intel4001::writeFrom(uint8_t *data, const int count)
{
	memcpy(this->rom_memory, data, count * sizeof(uint8_t));
	return count;
}
/**
   * Setzt die Adresse für I/O-Aktivitäten
   * @param source Adresse des Ports
   */

void Intel4001::setSource(const uint8_t source) {
}

/**
	 * Ist die lokale Adresse vorhanden (gibt es diese Adresse 12bit).
	 * falls nicht wird false zurückgegeben
	 * @param address Lineare Adresse ohne Bankangabe
	 * @return <c>true</c> wenn addressierbar, sonst <c>false</c>
	 */
bool Intel4001::isLinAdrAccessable(const uint12_t address) const
{
	return isBankInstalled((EROMChip)UBankedAddress(address).banked.bank);
}
/**
	 * Liest ein Byte aus dem Speicher
	 * @param address Adresse im Speicher
	 * @return Byte
	 */
uint8_t Intel4001::read(const UBankedAddress address) const
{
	return this->rom_memory[address.raw];
}
/**
	 * Liest Nibble aus Portschnittstelle
	 * @param chip Chip
	 * @return value Wert
	 */
uint4_t Intel4001::readFromPort(const EROMChip chip) const
{
	//Wenn Chip nicht verbaut ist, wird 0 returned. (Standart im portsarray) 

	return ports[(int)chip];
}
/**
	 * Schreibe Nibble auf Portschnittstelle
	 * @param chip Chip
	 * @param value Wert
	 * @return <c>true</c> wenn addressierbar, sonst <c>false</c>
	 */
bool Intel4001::writeToPort(const EROMChip chip, const uint4_t value)
{
	//Checken ob der chip verbaut ist, 
	if (isBankInstalled(chip))
	{
		ports[(int)chip] = value;
		return true;
	}
	return false;
}
/**
	* @return <true> wenn abgefragter Chip installiert ist, sonst <false>
*/
bool Intel4001::isBankInstalled(const EROMChip chip) const
{

	//typedef bitset<16> banks;
	//return banks(installed_banks).test((int)chip);
	return (this->installed_banks & (1 << chip)) != 0;
}
