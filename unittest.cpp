#define _UNITTEST_
#ifdef _UNITTEST_
#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
	#include "catch.hpp"
    #include "Intel4004.h"
#elif __unix__
	#include "../inc/catch.hpp"
    #include "../4004/4004.h"
#endif

#include <cstdint>

typedef enum : uint8_t {
    NOP,
    JCN_0 = 0x10,
    JCN_1,
    JNT = 0x11,
    JCN_2,
    JC = 0x12,
    JCN_3,
    JCN_4,
    JZ = 0x14,
    JCN_5,
    JCN_6,
    JCN_7,
    JCN_8,
    JCN_9,
    JT = 0x19,
    JCN_10,
    JNC = 0x1A,
    JCN_11,
    JCN_12,
    JNZ = 0x1C,
    JCN_13,
    JCN_14,
    JCN_15,
    FIM_0,
    SRC_0,
    FIM_2,
    SRC_2,
    FIM_4,
    SRC_4,
    FIM_6,
    SRC_6,
    FIM_8,
    SRC_8,
    FIM_10,
    SRC_10,
    FIM_12,
    SRC_12,
    FIM_14,
    SRC_14,
    FIN_0,
    JIN_0,
    FIN_2,
    JIN_2,
    FIN_4,
    JIN_4,
    FIN_6,
    JIN_6,
    FIN_8,
    JIN_8,
    FIN_10,
    JIN_10,
    FIN_12,
    JIN_12,
    FIN_14,
    JIN_14,
    JUN_0,
    JUN_1,
    JUN_2,
    JUN_3,
    JUN_4,
    JUN_5,
    JUN_6,
    JUN_7,
    JUN_8,
    JUN_9,
    JUN_10,
    JUN_11,
    JUN_12,
    JUN_13,
    JUN_14,
    JUN_15,
    JMS_0,
    JMS_1,
    JMS_2,
    JMS_3,
    JMS_4,
    JMS_5,
    JMS_6,
    JMS_7,
    JMS_8,
    JMS_9,
    JMS_10,
    JMS_11,
    JMS_12,
    JMS_13,
    JMS_14,
    JMS_15,
    INC_0,
    INC_1,
    INC_2,
    INC_3,
    INC_4,
    INC_5,
    INC_6,
    INC_7,
    INC_8,
    INC_9,
    INC_10,
    INC_11,
    INC_12,
    INC_13,
    INC_14,
    INC_15,
    ISZ_0,
    ISZ_1,
    ISZ_2,
    ISZ_3,
    ISZ_4,
    ISZ_5,
    ISZ_6,
    ISZ_7,
    ISZ_8,
    ISZ_9,
    ISZ_10,
    ISZ_11,
    ISZ_12,
    ISZ_13,
    ISZ_14,
    ISZ_15,
    ADD_0,
    ADD_1,
    ADD_2,
    ADD_3,
    ADD_4,
    ADD_5,
    ADD_6,
    ADD_7,
    ADD_8,
    ADD_9,
    ADD_10,
    ADD_11,
    ADD_12,
    ADD_13,
    ADD_14,
    ADD_15,
    SUB_0,
    SUB_1,
    SUB_2,
    SUB_3,
    SUB_4,
    SUB_5,
    SUB_6,
    SUB_7,
    SUB_8,
    SUB_9,
    SUB_10,
    SUB_11,
    SUB_12,
    SUB_13,
    SUB_14,
    SUB_15,
    LD_0,
    LD_1,
    LD_2,
    LD_3,
    LD_4,
    LD_5,
    LD_6,
    LD_7,
    LD_8,
    LD_9,
    LD_10,
    LD_11,
    LD_12,
    LD_13,
    LD_14,
    LD_15,
    XCH_0,
    XCH_1,
    XCH_2,
    XCH_3,
    XCH_4,
    XCH_5,
    XCH_6,
    XCH_7,
    XCH_8,
    XCH_9,
    XCH_10,
    XCH_11,
    XCH_12,
    XCH_13,
    XCH_14,
    XCH_15,
    BBL_0,
    BBL_1,
    BBL_2,
    BBL_3,
    BBL_4,
    BBL_5,
    BBL_6,
    BBL_7,
    BBL_8,
    BBL_9,
    BBL_10,
    BBL_11,
    BBL_12,
    BBL_13,
    BBL_14,
    BBL_15,
    LDM_0,
    LDM_1,
    LDM_2,
    LDM_3,
    LDM_4,
    LDM_5,
    LDM_6,
    LDM_7,
    LDM_8,
    LDM_9,
    LDM_10,
    LDM_11,
    LDM_12,
    LDM_13,
    LDM_14,
    LDM_15,
    WRM,
    WMP,
    WRR,
    WPM,
    WR0,
    WR1,
    WR2,
    WR3,
    SBM,
    RDM,
    RDR,
    ADM,
    RD0,
    RD1,
    RD2,
    RD3,
    CLB,
    CLC,
    IAC,
    CMC,
    CMA,
    RAL,
    RAR,
    TCC,
    DAC,
    TCS,
    STC,
    DAA,
    KBP,
    DCL
} COMMAND;

