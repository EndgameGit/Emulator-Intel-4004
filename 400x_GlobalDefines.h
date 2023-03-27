/*
 * 400x_GlobalDefines.h
 *
 *  Created on: 31.01.2021
 *      Author: Thomas Staudacher
 */

#ifndef INCLUDE_400X_GLOBALDEFINES_H_
#define INCLUDE_400X_GLOBALDEFINES_H_

#include <cstdint>

using namespace std;

/**
 * Bänke der Speicherverwaltung.
 * Dokumentation unter 'MCS-4_Assembly_Language_Programming_Manual_Dec73.pdf' S.78 DCL Befehl
 */
typedef enum : uint8_t
{
        ROMCHIP0,  //!< Chip 0
        ROMCHIP1,  //!< Chip 1
        ROMCHIP2,  //!< Chip 2
        ROMCHIP3,  //!< Chip 3
        ROMCHIP4,  //!< Chip 4
        ROMCHIP5,  //!< Chip 5
        ROMCHIP6,  //!< Chip 6
        ROMCHIP7,  //!< Chip 7
        ROMCHIP8,  //!< Chip 8
        ROMCHIP9,  //!< Chip 9
        ROMCHIP10, //!< Chip 10
        ROMCHIP11, //!< Chip 11
        ROMCHIP12, //!< Chip 12
        ROMCHIP13, //!< Chip 13
        ROMCHIP14, //!< Chip 14
        ROMCHIP15  //!< Chip 15
} EROMChip;

/**
 * Bänke der Speicherverwaltung.
 * Dokumentation unter 'MCS-4_Assembly_Language_Programming_Manual_Dec73.pdf' S.78 DCL Befehl
 */
typedef enum : uint8_t
{
        BANK0, //!< Bank 0
        BANK1, //!< Bank 1
        BANK2, //!< Bank 2
        BANK3, //!< Bank 3
        BANK4, //!< Bank 4
        BANK5, //!< Bank 5
        BANK6, //!< Bank 6
        BANK7, //!< Bank 7
} ERAMBank;

/**
 * Chipposition Speicherverwaltung.
 * Dokumentation unter 'MCS-4_Assembly_Language_Programming_Manual_Dec73.pdf' S.79 SRC Befehl
 */
typedef enum : uint8_t
{
        CHIP0, //!< Chip 0
        CHIP1, //!< Chip 1
        CHIP2, //!< Chip 2
        CHIP3, //!< Chip 3
} ERAMChip;

/**
 * Status Register zur Adressierung der Speicherstelle.
 * Dokumentation unter 'MCS-4_Assembly_Language_Programming_Manual_Dec73.pdf' S.79 SRC Befehl
 */
typedef enum : uint8_t
{
        REG0, //!< Register 0
        REG1, //!< Register 1
        REG2, //!< Register 2
        REG3, //!< Register 3
} ERAMRegister;

#ifdef _RAM_SPLITOFF_
typedef enum
{
        UNKNOWN,            //!< Unbekanmntes Kommando (gehört nicht zum Modul RAM)
        NO_RAM_IMPLEMENTED, //!< Für RAM freie Projekte zum testen
        DCL,                //!< Kommando 'DCL'
        SRC,                //!< Kommando 'SRC'
        WRM,                //!< Kommando 'WRM'
        WMP,                //!< Kommando 'WMP'
        WR0,                //!< Kommando 'WR0'
        WR1,                //!< Kommando 'WR1'
        WR2,                //!< Kommando 'WR2'
        WR3,                //!< Kommando 'WR3'
        SBM,                //!< Kommando 'SBM'
        RDM,                //!< Kommando 'RDM'
        ADM,                //!< Kommando 'ADM'
        RD0,                //!< Kommando 'RD0'
        RD1,                //!< Kommando 'RD1'
        RD2,                //!< Kommando 'RD2'
        RD3                 //!< Kommando 'RD3'
} ERAMCommand;
#endif

typedef uint8_t uint4_t;
typedef uint16_t uint12_t;

/**
 * Adressangabe für das ROM
 */
union UBankedAddress
{
        /**
         * Initalisierungs-Konstruktor
         * @param value Linearer Speicherwert ohne Bankangabe
         */
        UBankedAddress(const uint12_t value = 0) : raw{value}
        {
        }

