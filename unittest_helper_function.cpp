/*
 * unittest_helper_function.cpp
 *
 *  Created on: Jul 2, 2021
 *      Author: Thomas Staudacher
 */

#ifdef _UNITTEST_
#include <easylogging++.h>

#include <400x_GlobalDefines.h>
#include <400x_OtherDefines.h>
#include <MCS4BaseClasses.h>

#include <unittest_helper_function.h>

#include <cstdint>
#include <ctime>
#include <map>
#include <fstream>
#include <string>
using namespace std;

void InitRandomValues()
{
    /* Initialisierung das auch immer andere Zufallszahlen kommen */
    time_t t;
    srand((unsigned) time(&t));
}

bool FillProcessorWithRandomValues(Intel4004Base *processor)
{
    if (processor)
    {
        uint8_t data[1 + 1 + 2 * 16];

        CreateCodeToFillCPUWithRandomValues(data);

        processor->getPtrToROM()->writeFrom(data, sizeof(data));
        for (size_t i = 0; i < sizeof(data); ++i)
            processor->nextCommand();
        return true;
    }
    else
        return false;
}

int CreateCodeToFillCPUWithRandomValues(uint8_t *data)
{
    if (data)
    {
        uint8_t data[SizeOfCreateCodeToFillCPUWithRandomValues];

        data[0] = 0xA0 | static_cast<uint8_t>(rand() & 15);
        data[1] = rand() & 1 ? 0xF3 : 0xF1;

        for (int reg = ERegister::R0; reg <= ERegister::R15; ++reg)
        {
            data[2 + (reg * 2)] = 0x20 + reg;
            data[2 + (reg * 2) + 1] = static_cast<uint8_t>(rand() & 255);
        }
        return sizeof(data);
    }
    else
        return 0;
}

static int8_t BubbleSort8(uint8_t * const array, const int length)
{
    int count =
    { 0 }, changed;

    if (array && (length > 1))
        do
        {
            changed = 0;

            for (int i = 0; i < (length - 1); i++)
                if (*(array + i) > *(array + i + 1))
                {
                    int8_t value = *(array + i);
                    *(array + i) = *(array + i + 1);
                    *(array + i + 1) = value;

                    changed++;
                }

            count++;
        } while (changed);

    return count;
}

void FillByteArrayRandomUniqueXToY(uint8_t * const array, const int32_t length,
                                   const bool sort, const uint8_t min, const uint8_t max)
{
    bool isdouble;
    uint8_t value;

    for (int i = 0; i < length; i++)
    {
        do
        {
            isdouble = false;
            value = static_cast<uint8_t>(min + rand() % (max - min));
            for (int ii = 0; ii < i; ii++)
                if (*(array + ii) == value)
                {
                    isdouble = true;
                    break;
                }

        } while (isdouble);

        *(array + i) = value;
    }

    if (sort)
        BubbleSort8(array, length);
}

void FillByteArrayRandom(uint8_t * const array, const int32_t length,
                         const uint8_t min, const uint8_t max)
{
    for (int i = 0; i < length; i++)
    {
        *(array + i) = static_cast<uint8_t>(min + rand() % ((max - min)+1));
    }
}
//*****************************************************************************
TStatistic::TStatistic() :
    good(0), bad(0)
{
}

TStatistic::TStatistic(const int good, const int bad) :
    good(good), bad(bad)
{
}

TStatistic::TStatistic(const TStatistic& other) :
    good(other.good), bad(other.bad)
{
}

int TStatistic::totalNumberTestcases() const
{
    return good + bad;
}

ostream& operator<<(ostream& os, const TStatistic& value)
{
    os << "Total:" << value.totalNumberTestcases() << ", Good:" << value.good
       << ", Bad:" << value.bad;

    return os;
}
//*****************************************************************************
CPoints *CPoints::getHandle()
{
    if (handle)
        return handle;
    else
    {
        handle = new CPoints;
        testcases = new map<string, TStatistic>;
        return handle;
    }
}

void CPoints::DestroyAllData()
{
    delete handle, handle = nullptr;
    delete testcases, testcases = nullptr;
}

void CPoints::reset()
{
    if (testcases)
        testcases->clear();
}

bool CPoints::testCase(const string& testname, const bool value,
                       const int multiplier)
{
    const map<string, TStatistic>::iterator it = testcases->find(testname);

    if (it == testcases->end())
    {
        (*testcases)[testname] =
            value ? TStatistic(multiplier) : TStatistic(0, multiplier);
    }
    else
    {
        if (value)
            (*testcases)[testname].good += multiplier;
        else
            (*testcases)[testname].bad += multiplier;
    }

    return value;
}

