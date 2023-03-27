#include <Intel4004.h>
#include <CommandsPW.h>

/* 
*   Intel4004 Emulator
*   Gruppe: Tobias Traiser, Kilian Wachter, Pascal Wildermuth, Shaig Rustamov
*   Projektabgabe C 2.Semester - 18.07.2021
*/

/**
	 * Konstruktor
	 */
Intel4004::Intel4004(const uint16_t installed_ROM_Chips,
					 const uint32_t installed_RAM_Chips) : carry(false), accumulator(0), rompointer(0), ticks(0), rampointer(0), stackpointer(0), testpin(false), control(0), selected_ram_bank(BANK0), source_address(0)
{
	rampointer = new Intel4002(installed_RAM_Chips);
	rompointer = new Intel4001(installed_ROM_Chips);
	stackpointer = new Intel4004Stack();
	reset();
}
/**
	 * Destruktor
	 */
Intel4004::~Intel4004()
{
}
/**
	 * Setzt den Prozessor zurück
	 */
void Intel4004::reset()
{
	rampointer->reset();
	rompointer->reset();
	stackpointer->reset();
	carry = false;
	accumulator = 0;
	ticks = 0;
	control = 0;
	selected_ram_bank = BANK0;
	source_address = 0;
	for (int i = 0; i < 16; i++)
	{
		working_register[i] = 0b0000;
		register_pair[i] = 0b00000000;
	}
};
/**
	 * Gibt den Wert des Übertrags aus.
	 * <br>Hinweis:</br> Siehe studienarbeit-4004.pdf S.19
	 * @return Übertrag
	 */
bool Intel4004::getCarry() const
{
	return carry;
};

/**
	 * Gibt den Wert des Akkumulators aus.
	 * <br>Hinweis:</br> Siehe studienarbeit-4004.pdf S.19
	 * @return Akkumulator
	 */
uint4_t Intel4004::getAccumulator() const
{
	return accumulator;
};

/**
	 * Gibt die aktuelle Adresse der Ablaufsteuerung aus.
	 * <br>Hinweis:</br> Siehe studienarbeit-4004.pdf S.19
	 * @return Adresse der Ablaufsteuerung
	 */
UBankedAddress Intel4004::getPC() const
{
	return control;
};
/**
	 * Dient zum Auslesen eines Registers (Register 0..15).
	 * <br>Hinweis:</br> Siehe studienarbeit-4004.pdf S.19 und MCS-4_Assembly_Language_Programming_Manual_Dec73.pdf S. 11
	 * @param reg Registernummer
	 * @return Nibble
	 */
uint4_t Intel4004::getRegister(const ERegister reg)
{
	return working_register[((int)reg)];
};

/**
	 * Dient zum Auslesen eines Registerspaars (Register R1R0 ... R15R14).
	 * <br>Hinweis:</br> Siehe studienarbeit-4004.pdf S.19 und MCS-4_Assembly_Language_Programming_Manual_Dec73.pdf S. 11
	 * @param reg Registerpaar Nummer
	 * @return Byte
	 */
uint8_t Intel4004::getRegisterPair(const ERegister reg)
{
	return register_pair[((int)reg)];
};
/**
	 * Gibt den ROM Handle zurück.
	 * @return ROM Handle
	 */
Intel4001Base *Intel4004::getPtrToROM()
{
	return rompointer;
};
/**
	 * Gibt den RAM Handle zurück.
	 * @return RAM Handle
	 */
Intel4002Base *Intel4004::getPtrToRAM()
{
	return rampointer;
};
/**
	 * Gibt den Stack Handle zurück.
	 * @return Stack Handle
	 */
Intel4004StackBase *Intel4004::getPtrToStack()
{
	return stackpointer;
}
/**
	 * Gibt die Anzahl der Ticks (Subzyklen) zurück die bisher gemessen wurden.
	 * <br>Hinweis:</br> Siehe studienarbeit-4004.pdf S.6
	 * @return Anzahl Ticks
	 */
uint64_t Intel4004::getTicks() const
{
	return ticks;
};
/**
	 * Setzt die Ticks zurück (Subzyklen)
	 */
