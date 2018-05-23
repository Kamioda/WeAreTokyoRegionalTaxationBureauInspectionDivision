#pragma once
#include <ctime>
#include <functional>

class Calendar {
public:
	Calendar();
	Calendar(const int Year, const int Month, const int Day);
	Calendar GetAfterTwoMonthDay() const;
	Calendar GetAfterAWeekDay() const;
	Calendar operator - (const Calendar cal) const;
	time_t to_time_t() const;
	int Year, Month, Day;
};