        /**
         * Initalisierungs-Konstruktor
         * @param bank Bankangabe
         * @param address Address segmentiert
         */
        UBankedAddress(const uint4_t bank, const uint8_t address) : banked{banked.address = address, banked.bank = bank}
        {
        }

        uint12_t raw; //!< Rohwert

        struct
        {
                uint8_t address;  //!< Adresse im Segment
                uint8_t bank : 4; //!< Bankangabe
                uint8_t : 4;
        } banked; //!< Segmente in Bank und Segmentadresse

        /**
         * Erhöht die Adresse (Wert) um 1
         * @return Adresse (Wert) um 1 erhöht
         */
        uint12_t inc()
        {
                return raw = 0x0FFF & (raw + 1);
        }
};

/**
 * Ein Byte in ein Kommando zerlegt
 */
union UCommand
{
        uint8_t data; //!< Rohwert
        struct
        {
                uint8_t opa : 4; //!< Unter Teil des Befehls
                uint8_t opr : 4; //!< Hauptbefehl
        } nibble;                //!< Einzelen 4Bit Werte
};

/**
 * Definition der Register des i4004 (4Bit Breit)
 * Achtung: Bei Registerpaar (Bsp. R0/R1) ist R0 der High, R1 ist Low
 */
typedef enum
{
        Pair_R1_R0,   //!< Registerpaar R1/R0
        R0 = 0,       //!< Register R0 (High)
        R1,           //!< Register R1 (Low)
        Pair_R3_R2,   //!< Registerpaar R3/R2
        R2 = 2,       //!< Register R2 (High)
        R3,           //!< Register R3 (Low)
        Pair_R5_R4,   //!< Registerpaar R5/R4
        R4 = 4,       //!< Register R4 (High)
        R5,           //!< Register R5 (Low)
        Pair_R7_R6,   //!< Registerpaar R7/R6
        R6 = 6,       //!< Register R6 (High)
        R7,           //!< Register R7 (Low)
        Pair_R9_R8,   //!< Registerpaar R9/R8
        R8 = 8,       //!< Register R8 (High)
        R9,           //!< Register R9 (Low)
        Pair_R11_R10, //!< Registerpaar R11/R10
        R10 = 10,     //!< Register R10 (High)
        R11,          //!< Register R11 (Low)
        Pair_R13_R12, //!< Registerpaar R13/R12
        R12 = 12,     //!< Register R12 (High)
        R13,          //!< Register R13 (Low)
        Pair_R15_R14, //!< Registerpaar R15/R14
        R14 = 14,     //!< Register R14 (High)
        R15           //!< Register R15 (Low)
} ERegister;

#pragma pack(push, 1)
/**
 * Definition der Registerpaars des i4004 (4Bit Breit)
 * Achtung: Bei Registerpaar (Bsp. R0/R1) ist R0 der High, R1 ist Low
 */
union URegisterPair
{
        /**
         * Initialisiert die Union
         * @param value Rohwert
         */
        URegisterPair(const uint8_t value = 0) : raw(value)
        {
        }
        uint8_t raw; //!< Rohwert
        struct
        {
                uint8_t R1 : 4; //!< Register R1,R3,R5,R7,R9,R11,R13,R15
                uint8_t R0 : 4; //!< Register R0,R2,R4,R6,R8,R10,R12,R14
        } pair;                 //!< Registerpaar

        /**
         * Setzt das Register zurück
         */
        void reset()
        {
                raw = 0;
        }
};

union Usrc
{
        /**
         * Initalisierungs-Konstruktor
         * @param value Linearer Speicherwert ohne Bankangabe
         */
        Usrc(const uint8_t value = 0) : raw{value}
        {
        }

        uint8_t raw;

        struct
        {
                uint4_t register_data : 4;
                uint4_t ram_register : 2;
                uint4_t ram_chip : 2;
        } ram_data_character;

        struct
        {
                uint4_t : 4;
                uint4_t ram_register : 2;
                uint4_t ram_chip : 2;
        } ram_status_character;

        struct
        {
                uint4_t : 6;
                uint4_t port : 2;
        } ram_output_port;

        struct
        {
                uint4_t : 4;
                uint4_t port : 4;
        } rom_io_port;
};

#pragma pack(pop)

#endif /* INCLUDE_400X_GLOBALDEFINES_H_ */