void Intel4004::resetTicks()
{
	ticks = 0;
};
/** Gibt den Pin zurück (Hardwareschnittstelle).
	 * <br>Hinweis:</br> Siehe studienarbeit-4004.pdf S.6
	 * @return <c>true</c> wenn eingeschaltet, sonst <c>false</c>
	 */
bool Intel4004::getTestPin() const
{
	return testpin;
};

void Intel4004::setRegister(uint4_t registerNum, uint4_t value)
{
	working_register[registerNum] = value;
}
/**
	 * Setzt den Pin (Hardwareschnittstelle)
	 * <BR>Hinweis:</BR> Siehe studienarbeit-4004.pdf S.6
	 * @param value <c>true</c> wenn eingeschaltet, sonst <c>false</c>
	 */
void Intel4004::setTestPin(const bool value)
{
	testpin = value;
};
/** Ruft die Programmablaufschnittstelle auf. Über diese Schnittstelle können die Befehle Step für Step abgearbeitet werden. */
void Intel4004::nextCommand()
{

	uint8_t a = this->rompointer->read(this->control);

	switch (a)
	{
	case 0x00: //NOP: No Operation
		break;
	case 0x01:
		break;
	case 0x02:
		break;
	case 0x03:
		break;
	case 0x04:
		break;
	case 0x05:
		break;
	case 0x06:
		break;
	case 0x07:
		break;
	case 0x08:
		break;
	case 0x09:
		break;
	case 0x0A:
		break;
	case 0x0B:
		break;
	case 0x0C:
		break;
	case 0x0D:
		break;
	case 0x0E:
		break;
	case 0x0F:
		break;

	case 0x10:
		comm_jcn(this, 0);
		break;
	case 0x11:
		comm_jcn(this, 1);
		break;
	case 0x12:
		comm_jcn(this, 2);
		break;
	case 0x13:
		comm_jcn(this, 3);
		break;
	case 0x14:
		comm_jcn(this, 4);
		break;
	case 0x15:
		comm_jcn(this, 5);
		break;
	case 0x16:
		comm_jcn(this, 6);
		break;
	case 0x17:
		comm_jcn(this, 7);
		break;
	case 0x18:
		comm_jcn(this, 8);
		break;
	case 0x19:
		comm_jcn(this, 9);
		break;
	case 0x1A:
		comm_jcn(this, 10);
		break;
	case 0x1B:
		comm_jcn(this, 11);
		break;
	case 0x1C:
		comm_jcn(this, 12);
		break;
	case 0x1D:
		comm_jcn(this, 13);
		break;
	case 0x1E:
		comm_jcn(this, 14);
		break;
	case 0x1F:
		comm_jcn(this, 15);
		break;

	case 0x20:
		comm_fim(this, 0);
		break;
	case 0x21:
		comm_src(this, 0);
		break;
	case 0x22:
		comm_fim(this, 2);
		break;
	case 0x23:
		comm_src(this, 2);
		break;
	case 0x24:
		comm_fim(this, 4);
		break;
	case 0x25:
		comm_src(this, 4);
		break;
	case 0x26:
		comm_fim(this, 6);
		break;
	case 0x27:
		comm_src(this, 6);
		break;
	case 0x28:
		comm_fim(this, 8);
		break;
	case 0x29:
		comm_src(this, 8);
		break;
	case 0x2A:
		comm_fim(this, 10);
		break;
	case 0x2B:
		comm_src(this, 10);
		break;
	case 0x2C:
		comm_fim(this, 12);
		break;
	case 0x2D:
		comm_src(this, 12);
		break;
	case 0x2E:
		comm_fim(this, 14);
		break;
	case 0x2F:
		comm_src(this, 14);
		break;

	case 0x30:
		comm_fin(this, 0);
		break;
	case 0x31:
		comm_jin(this, 0);
		break;
	case 0x32:
		comm_fin(this, 2);
		break;
	case 0x33:
		comm_jin(this, 2);
		break;
	case 0x34:
		comm_fin(this, 4);
		break;
	case 0x35:
		comm_jin(this, 4);
		break;
	case 0x36:
		comm_fin(this, 6);
		break;
	case 0x37:
		comm_jin(this, 6);
		break;
	case 0x38:
		comm_fin(this, 8);
		break;
	case 0x39:
		comm_jin(this, 8);
		break;
	case 0x3A:
		comm_fin(this, 10);
		break;
	case 0x3B:
		comm_jin(this, 10);
		break;
	case 0x3C:
		comm_fin(this, 12);
		break;
	case 0x3D:
		comm_jin(this, 12);
		break;
	case 0x3E:
		comm_fin(this, 14);
		break;
	case 0x3F:
		comm_jin(this, 14);
		break;

	case 0x40:
		comm_jun(this, 0x000);
		break;
	case 0x41:
		comm_jun(this, 0x100);
		break;
	case 0x42:
		comm_jun(this, 0x200);
		break;
	case 0x43:
		comm_jun(this, 0x300);
		break;
	case 0x44:
		comm_jun(this, 0x400);
		break;
	case 0x45:
		comm_jun(this, 0x500);
		break;
	case 0x46:
		comm_jun(this, 0x600);
		break;
	case 0x47:
		comm_jun(this, 0x700);
		break;
	case 0x48:
		comm_jun(this, 0x800);
		break;
	case 0x49:
		comm_jun(this, 0x900);
		break;
	case 0x4A:
		comm_jun(this, 0xA00);
		break;
	case 0x4B:
		comm_jun(this, 0xB00);
		break;
	case 0x4C:
		comm_jun(this, 0xC00);
		break;
	case 0x4D:
		comm_jun(this, 0xD00);
		break;
	case 0x4E:
		comm_jun(this, 0xE00);
		break;
	case 0x4F:
		comm_jun(this, 0xF00);
		break;

	case 0x50:
		comm_jms(this, 0x000);
		break; //second digit is part of jump address
	case 0x51:
		comm_jms(this, 0x100);
		break;
	case 0x52:
		comm_jms(this, 0x200);
		break;
	case 0x53:
		comm_jms(this, 0x300);
		break;
	case 0x54:
		comm_jms(this, 0x400);
		break;
	case 0x55:
		comm_jms(this, 0x500);
		break;
	case 0x56:
		comm_jms(this, 0x600);
		break;
	case 0x57:
		comm_jms(this, 0x700);
		break;
	case 0x58:
		comm_jms(this, 0x800);
		break;
	case 0x59:
		comm_jms(this, 0x900);
		break;
	case 0x5A:
		comm_jms(this, 0xA00);
		break;
	case 0x5B:
		comm_jms(this, 0xB00);
		break;
	case 0x5C:
		comm_jms(this, 0xC00);
		break;
	case 0x5D:
		comm_jms(this, 0xD00);
		break;
	case 0x5E:
		comm_jms(this, 0xE00);
		break;
	case 0x5F:
		comm_jms(this, 0xF00);
		break;

	case 0x60:
		comm_inc(this, 0);
		break;
	case 0x61:
		comm_inc(this, 1);
		break;
	case 0x62:
		comm_inc(this, 2);
		break;
	case 0x63:
		comm_inc(this, 3);
		break;
	case 0x64:
		comm_inc(this, 4);
		break;
	case 0x65:
		comm_inc(this, 5);
		break;
	case 0x66:
		comm_inc(this, 6);
		break;
	case 0x67:
		comm_inc(this, 7);
		break;
	case 0x68:
		comm_inc(this, 8);
		break;
	case 0x69:
		comm_inc(this, 9);
		break;
	case 0x6A:
		comm_inc(this, 10);
		break;
	case 0x6B:
		comm_inc(this, 11);
		break;
	case 0x6C:
		comm_inc(this, 12);
		break;
	case 0x6D:
		comm_inc(this, 13);
		break;
	case 0x6E:
		comm_inc(this, 14);
		break;
	case 0x6F:
		comm_inc(this, 15);
		break;

	case 0x70:
		comm_isz(this, 0);
		break;
	case 0x71:
		comm_isz(this, 1);
		break;
	case 0x72:
		comm_isz(this, 2);
		break;
	case 0x73:
		comm_isz(this, 3);
		break;
	case 0x74:
		comm_isz(this, 4);
		break;
	case 0x75:
		comm_isz(this, 5);
		break;
	case 0x76:
		comm_isz(this, 6);
		break;
	case 0x77:
		comm_isz(this, 7);
		break;
	case 0x78:
		comm_isz(this, 8);
		break;
	case 0x79:
		comm_isz(this, 9);
		break;
	case 0x7A:
		comm_isz(this, 10);
		break;
	case 0x7B:
		comm_isz(this, 11);
		break;
	case 0x7C:
		comm_isz(this, 12);
		break;
	case 0x7D:
		comm_isz(this, 13);
		break;
	case 0x7E:
		comm_isz(this, 14);
		break;
	case 0x7F:
		comm_isz(this, 15);
		break;

	case 0x80:
		comm_add(this, 0);
		break;
	case 0x81:
		comm_add(this, 1);
		break;
	case 0x82:
		comm_add(this, 2);
		break;
	case 0x83:
		comm_add(this, 3);
		break;
	case 0x84:
		comm_add(this, 4);
		break;
	case 0x85:
		comm_add(this, 5);
		break;
	case 0x86:
		comm_add(this, 6);
		break;
	case 0x87:
		comm_add(this, 7);
		break;
	case 0x88:
		comm_add(this, 8);
		break;
	case 0x89:
		comm_add(this, 9);
		break;
	case 0x8A:
		comm_add(this, 10);
		break;
	case 0x8B:
		comm_add(this, 11);
		break;
	case 0x8C:
		comm_add(this, 12);
		break;
	case 0x8D:
		comm_add(this, 13);
		break;
	case 0x8E:
		comm_add(this, 14);
		break;
	case 0x8F:
		comm_add(this, 15);
		break;

	case 0x90:
		comm_sub(this, 0);
		break;
	case 0x91:
		comm_sub(this, 1);
		break;
	case 0x92:
		comm_sub(this, 2);
		break;
	case 0x93:
		comm_sub(this, 3);
		break;
	case 0x94:
		comm_sub(this, 4);
		break;
	case 0x95:
		comm_sub(this, 5);
		break;
	case 0x96:
		comm_sub(this, 6);
		break;
	case 0x97:
		comm_sub(this, 7);
		break;
	case 0x98:
		comm_sub(this, 8);
		break;
	case 0x99:
		comm_sub(this, 9);
		break;
	case 0x9A:
		comm_sub(this, 10);
		break;
	case 0x9B:
		comm_sub(this, 11);
		break;
	case 0x9C:
		comm_sub(this, 12);
		break;
	case 0x9D:
		comm_sub(this, 13);
		break;
	case 0x9E:
		comm_sub(this, 14);
		break;
	case 0x9F:
		comm_sub(this, 15);
		break;

	case 0xA0:
		comm_ld(this, 0);
		break;
	case 0xA1:
		comm_ld(this, 1);
		break;
	case 0xA2:
		comm_ld(this, 2);
		break;
	case 0xA3:
		comm_ld(this, 3);
		break;
	case 0xA4:
		comm_ld(this, 4);
		break;
	case 0xA5:
		comm_ld(this, 5);
		break;
	case 0xA6:
		comm_ld(this, 6);
		break;
	case 0xA7:
		comm_ld(this, 7);
		break;
	case 0xA8:
		comm_ld(this, 8);
		break;
	case 0xA9:
		comm_ld(this, 9);
		break;
	case 0xAA:
		comm_ld(this, 10);
		break;
	case 0xAB:
		comm_ld(this, 11);
		break;
	case 0xAC:
		comm_ld(this, 12);
		break;
	case 0xAD:
		comm_ld(this, 13);
		break;
	case 0xAE:
		comm_ld(this, 14);
		break;
	case 0xAF:
		comm_ld(this, 15);
		break;

	case 0xB0:
		comm_xch(this, 0);
		break;
	case 0xB1:
		comm_xch(this, 1);
		break;
	case 0xB2:
		comm_xch(this, 2);
		break;
	case 0xB3:
		comm_xch(this, 3);
		break;
	case 0xB4:
		comm_xch(this, 4);
		break;
	case 0xB5:
		comm_xch(this, 5);
		break;
	case 0xB6:
		comm_xch(this, 6);
		break;
	case 0xB7:
		comm_xch(this, 7);
		break;
	case 0xB8:
		comm_xch(this, 8);
		break;
	case 0xB9:
		comm_xch(this, 9);
		break;
	case 0xBA:
		comm_xch(this, 10);
		break;
	case 0xBB:
		comm_xch(this, 11);
		break;
	case 0xBC:
		comm_xch(this, 12);
		break;
	case 0xBD:
		comm_xch(this, 13);
		break;
	case 0xBE:
		comm_xch(this, 14);
		break;
	case 0xBF:
		comm_xch(this, 15);
		break;

	case 0xC0:
		comm_bbl(this, 0);
		break;
	case 0xC1:
		comm_bbl(this, 1);
		break;
	case 0xC2:
		comm_bbl(this, 2);
		break;
	case 0xC3:
		comm_bbl(this, 3);
		break;
	case 0xC4:
		comm_bbl(this, 4);
		break;
	case 0xC5:
		comm_bbl(this, 5);
		break;
	case 0xC6:
		comm_bbl(this, 6);
		break;
	case 0xC7:
		comm_bbl(this, 7);
		break;
	case 0xC8:
		comm_bbl(this, 8);
		break;
	case 0xC9:
		comm_bbl(this, 9);
		break;
	case 0xCA:
		comm_bbl(this, 10);
		break;
	case 0xCB:
		comm_bbl(this, 11);
		break;
	case 0xCC:
		comm_bbl(this, 12);
		break;
	case 0xCD:
		comm_bbl(this, 13);
		break;
	case 0xCE:
		comm_bbl(this, 14);
		break;
	case 0xCF:
		comm_bbl(this, 15);
		break;

	case 0xD0:
		comm_ldm(this, 0);
		break;
	case 0xD1:
		comm_ldm(this, 1);
		break;
	case 0xD2:
		comm_ldm(this, 2);
		break;
	case 0xD3:
		comm_ldm(this, 3);
		break;
	case 0xD4:
		comm_ldm(this, 4);
		break;
	case 0xD5:
		comm_ldm(this, 5);
		break;
	case 0xD6:
		comm_ldm(this, 6);
		break;
	case 0xD7:
		comm_ldm(this, 7);
		break;
	case 0xD8:
		comm_ldm(this, 8);
		break;
	case 0xD9:
		comm_ldm(this, 9);
		break;
	case 0xDA:
		comm_ldm(this, 10);
		break;
	case 0xDB:
		comm_ldm(this, 11);
		break;
	case 0xDC:
		comm_ldm(this, 12);
		break;
	case 0xDD:
		comm_ldm(this, 13);
		break;
	case 0xDE:
		comm_ldm(this, 14);
		break;
	case 0xDF:
		comm_ldm(this, 15);
		break;

	case 0xE0:
		comm_wrm(this);
		break;
	case 0xE1:
		comm_wmp(this);
		break;
	case 0xE2:
		comm_wrr(this);
		break;
	case 0xE3:
		comm_wpm(this);
		break;
	case 0xE4:
		comm_wr0(this);
		break;
	case 0xE5:
		comm_wr1(this);
		break;
	case 0xE6:
		comm_wr2(this);
		break;
	case 0xE7:
		comm_wr3(this);
		break;
	case 0xE8:
		comm_sbm(this);
		break;
	case 0xE9:
		comm_rdm(this);
		break;
	case 0xEA:
		comm_rdr(this);
		break;
	case 0xEB:
		comm_adm(this);
		break;
	case 0xEC:
		comm_rd0(this);
		break;
	case 0xED:
		comm_rd1(this);
		break;
	case 0xEE:
		comm_rd2(this);
		break;
	case 0xEF:
		comm_rd3(this);
		break;

	case 0xF0:
		comm_clb(this);
		break;
	case 0xF1:
		comm_clc(this);
		break;
	case 0xF2:
		comm_iac(this);
		break;
	case 0xF3:
		comm_cmc(this);
		break;
	case 0xF4:
		comm_cma(this);
		break;
	case 0xF5:
		comm_ral(this);
		break;
	case 0xF6:
		comm_rar(this);
		break;
	case 0xF7:
		comm_tcc(this);
		break;
	case 0xF8:
		comm_dac(this);
		break;
	case 0xF9:
		comm_tcs(this);
		break;
	case 0xFA:
		comm_stc(this);
		break;
	case 0xFB:
		comm_daa(this);
		break;
	case 0xFC:
		comm_kbp(this);
		break;
	case 0xFD:
		comm_dcl(this);
		break;
	case 0xFE:
		break;
	case 0xFF:
		break;

	default:
		break;
	}

	control.raw++;
	ticks += 8;
};