TEST_CASE("UnitTest_Intel4004_Mnemonics") {
    SECTION("NOP") {
        /**
         * NOP          1
         * NOP          1
         */

        uint8_t source[] = { NOP, NOP };

        Intel4004Base *processor = { get4004Instance(0xFFFF, 0xFFFFFFFF) };

        CHECK(processor->getPtrToROM()->writeFrom(source, sizeof(source)) == 2);

        CHECK_FALSE(processor->getCarry());
        CHECK_FALSE(processor->getAccumulator());
        CHECK(processor->getTicks() == 0);
        // NOP
        processor->nextCommand();
        CHECK_FALSE(processor->getCarry());
        CHECK_FALSE(processor->getAccumulator());

        CHECK(processor->getTicks() == 1);
    }
    SECTION("JCN") {
        /**
         * JCN_10 0x03  1   JUMP to 0x03 because carry=0
         * NOP          0
         * CMC          1   set carry=1
         * JCN_10 0x07  1   no JUMP because no condition is true
         * NOP          1
         * JCN_1 0x0A   1   JUMP to 0x0A because testPin=0
         * NOP          0
         * JCN_2 0x0D   1   JUMP to 0x0D because carry=1
         * NOP          0
         * JCN_4 0x10   1   JUMP to 0x10 because accumulator=0
         * NOP          0
         * JCN_9 0x13   1   no JUMP because testPin!=1
         * NOP          1
         * JCN_10 0x16  1   no JUMP becuase carry!=0
         * NOP          1   
         * JCN_12 0x19  1   no JUMP because accumulator=0
         * NOP          1
         * JCN_7 0x1C   1   JUMP to 0x1C because every condition is true
         * NOP          0
         * NOP          1
         */

        uint8_t source[] = { JCN_10, 0x03, NOP, CMC, JCN_10, 0x07, NOP, JCN_1, 0x0A, NOP, JCN_2, 0x0D, NOP, JCN_4, 0x10, NOP, JCN_9, 0x13, NOP, JCN_10, 0x16, NOP, JCN_12, 0x19, NOP, JCN_7, 0x1C, NOP, NOP };

        Intel4004Base *processor = { get4004Instance(0xFFFF, 0xFFFFFFFF) };

        CHECK(processor->getPtrToROM()->writeFrom(source, sizeof(source)) == 29);

        REQUIRE(processor->getPC().banked.address == 0x00);
        CHECK_FALSE(processor->getCarry());
        CHECK_FALSE(processor->getAccumulator());
        CHECK_FALSE(processor->getTestPin());
        // JCN_10 0x03
        processor->nextCommand();
        CHECK(processor->getPC().banked.address == 0x03);
        CHECK(processor->getPtrToStack()->getCount() == 0x0);
        // CMC
        processor->nextCommand();
        CHECK(processor->getCarry());
        CHECK(processor->getPC().banked.address == 0x04);
        // JCN_10 0x07
        processor->nextCommand();
        CHECK(processor->getPC().banked.address == 0x06);
        CHECK(processor->getCarry());
        // NOP
        processor->nextCommand();
        CHECK(processor->getPC().banked.address == 0x07);
        // JCN_1 0x0A
        processor->nextCommand();
        CHECK(processor->getPC().banked.address == 0x0A);
        CHECK(processor->getPtrToStack()->getCount() == 0x0);
        // JCN_2 0x0D
        processor->nextCommand();
        CHECK(processor->getPC().banked.address == 0x0D);
        CHECK(processor->getPtrToStack()->getCount() == 0x0);
        // JCN_4 0x10
        processor->nextCommand();
        CHECK(processor->getPC().banked.address == 0x10);
        CHECK(processor->getPtrToStack()->getCount() == 0x0);
        // JCN_9 0x13
        processor->nextCommand();
        CHECK(processor->getPC().banked.address == 0x12);
        // NOP
        processor->nextCommand();
        CHECK(processor->getPC().banked.address == 0x13);
        // JCN_10 0x16
        processor->nextCommand();
        CHECK(processor->getPC().banked.address == 0x15);
        // NOP
        processor->nextCommand();
        CHECK(processor->getPC().banked.address == 0x16);
        // JCN_12 0x19
        processor->nextCommand();
        CHECK(processor->getPC().banked.address == 0x18);
        // NOP
        processor->nextCommand();
        CHECK(processor->getPC().banked.address == 0x19);
        // JCN_7 0x1C
        processor->nextCommand();
        CHECK(processor->getPC().banked.address == 0x1C);
        CHECK(processor->getPtrToStack()->getCount() == 0x0);

        CHECK(processor->getTicks() == 23);

        // RESET Processor to test jump at ROM-END
        processor->reset();

        /**
         * JCN_4 0xFE   1   JUMP to 0xFE because accumulator=0
         * JCN_4 0x02   1   JUMP to 0x02 of next ROM-Cell because accumulator=0 and JCN in last two positions of ROM
         * FIM_0 0x02   1   fetch 0x02 to register pair 0
         * NOP          1
         */

        uint8_t sourceTwo[261];

        for (int i = 0; i < 261; i++) {
            sourceTwo[i] = 0x00;
        }

        sourceTwo[0] = JCN_4;
        sourceTwo[1] = 0xFE;
        sourceTwo[0xFE] = JCN_4;
        sourceTwo[0xFF] = 0x02;
        sourceTwo[0x102] = FIM_0;
        sourceTwo[0x103] = 0x02;
        sourceTwo[0x104] = NOP;

        CHECK(processor->getPtrToROM()->writeFrom(sourceTwo, sizeof(sourceTwo)) == 261);

        REQUIRE(processor->getPC().banked.bank == 0x0);
        REQUIRE(processor->getPC().banked.address == 0x00);
        CHECK_FALSE(processor->getCarry());
        CHECK_FALSE(processor->getAccumulator());
        CHECK_FALSE(processor->getTestPin());
        CHECK_FALSE(processor->getRegisterPair(Pair_R1_R0));
        // JCN_4 0xFE
        processor->nextCommand();
        CHECK(processor->getPC().banked.address == 0xFE);
        CHECK(processor->getPtrToStack()->getCount() == 0x0);
        // JCN_4 0x02
        processor->nextCommand();
        CHECK(processor->getPC().banked.bank == 0x1);
        CHECK(processor->getPC().banked.address == 0x02);
        CHECK(processor->getPtrToStack()->getCount() == 0x0);
        // FIM_0 0x02
        processor->nextCommand();
        CHECK(processor->getRegisterPair(Pair_R1_R0) == 0x02);

        CHECK(processor->getTicks() == 6);
    }
    SECTION("FIM") {
        /**
         * CMC          1   set carry=1
         * FIM_0 0x11   1   fetch 0x11 to register pair 0
         * FIM_2 0x02   1   fetch 0x02 to register pair 2
         * FIM_4 0x04   1   fetch 0x04 to register pair 4
         * FIM_6 0x06   1   fetch 0x06 to register pair 6
         * FIM_8 0x08   1   fetch 0x08 to register pair 8
         * FIM_10 0x0A  1   fetch 0x0A to register pair 10
         * FIM_12 0xOC  1   fetch 0x0C to register pair 12
         * FIM_14 0x0E  1   fetch 0x0E to register pair 14
         * NOP          1
         */

        uint8_t source[] = { CMC, FIM_0, 0x11, FIM_2, 0x02, FIM_4, 0x04, FIM_6, 0x06, FIM_8, 0x08, FIM_10, 0x0A, FIM_12, 0x0C, FIM_14, 0x0E, NOP };

        Intel4004Base *processor = { get4004Instance(0xFFFF, 0xFFFFFFFF) };

        CHECK(processor->getPtrToROM()->writeFrom(source, sizeof(source)) == 18);

        REQUIRE(processor->getPC().banked.address == 0x00);
        CHECK_FALSE(processor->getCarry());
        CHECK_FALSE(processor->getAccumulator());
        CHECK_FALSE(processor->getTestPin());
        CHECK_FALSE(processor->getRegisterPair(Pair_R1_R0));
        CHECK_FALSE(processor->getRegisterPair(Pair_R3_R2));
        CHECK_FALSE(processor->getRegisterPair(Pair_R5_R4));
        CHECK_FALSE(processor->getRegisterPair(Pair_R7_R6));
        CHECK_FALSE(processor->getRegisterPair(Pair_R9_R8));
        CHECK_FALSE(processor->getRegisterPair(Pair_R11_R10));
        CHECK_FALSE(processor->getRegisterPair(Pair_R13_R12));
        CHECK_FALSE(processor->getRegisterPair(Pair_R15_R14));
        // CMC
        processor->nextCommand();
        CHECK(processor->getCarry());
        // FIM_0 0x11
        processor->nextCommand();
        CHECK(processor->getRegisterPair(Pair_R1_R0) == 0x11);
        CHECK(processor->getPC().banked.address == 0x03);
        CHECK(processor->getCarry());
        // FIM_2 0x02
        processor->nextCommand();
        CHECK(processor->getRegisterPair(Pair_R3_R2) == 0x02);
        // FIM_4 0x04
        processor->nextCommand();
        CHECK(processor->getRegisterPair(Pair_R5_R4) == 0x04);
        // FIM_6 0x06
        processor->nextCommand();
        CHECK(processor->getRegisterPair(Pair_R7_R6) == 0x06);
        // FIM_8 0x08
        processor->nextCommand();
        CHECK(processor->getRegisterPair(Pair_R9_R8) == 0x08);
        // FIM_10 0x0A
        processor->nextCommand();
        CHECK(processor->getRegisterPair(Pair_R11_R10) == 0x0A);
        // FIM_12 0x0C
        processor->nextCommand();
        CHECK(processor->getRegisterPair(Pair_R13_R12) == 0x0C);
        // FIM_14 0x0E
        processor->nextCommand();
        CHECK(processor->getRegisterPair(Pair_R15_R14) == 0x0E);

        CHECK(processor->getTicks() == 17);
    }
    SECTION("FIN") {
        /**
         * FIN_0        1   fetch FIN_0 at 0x00 to register pair 0
         * FIM_0 0x02   1   fetch 0x02 to register pair 0
         * CMC          1   set carry=1
         * FIN_2        1   fetch 0x02 at 0x02 to register pair 2
         * FIN_4        1   fetch 0x02 at 0x02 to register pair 4
         * FIN_6        1   fetch 0x02 at 0x02 to register pair 6
         * FIN_8        1   fetch 0x02 at 0x02 to register pair 8
         * FIN_10       1   fetch 0x02 at 0x02 to register pair 10
         * FIN_12       1   fetch 0x02 at 0x02 to register pair 12
         * FIN_14       1   fetch 0x02 at 0x02 to register pair 14
         * NOP          1
         */

        uint8_t source[] = { FIN_0, FIM_0, 0x02, CMC, FIN_2, FIN_4, FIN_6, FIN_8, FIN_10, FIN_12, FIN_14, NOP };

        Intel4004Base *processor = { get4004Instance(0xFFFF, 0xFFFFFFFF) };

        CHECK(processor->getPtrToROM()->writeFrom(source, sizeof(source)) == 12);

        REQUIRE(processor->getPC().banked.address == 0x00);
        CHECK_FALSE(processor->getCarry());
        CHECK_FALSE(processor->getAccumulator());
        CHECK_FALSE(processor->getRegisterPair(Pair_R1_R0));
        CHECK_FALSE(processor->getRegisterPair(Pair_R3_R2));
        CHECK_FALSE(processor->getRegisterPair(Pair_R5_R4));
        CHECK_FALSE(processor->getRegisterPair(Pair_R7_R6));
        CHECK_FALSE(processor->getRegisterPair(Pair_R9_R8));
        CHECK_FALSE(processor->getRegisterPair(Pair_R11_R10));
        CHECK_FALSE(processor->getRegisterPair(Pair_R13_R12));
        CHECK_FALSE(processor->getRegisterPair(Pair_R15_R14));
        // FIN_0
        processor->nextCommand();
        CHECK(processor->getRegisterPair(Pair_R1_R0) == FIN_0);
        // FIM_0 0x02
        processor->nextCommand();
        CHECK(processor->getRegisterPair(Pair_R1_R0) == 0x02);
        // CMC
        processor->nextCommand();
        CHECK(processor->getCarry());
        // FIN_2
        processor->nextCommand();
        CHECK(processor->getRegisterPair(Pair_R3_R2) == 0x02);
        CHECK(processor->getCarry());
        // FIN_4
        processor->nextCommand();
        CHECK(processor->getRegisterPair(Pair_R5_R4) == 0x02);
        // FIN_6
        processor->nextCommand();
        CHECK(processor->getRegisterPair(Pair_R7_R6) == 0x02);
        // FIN_8
        processor->nextCommand();
        CHECK(processor->getRegisterPair(Pair_R9_R8) == 0x02);
        // FIN_10
        processor->nextCommand();
        CHECK(processor->getRegisterPair(Pair_R11_R10) == 0x02);
        // FIN_12
        processor->nextCommand();
        CHECK(processor->getRegisterPair(Pair_R13_R12) == 0x02);
        // FIN_14
        processor->nextCommand();
        CHECK(processor->getRegisterPair(Pair_R15_R14) == 0x02);
        CHECK(processor->getCarry());
        CHECK_FALSE(processor->getAccumulator());

        CHECK(processor->getTicks() == 19);

        // RESET Processor to test jump at ROM-END
        processor->reset();

        /**
         * FIM_0 0x02   1   fetch 0x02 to register pair 0
         * JCN_4 0xFF   1   JUMP to 0xFF because accumulator=0
         * FIN_2        1   fetch 0x3A at 0x102 to register pair 2
         * NOP          1
         * NOP          1
         */

        uint8_t sourceTwo[261];

        for (int i = 0; i < 261; i++) {
            sourceTwo[i] = 0x00;
        }

        sourceTwo[0] = FIM_0;
        sourceTwo[1] = 0x02;
        sourceTwo[2] = JCN_4;
        sourceTwo[3] = 0xFF;
        sourceTwo[0xFF] = FIN_2;
        sourceTwo[0x100] = NOP;
        sourceTwo[0x101] = NOP;
        sourceTwo[0x102] = 0x3A;

        CHECK(processor->getPtrToROM()->writeFrom(sourceTwo, sizeof(sourceTwo)) == 261);

        REQUIRE(processor->getPC().banked.bank == 0x0);
        REQUIRE(processor->getPC().banked.address == 0x00);
        CHECK_FALSE(processor->getCarry());
        CHECK_FALSE(processor->getAccumulator());
        CHECK_FALSE(processor->getTestPin());
        CHECK_FALSE(processor->getRegisterPair(Pair_R1_R0));
        CHECK_FALSE(processor->getRegisterPair(Pair_R3_R2));
        // FIM_0 0x02
        processor->nextCommand();
        CHECK(processor->getRegisterPair(Pair_R1_R0) == 0x02);
        // JCN_4 0xFF
        processor->nextCommand();
        CHECK(processor->getPC().banked.address == 0xFF);
        // FIN_2
        processor->nextCommand();
        CHECK(processor->getRegisterPair(Pair_R3_R2) == 0x3A);

        CHECK(processor->getTicks() == 6);
    }
    SECTION("JIN") {
        /**
         * FIM_0 0x13   1
         * FIM_2 0x15   1
         * FIM_4 0x17   1
         * FIM_6 0x19   1
         * FIM_8 0x1B   1
         * FIM_10 0x1D  1
         * FIM_12 0x1F  1
         * FIM_14 0x21  1
         * CMC          1
         * JIN_0        1
         * NOP          0
         * JIN_2        1
         * NOP          0
         * JIN_4        1
         * NOP          0
         * JIN_6        1
         * NOP          0
         * JIN_8        1
         * NOP          0
         * JIN_10       1
         * NOP          0
         * JIN_12       1
         * NOP          0
         * JIN_14       1
         * NOP          0
         * NOP          1
         */

        uint8_t source[] = { FIM_0, 0x13, FIM_2, 0x15, FIM_4, 0x17, FIM_6, 0x19, FIM_8, 0x1B, FIM_10, 0x1D, FIM_12, 0x1F, FIM_14, 0x21, CMC, JIN_0, NOP, JIN_2, NOP, JIN_4, NOP, JIN_6, NOP, JIN_8, NOP, JIN_10, NOP, JIN_12, NOP, JIN_14, NOP, NOP };

        Intel4004Base *processor = { get4004Instance(0xFFFF, 0xFFFFFFFF) };

        CHECK(processor->getPtrToROM()->writeFrom(source, sizeof(source)) == 34);

        REQUIRE(processor->getPC().banked.address == 0x00);
        CHECK_FALSE(processor->getCarry());
        CHECK_FALSE(processor->getAccumulator());
        CHECK_FALSE(processor->getRegisterPair(Pair_R1_R0));
        CHECK_FALSE(processor->getRegisterPair(Pair_R3_R2));
        CHECK_FALSE(processor->getRegisterPair(Pair_R5_R4));
        CHECK_FALSE(processor->getRegisterPair(Pair_R7_R6));
        CHECK_FALSE(processor->getRegisterPair(Pair_R9_R8));
        CHECK_FALSE(processor->getRegisterPair(Pair_R11_R10));
        CHECK_FALSE(processor->getRegisterPair(Pair_R13_R12));
        CHECK_FALSE(processor->getRegisterPair(Pair_R15_R14));
        // FIM_0 0x13
        processor->nextCommand();
        // FIM_2 0x15
        processor->nextCommand();
        // FIM_4 0x17
        processor->nextCommand();
        // FIM_6 0x19
        processor->nextCommand();
        // FIM_8 0x1B
        processor->nextCommand();
        // FIM_10 0x1D
        processor->nextCommand();
        // FIM_12 0x1F
        processor->nextCommand();
        // FIM_14 0x21
        processor->nextCommand();
        // CMC
        processor->nextCommand();
        CHECK(processor->getCarry());
        CHECK(processor->getRegisterPair(Pair_R1_R0) == 0x13);
        CHECK(processor->getRegisterPair(Pair_R3_R2) == 0x15);
        CHECK(processor->getRegisterPair(Pair_R5_R4) == 0x17);
        CHECK(processor->getRegisterPair(Pair_R7_R6) == 0x19);
        CHECK(processor->getRegisterPair(Pair_R9_R8) == 0x1B);
        CHECK(processor->getRegisterPair(Pair_R11_R10) == 0x1D);
        CHECK(processor->getRegisterPair(Pair_R13_R12) == 0x1F);
        CHECK(processor->getRegisterPair(Pair_R15_R14) == 0x21);
        CHECK(processor->getPC().banked.address == 0x11);
        // JIN_0
        processor->nextCommand();
        CHECK(processor->getPC().banked.address == 0x13);
        CHECK(processor->getPtrToStack()->getCount() == 0x0);
        CHECK(processor->getCarry());
        // JIN_2
        processor->nextCommand();
        CHECK(processor->getPC().banked.address == 0x15);
        CHECK(processor->getPtrToStack()->getCount() == 0x0);
        // JIN_4
        processor->nextCommand();
        CHECK(processor->getPC().banked.address == 0x17);
        CHECK(processor->getPtrToStack()->getCount() == 0x0);
        // JIN_6
        processor->nextCommand();
        CHECK(processor->getPC().banked.address == 0x19);
        CHECK(processor->getPtrToStack()->getCount() == 0x0);
        // JIN_8
        processor->nextCommand();
        CHECK(processor->getPC().banked.address == 0x1B);
        CHECK(processor->getPtrToStack()->getCount() == 0x0);
        // JIN_10
        processor->nextCommand();
        CHECK(processor->getPC().banked.address == 0x1D);
        CHECK(processor->getPtrToStack()->getCount() == 0x0);
        // JIN_12
        processor->nextCommand();
        CHECK(processor->getPC().banked.address == 0x1F);
        CHECK(processor->getPtrToStack()->getCount() == 0x0);
        // JIN_14
        processor->nextCommand();
        CHECK(processor->getPC().banked.address == 0x21);
        CHECK(processor->getPtrToStack()->getCount() == 0x0);

        CHECK(processor->getTicks() == 25);

        // RESET Processor to test jump at ROM-END
        processor->reset();

        /**
         * FIM_0 0x02   1   fetch 0x02 to register pair 0
         * JCN_4 0xFF   1   JUMP to 0xFF because accumulator=0
         * JIN_0        1   JUMP to 0x102
         * NOP          1
         * NOP          1
         */

        uint8_t sourceTwo[261];

        for (int i = 0; i < 261; i++) {
            sourceTwo[i] = 0x00;
        }

        sourceTwo[0] = FIM_0;
        sourceTwo[1] = 0x02;
        sourceTwo[2] = JCN_4;
        sourceTwo[3] = 0xFF;
        sourceTwo[0xFF] = JIN_0;
        sourceTwo[0x100] = NOP;
        sourceTwo[0x101] = NOP;
        sourceTwo[0x102] = NOP;

        CHECK(processor->getPtrToROM()->writeFrom(sourceTwo, sizeof(sourceTwo)) == 261);

        REQUIRE(processor->getPC().banked.bank == 0x0);
        REQUIRE(processor->getPC().banked.address == 0x00);
        CHECK_FALSE(processor->getCarry());
        CHECK_FALSE(processor->getAccumulator());
        CHECK_FALSE(processor->getTestPin());
        CHECK_FALSE(processor->getRegisterPair(Pair_R1_R0));
        // FIM_0 0x02
        processor->nextCommand();
        CHECK(processor->getRegisterPair(Pair_R1_R0) == 0x02);
        // JCN_4 0xFF
        processor->nextCommand();
        CHECK(processor->getPC().banked.bank == 0x0);
        CHECK(processor->getPC().banked.address == 0xFF);
        // JIN_0
        processor->nextCommand();
        CHECK(processor->getPC().banked.bank == 0x1);
        CHECK(processor->getPC().banked.address == 0x02);
        CHECK(processor->getPtrToStack()->getCount() == 0x0);

        CHECK(processor->getTicks() == 5);
    }
    SECTION("JUN") {
        /**
         * CMC          1   set carry=1
         * JUN_1 0x28   1   JUMP to 0x128
         * JUN_2 0x3A   1   JUMP to 0x23A
         * JUN_3 0x10   1   JUMP to 0x310
         * JUN_4 0x83   1   JUMP to 0x483
         * JUN_5 0x00   1   JUMP to 0x500
         * JUN_6 0xCE   1   JUMP to 0x6CE
         * JUN_7 0x51   1   JUMP to 0x751
         * JUN_8 0x39   1   JUMP to 0x839
         * JUN_9 0x11   1   JUMP to 0x911
         * JUN_10 0x12  1   JUMP to 0xA12
         * JUN_11 0x87  1   JUMP to 0xB87
         * JUN_12 0x24  1   JUMP to 0xC24
         * JUN_13 0x11  1   JUMP to 0xD11
         * JUN_14 0x87  1   JUMP to 0xE87
         * JUN_15 0x12  1   JUMP to 0xF12
         * JUN_0 0x03   1   JUMP to 0x003
         * NOP          1
         */

        uint8_t source[0x1000];

        for (int i = 0; i < 0x1000; i++) {
            source[i] = 0x00;
        }

        source[0x000] = CMC;
        source[0x001] = JUN_1;
        source[0x002] = 0x28;
        source[0x128] = JUN_2;
        source[0x129] = 0x3A;
        source[0x23A] = JUN_3;
        source[0x23B] = 0x10;
        source[0x310] = JUN_4;
        source[0x311] = 0x83;
        source[0x483] = JUN_5;
        source[0x484] = 0x00;
        source[0x500] = JUN_6;
        source[0x501] = 0xCE;
        source[0x6CE] = JUN_7;
        source[0x6CF] = 0x51;
        source[0x751] = JUN_8;
        source[0x752] = 0x39;
        source[0x839] = JUN_9;
        source[0x83A] = 0x11;
        source[0x911] = JUN_10;
        source[0x912] = 0x12;
        source[0xA12] = JUN_11;
        source[0xA13] = 0x87;
        source[0xB87] = JUN_12;
        source[0xB88] = 0x24;
        source[0xC24] = JUN_13;
        source[0xC25] = 0x11;
        source[0xD11] = JUN_14;
        source[0xD12] = 0x87;
        source[0xE87] = JUN_15;
        source[0xE88] = 0x12;
        source[0xF12] = JUN_0;
        source[0xF13] = 0x03;
        source[0x003] = NOP;

        Intel4004Base *processor = { get4004Instance(0xFFFF, 0xFFFFFFFF) };

        CHECK(processor->getPtrToROM()->writeFrom(source, sizeof(source)) == 4096);

        REQUIRE(processor->getPC().banked.bank == 0x0);
        REQUIRE(processor->getPC().banked.address == 0x00);
        CHECK_FALSE(processor->getCarry());
        CHECK_FALSE(processor->getAccumulator());
        // CMC
        processor->nextCommand();
        CHECK(processor->getCarry());
        // JUN_1 0x28
        processor->nextCommand();
        CHECK(processor->getPC().banked.bank == 0x1);
        CHECK(processor->getPC().banked.address == 0x28);
        CHECK(processor->getPtrToStack()->getCount() == 0x0);
        CHECK(processor->getCarry());
        // JUN_2 0x3A
        processor->nextCommand();
        CHECK(processor->getPC().banked.bank == 0x2);
        CHECK(processor->getPC().banked.address == 0x3A);
        CHECK(processor->getPtrToStack()->getCount() == 0x0);
        // JUN_3 0x10
        processor->nextCommand();
        CHECK(processor->getPC().banked.bank == 0x3);
        CHECK(processor->getPC().banked.address == 0x10);
        CHECK(processor->getPtrToStack()->getCount() == 0x0);
        // JUN_4 0x83
        processor->nextCommand();
        CHECK(processor->getPC().banked.bank == 0x4);
        CHECK(processor->getPC().banked.address == 0x83);
        CHECK(processor->getPtrToStack()->getCount() == 0x0);
        // JUN_5 0x00
        processor->nextCommand();
        CHECK(processor->getPC().banked.bank == 0x5);
        CHECK(processor->getPC().banked.address == 0x00);
        CHECK(processor->getPtrToStack()->getCount() == 0x0);
        // JUN_6 0xCE
        processor->nextCommand();
        CHECK(processor->getPC().banked.bank == 0x6);
        CHECK(processor->getPC().banked.address == 0xCE);
        CHECK(processor->getPtrToStack()->getCount() == 0x0);
        // JUN_7 0x51
        processor->nextCommand();
        CHECK(processor->getPC().banked.bank == 0x7);
        CHECK(processor->getPC().banked.address == 0x51);
        CHECK(processor->getPtrToStack()->getCount() == 0x0);
        // JUN_8 0x39
        processor->nextCommand();
        CHECK(processor->getPC().banked.bank == 0x8);
        CHECK(processor->getPC().banked.address == 0x39);
        CHECK(processor->getPtrToStack()->getCount() == 0x0);
        // JUN_9 0x11
        processor->nextCommand();
        CHECK(processor->getPC().banked.bank == 0x9);
        CHECK(processor->getPC().banked.address == 0x11);
        CHECK(processor->getPtrToStack()->getCount() == 0x0);
        // JUN_10 0x12
        processor->nextCommand();
        CHECK(processor->getPC().banked.bank == 0xA);
        CHECK(processor->getPC().banked.address == 0x12);
        CHECK(processor->getPtrToStack()->getCount() == 0x0);
        // JUN_11 0x87
        processor->nextCommand();
        CHECK(processor->getPC().banked.bank == 0xB);
        CHECK(processor->getPC().banked.address == 0x87);
        CHECK(processor->getPtrToStack()->getCount() == 0x0);
        // JUN_12 0x24
        processor->nextCommand();
        CHECK(processor->getPC().banked.bank == 0xC);
        CHECK(processor->getPC().banked.address == 0x24);
        CHECK(processor->getPtrToStack()->getCount() == 0x0);
        // JUN_13 0x11
        processor->nextCommand();
        CHECK(processor->getPC().banked.bank == 0xD);
        CHECK(processor->getPC().banked.address == 0x11);
        CHECK(processor->getPtrToStack()->getCount() == 0x0);
        // JUN_14 0x87
        processor->nextCommand();
        CHECK(processor->getPC().banked.bank == 0xE);
        CHECK(processor->getPC().banked.address == 0x87);
        CHECK(processor->getPtrToStack()->getCount() == 0x0);
        // JUN_15 0x12
        processor->nextCommand();
        CHECK(processor->getPC().banked.bank == 0xF);
        CHECK(processor->getPC().banked.address == 0x12);
        CHECK(processor->getPtrToStack()->getCount() == 0x0);
        // JUN_0 0x03
        processor->nextCommand();
        CHECK(processor->getPC().banked.bank == 0x0);
        CHECK(processor->getPC().banked.address == 0x03);
        CHECK(processor->getPtrToStack()->getCount() == 0x0);

        CHECK(processor->getTicks() == 33);
    }
    SECTION("JMS") {
        /**
         * CMC          1   set carry=1
         * JMS_0 0x04   1
         * NOP          0
         * JMS_1 0x21   1
         * NOP          1
         */

        uint8_t source[] = { CMC, JMS_0, 0x04, NOP, JMS_1, 0x21, NOP };

        Intel4004Base *processor = { get4004Instance(0xFFFF, 0xFFFFFFFF) };

        CHECK(processor->getPtrToROM()->writeFrom(source, sizeof(source)) == 7);

        REQUIRE(processor->getPC().banked.bank == 0x0);
        REQUIRE(processor->getPC().banked.address == 0x00);
        CHECK_FALSE(processor->getCarry());
        CHECK_FALSE(processor->getAccumulator());
        // CMC
        processor->nextCommand();
        CHECK(processor->getCarry());
        // JMS_0 0x04
        processor->nextCommand();
        CHECK(processor->getCarry());
        CHECK(processor->getPC().banked.bank == 0x0);
        CHECK(processor->getPC().banked.address == 0x04);
        UBankedAddress *stackCopy = new UBankedAddress[3]();
        processor->getPtrToStack()->getCopyOfStack(stackCopy);
        CHECK(stackCopy[0].banked.bank == 0x0);
        CHECK(stackCopy[0].banked.address == 0x03);
        // JMS_1 0x21
        processor->nextCommand();
        CHECK(processor->getPC().banked.bank == 0x1);
        CHECK(processor->getPC().banked.address == 0x21);
        stackCopy = processor->getPtrToStack()->getCopyOfStack(stackCopy);
        CHECK(stackCopy[0].banked.bank == 0x0);
        CHECK(stackCopy[0].banked.address == 0x06);
        CHECK(stackCopy[1].banked.bank == 0x0);
        CHECK(stackCopy[1].banked.address == 0x03);

        delete[] stackCopy;

        CHECK(processor->getTicks() == 5);
    }
    SECTION("INC") {
        /**
         * CMC          1   set carry=1
         * FIM_0 0x01   1
         * FIM_2 0x23   1
         * FIM_3 0x45   1
         * FIM_4 0x67   1
         * FIM_6 0x89   1
         * FIM_8 0xAB   1
         * FIM_10 0xCD  1
         * FIM_12 0xEF  1
         * INC_0        1
         * INC_1        1
         * INC_2        1
         * INC_3        1
         * INC_4        1
         * INC_5        1
         * INC_6        1   
         * INC_7        1
         * INC_8        1
         * INC_9        1
         * INC_10       1
         * INC_11       1
         * INC_12       1
         * INC_13       1
         * INC_14       1
         * INC_15       1
         * NOP          1
         */

        uint8_t source[] = { CMC, FIM_0, 0x01, FIM_2, 0x23, FIM_4, 0x45, FIM_6, 0x67, FIM_8, 0x89, FIM_10, 0xAB, FIM_12, 0xCD, FIM_14, 0xEF, INC_0, INC_1, INC_2, INC_3, INC_4, INC_5, INC_6, INC_7, INC_8, INC_9, INC_10, INC_11, INC_12, INC_13, INC_14, INC_15, NOP };

        Intel4004Base *processor = { get4004Instance(0xFFFF, 0xFFFFFFFF) };

        CHECK(processor->getPtrToROM()->writeFrom(source, sizeof(source)) == 34);

        REQUIRE(processor->getPC().banked.bank == 0x0);
        REQUIRE(processor->getPC().banked.address == 0x00);
        CHECK_FALSE(processor->getCarry());
        CHECK_FALSE(processor->getAccumulator());
        // CMC
        processor->nextCommand();
        CHECK(processor->getCarry());
        // FIM_0 0x01
        processor->nextCommand();
        CHECK(processor->getRegisterPair(Pair_R1_R0) == 0x01);
        // FIM_2 0x23
        processor->nextCommand();
        CHECK(processor->getRegisterPair(Pair_R3_R2) == 0x23);
        // FIM_4 0x45
        processor->nextCommand();
        CHECK(processor->getRegisterPair(Pair_R5_R4) == 0x45);
        // FIM_6 0x67
        processor->nextCommand();
        CHECK(processor->getRegisterPair(Pair_R7_R6) == 0x67);
        // FIM_8 0x89
        processor->nextCommand();
        CHECK(processor->getRegisterPair(Pair_R9_R8) == 0x89);
        // FIM_10 0xAB
        processor->nextCommand();
        CHECK(processor->getRegisterPair(Pair_R11_R10) == 0xAB);
        // FIM_12 0xCD
        processor->nextCommand();
        CHECK(processor->getRegisterPair(Pair_R13_R12) == 0xCD);
        // FIM_14 0xEF
        processor->nextCommand();
        CHECK(processor->getRegisterPair(Pair_R15_R14) == 0xEF);
        // INC_0
        processor->nextCommand();
        CHECK(processor->getRegister(R0) == 0x1);
        // INC_1
        processor->nextCommand();
        CHECK(processor->getRegister(R1) == 0x2);
        // INC_2
        processor->nextCommand();
        CHECK(processor->getRegister(R2) == 0x3);
        // INC_3
        processor->nextCommand();
        CHECK(processor->getRegister(R3) == 0x4);
        // INC_4
        processor->nextCommand();
        CHECK(processor->getRegister(R4) == 0x5);
        // INC_5
        processor->nextCommand();
        CHECK(processor->getRegister(R5) == 0x6);
        // INC_6
        processor->nextCommand();
        CHECK(processor->getRegister(R6) == 0x7);
        // INC_7
        processor->nextCommand();
        CHECK(processor->getRegister(R7) == 0x8);
        // INC_8
        processor->nextCommand();
        CHECK(processor->getRegister(R8) == 0x9);
        // INC_9
        processor->nextCommand();
        CHECK(processor->getRegister(R9) == 0xA);
        // INC_10
        processor->nextCommand();
        CHECK(processor->getRegister(R10) == 0xB);
        // INC_11
        processor->nextCommand();
        CHECK(processor->getRegister(R11) == 0xC);
        // INC_12
        processor->nextCommand();
        CHECK(processor->getRegister(R12) == 0xD);
        // INC_13
        processor->nextCommand();
        CHECK(processor->getRegister(R13) == 0xE);
        // INC_14
        processor->nextCommand();
        CHECK(processor->getRegister(R14) == 0xF);
        // INC_15
        processor->nextCommand();
        CHECK(processor->getRegister(R15) == 0x0);
        CHECK(processor->getCarry());

        CHECK(processor->getTicks() == 33);
    }
    SECTION("ISZ") {
        /**
         * CMC          1   set carry=1
         * FIM_0 0x00   1
         * INC_1        1
         * ISZ_0 0x03   1   JUMP to INC_1 (15 times then skip)
         * JUN_0 0xFE   1   JUMP to 0x0FE
         * ISZ_1 0x14   1   JUMP to 0x114
         * NOP          1
         */

        uint8_t source[0x200];

        source[0x000] = CMC;
        source[0x001] = FIM_0;
        source[0x002] = 0x00;
        source[0x003] = INC_1;
        source[0x004] = ISZ_0;
        source[0x005] = 0x03;
        source[0x006] = JUN_0;
        source[0x007] = 0xFE;
        source[0x0FE] = ISZ_1;
        source[0x0FF] = 0x14;
        source[0x114] = NOP;

        Intel4004Base *processor = { get4004Instance(0xFFFF, 0xFFFFFFFF) };

        CHECK(processor->getPtrToROM()->writeFrom(source, sizeof(source)) == 512);

        REQUIRE(processor->getPC().banked.bank == 0x0);
        REQUIRE(processor->getPC().banked.address == 0x00);
        CHECK_FALSE(processor->getCarry());
        CHECK_FALSE(processor->getAccumulator());
        CHECK_FALSE(processor->getRegisterPair(Pair_R1_R0));
        CHECK_FALSE(processor->getRegisterPair(Pair_R3_R2));
        // CMC
        processor->nextCommand();
        CHECK(processor->getCarry());
        // FIM_0 0x00
        processor->nextCommand();
        CHECK(processor->getRegisterPair(Pair_R1_R0) == 0x00);
        for (int i = 0x01; i <= 0xF; i++) {
            // INC_1
            processor->nextCommand();
            CHECK(processor->getRegister(R1) == i);
            // ISZ_0 0x03
            processor->nextCommand();
            CHECK(processor->getRegister(R0) == i);
            CHECK(processor->getPC().banked.address == 0x03);
            CHECK(processor->getPtrToStack()->getCount() == 0x0);
            CHECK(processor->getCarry());
        }
        // INC_1
        processor->nextCommand();
        CHECK(processor->getRegister(R1) == 0x0);
        // ISZ_0 0x03
        processor->nextCommand();
        CHECK(processor->getRegister(R0) == 0x0);
        CHECK(processor->getPC().banked.bank == 0x0);
        CHECK(processor->getPC().banked.address == 0x06);
        CHECK(processor->getPtrToStack()->getCount() == 0x0);
        CHECK(processor->getCarry());
        // JUN_0 0xFE
        processor->nextCommand();
        CHECK(processor->getPC().banked.bank == 0x0);
        CHECK(processor->getPC().banked.address == 0xFE);
        // ISZ_1 0x14
        processor->nextCommand();
        CHECK(processor->getPC().banked.bank == 0x1);
        CHECK(processor->getPC().banked.address == 0x14);
        CHECK(processor->getRegister(R1) == 0x1);
        CHECK(processor->getCarry());
        
        CHECK(processor->getTicks() == 55);

    }
    SECTION("ADD") {
        /**
         * LDM_2        1
         * XCH_0    	1
         * LDM_9        1
         * XCH_14       1
         * LDM_6        1
         * ADD_14       1
         * ADD_0        1
         * ADD_0        1
         * NOP          1
         */

        uint8_t source[] = { LDM_2, XCH_0, LDM_9, XCH_14, LDM_6, ADD_14, ADD_0, ADD_0, NOP };

        Intel4004Base *processor = { get4004Instance(0xFFFF, 0xFFFFFFFF) };

        CHECK(processor->getPtrToROM()->writeFrom(source, sizeof(source)) == 9);

        REQUIRE(processor->getPC().banked.bank == 0x0);
        REQUIRE(processor->getPC().banked.address == 0x00);
        CHECK_FALSE(processor->getCarry());
        CHECK_FALSE(processor->getAccumulator());
        // LDM_2
        processor->nextCommand();
        // XCH_0
        processor->nextCommand();
        CHECK(processor->getRegister(R0) == 0x2);
        // LDM_9
        processor->nextCommand();
        // XCH_14
        processor->nextCommand();
        CHECK(processor->getRegister(R14) == 0x9);
        // LDM_6
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x6);
        // ADD_14
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0xF);
        CHECK_FALSE(processor->getCarry());
        CHECK(processor->getRegister(R14) == 0x9);
        // ADD_0
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x1);
        CHECK(processor->getCarry());
        CHECK(processor->getRegister(R0) == 0x2);
        // ADD_0
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x4);
        CHECK_FALSE(processor->getCarry());
        CHECK(processor->getRegister(R0) == 0x2);

        CHECK(processor->getTicks() == 0x8);
    }
    SECTION("SUB") {
        /**
         * LDM_2        1
         * XCH_0    	1
         * LDM_9        1
         * XCH_14       1
         * LDM_6        1
         * SUB_0        1
         * SUB_0        1
         * CLC          1
         * SUB_14       1
         * NOP          1
         */

        uint8_t source[] = { LDM_2, XCH_0, LDM_9, XCH_14, LDM_6, SUB_0, SUB_0, CLC, SUB_14, NOP };

        Intel4004Base *processor = { get4004Instance(0xFFFF, 0xFFFFFFFF) };

        CHECK(processor->getPtrToROM()->writeFrom(source, sizeof(source)) == 10);

        REQUIRE(processor->getPC().banked.bank == 0x0);
        REQUIRE(processor->getPC().banked.address == 0x00);
        CHECK_FALSE(processor->getCarry());
        CHECK_FALSE(processor->getAccumulator());
        // LDM_2
        processor->nextCommand();
        // XCH_0
        processor->nextCommand();
        CHECK(processor->getRegister(R0) == 0x2);
        // LDM_9
        processor->nextCommand();
        // XCH_14
        processor->nextCommand();
        CHECK(processor->getRegister(R14) == 0x9);
        // LDM_6
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x6);
        // SUB_0
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x4);
        CHECK(processor->getCarry());
        CHECK(processor->getRegister(R0) == 0x2);
        // SUB_0
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x1);
        CHECK(processor->getCarry());
        CHECK(processor->getRegister(R0) == 0x2);
        // CLC
        processor->nextCommand();
        CHECK_FALSE(processor->getCarry());
        // SUB_14
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x8);
        CHECK_FALSE(processor->getCarry());
        CHECK(processor->getRegister(R14) == 0x9);

        CHECK(processor->getTicks() == 9);
    }
    SECTION("LD") {
        /**
         * LDM_2        1
         * XCH_0    	1
         * LDM_9        1
         * XCH_14       1
         * LDM_6        1
         * LD_0         1
         * CMC          1
         * LD_14        1
         * NOP          1
         */

        uint8_t source[] = { LDM_2, XCH_0, LDM_9, XCH_14, LDM_6, LD_0, CMC, LD_14, NOP };

        Intel4004Base *processor = { get4004Instance(0xFFFF, 0xFFFFFFFF) };

        CHECK(processor->getPtrToROM()->writeFrom(source, sizeof(source)) == 9);

        REQUIRE(processor->getPC().banked.bank == 0x0);
        REQUIRE(processor->getPC().banked.address == 0x00);
        CHECK_FALSE(processor->getCarry());
        CHECK_FALSE(processor->getAccumulator());
        // LDM_2
        processor->nextCommand();
        // XCH_0
        processor->nextCommand();
        CHECK(processor->getRegister(R0) == 0x2);
        // LDM_9
        processor->nextCommand();
        // XCH_14
        processor->nextCommand();
        CHECK(processor->getRegister(R14) == 0x9);
        // LDM_6
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x6);
        // LD_0
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x2);
        CHECK(processor->getRegister(R0) == 0x2);
        CHECK_FALSE(processor->getCarry());
        // CMC
        processor->nextCommand();
        CHECK(processor->getCarry());
        // LD_14
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x9);
        CHECK(processor->getRegister(R14) == 0x9);
        CHECK(processor->getCarry());

        CHECK(processor->getTicks() == 8);
    }
    SECTION("XCH") {
        /**
         * LDM_2        1
         * XCH_0    	1
         * LDM_9        1
         * XCH_14       1
         * LDM_6        1
         * CMC          1
         * XCH_0        1
         * XCH_14       1
         * NOP          1
         */

        uint8_t source[] = { LDM_2, XCH_0, LDM_9, XCH_14, LDM_6, CMC, XCH_0, XCH_14, NOP };

        Intel4004Base *processor = { get4004Instance(0xFFFF, 0xFFFFFFFF) };

        CHECK(processor->getPtrToROM()->writeFrom(source, sizeof(source)) == 9);

        REQUIRE(processor->getPC().banked.bank == 0x0);
        REQUIRE(processor->getPC().banked.address == 0x00);
        CHECK_FALSE(processor->getCarry());
        CHECK_FALSE(processor->getAccumulator());
        // LDM_2
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x2);
        // XCH_0
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x0);
        CHECK(processor->getRegister(R0) == 0x2);
        CHECK_FALSE(processor->getCarry());
        // LDM_9
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x9);
        // XCH_14
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x0);
        CHECK(processor->getRegister(R14) == 0x9);
        CHECK_FALSE(processor->getCarry());
        // LDM_6
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x6);
        // CMC
        processor->nextCommand();
        CHECK(processor->getCarry());
        // XCH_0
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x2);
        CHECK(processor->getRegister(R0) == 0x6);
        CHECK(processor->getCarry());
        // XCH_14
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x9);
        CHECK(processor->getRegister(R14) == 0x2);
        CHECK(processor->getCarry());

        CHECK(processor->getTicks() == 8);
    }
    SECTION("BBL") {
        /**
         * JMS_1 0x12   1
         * BBL_5        1
         * JMS_1 0x24   1
         * CMC          1
         * BBL_0        1
         * JMS_1 0x36   1
         * JMS_2 0x00   1
         * JMS_3 0x00   1
         * JMS_4 0x00   1
         * BBL_1        1
         * BBL_2        1
         * BBL_3        1
         * BBL_4        1
         */

        uint8_t source[0x1000];

        for (int i = 0; i < 0x1000; i++) {
            source[i] = 0x00;
        }

        source[0x000] = JMS_1;
        source[0x001] = 0x12;
        source[0x112] = BBL_5;
        source[0x002] = JMS_1;
        source[0x003] = 0x24;
        source[0x124] = CMC;
        source[0x125] = BBL_0;
        source[0x004] = JMS_1;
        source[0x005] = 0x36;
        source[0x136] = JMS_2;
        source[0x137] = 0x00;
        source[0x200] = JMS_3;
        source[0x201] = 0x00;
        source[0x300] = JMS_4;
        source[0x301] = 0x00;
        source[0x400] = BBL_1;
        source[0x302] = BBL_2;
        source[0x202] = BBL_3;
        source[0x138] = BBL_4;

        Intel4004Base *processor = { get4004Instance(0xFFFF, 0xFFFFFFFF) };

        CHECK(processor->getPtrToROM()->writeFrom(source, sizeof(source)) == 4096);

        UBankedAddress *stackCopy = new UBankedAddress[3];

        REQUIRE(processor->getPC().banked.bank == 0x0);
        REQUIRE(processor->getPC().banked.address == 0x00);
        CHECK_FALSE(processor->getCarry());
        CHECK_FALSE(processor->getAccumulator());
        // JMS_1 0x12
        processor->nextCommand();
        CHECK(processor->getPC().banked.bank == 0x1);
        CHECK(processor->getPC().banked.address == 0x12);
        processor->getPtrToStack()->getCopyOfStack(stackCopy);
        CHECK(stackCopy[0].banked.bank == 0x0);
        CHECK(stackCopy[0].banked.address == 0x02);
        CHECK(stackCopy[1].banked.bank == 0x0);
        CHECK(stackCopy[1].banked.address == 0x00);
        CHECK(stackCopy[2].banked.bank == 0x0);
        CHECK(stackCopy[2].banked.address == 0x00);
        // BBL_5
        processor->nextCommand();
        CHECK(processor->getPC().banked.bank == 0x0);
        CHECK(processor->getPC().banked.address == 0x02);
        processor->getPtrToStack()->getCopyOfStack(stackCopy);
        CHECK(stackCopy[0].banked.bank == 0x0);
        CHECK(stackCopy[0].banked.address == 0x00);
        CHECK(stackCopy[1].banked.bank == 0x0);
        CHECK(stackCopy[1].banked.address == 0x00);
        CHECK(stackCopy[2].banked.bank == 0x0);
        CHECK(stackCopy[2].banked.address == 0x02);
        CHECK(processor->getAccumulator() == 0x5);
        CHECK_FALSE(processor->getCarry());
        //JMS_1 0x24
        processor->nextCommand();
        CHECK(processor->getPC().banked.bank == 0x1);
        CHECK(processor->getPC().banked.address == 0x24);
        processor->getPtrToStack()->getCopyOfStack(stackCopy);
        CHECK(stackCopy[0].banked.bank == 0x0);
        CHECK(stackCopy[0].banked.address == 0x04);
        CHECK(stackCopy[1].banked.bank == 0x0);
        CHECK(stackCopy[1].banked.address == 0x00);
        CHECK(stackCopy[2].banked.bank == 0x0);
        CHECK(stackCopy[2].banked.address == 0x00);
        // CMC
        processor->nextCommand();
        CHECK(processor->getCarry());
        // BBL_0
        processor->nextCommand();
        CHECK(processor->getPC().banked.bank == 0x0);
        CHECK(processor->getPC().banked.address == 0x04);
        processor->getPtrToStack()->getCopyOfStack(stackCopy);
        CHECK(stackCopy[0].banked.bank == 0x0);
        CHECK(stackCopy[0].banked.address == 0x00);
        CHECK(stackCopy[1].banked.bank == 0x0);
        CHECK(stackCopy[1].banked.address == 0x00);
        CHECK(stackCopy[2].banked.bank == 0x0);
        CHECK(stackCopy[2].banked.address == 0x04);
        CHECK(processor->getAccumulator() == 0x0);
        CHECK(processor->getCarry());
        //JMS_1 0x36
        processor->nextCommand();
        CHECK(processor->getPC().banked.bank == 0x1);
        CHECK(processor->getPC().banked.address == 0x36);
        processor->getPtrToStack()->getCopyOfStack(stackCopy);
        CHECK(stackCopy[0].banked.bank == 0x0);
        CHECK(stackCopy[0].banked.address == 0x06);
        CHECK(stackCopy[1].banked.bank == 0x0);
        CHECK(stackCopy[1].banked.address == 0x00);
        CHECK(stackCopy[2].banked.bank == 0x0);
        CHECK(stackCopy[2].banked.address == 0x00);
        //JMS_2 0x00
        processor->nextCommand();
        CHECK(processor->getPC().banked.bank == 0x2);
        CHECK(processor->getPC().banked.address == 0x00);
        processor->getPtrToStack()->getCopyOfStack(stackCopy);
        CHECK(stackCopy[0].banked.bank == 0x1);
        CHECK(stackCopy[0].banked.address == 0x38);
        CHECK(stackCopy[1].banked.bank == 0x0);
        CHECK(stackCopy[1].banked.address == 0x06);
        CHECK(stackCopy[2].banked.bank == 0x0);
        CHECK(stackCopy[2].banked.address == 0x00);
        //JMS_3 0x00
        processor->nextCommand();
        CHECK(processor->getPC().banked.bank == 0x3);
        CHECK(processor->getPC().banked.address == 0x00);
        processor->getPtrToStack()->getCopyOfStack(stackCopy);
        CHECK(stackCopy[0].banked.bank == 0x2);
        CHECK(stackCopy[0].banked.address == 0x02);
        CHECK(stackCopy[1].banked.bank == 0x1);
        CHECK(stackCopy[1].banked.address == 0x38);
        CHECK(stackCopy[2].banked.bank == 0x0);
        CHECK(stackCopy[2].banked.address == 0x06);
        //JMS_4 0x00
        processor->nextCommand();
        CHECK(processor->getPC().banked.bank == 0x4);
        CHECK(processor->getPC().banked.address == 0x00);
        processor->getPtrToStack()->getCopyOfStack(stackCopy);
        CHECK(stackCopy[0].banked.bank == 0x3);
        CHECK(stackCopy[0].banked.address == 0x02);
        CHECK(stackCopy[1].banked.bank == 0x2);
        CHECK(stackCopy[1].banked.address == 0x02);
        CHECK(stackCopy[2].banked.bank == 0x1);
        CHECK(stackCopy[2].banked.address == 0x38);
        // BBL_1
        processor->nextCommand();
        CHECK(processor->getPC().banked.bank == 0x3);
        CHECK(processor->getPC().banked.address == 0x02);
        processor->getPtrToStack()->getCopyOfStack(stackCopy);
        CHECK(stackCopy[0].banked.bank == 0x2);
        CHECK(stackCopy[0].banked.address == 0x02);
        CHECK(stackCopy[1].banked.bank == 0x1);
        CHECK(stackCopy[1].banked.address == 0x38);
        CHECK(stackCopy[2].banked.bank == 0x3);
        CHECK(stackCopy[2].banked.address == 0x02);
        CHECK(processor->getAccumulator() == 0x1);
        // BBL_2
        processor->nextCommand();
        CHECK(processor->getPC().banked.bank == 0x2);
        CHECK(processor->getPC().banked.address == 0x02);
        processor->getPtrToStack()->getCopyOfStack(stackCopy);
        CHECK(stackCopy[0].banked.bank == 0x1);
        CHECK(stackCopy[0].banked.address == 0x38);
        CHECK(stackCopy[1].banked.bank == 0x3);
        CHECK(stackCopy[1].banked.address == 0x02);
        CHECK(stackCopy[2].banked.bank == 0x2);
        CHECK(stackCopy[2].banked.address == 0x02);
        CHECK(processor->getAccumulator() == 0x2);
        // BBL_3
        processor->nextCommand();
        CHECK(processor->getPC().banked.bank == 0x1);
        CHECK(processor->getPC().banked.address == 0x38);
        processor->getPtrToStack()->getCopyOfStack(stackCopy);
        CHECK(stackCopy[0].banked.bank == 0x3);
        CHECK(stackCopy[0].banked.address == 0x02);
        CHECK(stackCopy[1].banked.bank == 0x2);
        CHECK(stackCopy[1].banked.address == 0x02);
        CHECK(stackCopy[2].banked.bank == 0x1);
        CHECK(stackCopy[2].banked.address == 0x38);
        CHECK(processor->getAccumulator() == 0x3);
        // BBL_4
        processor->nextCommand();
        CHECK(processor->getPC().banked.bank == 0x3);
        CHECK(processor->getPC().banked.address == 0x02);
        processor->getPtrToStack()->getCopyOfStack(stackCopy);
        CHECK(stackCopy[0].banked.bank == 0x2);
        CHECK(stackCopy[0].banked.address == 0x02);
        CHECK(stackCopy[1].banked.bank == 0x1);
        CHECK(stackCopy[1].banked.address == 0x38);
        CHECK(stackCopy[2].banked.bank == 0x3);
        CHECK(stackCopy[2].banked.address == 0x02);
        CHECK(processor->getAccumulator() == 0x4);

        delete[] stackCopy;

        CHECK(processor->getTicks() == 19);
    }
    SECTION("LDM") {
        /**
         * LDM_2        1
         * CMC          1
         * LDM_15       1
         * LDM_0        1
         * NOP          1
         */

        uint8_t source[] = { LDM_2, CMC, LDM_15, LDM_0, NOP };

        Intel4004Base *processor = { get4004Instance(0xFFFF, 0xFFFFFFFF) };

        CHECK(processor->getPtrToROM()->writeFrom(source, sizeof(source)) == 5);

        REQUIRE(processor->getPC().banked.bank == 0x0);
        REQUIRE(processor->getPC().banked.address == 0x00);
        CHECK_FALSE(processor->getCarry());
        CHECK_FALSE(processor->getAccumulator());
        // LDM_2
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x2);
        CHECK_FALSE(processor->getCarry());
        // CMC
        processor->nextCommand();
        CHECK(processor->getCarry());
        // LDM_15
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0xF);
        CHECK(processor->getCarry());
        //LDM_0
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x0);
        CHECK(processor->getCarry());

        CHECK(processor->getTicks() == 4);
    }
    SECTION("CLB") {
        /**
         * LDM_2        1
         * CLB          1
         * CMC          1
         * LDM_15       1
         * CLB          1
         * CMC          1
         * CLB          1
         * NOP          1
         */

        uint8_t source[] = { LDM_2, CLB, CMC, LDM_15, CLB, CMC, CLB, NOP };

        Intel4004Base *processor = { get4004Instance(0xFFFF, 0xFFFFFFFF) };

        CHECK(processor->getPtrToROM()->writeFrom(source, sizeof(source)) == 8);

        REQUIRE(processor->getPC().banked.bank == 0x0);
        REQUIRE(processor->getPC().banked.address == 0x00);
        CHECK_FALSE(processor->getCarry());
        CHECK_FALSE(processor->getAccumulator());
        // LDM_2
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x2);
        CHECK_FALSE(processor->getCarry());
        // CLB
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x0);
        CHECK_FALSE(processor->getCarry());
        // CMC
        processor->nextCommand();
        CHECK(processor->getCarry());
        // LDM_15
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0xF);
        CHECK(processor->getCarry());
        // CLB
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x0);
        CHECK_FALSE(processor->getCarry());
        // CMC
        processor->nextCommand();
        CHECK(processor->getCarry());
        // CLB
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x0);
        CHECK_FALSE(processor->getCarry());

        CHECK(processor->getTicks() == 7);
    }
    SECTION("CLC") {
        /**
         * LDM_2        1
         * CLC          1
         * CMC          1
         * CLC          1
         * NOP          1
         */

        uint8_t source[] = { LDM_2, CLC, CMC, CLC, NOP };

        Intel4004Base *processor = { get4004Instance(0xFFFF, 0xFFFFFFFF) };

        CHECK(processor->getPtrToROM()->writeFrom(source, sizeof(source)) == 5);

        REQUIRE(processor->getPC().banked.bank == 0x0);
        REQUIRE(processor->getPC().banked.address == 0x00);
        CHECK_FALSE(processor->getCarry());
        CHECK_FALSE(processor->getAccumulator());
        // LDM_2
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x2);
        CHECK_FALSE(processor->getCarry());
        // CLC
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x2);
        CHECK_FALSE(processor->getCarry());
        // CMC
        processor->nextCommand();
        CHECK(processor->getCarry());
        // CLC
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x2);
        CHECK_FALSE(processor->getCarry());

        CHECK(processor->getTicks() == 4);
    }
    SECTION("IAC") {
        /**
         * LDM_13       1
         * CMC          1
         * IAC          1
         * IAC          1
         * IAC          1
         * IAC          1
         * NOP          1
         */

        uint8_t source[] = { LDM_13, CMC, IAC, IAC, IAC, IAC, NOP };

        Intel4004Base *processor = { get4004Instance(0xFFFF, 0xFFFFFFFF) };

        CHECK(processor->getPtrToROM()->writeFrom(source, sizeof(source)) == 7);

        REQUIRE(processor->getPC().banked.bank == 0x0);
        REQUIRE(processor->getPC().banked.address == 0x00);
        CHECK_FALSE(processor->getCarry());
        CHECK_FALSE(processor->getAccumulator());
        // LDM_13
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0xD);
        CHECK_FALSE(processor->getCarry());
        // CMC
        processor->nextCommand();
        CHECK(processor->getCarry());
        // IAC
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0xE);
        CHECK_FALSE(processor->getCarry());
        // IAC
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0xF);
        CHECK_FALSE(processor->getCarry());
        // IAC
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x0);
        CHECK(processor->getCarry());
        // IAC
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x1);
        CHECK_FALSE(processor->getCarry());

        CHECK(processor->getTicks() == 6);
    }
    SECTION("CMC") {
        /**
         * CMC          1
         * CMC          1
         * CMC          1
         * NOP          1
         */

        uint8_t source[] = { CMC, CMC, CMC, NOP };

        Intel4004Base *processor = { get4004Instance(0xFFFF, 0xFFFFFFFF) };

        CHECK(processor->getPtrToROM()->writeFrom(source, sizeof(source)) == 4);

        REQUIRE(processor->getPC().banked.bank == 0x0);
        REQUIRE(processor->getPC().banked.address == 0x00);
        CHECK_FALSE(processor->getCarry());
        CHECK_FALSE(processor->getAccumulator());
        // CMC
        processor->nextCommand();
        CHECK(processor->getCarry());
        // CMC
        processor->nextCommand();
        CHECK_FALSE(processor->getCarry());
        // CMC
        processor->nextCommand();
        CHECK(processor->getCarry());

        CHECK(processor->getTicks() == 3);
    }
    SECTION("RAL") {
        /**
         * LDM_11       1
         * RAL          1
         * RAL          1
         * NOP          1
         */

        uint8_t source[] = { LDM_11, RAL, RAL, NOP };

        Intel4004Base *processor = { get4004Instance(0xFFFF, 0xFFFFFFFF) };

        CHECK(processor->getPtrToROM()->writeFrom(source, sizeof(source)) == 4);

        REQUIRE(processor->getPC().banked.bank == 0x0);
        REQUIRE(processor->getPC().banked.address == 0x00);
        CHECK_FALSE(processor->getCarry());
        CHECK_FALSE(processor->getAccumulator());
        // LDM_11
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0xB);
        CHECK_FALSE(processor->getCarry());
        // RAL
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x6);
        CHECK(processor->getCarry());
        // RAL
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0xD);
        CHECK_FALSE(processor->getCarry());

        CHECK(processor->getTicks() == 3);
    }
    SECTION("RAR") {
        /**
         * LDM_11       1
         * RAR          1
         * RAR          1
         * NOP          1
         */

        uint8_t source[] = { LDM_11, RAR, RAR, NOP };

        Intel4004Base *processor = { get4004Instance(0xFFFF, 0xFFFFFFFF) };

        CHECK(processor->getPtrToROM()->writeFrom(source, sizeof(source)) == 4);

        REQUIRE(processor->getPC().banked.bank == 0x0);
        REQUIRE(processor->getPC().banked.address == 0x00);
        CHECK_FALSE(processor->getCarry());
        CHECK_FALSE(processor->getAccumulator());
        // LDM_11
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0xB);
        CHECK_FALSE(processor->getCarry());
        // RAR
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x5);
        CHECK(processor->getCarry());
        // RAR
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0xA);
        CHECK(processor->getCarry());

        CHECK(processor->getTicks() == 3);
    }
    SECTION("TCC") {
        /**
         * LDM_11       1
         * TCC          1
         * CMC          1
         * TCC          1
         * TCC          1
         * TCC          1
         * NOP          1
         */

        uint8_t source[] = { LDM_11, TCC, CMC, TCC, TCC, TCC, NOP };

        Intel4004Base *processor = { get4004Instance(0xFFFF, 0xFFFFFFFF) };

        CHECK(processor->getPtrToROM()->writeFrom(source, sizeof(source)) == 7);

        REQUIRE(processor->getPC().banked.bank == 0x0);
        REQUIRE(processor->getPC().banked.address == 0x00);
        CHECK_FALSE(processor->getCarry());
        CHECK_FALSE(processor->getAccumulator());
        // LDM_11
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0xB);
        CHECK_FALSE(processor->getCarry());
        // TCC
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x0);
        CHECK_FALSE(processor->getCarry());
        // CMC
        processor->nextCommand();
        CHECK(processor->getCarry());
        // TCC
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x1);
        CHECK_FALSE(processor->getCarry());
        // TCC
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x0);
        CHECK_FALSE(processor->getCarry());
        // TCC
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x0);
        CHECK_FALSE(processor->getCarry());

        CHECK(processor->getTicks() == 6);
    }
    SECTION("DAC") {
        /**
         * LDM_1        1
         * DAC          1
         * DAC          1
         * DAC          1
         * DAC          1
         * NOP          1
         */

        uint8_t source[] = { LDM_1, DAC, DAC, DAC, DAC, NOP };

        Intel4004Base *processor = { get4004Instance(0xFFFF, 0xFFFFFFFF) };

        CHECK(processor->getPtrToROM()->writeFrom(source, sizeof(source)) == 6);

        REQUIRE(processor->getPC().banked.bank == 0x0);
        REQUIRE(processor->getPC().banked.address == 0x00);
        CHECK_FALSE(processor->getCarry());
        CHECK_FALSE(processor->getAccumulator());
        // LDM_1
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x1);
        CHECK_FALSE(processor->getCarry());
        // DAC
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x0);
        CHECK(processor->getCarry());
        // DAC
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0xF);
        CHECK_FALSE(processor->getCarry());
        // DAC
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0xE);
        CHECK(processor->getCarry());
        // DAC
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0xD);
        CHECK(processor->getCarry());

        CHECK(processor->getTicks() == 5);
    }
    SECTION("TCS") {
        /**
         * TCS          1
         * CMC          1
         * TCS          1
         * TCS          1
         * NOP          1
         */

        uint8_t source[] = { TCS, CMC, TCS, TCS, NOP };

        Intel4004Base *processor = { get4004Instance(0xFFFF, 0xFFFFFFFF) };

        CHECK(processor->getPtrToROM()->writeFrom(source, sizeof(source)) == 5);

        REQUIRE(processor->getPC().banked.bank == 0x0);
        REQUIRE(processor->getPC().banked.address == 0x00);
        CHECK_FALSE(processor->getCarry());
        CHECK_FALSE(processor->getAccumulator());
        // TCS
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x9);
        CHECK_FALSE(processor->getCarry());
        // CMC
        processor->nextCommand();
        CHECK(processor->getCarry());
        // TCS
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0xA);
        CHECK_FALSE(processor->getCarry());
        // TCS
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x9);
        CHECK_FALSE(processor->getCarry());

        CHECK(processor->getTicks() == 4);
    }
    SECTION("STC") {
        /**
         * STC          1
         * CLB          1
         * LDM_5        1
         * STC          1
         * STC          1
         * NOP          1
         */

        uint8_t source[] = { STC, CLB, LDM_5, STC, STC, NOP };

        Intel4004Base *processor = { get4004Instance(0xFFFF, 0xFFFFFFFF) };

        CHECK(processor->getPtrToROM()->writeFrom(source, sizeof(source)) == 6);

        REQUIRE(processor->getPC().banked.bank == 0x0);
        REQUIRE(processor->getPC().banked.address == 0x00);
        CHECK_FALSE(processor->getCarry());
        CHECK_FALSE(processor->getAccumulator());
        // STC
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x0);
        CHECK(processor->getCarry());
        // CLB
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x0);
        CHECK_FALSE(processor->getCarry());
        // LDM_5
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x5);
        // STC
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x5);
        CHECK(processor->getCarry());
        // STC
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x5);
        CHECK(processor->getCarry());

        CHECK(processor->getTicks() == 5);        
    }
    SECTION("DAA") {
        /**
         * LDM_5        1
         * DAA          1
         * STC          1
         * DAA          1
         * CLC          1
         * DAA          1
         * LDM_10       1
         * DAA          1
         * NOP          1
         */

        uint8_t source[] = { LDM_5, DAA, STC, DAA, CLC, DAA, LDM_10, DAA, NOP };

        Intel4004Base *processor = { get4004Instance(0xFFFF, 0xFFFFFFFF) };

        CHECK(processor->getPtrToROM()->writeFrom(source, sizeof(source)) == 9);

        REQUIRE(processor->getPC().banked.bank == 0x0);
        REQUIRE(processor->getPC().banked.address == 0x00);
        CHECK_FALSE(processor->getCarry());
        CHECK_FALSE(processor->getAccumulator());
        // LDM_5
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x5);
        CHECK_FALSE(processor->getCarry());
        // DAA
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x5);
        CHECK_FALSE(processor->getCarry());
        // STC
        processor->nextCommand();
        CHECK(processor->getCarry());
        // DAA
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0xB);
        CHECK(processor->getCarry());
        // CLC
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0xB);
        CHECK_FALSE(processor->getCarry());
        // DAA
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x1);
        CHECK(processor->getCarry());
        // LDM_10
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0xA);
        CHECK(processor->getCarry());
        // DAA
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x0);
        CHECK(processor->getCarry());

        CHECK(processor->getTicks() == 8);
    }
    SECTION("KBP") {
        /**
         * KBP          1
         * LDM_1        1
         * KBP          1
         * LDM_2        1
         * KBP          1
         * LDM_4        1
         * KBP          1
         * LDM_8        1
         * KBP          1
         * LDM_3        1
         * KBP          1
         * LDM_5        1
         * KBP          1
         * STC          1
         * LDM_6        1
         * KBP          1
         * LDM_7        1
         * KBP          1
         * LDM_9        1
         * KBP          1
         * LDM_10       1
         * KBP          1
         * LDM_11       1
         * KBP          1
         * LDM_12       1
         * KBP          1
         * LDM_13       1
         * KBP          1
         * LDM_14       1
         * KBP          1
         * LDM_15       1
         * KBP          1
         * NOP          1
         */

        uint8_t source[] = { KBP, LDM_1, KBP, LDM_2, KBP, LDM_4, KBP, LDM_8, KBP, LDM_3, KBP, LDM_5, KBP, STC, LDM_6, KBP, LDM_7, KBP, LDM_9, KBP, LDM_10, KBP, LDM_11, KBP, LDM_12, KBP, LDM_13, KBP, LDM_14, KBP, LDM_15, KBP, NOP };

        Intel4004Base *processor = { get4004Instance(0xFFFF, 0xFFFFFFFF) };

        CHECK(processor->getPtrToROM()->writeFrom(source, sizeof(source)) == 33);

        REQUIRE(processor->getPC().banked.bank == 0x0);
        REQUIRE(processor->getPC().banked.address == 0x00);
        CHECK_FALSE(processor->getCarry());
        CHECK_FALSE(processor->getAccumulator());
        // KBP
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x0);
        CHECK_FALSE(processor->getCarry());
        // LDM_1
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x1);
        CHECK_FALSE(processor->getCarry());
        // KBP
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x1);
        CHECK_FALSE(processor->getCarry());
        // LDM_2
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x2);
        CHECK_FALSE(processor->getCarry());
        // KBP
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x2);
        CHECK_FALSE(processor->getCarry());
        // LDM_4
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x4);
        CHECK_FALSE(processor->getCarry());
        // KBP
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x3);
        CHECK_FALSE(processor->getCarry());
        // LDM_8
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x8);
        CHECK_FALSE(processor->getCarry());
        // KBP
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x4);
        CHECK_FALSE(processor->getCarry());
        // LDM_(3,5)
        int check[2] = {3, 5};
        for (int i = 0; i < 2; i++) {
            // LDM_i
            processor->nextCommand();
            CHECK(processor->getAccumulator() == check[i]);
            CHECK_FALSE(processor->getCarry());
            // KBP
            processor->nextCommand();
            CHECK(processor->getAccumulator() == 0xF);
            CHECK_FALSE(processor->getCarry());
        }
        // STC
        processor->nextCommand();
        CHECK(processor->getCarry());
        //LDM_(6,7,9-15)
        int checkTwo[9] = {6, 7, 9, 10, 11, 12, 13, 14, 15};
        for (int i = 0; i < 9; i++) {
            // LDM_i
            processor->nextCommand();
            CHECK(processor->getAccumulator() == checkTwo[i]);
            CHECK(processor->getCarry());
            // KBP
            processor->nextCommand();
            CHECK(processor->getAccumulator() == 0xF);
            CHECK(processor->getCarry());
        }

        CHECK(processor->getTicks() == 32);
    }
    SECTION("DCL") {
        /**
         * LDM_5        1
         * WRM          1
         * LDM_0        1
         * DCL          1
         * WRM          1
         * LDM_1        1
         * DCL          1
         * WRM          1
         * LDM_2        1
         * DCL          1
         * WRM          1
         * LDM_3        1
         * DCL          1
         * WRM          1
         * LDM_4        1
         * DCL          1
         * WRM          1
         * LDM_5        1
         * DCL          1
         * WRM          1
         * LDM_6        1
         * DCL          1
         * WRM          1
         * LDM_7        1
         * DCL          1
         * WRM          1
         * NOP          1
         */

        uint8_t source[] = { LDM_5, WRM, LDM_0, DCL, WRM, LDM_1, DCL, WRM, LDM_2, DCL, WRM, LDM_3, DCL, WRM, LDM_4, DCL, WRM, LDM_5, DCL, WRM, LDM_6, DCL, WRM, LDM_7, DCL, WRM, NOP };

        Intel4004Base *processor = { get4004Instance(0xFFFF, 0xFFFFFFFF) };

        CHECK(processor->getPtrToROM()->writeFrom(source, sizeof(source)) == 27);

        REQUIRE(processor->getPC().banked.bank == 0x0);
        REQUIRE(processor->getPC().banked.address == 0x00);
        CHECK_FALSE(processor->getCarry());
        CHECK_FALSE(processor->getAccumulator());
        // LDM_5
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x5);
        CHECK_FALSE(processor->getCarry());
        // WRM
        processor->nextCommand();
        CHECK(processor->getPtrToRAM()->readRAMNibble(BANK0, CHIP0, REG0, 0x0) == 0x5);
        // 0-7
        for (int i = 0; i < 8; i++) {
            // LDM_i
            processor->nextCommand();
            CHECK(processor->getAccumulator() == i);
            CHECK_FALSE(processor->getCarry());
            // DCL
            processor->nextCommand();
            CHECK(processor->getAccumulator() == i);
            // WRM
            processor->nextCommand();
            CHECK(processor->getPtrToRAM()->readRAMNibble((ERAMBank) i, CHIP0, REG0, 0x0) == i);
        }

        CHECK(processor->getTicks() == 26);
    }
    SECTION("SRC") {
        /**
         * LDM_5        1
         * FIM_0 0x00   1
         * FIM_2 0x51   1
         * FIM_4 0xA2   1
         * FIM_6 0xF3   1
         * FIM_8 0x00   1
         * FIM_10 0x51  1
         * FIM_12 0xA2  1
         * FIM_14 0xF3  1
         * SRC_0-14     1
         * WRM          1
         * WR0          1
         * WMP          1
         * WRR          1
         * NOP          1
         */

        uint8_t source[] = { LDM_5, FIM_0, 0x00, FIM_2, 0x51, FIM_4, 0xA2, FIM_6, 0xF3, FIM_8, 0x00, FIM_10, 0x51, FIM_12, 0xA2, FIM_14, 0xF3, SRC_0, WRM, WR0, WMP, WRR, SRC_2, WRM, WR0, WMP, WRR, SRC_4, WRM, WR0, WMP, WRR, SRC_6, WRM, WR0, WMP, WRR, SRC_8, WRM, WR0, WMP, WRR, SRC_10, WRM, WR0, WMP, WRR, SRC_12, WRM, WR0, WMP, WRR, SRC_14, WRM, WR0, WMP, WRR, NOP };

        Intel4004Base *processor = { get4004Instance(0xFFFF, 0xFFFFFFFF) };

        CHECK(processor->getPtrToROM()->writeFrom(source, sizeof(source)) == 58);

        REQUIRE(processor->getPC().banked.bank == 0x0);
        REQUIRE(processor->getPC().banked.address == 0x00);
        CHECK_FALSE(processor->getCarry());
        CHECK_FALSE(processor->getAccumulator());
        // LDM_5
        processor->nextCommand();
        // FIM_0 0x00
        processor->nextCommand();
        // FIM_2 0x51
        processor->nextCommand();
        // FIM_4 0xA2
        processor->nextCommand();
        // FIM_6 0xF3
        processor->nextCommand();
        // FIM_8 0x00
        processor->nextCommand();
        // FIM_10 0x51
        processor->nextCommand();
        // FIM_12 0xA2
        processor->nextCommand();
        // FIM_14 0xF3
        processor->nextCommand();
        // SRC_0-14
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 4; j++) {
                // SRC 0-14
                processor->nextCommand();
                // WRM
                processor->nextCommand();
                // WR0
                processor->nextCommand();
                // WMP
                processor->nextCommand();
                // WRR
                processor->nextCommand();
                CHECK(processor->getPtrToRAM()->readRAMNibble(BANK0, (ERAMChip) j, (ERAMRegister) j, j) == 5);
                CHECK(processor->getPtrToRAM()->readStatusNibble(BANK0, (ERAMChip) j, (ERAMRegister) j, 0) == 5);
                CHECK(processor->getPtrToRAM()->readFromPortBuffer(BANK0, (ERAMChip) j) == 5);
                CHECK(processor->getPtrToROM()->readFromPort((EROMChip) ((j << 2) + j)) == 5);
            }
        }

        CHECK(processor->getTicks() == 57);
    }
    SECTION("WRM") {
        /**
         * FIM_0 0x36   1
         * SRC_0        1
         * LDM_15       1
         * WRM          1
         * LDM_6        1
         * STC          1
         * WRM          1
         * FIM_0 0xFF   1
         * SRC_0        1
         * WRM          1
         * NOP          1
         */

        uint8_t source[] = { FIM_0, 0x36, SRC_0, LDM_15, WRM, LDM_6, STC, WRM, FIM_0, 0xFF, SRC_0, WRM, NOP };

        Intel4004Base *processor = { get4004Instance(0xFFFF, 0xFFFFFFFF) };

        CHECK(processor->getPtrToROM()->writeFrom(source, sizeof(source)) == 13);

        REQUIRE(processor->getPC().banked.bank == 0x0);
        REQUIRE(processor->getPC().banked.address == 0x00);
        CHECK_FALSE(processor->getCarry());
        CHECK_FALSE(processor->getAccumulator());
        // FIM_0 0x36
        processor->nextCommand();
        // SRC_0
        processor->nextCommand();
        // LDM_15
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0xF);
        CHECK_FALSE(processor->getCarry());
        // WRM
        processor->nextCommand();
        CHECK(processor->getPtrToRAM()->readRAMNibble(BANK0, CHIP0, REG3, 6) == 0xF);
        CHECK(processor->getAccumulator() == 0xF);
        CHECK_FALSE(processor->getCarry());
        // LDM_6
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x6);
        // STC
        processor->nextCommand();
        CHECK(processor->getCarry());
        // WRM
        processor->nextCommand();
        CHECK(processor->getPtrToRAM()->readRAMNibble(BANK0, CHIP0, REG3, 6) == 0x6);
        CHECK(processor->getAccumulator() == 0x6);
        CHECK(processor->getCarry());
        // FIM_0 0xFF
        processor->nextCommand();
        // SRC_0
        processor->nextCommand();
        // WRM
        processor->nextCommand();
        CHECK(processor->getPtrToRAM()->readRAMNibble(BANK0, CHIP3, REG3, 15) == 0x6);
        CHECK(processor->getPtrToRAM()->readRAMNibble(BANK0, CHIP0, REG3, 6) == 0x6);
        CHECK(processor->getAccumulator() == 0x6);
        CHECK(processor->getCarry());

        CHECK(processor->getTicks() == 12);
    }
    SECTION("WMP") {
        /**
         * FIM_0 0x36   1
         * SRC_0        1
         * LDM_15       1
         * WMP          1
         * LDM_6        1
         * STC          1
         * WMP          1
         * FIM_0 0xFF   1
         * SRC_0        1
         * WMP          1
         * NOP          1
         */

        uint8_t source[] = { FIM_0, 0x36, SRC_0, LDM_15, WMP, LDM_6, STC, WMP, FIM_0, 0xFF, SRC_0, WMP, NOP };

        Intel4004Base *processor = { get4004Instance(0xFFFF, 0xFFFFFFFF) };

        CHECK(processor->getPtrToROM()->writeFrom(source, sizeof(source)) == 13);

        REQUIRE(processor->getPC().banked.bank == 0x0);
        REQUIRE(processor->getPC().banked.address == 0x00);
        CHECK_FALSE(processor->getCarry());
        CHECK_FALSE(processor->getAccumulator());
        // FIM_0 0x36
        processor->nextCommand();
        // SRC_0
        processor->nextCommand();
        // LDM_15
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0xF);
        CHECK_FALSE(processor->getCarry());
        // WMP
        processor->nextCommand();
        CHECK(processor->getPtrToRAM()->readFromPortBuffer(BANK0, CHIP0) == 0xF);
        CHECK(processor->getAccumulator() == 0xF);
        CHECK_FALSE(processor->getCarry());
        // LDM_6
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x6);
        // STC
        processor->nextCommand();
        CHECK(processor->getCarry());
        // WMP
        processor->nextCommand();
        CHECK(processor->getPtrToRAM()->readFromPortBuffer(BANK0, CHIP0) == 0x6);
        CHECK(processor->getAccumulator() == 0x6);
        CHECK(processor->getCarry());
        // FIM_0 0xFF
        processor->nextCommand();
        // SRC_0
        processor->nextCommand();
        // WMP
        processor->nextCommand();
        CHECK(processor->getPtrToRAM()->readFromPortBuffer(BANK0, CHIP3) == 0x6);
        CHECK(processor->getPtrToRAM()->readFromPortBuffer(BANK0, CHIP0) == 0x6);
        CHECK(processor->getAccumulator() == 0x6);
        CHECK(processor->getCarry());

        CHECK(processor->getTicks() == 12);
    }
    SECTION("WRR") {
        /**
         * FIM_0 0x36   1
         * SRC_0        1
         * LDM_15       1
         * WRR          1
         * LDM_6        1
         * STC          1
         * WRR          1
         * FIM_0 0xFF   1
         * SRC_0        1
         * WRR          1
         * NOP          1
         */

        uint8_t source[] = { FIM_0, 0x36, SRC_0, LDM_15, WRR, LDM_6, STC, WRR, FIM_0, 0xFF, SRC_0, WRR, NOP };

        Intel4004Base *processor = { get4004Instance(0xFFFF, 0xFFFFFFFF) };

        CHECK(processor->getPtrToROM()->writeFrom(source, sizeof(source)) == 13);

        REQUIRE(processor->getPC().banked.bank == 0x0);
        REQUIRE(processor->getPC().banked.address == 0x00);
        CHECK_FALSE(processor->getCarry());
        CHECK_FALSE(processor->getAccumulator());
        // FIM_0 0x36
        processor->nextCommand();
        // SRC_0
        processor->nextCommand();
        // LDM_15
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0xF);
        CHECK_FALSE(processor->getCarry());
        // WRR
        processor->nextCommand();
        CHECK(processor->getPtrToROM()->readFromPort(ROMCHIP3) == 0xF);
        CHECK(processor->getAccumulator() == 0xF);
        CHECK_FALSE(processor->getCarry());
        // LDM_6
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x6);
        // STC
        processor->nextCommand();
        CHECK(processor->getCarry());
        // WRR
        processor->nextCommand();
        CHECK(processor->getPtrToROM()->readFromPort(ROMCHIP3) == 0x6);
        CHECK(processor->getAccumulator() == 0x6);
        CHECK(processor->getCarry());
        // FIM_0 0xFF
        processor->nextCommand();
        // SRC_0
        processor->nextCommand();
        // WRR
        processor->nextCommand();
        CHECK(processor->getPtrToROM()->readFromPort(ROMCHIP15) == 0x6);
        CHECK(processor->getPtrToROM()->readFromPort(ROMCHIP3) == 0x6);
        CHECK(processor->getAccumulator() == 0x6);
        CHECK(processor->getCarry());

        CHECK(processor->getTicks() == 12);
    }
    SECTION("WPM") {
        /**
         * LDM_5        1
         * WPM          1
         * STC          1
         * WPM          1
         * NOP          1
         */

        uint8_t source[] = { LDM_5, WPM, STC, WPM, NOP };

        Intel4004Base *processor = { get4004Instance(0xFFFF, 0xFFFFFFFF) };

        CHECK(processor->getPtrToROM()->writeFrom(source, sizeof(source)) == 5);

        REQUIRE(processor->getPC().banked.bank == 0x0);
        REQUIRE(processor->getPC().banked.address == 0x00);
        CHECK_FALSE(processor->getCarry());
        CHECK_FALSE(processor->getAccumulator());
        // LDM_5
        processor->nextCommand();
        // WPM
        processor->nextCommand();
        CHECK(processor->getPtrToRAM()->readRAMNibble(BANK0, CHIP0, REG0, 0) == 0x0);
        CHECK(processor->getPtrToRAM()->readFromPortBuffer(BANK0, CHIP0) == 0x0);
        CHECK(processor->getAccumulator() == 0x5);
        CHECK_FALSE(processor->getCarry());
        // STC
        processor->nextCommand();
        CHECK(processor->getCarry());
        // WPM
        processor->nextCommand();
        CHECK(processor->getPtrToRAM()->readRAMNibble(BANK0, CHIP0, REG0, 0) == 0x0);
        CHECK(processor->getPtrToRAM()->readFromPortBuffer(BANK0, CHIP0) == 0x0);
        CHECK(processor->getAccumulator() == 0x5);
        CHECK(processor->getCarry());

        CHECK(processor->getTicks() == 4);
    }
    SECTION("WR0") {
        /**
         * LDM_15       1
         * WR0          1
         * STC          1
         * FIM_0 0xFF   1
         * SRC_0        1
         * WR0          1
         * LDM_2        1
         * FIM_0 0x0F   1
         * SRC_0        1
         * WR0          1
         * NOP          1
         */

        uint8_t source[] = { LDM_15, WR0, STC, FIM_0, 0xFF, SRC_0, WR0, LDM_2, FIM_0, 0x0F, SRC_0, WR0, NOP };

        Intel4004Base *processor = { get4004Instance(0xFFFF, 0xFFFFFFFF) };

        CHECK(processor->getPtrToROM()->writeFrom(source, sizeof(source)) == 13);

        REQUIRE(processor->getPC().banked.bank == 0x0);
        REQUIRE(processor->getPC().banked.address == 0x00);
        CHECK_FALSE(processor->getCarry());
        CHECK_FALSE(processor->getAccumulator());
        // LDM_15
        processor->nextCommand();
        // WR0
        processor->nextCommand();
        CHECK(processor->getPtrToRAM()->readStatusNibble(BANK0, CHIP0, REG0, 0) == 0xF);
        CHECK(processor->getAccumulator() == 0xF);
        CHECK_FALSE(processor->getCarry());
        // STC
        processor->nextCommand();
        CHECK(processor->getCarry());
        // FIM_0 0xFF
        processor->nextCommand();
        // SRC_0
        processor->nextCommand();
        // WR0
        processor->nextCommand();
        CHECK(processor->getPtrToRAM()->readStatusNibble(BANK0, CHIP3, REG3, 0) == 0xF);
        CHECK(processor->getPtrToRAM()->readStatusNibble(BANK0, CHIP0, REG0, 0) == 0xF);
        CHECK(processor->getAccumulator() == 0xF);
        CHECK(processor->getCarry());
        // LDM_2
        processor->nextCommand();
        // FIM_0 0x0F
        processor->nextCommand();
        // SRC_0
        processor->nextCommand();
        // WR0
        processor->nextCommand();
        CHECK(processor->getPtrToRAM()->readStatusNibble(BANK0, CHIP0, REG0, 0) == 0x2);
        CHECK(processor->getPtrToRAM()->readStatusNibble(BANK0, CHIP3, REG3, 0) == 0xF);
        CHECK(processor->getAccumulator() == 0x2);
        CHECK(processor->getCarry());

        CHECK(processor->getTicks() == 12);
    }
    SECTION("WR1") {
        /**
         * LDM_15       1
         * WR1          1
         * STC          1
         * FIM_0 0xFF   1
         * SRC_0        1
         * WR1          1
         * LDM_2        1
         * FIM_0 0x0F   1
         * SRC_0        1
         * WR1          1
         * NOP          1
         */

        uint8_t source[] = { LDM_15, WR1, STC, FIM_0, 0xFF, SRC_0, WR1, LDM_2, FIM_0, 0x0F, SRC_0, WR1, NOP };

        Intel4004Base *processor = { get4004Instance(0xFFFF, 0xFFFFFFFF) };

        CHECK(processor->getPtrToROM()->writeFrom(source, sizeof(source)) == 13);

        REQUIRE(processor->getPC().banked.bank == 0x0);
        REQUIRE(processor->getPC().banked.address == 0x00);
        CHECK_FALSE(processor->getCarry());
        CHECK_FALSE(processor->getAccumulator());
        // LDM_15
        processor->nextCommand();
        // WR1
        processor->nextCommand();
        CHECK(processor->getPtrToRAM()->readStatusNibble(BANK0, CHIP0, REG0, 1) == 0xF);
        CHECK(processor->getAccumulator() == 0xF);
        CHECK_FALSE(processor->getCarry());
        // STC
        processor->nextCommand();
        CHECK(processor->getCarry());
        // FIM_0 0xFF
        processor->nextCommand();
        // SRC_0
        processor->nextCommand();
        // WR1
        processor->nextCommand();
        CHECK(processor->getPtrToRAM()->readStatusNibble(BANK0, CHIP3, REG3, 1) == 0xF);
        CHECK(processor->getPtrToRAM()->readStatusNibble(BANK0, CHIP0, REG0, 1) == 0xF);
        CHECK(processor->getAccumulator() == 0xF);
        CHECK(processor->getCarry());
        // LDM_2
        processor->nextCommand();
        // FIM_0 0x0F
        processor->nextCommand();
        // SRC_0
        processor->nextCommand();
        // WR1
        processor->nextCommand();
        CHECK(processor->getPtrToRAM()->readStatusNibble(BANK0, CHIP0, REG0, 1) == 0x2);
        CHECK(processor->getPtrToRAM()->readStatusNibble(BANK0, CHIP3, REG3, 1) == 0xF);
        CHECK(processor->getAccumulator() == 0x2);
        CHECK(processor->getCarry());

        CHECK(processor->getTicks() == 12);
    }
    SECTION("WR2") {
        /**
         * LDM_15       1
         * WR2          1
         * STC          1
         * FIM_0 0xFF   1
         * SRC_0        1
         * WR2          1
         * LDM_2        1
         * FIM_0 0x0F   1
         * SRC_0        1
         * WR2          1
         * NOP          1
         */

        uint8_t source[] = { LDM_15, WR2, STC, FIM_0, 0xFF, SRC_0, WR2, LDM_2, FIM_0, 0x0F, SRC_0, WR2, NOP };

        Intel4004Base *processor = { get4004Instance(0xFFFF, 0xFFFFFFFF) };

        CHECK(processor->getPtrToROM()->writeFrom(source, sizeof(source)) == 13);

        REQUIRE(processor->getPC().banked.bank == 0x0);
        REQUIRE(processor->getPC().banked.address == 0x00);
        CHECK_FALSE(processor->getCarry());
        CHECK_FALSE(processor->getAccumulator());
        // LDM_15
        processor->nextCommand();
        // WR2
        processor->nextCommand();
        CHECK(processor->getPtrToRAM()->readStatusNibble(BANK0, CHIP0, REG0, 2) == 0xF);
        CHECK(processor->getAccumulator() == 0xF);
        CHECK_FALSE(processor->getCarry());
        // STC
        processor->nextCommand();
        CHECK(processor->getCarry());
        // FIM_0 0xFF
        processor->nextCommand();
        // SRC_0
        processor->nextCommand();
        // WR2
        processor->nextCommand();
        CHECK(processor->getPtrToRAM()->readStatusNibble(BANK0, CHIP3, REG3, 2) == 0xF);
        CHECK(processor->getPtrToRAM()->readStatusNibble(BANK0, CHIP0, REG0, 2) == 0xF);
        CHECK(processor->getAccumulator() == 0xF);
        CHECK(processor->getCarry());
        // LDM_2
        processor->nextCommand();
        // FIM_0 0x0F
        processor->nextCommand();
        // SRC_0
        processor->nextCommand();
        // WR2
        processor->nextCommand();
        CHECK(processor->getPtrToRAM()->readStatusNibble(BANK0, CHIP0, REG0, 2) == 0x2);
        CHECK(processor->getPtrToRAM()->readStatusNibble(BANK0, CHIP3, REG3, 2) == 0xF);
        CHECK(processor->getAccumulator() == 0x2);
        CHECK(processor->getCarry());

        CHECK(processor->getTicks() == 12);
    }
    SECTION("WR3") {
        /**
         * LDM_15       1
         * WR3          1
         * STC          1
         * FIM_0 0xFF   1
         * SRC_0        1
         * WR3          1
         * LDM_2        1
         * FIM_0 0x0F   1
         * SRC_0        1
         * WR3          1
         * NOP          1
         */

        uint8_t source[] = { LDM_15, WR3, STC, FIM_0, 0xFF, SRC_0, WR3, LDM_2, FIM_0, 0x0F, SRC_0, WR3, NOP };

        Intel4004Base *processor = { get4004Instance(0xFFFF, 0xFFFFFFFF) };

        CHECK(processor->getPtrToROM()->writeFrom(source, sizeof(source)) == 13);

        REQUIRE(processor->getPC().banked.bank == 0x0);
        REQUIRE(processor->getPC().banked.address == 0x00);
        CHECK_FALSE(processor->getCarry());
        CHECK_FALSE(processor->getAccumulator());
        // LDM_15
        processor->nextCommand();
        // WR3
        processor->nextCommand();
        CHECK(processor->getPtrToRAM()->readStatusNibble(BANK0, CHIP0, REG0, 3) == 0xF);
        CHECK(processor->getAccumulator() == 0xF);
        CHECK_FALSE(processor->getCarry());
        // STC
        processor->nextCommand();
        CHECK(processor->getCarry());
        // FIM_0 0xFF
        processor->nextCommand();
        // SRC_0
        processor->nextCommand();
        // WR3
        processor->nextCommand();
        CHECK(processor->getPtrToRAM()->readStatusNibble(BANK0, CHIP3, REG3, 3) == 0xF);
        CHECK(processor->getPtrToRAM()->readStatusNibble(BANK0, CHIP0, REG0, 3) == 0xF);
        CHECK(processor->getAccumulator() == 0xF);
        CHECK(processor->getCarry());
        // LDM_2
        processor->nextCommand();
        // FIM_0 0x0F
        processor->nextCommand();
        // SRC_0
        processor->nextCommand();
        // WR3
        processor->nextCommand();
        CHECK(processor->getPtrToRAM()->readStatusNibble(BANK0, CHIP0, REG0, 3) == 0x2);
        CHECK(processor->getPtrToRAM()->readStatusNibble(BANK0, CHIP3, REG3, 3) == 0xF);
        CHECK(processor->getAccumulator() == 0x2);
        CHECK(processor->getCarry());

        CHECK(processor->getTicks() == 12);
    }
    SECTION("SBM") {
        /**
         * LDM_5        1
         * WRM          1
         * LDM_8        1
         * SBM          1
         * CMC          1
         * XCH_2        1
         * FIM_0 0xF3   1
         * SRC_0        1
         * LDM_9        1
         * WRM          1
         * XCH_2        1
         * SBM          1
         * CMC          1
         * SBM          1
         * NOP          1
         */

        uint8_t source[] = { LDM_5, WRM, LDM_8, SBM, CMC, XCH_2, FIM_0, 0xF3, SRC_0, LDM_9, WRM, XCH_2, SBM, CMC, SBM, NOP };

        Intel4004Base *processor = { get4004Instance(0xFFFF, 0xFFFFFFFF) };

        CHECK(processor->getPtrToROM()->writeFrom(source, sizeof(source)) == 16);

        REQUIRE(processor->getPC().banked.bank == 0x0);
        REQUIRE(processor->getPC().banked.address == 0x00);
        CHECK_FALSE(processor->getCarry());
        CHECK_FALSE(processor->getAccumulator());
        // LDM_5
        processor->nextCommand();
        // WRM
        processor->nextCommand();
        CHECK(processor->getPtrToRAM()->readRAMNibble(BANK0, CHIP0, REG0, 0) == 0x5);
        // LDM_8
        processor->nextCommand();
        // SBM
        processor->nextCommand();
        CHECK(processor->getPtrToRAM()->readRAMNibble(BANK0, CHIP0, REG0, 0) == 0x5);
        CHECK(processor->getAccumulator() == 0x3);
        CHECK(processor->getCarry());
        // CMC
        processor->nextCommand();
        CHECK_FALSE(processor->getCarry());
        // XCH_2
        processor->nextCommand();
        // FIM_0 0xF3
        processor->nextCommand();
        // SRC_0
        processor->nextCommand();
        // LDM_9
        processor->nextCommand();
        // WRM
        processor->nextCommand();
        CHECK(processor->getPtrToRAM()->readRAMNibble(BANK0, CHIP3, REG3, 3) == 0x9);
        // XCH_2
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x3);
        // SBM
        processor->nextCommand();
        CHECK(processor->getPtrToRAM()->readRAMNibble(BANK0, CHIP0, REG0, 0) == 0x5);
        CHECK(processor->getPtrToRAM()->readRAMNibble(BANK0, CHIP3, REG3, 3) == 0x9);
        CHECK(processor->getAccumulator() == 0xA);
        CHECK_FALSE(processor->getCarry());
        // CMC
        processor->nextCommand();
        CHECK(processor->getCarry());
        // SBM
        processor->nextCommand();
        CHECK(processor->getPtrToRAM()->readRAMNibble(BANK0, CHIP0, REG0, 0) == 0x5);
        CHECK(processor->getPtrToRAM()->readRAMNibble(BANK0, CHIP3, REG3, 3) == 0x9);
        CHECK(processor->getAccumulator() == 0x0);
        CHECK(processor->getCarry());

        CHECK(processor->getTicks() == 15);
    }
    SECTION("RDM") {
        /**
         * FIM_0 0x36   1
         * SRC_0        1
         * LDM_15       1
         * WRM          1
         * LDM_0        1
         * RDM          1
         * LDM_6        1
         * STC          1
         * WRM          1
         * RDM          1
         * FIM_0 0xFF   1
         * SRC_0        1
         * RDM  	    1
         * LDM_6        1
         * WRM          1
         * NOP          1
         */

        uint8_t source[] = { FIM_0, 0x36, SRC_0, LDM_15, WRM, LDM_0, RDM, LDM_6, STC, WRM, LDM_0, RDM, FIM_0, 0xFF, SRC_0, RDM, LDM_6, WRM, NOP };

        Intel4004Base *processor = { get4004Instance(0xFFFF, 0xFFFFFFFF) };

        CHECK(processor->getPtrToROM()->writeFrom(source, sizeof(source)) == 19);

        REQUIRE(processor->getPC().banked.bank == 0x0);
        REQUIRE(processor->getPC().banked.address == 0x00);
        CHECK_FALSE(processor->getCarry());
        CHECK_FALSE(processor->getAccumulator());
        // FIM_0 0x36
        processor->nextCommand();
        // SRC_0
        processor->nextCommand();
        // LDM_15
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0xF);
        CHECK_FALSE(processor->getCarry());
        // WRM
        processor->nextCommand();
        CHECK(processor->getPtrToRAM()->readRAMNibble(BANK0, CHIP0, REG3, 6) == 0xF);
        CHECK(processor->getAccumulator() == 0xF);
        CHECK_FALSE(processor->getCarry());
        // LDM_0
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x0);
        // RDM
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0xF);
        // LDM_6
        processor->nextCommand();
        CHECK(processor->getPtrToRAM()->readRAMNibble(BANK0, CHIP0, REG3, 6) == 0xF);
        CHECK(processor->getAccumulator() == 0x6);
        CHECK_FALSE(processor->getCarry());
        // STC
        processor->nextCommand();
        CHECK(processor->getCarry());
        // WRM
        processor->nextCommand();
        CHECK(processor->getPtrToRAM()->readRAMNibble(BANK0, CHIP0, REG3, 6) == 0x6);
        CHECK(processor->getAccumulator() == 0x6);
        CHECK(processor->getCarry());
        // LDM_0
        processor->nextCommand();
        // RDM
        processor->nextCommand();
        CHECK(processor->getPtrToRAM()->readRAMNibble(BANK0, CHIP0, REG3, 6) == 0x6);
        CHECK(processor->getAccumulator() == 0x6);
        CHECK(processor->getCarry());
        // FIM_0 0xFF
        processor->nextCommand();
        // SRC_0
        processor->nextCommand();
        // RDM
        processor->nextCommand();
        CHECK(processor->getPtrToRAM()->readRAMNibble(BANK0, CHIP0, REG3, 6) == 0x6);
        CHECK(processor->getAccumulator() == 0x0);
        CHECK(processor->getCarry());
        // LDM_6
        processor->nextCommand();
        // WRM
        processor->nextCommand();
        CHECK(processor->getPtrToRAM()->readRAMNibble(BANK0, CHIP3, REG3, 15) == 0x6);
        CHECK(processor->getPtrToRAM()->readRAMNibble(BANK0, CHIP0, REG3, 6) == 0x6);
        CHECK(processor->getAccumulator() == 0x6);
        CHECK(processor->getCarry());

        CHECK(processor->getTicks() == 18);
    }
    SECTION("RDR") {
        /**
         * FIM_0 0x36   1
         * SRC_0        1
         * LDM_15       1
         * WRR          1
         * LDM_0
         * RDR
         * LDM_6        1
         * STC          1
         * WRR          1
         * LDM_0
         * RDR
         * FIM_0 0xFF   1
         * SRC_0        1
         * LDM_8
         * WRR          1
         * LDM_0
         * RDR
         * NOP          1
         */

        uint8_t source[] = { FIM_0, 0x36, SRC_0, LDM_15, WRR, LDM_0, RDR, LDM_6, STC, WRR, LDM_0, RDR, FIM_0, 0xFF, SRC_0, LDM_8, WRR, LDM_0, RDR, NOP };

        Intel4004Base *processor = { get4004Instance(0xFFFF, 0xFFFFFFFF) };

        CHECK(processor->getPtrToROM()->writeFrom(source, sizeof(source)) == 20);

        REQUIRE(processor->getPC().banked.bank == 0x0);
        REQUIRE(processor->getPC().banked.address == 0x00);
        CHECK_FALSE(processor->getCarry());
        CHECK_FALSE(processor->getAccumulator());
        // FIM_0 0x36
        processor->nextCommand();
        // SRC_0
        processor->nextCommand();
        // LDM_15
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0xF);
        CHECK_FALSE(processor->getCarry());
        // WRR
        processor->nextCommand();
        CHECK(processor->getPtrToROM()->readFromPort(ROMCHIP3) == 0xF);
        CHECK(processor->getAccumulator() == 0xF);
        CHECK_FALSE(processor->getCarry());
        // LDM_0
        processor->nextCommand();
        // RDR
        processor->nextCommand();
        CHECK(processor->getPtrToROM()->readFromPort(ROMCHIP3) == 0xF);
        CHECK(processor->getAccumulator() == 0xF);
        CHECK_FALSE(processor->getCarry());
        // LDM_6
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x6);
        // STC
        processor->nextCommand();
        CHECK(processor->getCarry());
        // WRR
        processor->nextCommand();
        CHECK(processor->getPtrToROM()->readFromPort(ROMCHIP3) == 0x6);
        CHECK(processor->getAccumulator() == 0x6);
        CHECK(processor->getCarry());
        // LDM_0
        processor->nextCommand();
        // RDR
        processor->nextCommand();
        CHECK(processor->getPtrToROM()->readFromPort(ROMCHIP3) == 0x6);
        CHECK(processor->getAccumulator() == 0x6);
        CHECK(processor->getCarry());
        // FIM_0 0xFF
        processor->nextCommand();
        // SRC_0
        processor->nextCommand();
        // LDM_8
        processor->nextCommand();
        // WRR
        processor->nextCommand();
        CHECK(processor->getPtrToROM()->readFromPort(ROMCHIP15) == 0x8);
        CHECK(processor->getPtrToROM()->readFromPort(ROMCHIP3) == 0x6);
        CHECK(processor->getAccumulator() == 0x8);
        CHECK(processor->getCarry());
        // LDM_0
        processor->nextCommand();
        // RDR
        processor->nextCommand();
        CHECK(processor->getPtrToROM()->readFromPort(ROMCHIP15) == 0x8);
        CHECK(processor->getPtrToROM()->readFromPort(ROMCHIP3) == 0x6);
        CHECK(processor->getAccumulator() == 0x8);
        CHECK(processor->getCarry());

        CHECK(processor->getTicks() == 19);
    }
    SECTION("ADM") {
        /**
         * LDM_5        1
         * WRM          1
         * LDM_10       1
         * ADM          1
         * ADM          1
         * XCH_2        1
         * FIM_0 0xF3   1
         * SRC_0        1
         * LDM_9        1
         * WRM          1
         * XCH_2        1
         * ADM          1
         * NOP          1
         */

        uint8_t source[] = { LDM_5, WRM, LDM_10, ADM, ADM, XCH_2, FIM_0, 0xF3, SRC_0, LDM_9, WRM, XCH_2, ADM, NOP };

        Intel4004Base *processor = { get4004Instance(0xFFFF, 0xFFFFFFFF) };

        CHECK(processor->getPtrToROM()->writeFrom(source, sizeof(source)) == 14);

        REQUIRE(processor->getPC().banked.bank == 0x0);
        REQUIRE(processor->getPC().banked.address == 0x00);
        CHECK_FALSE(processor->getCarry());
        CHECK_FALSE(processor->getAccumulator());
        // LDM_5
        processor->nextCommand();
        // WRM
        processor->nextCommand();
        CHECK(processor->getPtrToRAM()->readRAMNibble(BANK0, CHIP0, REG0, 0) == 0x5);
        // LDM_10
        processor->nextCommand();
        // ADM
        processor->nextCommand();
        CHECK(processor->getPtrToRAM()->readRAMNibble(BANK0, CHIP0, REG0, 0) == 0x5);
        CHECK(processor->getAccumulator() == 0xF);
        CHECK_FALSE(processor->getCarry());
        // ADM
        processor->nextCommand();
        CHECK(processor->getPtrToRAM()->readRAMNibble(BANK0, CHIP0, REG0, 0) == 0x5);
        CHECK(processor->getAccumulator() == 0x4);
        CHECK(processor->getCarry());
        // XCH_2
        processor->nextCommand();
        // FIM_0 0xF3
        processor->nextCommand();
        // SRC_0
        processor->nextCommand();
        // LDM_9
        processor->nextCommand();
        // WRM
        processor->nextCommand();
        CHECK(processor->getPtrToRAM()->readRAMNibble(BANK0, CHIP3, REG3, 3) == 0x9);
        // XCH_2
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x4);
        CHECK(processor->getCarry());
        // ADM
        processor->nextCommand();
        CHECK(processor->getPtrToRAM()->readRAMNibble(BANK0, CHIP0, REG0, 0) == 0x5);
        CHECK(processor->getPtrToRAM()->readRAMNibble(BANK0, CHIP3, REG3, 3) == 0x9);
        CHECK(processor->getAccumulator() == 0xE);
        CHECK_FALSE(processor->getCarry());

        CHECK(processor->getTicks() == 13);
    }
    SECTION("RD0") {
        /**
         * LDM_15       1
         * WR0          1
         * LDM_0        1
         * RD0          1
         * STC          1
         * FIM_0 0xFF   1
         * SRC_0        1
         * LDM_2        1
         * WR0          1
         * LDM_0        1
         * RD0          1
         * FIM_0 0x0F   1
         * SRC_0        1
         * RD0          1
         * NOP          1
         */

        uint8_t source[] = { LDM_15, WR0, LDM_0, RD0, STC, FIM_0, 0xFF, SRC_0, LDM_2, WR0, LDM_0, RD0, FIM_0, 0x0F, SRC_0, RD0, NOP };

        Intel4004Base *processor = { get4004Instance(0xFFFF, 0xFFFFFFFF) };

        CHECK(processor->getPtrToROM()->writeFrom(source, sizeof(source)) == 17);

        REQUIRE(processor->getPC().banked.bank == 0x0);
        REQUIRE(processor->getPC().banked.address == 0x00);
        CHECK_FALSE(processor->getCarry());
        CHECK_FALSE(processor->getAccumulator());
        // LDM_15
        processor->nextCommand();
        // WR0
        processor->nextCommand();
        CHECK(processor->getPtrToRAM()->readStatusNibble(BANK0, CHIP0, REG0, 0) == 0xF);
        CHECK(processor->getAccumulator() == 0xF);
        CHECK_FALSE(processor->getCarry());
        // LDM_0
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x0);
        // RD0
        processor->nextCommand();
        CHECK(processor->getPtrToRAM()->readStatusNibble(BANK0, CHIP0, REG0, 0) == 0xF);
        CHECK(processor->getAccumulator() == 0xF);
        CHECK_FALSE(processor->getCarry());
        // STC
        processor->nextCommand();
        CHECK(processor->getCarry());
        // FIM_0 0xFF
        processor->nextCommand();
        // SRC_0
        processor->nextCommand();
        // LDM_2
        processor->nextCommand();
        // WR0
        processor->nextCommand();
        CHECK(processor->getPtrToRAM()->readStatusNibble(BANK0, CHIP3, REG3, 0) == 0x2);
        CHECK(processor->getPtrToRAM()->readStatusNibble(BANK0, CHIP0, REG0, 0) == 0xF);
        CHECK(processor->getAccumulator() == 0x2);
        CHECK(processor->getCarry());
        // LDM_0
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x0);
        // RD0
        processor->nextCommand();
        CHECK(processor->getPtrToRAM()->readStatusNibble(BANK0, CHIP3, REG3, 0) == 0x2);
        CHECK(processor->getPtrToRAM()->readStatusNibble(BANK0, CHIP0, REG0, 0) == 0xF);
        CHECK(processor->getAccumulator() == 0x2);
        CHECK(processor->getCarry());
        // FIM_0 0x0F
        processor->nextCommand();
        // SRC_0
        processor->nextCommand();
        // RD0
        processor->nextCommand();
        CHECK(processor->getPtrToRAM()->readStatusNibble(BANK0, CHIP3, REG3, 0) == 0x2);
        CHECK(processor->getPtrToRAM()->readStatusNibble(BANK0, CHIP0, REG0, 0) == 0xF);
        CHECK(processor->getAccumulator() == 0xF);
        CHECK(processor->getCarry());

        CHECK(processor->getTicks() == 16);
    }
    SECTION("RD1") {
        /**
         * LDM_15       1
         * WR1          1
         * LDM_0        1
         * RD1          1
         * STC          1
         * FIM_0 0xFF   1
         * SRC_0        1
         * LDM_2        1
         * WR1          1
         * LDM_0        1
         * RD1          1
         * FIM_0 0x0F   1
         * SRC_0        1
         * RD1          1
         * NOP          1
         */

        uint8_t source[] = { LDM_15, WR1, LDM_0, RD1, STC, FIM_0, 0xFF, SRC_0, LDM_2, WR1, LDM_0, RD1, FIM_0, 0x0F, SRC_0, RD1, NOP };

        Intel4004Base *processor = { get4004Instance(0xFFFF, 0xFFFFFFFF) };

        CHECK(processor->getPtrToROM()->writeFrom(source, sizeof(source)) == 17);

        REQUIRE(processor->getPC().banked.bank == 0x0);
        REQUIRE(processor->getPC().banked.address == 0x00);
        CHECK_FALSE(processor->getCarry());
        CHECK_FALSE(processor->getAccumulator());
        // LDM_15
        processor->nextCommand();
        // WR1
        processor->nextCommand();
        CHECK(processor->getPtrToRAM()->readStatusNibble(BANK0, CHIP0, REG0, 1) == 0xF);
        CHECK(processor->getAccumulator() == 0xF);
        CHECK_FALSE(processor->getCarry());
        // LDM_0
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x0);
        // RD1
        processor->nextCommand();
        CHECK(processor->getPtrToRAM()->readStatusNibble(BANK0, CHIP0, REG0, 1) == 0xF);
        CHECK(processor->getAccumulator() == 0xF);
        CHECK_FALSE(processor->getCarry());
        // STC
        processor->nextCommand();
        CHECK(processor->getCarry());
        // FIM_0 0xFF
        processor->nextCommand();
        // SRC_0
        processor->nextCommand();
        // LDM_2
        processor->nextCommand();
        // WR1
        processor->nextCommand();
        CHECK(processor->getPtrToRAM()->readStatusNibble(BANK0, CHIP3, REG3, 1) == 0x2);
        CHECK(processor->getPtrToRAM()->readStatusNibble(BANK0, CHIP0, REG0, 1) == 0xF);
        CHECK(processor->getAccumulator() == 0x2);
        CHECK(processor->getCarry());
        // LDM_0
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x0);
        // RD1
        processor->nextCommand();
        CHECK(processor->getPtrToRAM()->readStatusNibble(BANK0, CHIP3, REG3, 1) == 0x2);
        CHECK(processor->getPtrToRAM()->readStatusNibble(BANK0, CHIP0, REG0, 1) == 0xF);
        CHECK(processor->getAccumulator() == 0x2);
        CHECK(processor->getCarry());
        // FIM_0 0x0F
        processor->nextCommand();
        // SRC_0
        processor->nextCommand();
        // RD1
        processor->nextCommand();
        CHECK(processor->getPtrToRAM()->readStatusNibble(BANK0, CHIP3, REG3, 1) == 0x2);
        CHECK(processor->getPtrToRAM()->readStatusNibble(BANK0, CHIP0, REG0, 1) == 0xF);
        CHECK(processor->getAccumulator() == 0xF);
        CHECK(processor->getCarry());

        CHECK(processor->getTicks() == 16);
    }
    SECTION("RD2") {
        /**
         * LDM_15       1
         * WR2          1
         * LDM_0        1
         * RD2          1
         * STC          1
         * FIM_0 0xFF   1
         * SRC_0        1
         * LDM_2        1
         * WR2          1
         * LDM_0        1
         * RD2          1
         * FIM_0 0x0F   1
         * SRC_0        1
         * RD2          1
         * NOP          1
         */

        uint8_t source[] = { LDM_15, WR2, LDM_0, RD2, STC, FIM_0, 0xFF, SRC_0, LDM_2, WR2, LDM_0, RD2, FIM_0, 0x0F, SRC_0, RD2, NOP };

        Intel4004Base *processor = { get4004Instance(0xFFFF, 0xFFFFFFFF) };

        CHECK(processor->getPtrToROM()->writeFrom(source, sizeof(source)) == 17);

        REQUIRE(processor->getPC().banked.bank == 0x0);
        REQUIRE(processor->getPC().banked.address == 0x00);
        CHECK_FALSE(processor->getCarry());
        CHECK_FALSE(processor->getAccumulator());
        // LDM_15
        processor->nextCommand();
        // WR2
        processor->nextCommand();
        CHECK(processor->getPtrToRAM()->readStatusNibble(BANK0, CHIP0, REG0, 2) == 0xF);
        CHECK(processor->getAccumulator() == 0xF);
        CHECK_FALSE(processor->getCarry());
        // LDM_0
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x0);
        // RD2
        processor->nextCommand();
        CHECK(processor->getPtrToRAM()->readStatusNibble(BANK0, CHIP0, REG0, 2) == 0xF);
        CHECK(processor->getAccumulator() == 0xF);
        CHECK_FALSE(processor->getCarry());
        // STC
        processor->nextCommand();
        CHECK(processor->getCarry());
        // FIM_0 0xFF
        processor->nextCommand();
        // SRC_0
        processor->nextCommand();
        // LDM_2
        processor->nextCommand();
        // WR2
        processor->nextCommand();
        CHECK(processor->getPtrToRAM()->readStatusNibble(BANK0, CHIP3, REG3, 2) == 0x2);
        CHECK(processor->getPtrToRAM()->readStatusNibble(BANK0, CHIP0, REG0, 2) == 0xF);
        CHECK(processor->getAccumulator() == 0x2);
        CHECK(processor->getCarry());
        // LDM_0
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x0);
        // RD2
        processor->nextCommand();
        CHECK(processor->getPtrToRAM()->readStatusNibble(BANK0, CHIP3, REG3, 2) == 0x2);
        CHECK(processor->getPtrToRAM()->readStatusNibble(BANK0, CHIP0, REG0, 2) == 0xF);
        CHECK(processor->getAccumulator() == 0x2);
        CHECK(processor->getCarry());
        // FIM_0 0x0F
        processor->nextCommand();
        // SRC_0
        processor->nextCommand();
        // RD2
        processor->nextCommand();
        CHECK(processor->getPtrToRAM()->readStatusNibble(BANK0, CHIP3, REG3, 2) == 0x2);
        CHECK(processor->getPtrToRAM()->readStatusNibble(BANK0, CHIP0, REG0, 2) == 0xF);
        CHECK(processor->getAccumulator() == 0xF);
        CHECK(processor->getCarry());

        CHECK(processor->getTicks() == 16);
    }
    SECTION("RD3") {
        /**
         * LDM_15       1
         * WR3          1
         * LDM_0        1
         * RD3          1
         * STC          1
         * FIM_0 0xFF   1
         * SRC_0        1
         * LDM_2        1
         * WR3          1
         * LDM_0        1
         * RD3          1
         * FIM_0 0x0F   1
         * SRC_0        1
         * RD3          1
         * NOP          1
         */

        uint8_t source[] = { LDM_15, WR3, LDM_0, RD3, STC, FIM_0, 0xFF, SRC_0, LDM_2, WR3, LDM_0, RD3, FIM_0, 0x0F, SRC_0, RD3, NOP };

        Intel4004Base *processor = { get4004Instance(0xFFFF, 0xFFFFFFFF) };

        CHECK(processor->getPtrToROM()->writeFrom(source, sizeof(source)) == 17);

        REQUIRE(processor->getPC().banked.bank == 0x0);
        REQUIRE(processor->getPC().banked.address == 0x00);
        CHECK_FALSE(processor->getCarry());
        CHECK_FALSE(processor->getAccumulator());
        // LDM_15
        processor->nextCommand();
        // WR3
        processor->nextCommand();
        CHECK(processor->getPtrToRAM()->readStatusNibble(BANK0, CHIP0, REG0, 3) == 0xF);
        CHECK(processor->getAccumulator() == 0xF);
        CHECK_FALSE(processor->getCarry());
        // LDM_0
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x0);
        // RD3
        processor->nextCommand();
        CHECK(processor->getPtrToRAM()->readStatusNibble(BANK0, CHIP0, REG0, 3) == 0xF);
        CHECK(processor->getAccumulator() == 0xF);
        CHECK_FALSE(processor->getCarry());
        // STC
        processor->nextCommand();
        CHECK(processor->getCarry());
        // FIM_0 0xFF
        processor->nextCommand();
        // SRC_0
        processor->nextCommand();
        // LDM_2
        processor->nextCommand();
        // WR3
        processor->nextCommand();
        CHECK(processor->getPtrToRAM()->readStatusNibble(BANK0, CHIP3, REG3, 3) == 0x2);
        CHECK(processor->getPtrToRAM()->readStatusNibble(BANK0, CHIP0, REG0, 3) == 0xF);
        CHECK(processor->getAccumulator() == 0x2);
        CHECK(processor->getCarry());
        // LDM_0
        processor->nextCommand();
        CHECK(processor->getAccumulator() == 0x0);
        // RD3
        processor->nextCommand();
        CHECK(processor->getPtrToRAM()->readStatusNibble(BANK0, CHIP3, REG3, 3) == 0x2);
        CHECK(processor->getPtrToRAM()->readStatusNibble(BANK0, CHIP0, REG0, 3) == 0xF);
        CHECK(processor->getAccumulator() == 0x2);
        CHECK(processor->getCarry());
        // FIM_0 0x0F
        processor->nextCommand();
        // SRC_0
        processor->nextCommand();
        // RD3
        processor->nextCommand();
        CHECK(processor->getPtrToRAM()->readStatusNibble(BANK0, CHIP3, REG3, 3) == 0x2);
        CHECK(processor->getPtrToRAM()->readStatusNibble(BANK0, CHIP0, REG0, 3) == 0xF);
        CHECK(processor->getAccumulator() == 0xF);
        CHECK(processor->getCarry());

        CHECK(processor->getTicks() == 16);
    }
}
#endif