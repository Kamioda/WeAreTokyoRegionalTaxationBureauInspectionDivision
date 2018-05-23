#pragma once
#include "Number.hpp"
#include <tchar.h>

class Tax {
private:
	standard::number<unsigned int> LessThanTenThousand;
	standard::number<unsigned int> TenThousand;
	standard::number<unsigned int> OneHundredMillion;
public:
	Tax() = default;
	Tax(const unsigned long TaxNum);
	std::string to_astring() const;
	std::wstring to_wstring() const;
	std::basic_string<TCHAR> to_string() {
#ifdef UNICODE
		return this->to_wstring();
#else
		return this->to_astring();
#endif
	}
};
