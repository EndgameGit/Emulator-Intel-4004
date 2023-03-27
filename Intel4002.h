#ifndef _INTEL4002_H_
#define _INTEL4002_H_

#include "MCS4BaseClasses.h"

/* 
*   Intel4004 Emulator
*   Gruppe: Tobias Traiser, Kilian Wachter, Pascal Wildermuth, Shaig Rustamov
*   Projektabgabe C 2.Semester - 18.07.2021
*/

class Intel4002 : public Intel4002Base {
public:
	/**
	 * Konstruktor
	 */
	Intel4002(const uint32_t installed_ram);
	
	/**
	 * Destruktor
	 */
	virtual ~Intel4002();
	/**
	 * Setzt die internen Register zurück zurück
	 */
	virtual void reset();
	/**
	 * Ist die RAM Adresse vorhanden.
	 * Falls nicht wird false zurückgegeben
	 * @param bank Bank 0...7
	 * @param chip Chip 0...3
	 * @return <c>true</c> wenn addressierbar, sonst <c>false</c>
	 */
	virtual bool isRAMAdrAccessable(const ERAMBank bank,
			const ERAMChip chips) const;
	/**
	 * Ein Nibble an der derzeit angeforderten Adresse
	 * @param bank Bank 0...7
	 * @param chip Chip 0...3
	 * @param ramregister Register 0...3
	 * @param nibbleaddress Speicherzellenaddresse 0...15
	 * @return Wert
	 */
	virtual uint4_t readRAMNibble(const ERAMBank bank, const ERAMChip chip,
			const ERAMRegister ramregister, const int nibbleaddress) const;
	/**
	 * Ein Nibble an der derzeit angeforderten Adresse
	 * @param bank Bank 0...7
	 * @param chip Chip 0...3
	 * @param ramregister Register 0...3
	 * @param nibbleaddress Speicherzellenaddresse 0...15
	 * @param value Wert
	 * @return Ob an dieser Stelle schreibbar war
	 */
	virtual bool writeRAMNibble(const ERAMBank bank, const ERAMChip chip,
			const ERAMRegister ramregister, const int nibbleaddress,
			const uint4_t value);
	/**
	 * Ist die Status Adresse vorhanden.
	 * Falls nicht wird false zurückgegeben
	 * @param bank Bank 0...7
	 * @param chip Chip 0...3
	 * @return <c>true</c> wenn addressierbar, sonst <c>false</c>
	 */
	virtual bool isStatusAdrAccessable(const ERAMBank bank,
			const ERAMChip chip) const;
	/**
	 * Ein Nibble an der derzeit angeforderten Adresse
	 * @param bank Bank 0...7
	 * @param chip Chip 0...3
	 * @param ramregister Register 0...3
	 * @param nibbleaddress Speicherzellenaddresse 0...3
	 * @return Wert
	 */
	virtual uint4_t readStatusNibble(const ERAMBank bank, const ERAMChip chip,
			const ERAMRegister ramregister, const int nibbleaddress) const;
	/**
	 * Ein Nibble an der derzeit angeforderten Adresse
	 * @param bank Bank 0...7
	 * @param chip Chip 0...3
	 * @param ramregister Register 0...3
	 * @param nibbleaddress Speicherzellenaddresse 0...3
	 * @param value Wert
	 * @return Ob an dieser Stelle schreibbar war
	 */
	virtual bool writeStatusNibble(const ERAMBank bank, const ERAMChip chip,
			const ERAMRegister ramregister, const int nibbleaddress,
			const uint4_t value);
	/**
	 * Liest ein Nibble aus dem Ausgangspuffer
	 * @param bank Bank
	 * @param chip Chip
	 * @return Wert
	 */
	virtual uint4_t readFromPortBuffer(const ERAMBank bank,
			const ERAMChip chip) const;

	virtual void writeToPortBuffer(const ERAMBank bank,
			const ERAMChip chip, uint4_t value);

private:
	uint4_t ram_memory[2048];
	uint4_t ram_status_memory[512];
	uint4_t ram_ports[32];
	uint32_t installed_ram;

#ifdef _RAM_SPLITOFF_
	/**
	 * Befehl der an die Adressleitungen des RAM geschickt wird und an die ausgelagerte RAM Befehlsauführung.
	 * @param ptr Zugriff auf den Intel 4004 Prozessor
	 * @param command Kommando aus der Befehlsablaufsteuerung
	 * @return Erkannter Befehl
	 */
	virtual ERAMCommand nextCommand(Intel4004Base *ptr,
			const UCommand command) = 0;
#endif
};

#endif