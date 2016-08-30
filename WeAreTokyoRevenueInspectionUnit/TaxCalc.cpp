#include <chrono>
using day = std::chrono::duration<int, std::ratio_multiply<std::chrono::hours::period, std::ratio<24>>::type>;


class AdditionalTaxCalc {
private:
	/*long over_day, back_tax; // ’´‰ß“ú”‚Æ’Ç’¥‰ÛÅ
	bool within_time_limit; // ŠúŒÀ“à\‚©‚Ç‚¤‚©*/
	day limit, paid;
	long back_tax;
	long delinquent_tax(); // ‰„‘ØÅ
	// ‰ÁZÅ
	long under_reporting_additional_tax(); //@‰ß­\‰ÁZÅ
	long undeclared_additional_tax(); // –³\‰ÁZÅ
	long non_payment_additional_tax(); // •s”[•t‰ÁZÅ
	long heavy_additional_tax(); // d‰ÁZÅ
public:
	AdditionalTaxCalc(day limit, day paid, long back_tax);
	long calc();
};

AdditionalTaxCalc::AdditionalTaxCalc(day limit, day paid, long back_tax)
	: limit(limit), paid(paid), back_tax(back_tax) {}

long AdditionalTaxCalc::under_reporting_additional_tax() {

}
