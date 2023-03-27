/*
 * unittest_helper_function.h
 *
 *  Created on: Jul 2, 2021
 *      Author: Thomas Staudacher
 */

#ifndef INCLUDE_UNITTEST_HELPER_FUNCTION_H_
#define INCLUDE_UNITTEST_HELPER_FUNCTION_H_
#ifdef _UNITTEST_
#include <400x_GlobalDefines.h>
#include <400x_OtherDefines.h>
#include <MCS4BaseClasses.h>

#include <map>
#include <string>
#include <cstdarg>
using namespace std;

enum
{
    SizeOfCreateCodeToFillCPUWithRandomValues = 1 + 1 + 2 * 16
};

extern void InitRandomValues();
extern bool FillProcessorWithRandomValues(Intel4004Base *processor);
extern int CreateCodeToFillCPUWithRandomValues(uint8_t *data);
extern void FillByteArrayRandomUniqueXToY(uint8_t * const array, const int32_t length, const bool sort = false, const uint8_t min = 0, const uint8_t max = 255);
extern void FillByteArrayRandom(uint8_t * const array, const int32_t length, const uint8_t min = 0, const uint8_t max = 255);

union UCpuValue
{
    UCpuValue(const uint8_t init = 0) :
        raw(init)
    {
    }

    UCpuValue(const uint4_t accu, bool carry) :
        raw(accu | (carry ? 0b10000 : 0))
    {
    }

    UCpuValue(const UCpuValue& other) :
        raw(other.raw)
    {
    }

    uint8_t raw;
    struct
    {
        uint8_t accu :4;
        uint8_t carry :1;
        uint8_t :3;
    } cpu;
};

struct TStatistic
{
    TStatistic();
    TStatistic(const int good, const int bad = 0);
    TStatistic(const TStatistic& other);

    int good;
    int bad;

    int totalNumberTestcases() const;
};

ostream& operator<<(ostream& os, const TStatistic& value);

class CPoints
{
public:
    static CPoints *getHandle();
    static void DestroyAllData();
    void reset();
    bool testCase(const string& testname, const bool value = false, const int multiplier = 1);
    TStatistic getOverallStatistic() const;
    int getPoinstRelatedToTestCases(const int maxpoints) const;
    void toFile() const;
private:
    CPoints();
    static CPoints *handle;
    static map<string, TStatistic> *testcases;
};

typedef enum {TIT20,TIM20,TIS20} ECourse;

typedef enum {IMPLEMENT_FULL,IMPLEMENT_WITHOUT_RAM,IMPLEMENT_RAM_ONLY} EImplementationRange;

struct TStudent {
    string name;
    string surname;
    string mail;
    ECourse course;
    string listedingroup;
    EImplementationRange implementationrange;
    int pythonpoints;
    bool exmatriculate;
};

extern int countGroupMebers();
extern const TStudent *getGroupMebers();

#endif
#endif /* INCLUDE_UNITTEST_HELPER_FUNCTION_H_ */