TStatistic CPoints::getOverallStatistic() const
{
    TStatistic ret;

    for (map<string, TStatistic>::iterator it = testcases->begin();
            it != testcases->end(); ++it)
    {
        TStatistic element = it->second;
        //LOG(DEBUG)<< "Testcase (" << it->first << "):" << it->second;

        ret.good += element.good;
        ret.bad += element.bad;
    }

    return ret;
}

int CPoints::getPoinstRelatedToTestCases(const int maxpoints) const
{
    auto s = getOverallStatistic();

    if (s.totalNumberTestcases())
        return static_cast<int>(.5f
                                + static_cast<float>(maxpoints) * static_cast<float>(s.good)
                                / static_cast<float>(s.totalNumberTestcases()));
    else
    {
        LOG(ERROR)<< "Kein einziger Unittest ausgefuehrt";
        return maxpoints;
    }
}

void CPoints::toFile() const
{
    const int COUNT = countGroupMebers();

    if(COUNT) {
        const TStudent *MEMBERS = getGroupMebers();

        if(MEMBERS) for(int i = 0; i < COUNT; ++i) {

                {
                    //Variante RESULT-Datei
                    string path = MEMBERS[i].name + '.' + MEMBERS[i].surname + ".result";
                    ofstream f(path);

                    if (f.is_open())
                    {
                        for (map<string, TStatistic>::iterator it = testcases->begin();
                                it != testcases->end(); ++it)
                        {
                            //Exemplarisch fuer besser Aufbereitung
                            f << it->first << ';' << it->second.totalNumberTestcases() << ';'
                              << it->second.good << ';' << it->second.bad << '\n';
                        }

                        f.flush();
                        f.close();
                    }
                    else
                        LOG(ERROR) << "Unable to open file " << path;
                }

                {
                    //Variante XML Schnipsel
                    TStudent const * const student = &MEMBERS[i];

                    string path = student->name + '.' + student->surname + ".xml";
                    ofstream f(path);

                    if (f.is_open())
                    {
                        {
                            //TAG schreiben
                            f << "<student name=\"" << student->name << "\" surname=\"" << student->surname << "\" mail=\"" << student->mail << "\" ";
                            switch(student->course) {
                            case ECourse::TIT20:
                                f << "course=\"TIT20\"";
                                break;
                            case ECourse::TIM20:
                                f << "course=\"TIM20\"";
                                break;
                            case ECourse::TIS20:
                                f << "course=\"TIS20\"";
                                break;
                            default:
                                LOG(ERROR) << "Unknown course " << static_cast<int>(student->course) << " for Student " << student->mail;
                            }
                            f << " listedingroup=\"" << student->listedingroup << "\" ";
                            switch(student->implementationrange) {
                            case EImplementationRange::IMPLEMENT_FULL:
                                f << "implementationrange=\"IMPLEMENT_FULL\"";
                                break;
                            case EImplementationRange::IMPLEMENT_RAM_ONLY:
                                f << "implementationrange=\"IMPLEMENT_RAM_ONLY\"";
                                break;
                            case EImplementationRange::IMPLEMENT_WITHOUT_RAM:
                                f << "implementationrange=\"IMPLEMENT_WITHOUT_RAM\"";
                                break;
                            default:
                                LOG(ERROR) << "Unknown group " << static_cast<int>(student->implementationrange) << " for Student " << student->mail;
                            }
                            f << " pythonpoints=\"" << student->pythonpoints << "\" exmatriculate=\"" << (student->exmatriculate ? "true" : "false") << "\">" << endl;
                        }

                        for (map<string, TStatistic>::iterator it = testcases->begin();
                                it != testcases->end(); ++it)
                        {
                            f << "<test name=\"" << it->first << "\" maxpoints=\"" << it->second.totalNumberTestcases() << "\" good=\"" << it->second.good << "\" bad=\"" << it->second.bad << "\"/>" << endl;
                        }

                        {
                            //Endtag
                            f << "</student>" << endl;
                        }

                        f.flush();
                        f.close();
                    }
                    else
                        LOG(ERROR) << "Unable to open file " << path;
                }
            }
        else LOG(ERROR) << "Groupmembers are Zero";
    }
    else LOG(ERROR) << "Groupsize is Zero";
}

CPoints::CPoints()
{
}

CPoints *CPoints::handle = nullptr;

map<string, TStatistic> *CPoints::testcases = nullptr;

#endif
