#include "Tax.hpp"

static inline standard::number<unsigned int> PickupLastFourDigits(standard::number<unsigned long> &temp) {
	standard::number<unsigned int> num(static_cast<unsigned int>(temp.Get() % 10000), 1000, 0);
	temp -= num;
	temp /= 1000;
	return num;
}

Tax::Tax(const unsigned long Tax) {
	standard::number<unsigned long> temp(Tax, 3000000000, 50000000);
	this->LessThanTenThousand = PickupLastFourDigits(temp);
	this->TenThousand = PickupLastFourDigits(temp);
	this->OneHundredMillion = PickupLastFourDigits(temp);
}

std::string Tax::to_astring() const {
	return std::to_string(this->OneHundredMillion.Get()) + "‰­"
		+ std::to_string(this->TenThousand.Get()) + "–œ"
		+ std::to_string(this->LessThanTenThousand.Get()) + "‰~";
}

std::wstring Tax::to_wstring() const {
	return std::to_wstring(this->OneHundredMillion.Get()) + L"‰­"
		+ std::to_wstring(this->TenThousand.Get()) + L"–œ"
		+ std::to_wstring(this->LessThanTenThousand.Get()) + L"‰~";
}
