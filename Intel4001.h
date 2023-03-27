#ifndef _INTEL4001_H_
#define _INTEL4001_H_

#include "MCS4BaseClasses.h"

/* 
*   Intel4004 Emulator
*   Gruppe: Tobias Traiser, Kilian Wachter, Pascal Wildermuth, Shaig Rustamov
*   Projektabgabe C 2.Semester - 18.07.2021
*/

class Intel4001 : public Intel4001Base
{
public:
	/**
	 * Konstruktor
	 */
	Intel4001(const uint16_t installed_banks = 0xFFFF) : installed_banks(installed_banks)
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
	 * Destruktor
	 */
	virtual ~Intel4001();
	/**
	 * Setzt die internen Register zurück (Datenzellen auf 0x00, Ports auch auf 0)
	 */
	virtual void reset();
	/**
	 * Welche Bänke sind in diesem System verbaut
	 * @return Bits der eingeschalteten Bänke
	 */
	virtual uint16_t getEnabledBank() const; //100000000000000
	/**
	 * Liest das Programm ein (Typ binär)
	 * @param path Quelldatei
	 */
	virtual void writeFromBinaryFile(const char *const path);
	/**
	 * Liest das Programm ein (Typ Intel HEX)
	 * @param path Quelldatei
	 */
	virtual void writeFromIntelHexFile(const char *const path);
	/**
	 * Liest das Programm ein (Typ Bytes)
	 * @param data Datenquelle
	 * @param count Anzahl Bytes die geschrieben werden
	 * @return Anzahl
	 */
	virtual int writeFrom(uint8_t *data, const int count);
	/**
	 * Ist die lokale Adresse vorhanden (gibt es diese Adresse 12bit).
	 * falls nicht wird false zurückgegeben
	 * @param address Lineare Adresse ohne Bankangabe
	 * @return <c>true</c> wenn addressierbar, sonst <c>false</c>
	 */
	virtual bool isLinAdrAccessable(const uint12_t address) const;
	/**
	 * Liest ein Byte aus dem Speicher
	 * @param address Adresse im Speicher
	 * @return Byte
	 */
	virtual uint8_t read(const UBankedAddress address) const;
	/**
	 * Liest Nibble aus Portschnittstelle
	 * @param chip Chip
	 * @return value Wert
	 */
	virtual uint4_t readFromPort(const EROMChip chip) const;
	/**
	 * Schreibe Nibble auf Portschnittstelle
	 * @param chip Chip
	 * @param value Wert
	 * @return <c>true</c> wenn addressierbar, sonst <c>false</c>
	 */
	virtual bool writeToPort(const EROMChip chip, const uint4_t value);

	virtual void setSource(const uint8_t source);

	virtual bool isBankInstalled(const EROMChip chip) const;

private:
	uint8_t rom_memory[16 * 256];
	uint16_t installed_banks;
	uint4_t ports[16];
};

#endif