//Beispiel für eine Applikation die mit Logging und Unittest arbeitet
//Logging und Unittest sind optional
//Ein Beispiel für eine Logging.ini ist auch hochgeladen

#include <400x_GlobalDefines.h>
#include <easylogging++.h>
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
	SECTION("Command_CLB") {

		/* Source
		 * ldm 0
		 * dac
		 * clb
		 * nop
		 */

		uint8_t source[] = { 0xD0, 0xF8, 0xF0, 0x00 };

		Intel4004Base *processor = { get4004Instance(0xFFFF, 0xFFFFFFFF) };

		CHECK(processor->getPtrToROM()->writeFrom(source, sizeof(source)) == 4);

		CHECK_FALSE(processor->getCarry());
		CHECK_FALSE(processor->getAccumulator());
		processor->nextCommand();
		CHECK_FALSE(processor->getCarry());
		CHECK_FALSE(processor->getAccumulator());
		processor->nextCommand();
		CHECK(processor->getCarry());
		CHECK(processor->getAccumulator() == 15);
		processor->nextCommand();
		CHECK_FALSE(processor->getCarry());
		CHECK_FALSE(processor->getAccumulator());
		CHECK((Intel4004::CYCLES_PER_INSTRUCTION * 3) == processor->getTicks());

		delete processor;
	}

	SECTION("CMC") {

		/* Source
		 * clc
		 * cmc
		 * nop
		 */

		uint8_t source[] = { 0xF1, 0xF3, 0x00 };

		Intel4004Base *processor = { get4004Instance(0xFFFF, 0xFFFFFFFF) };

		CHECK(processor->getPtrToROM()->writeFrom(source, sizeof(source)) == 3);

		CHECK_FALSE(processor->getCarry());
		processor->nextCommand();
		CHECK_FALSE(processor->getCarry());
		processor->nextCommand();
		CHECK(processor->getCarry());
		CHECK((Intel4004::CYCLES_PER_INSTRUCTION * 2) == processor->getTicks());

		delete processor;
	}
}
