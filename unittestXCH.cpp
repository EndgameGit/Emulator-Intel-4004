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

enum CPUCommands
    : uint8_t
{
    FIM = 0x20,
    XCH = 0xB0,
    LDM = 0xD0,
    CLC = 0xF1,
    CMC = 0xF3,
    TCC = 0xF7,
    TCS = 0xF9,
    STC = 0xFA
};

TEST_CASE("UnitTest_Intel4004_Mnemonics") {
    SECTION("XCH") {
        unique_ptr<Intel4004Base> processor (get4004Instance());

        //bool nofault = true;

        for(int reg = 0; reg < 16; ++reg)
        {
            const uint4_t a = static_cast<uint4_t>(rand() % (16)), r = static_cast<uint4_t>(rand() % (16));

            uint8_t source[] =
            {
                static_cast<uint8_t>(CPUCommands::LDM | a),
                static_cast<uint8_t>(CPUCommands::FIM | static_cast<uint4_t>(reg & 0b1110)),
                static_cast<uint8_t>(reg&1?r:r<<4),
                static_cast<uint8_t>(CPUCommands::XCH | reg)
            };

            processor->reset();

            CHECK(processor->getPtrToROM()->writeFrom(source, sizeof(source)) == 4);

            processor->nextCommand();
            processor->nextCommand();
            processor->nextCommand();
            CHECK(processor->getAccumulator() == r);
            CHECK(processor->getRegister(static_cast<const ERegister>(reg)) == a);

            //if((processor->getAccumulator() != r) || (processor->getRegister(static_cast<const ERegister>(reg)) != a))
                //nofault = false;
        }

        //CPoints::getHandle()->testCase("XCH",nofault);
    
    }
}
#endif