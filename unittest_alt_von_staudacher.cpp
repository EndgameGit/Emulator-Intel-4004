#include <400x_GlobalDefines.h>
#include <easylogging++.h>
#include <Get4004.h>
INITIALIZE_EASYLOGGINGPP

#define CATCH_CONFIG_FAST_COMPILE	//Beschleunigte Compilierung
#define CATCH_CONFIG_RUNNER

#include <catch.hpp>				//Sourcen von Catch2

void setUp() {
	//Logging einschalten
	el::Configurations conf("logging.ini");
	el::Loggers::reconfigureAllLoggers(conf);

	LOG(INFO) << "Unittest MCS4 System gestartet";
}

void tearDown() {
	LOG(INFO) << "Unittest MCS4 System beendet";
	cout << "Logging beendet" << endl;
}

int main( int argc, char* argv[] ) {
  // global setup...
  setUp();

  int result = Catch::Session().run( argc, argv );

  // global clean-up...
  tearDown();
  return result;
}

TEST_CASE("SimpleTest") {
    SECTION("Command_ADD") {
        /*  FIM R0R1,15	;15
            FIM R2R3,101	;101
            FIM R4R5,$00	;Ergebnis
  
            CLC			    ;Loesche Carry
  
            LD R1			;Register R1 in Akku
            ADD R3			;Addiere Summe R1/R3 + Carry
            XCH R5			;Ergebnis in Register R5 (Low)
		 */

		uint8_t source[] = { 0x20, 0x0F, 0x22, 0x65, 0x24, 0xF1, 0xA1, 0x83, 0xB5 };

		Intel4004Base *processor = { get4004Instance(0xFFFF, 0xFFFFFFFF) };

		CHECK(processor->getPtrToROM()->writeFrom(source, sizeof(source)) == 9);
        CHECK_FALSE(processor->getCarry());
        CHECK_FALSE(processor->getAccumulator());
        processor->nextCommand();

        for(int i=0; i<15;i++){
            processor->setRegister(i,7);
            processor->setRegister(i+1,3);
            processor->nextCommand(0xA1);
            CHECK(processor->getCarry());
        }

    }