/*
 * 400x_OtherDefines.h
 *
 *  Created on: Jul 2, 2021
 *      Author: Thomas Staudacher
 */

#ifndef INCLUDE_400X_OTHERDEFINES_H_
#define INCLUDE_400X_OTHERDEFINES_H_

#include <iostream>
#include <cstring>

using namespace std;

enum EGlobalConstants
{
    CYCLES_PER_INSTRUCTION = 8
};

class CDataDisplayHelper
{
public:
    CDataDisplayHelper(uint8_t *data, int length) :
        _data(nullptr), _length(length)
    {
        if (length > 0)
        {
            _data = new uint8_t[length];
            memcpy(_data, data, length);
        }
    }

    ~CDataDisplayHelper()
    {
        delete[] _data;
    }

    int getLength() const
    {
        return _length;
    }
    uint8_t at(int pos) const
    {
        return (pos < _length) ? _data[pos] : 0;
    }
private:
    uint8_t *_data;
    int _length;
};
/*
ostream& operator<<(ostream& os, const CDataDisplayHelper& data)
{
	const int length =
	{ data.getLength() };
	if (length < 1)
		os << "-- EMPTY --";
	else
	{
		const ios_base::fmtflags flags =
		{ os.flags() };
		os << hex;
		for (int i = 0; i < length; ++i)
			os << static_cast<int>(data.at(i)) << ' ';
		os.flags(flags);
	}
	return os;
}

ostream& formatByteDataToStream(ostream& os, const uint8_t * const data, const int length)
{
	if ((data == nullptr)||(length < 1))
		os << "-- EMPTY --";
	else
	{
		const ios_base::fmtflags flags =
		{ os.flags() };
		os << hex;
		for (int i = 0; i < length; ++i)
			os << static_cast<int>(data[i]) << ' ';
		os.flags(flags);
	}
	return os;
}
*/

#endif /* INCLUDE_400X_OTHERDEFINES_H_ */
