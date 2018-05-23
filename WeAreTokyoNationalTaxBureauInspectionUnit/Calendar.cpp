#include "Calendar.hpp"
#include <string>
#include <array>
#include <chrono>

Calendar::Calendar() {
	tm current;
	const time_t currenttime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	if (localtime_s(&current, &currenttime)) throw std::runtime_error("Failed to get current time");
	this->Year = current.tm_year + 1900;
	this->Month = current.tm_mon + 1;
	this->Day = current.tm_mday;
}

Calendar::Calendar(const int Year, const int Month, const int Day)
	: Year(Year), Month(Month), Day(Day) {}

static inline bool IsLeapYear(const int Year) {
	if (Year % 4 != 0) return false;
	if (Year % 100 != 0) return true;
	return Year % 400 == 0;
}

Calendar Calendar::GetAfterTwoMonthDay() const {
	if (this->Month == 12) {
		if (!IsLeapYear(this->Year + 1)) return this->Day >= 28 ? Calendar(this->Year + 1, 2, 28) : Calendar(this->Year + 1, 2, this->Day);
		else return this->Day >= 29 ? Calendar(this->Year + 1, 2, 29) : Calendar(this->Year + 1, 2, this->Day);
	}
	else if (this->Month == 11) return Calendar(this->Year + 1, 1, this->Day);
	else if (this->Month == 7 && this->Day == 31) return Calendar(this->Year, 9, 30);
	else return Calendar(this->Year, this->Month + 2, this->Day);
}

static inline bool IsNo31Month(const int Month) {
	static const std::array<int, 5> No31Month = { 2, 4, 6, 9, 11 };
	return std::any_of(No31Month.begin(), No31Month.end(), [Month](const int i) { return Month == i; });
}

Calendar Calendar::GetAfterAWeekDay() const {
	auto AfterAWeekDate = [this](const int AbleToSimpleAddBorderDay) { 
		return this->Day <= AbleToSimpleAddBorderDay ? Calendar(this->Year, this->Month, this->Day + 7) : Calendar(this->Year, Month + 1, this->Day - AbleToSimpleAddBorderDay);
	};
	if (this->Month == 12 && this->Day > 24) return Calendar(this->Year + 1, 1, this->Day - 24);
	else if (!IsNo31Month(this->Month)) return AfterAWeekDate(24);
	else if (this->Month != 2) return AfterAWeekDate(23);
	else return AfterAWeekDate((IsLeapYear(this->Year) ? 22 : 21));
}

time_t Calendar::to_time_t() const {
	tm timeinfo{};
	timeinfo.tm_year = this->Year - 1900;
	timeinfo.tm_mon = this->Month - 1;
	timeinfo.tm_mday = this->Day;
	return mktime(&timeinfo);
}

Calendar Calendar::operator - (const Calendar cal) const {
	if (this->Year < cal.Year || (this->Year == cal.Year && this->Month < cal.Month) || (this->Year == cal.Year && this->Month == cal.Month && this->Day < cal.Year))
		throw std::invalid_argument("cal is wrong.");
	Calendar temp = *this;
	temp.Day -= cal.Day;
	if (temp.Day <= 0) {
		if (IsNo31Month(temp.Month)) temp.Day += 31;
		else if (temp.Month != 3) temp.Day += 30;
		else temp.Day += (IsLeapYear(this->Year) ? 29 : 28); // ３月からの引き算だとその前が閏年かどうかでDayに加算する値が変わってくる
		temp.Month -= 1;
	}
	temp.Month -= cal.Month;
	while (temp.Month <= 0) { // 最大２ループ
		temp.Month += 12;
		temp.Year -= 1;
	}
	temp.Year -= cal.Year;
	return temp;
}
