#ifndef _INTEL4004_H_
#define _INTEL4004_H_
#include "MCS4BaseClasses.h"
#include <Intel4002.h>
#include <Intel4001.h>
#include <Intel4004Stack.h>

/* 
*   Intel4004 Emulator
*   Gruppe: Tobias Traiser, Kilian Wachter, Pascal Wildermuth, Shaig Rustamov
*   Projektabgabe C 2.Semester - 18.07.2021
*/


class Intel4004 : public Intel4004Base
{
public:
	/**
	 * Konstruktor
	 */
	Intel4004(	const uint16_t installed_ROM_Chips,
				const uint32_t installed_RAM_Chips);
	/**
	 * Destruktor
	 */
	virtual ~Intel4004();
	/**
	 * Setzt den Prozessor zurück
	 */
	virtual void reset();
	/**
	 * Gibt den Wert des Übertrags aus.
	 * <br>Hinweis:</br> Siehe studienarbeit-4004.pdf S.19
	 * @return Übertrag
	 */
	virtual bool getCarry() const;

	/**
	 * Gibt den Wert des Akkumulators aus.
	 * <br>Hinweis:</br> Siehe studienarbeit-4004.pdf S.19
	 * @return Akkumulator
	 */
	virtual uint4_t getAccumulator() const;

	/**
	 * Gibt die aktuelle Adresse der Ablaufsteuerung aus.
	 * <br>Hinweis:</br> Siehe studienarbeit-4004.pdf S.19
	 * @return Adresse der Ablaufsteuerung
	 */
	virtual UBankedAddress getPC() const;
	/**
	 * Dient zum auslesen eines Registers (Register 0..15).
	 * <br>Hinweis:</br> Siehe studienarbeit-4004.pdf S.19 und MCS-4_Assembly_Language_Programming_Manual_Dec73.pdf S. 11
	 * @param reg Registernummer
	 * @return Nibble
	 */
	virtual uint4_t getRegister(const ERegister reg);
	/**
	 * Dient zum auslesen eines Registerspaars (Register R1R0 ... R15R14).
	 * <br>Hinweis:</br> Siehe studienarbeit-4004.pdf S.19 und MCS-4_Assembly_Language_Programming_Manual_Dec73.pdf S. 11
	 * @param reg Registerpaar Nummer
	 * @return Byte
	 */
	virtual uint8_t getRegisterPair(const ERegister reg);
	/**
	 * Gibt den ROM Handle zurück.
	 * @return ROM Handle
	 */
	virtual Intel4001Base *getPtrToROM();
	/**
	 * Gibt den RAM Handle zurück.
	 * @return RAM Handle
	 */
	virtual Intel4002Base *getPtrToRAM();
	/**
	 * Gibt den Stack Handle zurück.
	 * @return Stack Handle
	 */
	virtual Intel4004StackBase *getPtrToStack();
	/**
	 * Gibt die Anzahl der Ticks (Subzyklen) zurück die bisher gemessen wurden.
	 * <br>Hinweis:</br> Siehe studienarbeit-4004.pdf S.6
	 * @return Anzahl Ticks
	 */
	virtual uint64_t getTicks() const;
	/**
	 * Setzt die Ticks zurück (Subzyklen)
	 */
	virtual void resetTicks();
	/** Gibt den Pin zurück (Hardwareschnittstelle).
	 * <br>Hinweis:</br> Siehe studienarbeit-4004.pdf S.6
	 * @return <c>true</c> wenn eingeschaltet, sonst <c>false</c>
	 */
	virtual bool getTestPin() const;

	virtual void setRegister(uint4_t registerNum, uint4_t value);
	/**
	 * Setzt den Pin (Hardwareschnittstelle)
	 * <BR>Hinweis:</BR> Siehe studienarbeit-4004.pdf S.6
	 * @param value <c>true</c> wenn eingeschaltet, sonst <c>false</c>
	 */
	virtual void setTestPin(const bool value);
	/** Ruft die Programmablaufschnittstelle auf. Über diese Schnittstelle können die Befehle Step für Step abgearbeitet werden. */
	virtual void nextCommand();

	//variablen
	bool carry;
	uint4_t accumulator;
	uint4_t working_register[16];
	Intel4001Base *rompointer;
	uint64_t ticks;
	Intel4002Base *rampointer;
	Intel4004StackBase *stackpointer;
	bool testpin;
	UBankedAddress control;
	uint8_t register_pair[16];
	ERAMBank selected_ram_bank;
	Usrc source_address;
};

#endif