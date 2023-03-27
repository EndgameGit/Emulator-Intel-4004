#include "Intel4002.h"

/* 
*   Intel4004 Emulator
*   Gruppe: Tobias Traiser, Kilian Wachter, Pascal Wildermuth, Shaig Rustamov
*   Projektabgabe C 2.Semester - 18.07.2021
*/

Intel4002::Intel4002(const uint32_t installed_ram = 0xFFFFFFFF) : installed_ram(installed_ram)
{
    reset();
}

Intel4002::~Intel4002() {
}

void Intel4002::reset() {
    for (int i = 0; i < 2048; i++)
	{
		this->ram_memory[i] = 0;
	}
    for (int i = 0; i < 512; i++)
	{
		this->ram_status_memory[i] = 0;
	}
    for (int i = 0; i < 32; i++) {
        this->ram_ports[i] = 0;
    }
}

bool Intel4002::isRAMAdrAccessable(const ERAMBank bank,
        const ERAMChip chips) const {
            return (this->installed_ram & (1 << (bank * 4 + chips))) != 0;
        }

uint4_t Intel4002::readRAMNibble(const ERAMBank bank, const ERAMChip chip,
        const ERAMRegister ramregister, const int nibbleaddress) const {
            return this->ram_memory[bank * 256 + chip * 64 + ramregister * 16 + nibbleaddress];
        }

bool Intel4002::writeRAMNibble(const ERAMBank bank, const ERAMChip chip,
        const ERAMRegister ramregister, const int nibbleaddress,
        const uint4_t value) {
            if(isRAMAdrAccessable(bank, chip)){
                this->ram_memory[bank * 256 + chip * 64 + ramregister * 16 + nibbleaddress] = value;
                return true;
            }
            return false;
            
        }

bool Intel4002::isStatusAdrAccessable(const ERAMBank bank,
        const ERAMChip chip) const {
            return isRAMAdrAccessable(bank, chip);
        }

uint4_t Intel4002::readStatusNibble(const ERAMBank bank, const ERAMChip chip,
        const ERAMRegister ramregister, const int nibbleaddress) const {
            return this->ram_status_memory[bank * 64 + chip * 16 + ramregister * 4 + nibbleaddress];
        }

bool Intel4002::writeStatusNibble(const ERAMBank bank, const ERAMChip chip,
        const ERAMRegister ramregister, const int nibbleaddress,
        const uint4_t value) {
            if(isRAMAdrAccessable(bank, chip)){
            this->ram_status_memory[bank * 64 + chip * 16 + ramregister * 4 + nibbleaddress] = value;
            return true;
            }
            return false;
        }

uint4_t Intel4002::readFromPortBuffer(const ERAMBank bank,
        const ERAMChip chip) const {
            return ram_ports[bank * 4 + chip];
        }

void Intel4002::writeToPortBuffer(const ERAMBank bank,
			const ERAMChip chip, uint4_t value) {
                if(isRAMAdrAccessable(bank, chip)) {
                    ram_ports[bank * 4 + chip] = value;
                }
        }
