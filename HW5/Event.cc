#include "Event.h"
#include "translate.h"  
#include <iostream>
#include <iomanip>
using namespace std;


Event::Event(string date){
	vector<int> my_dates;
	try{
		my_dates =  formatType(date);
	}
	catch(runtime_error &e){
                throw;
        }
	if(my_dates.size() == 1){
		vector<int> setDates = doMKtimeString(my_dates);	
		eYear = setDates[0];
                eMonth = setDates[1];
                eDay = setDates[2];
	}
	else if(my_dates.size() == 2){
		boundsCheck(my_dates, 1);
		vector<int> setDates = doMKtime(my_dates);
		eYear = setDates[0];
                eMonth = setDates[1];
                eDay = setDates[2];
	}
	else if(my_dates.size() == 3){
		boundsCheck(my_dates,2);
		eYear = my_dates[0];
                eMonth = my_dates[1];
                eDay = my_dates[2];
	}
	else{
	//Throw runtime error;
	}
}
Event::Event(const Event &rhs):
	eYear(rhs.eYear), eMonth(rhs.eMonth), eDay(rhs.eDay) 
{}
Event &Event::operator=(const Event &rhs){
	eYear = rhs.eYear;
	eMonth = rhs.eMonth;
	eDay = rhs.eDay;
	return *this;	
}
void Event::set(const int year, const int month, const int day){
	vector<int> bounds = {year, month, day};
	try{
		boundsCheck(bounds, 2);
	}
	catch(runtime_error &e){
                throw;
        }
	this->eYear = year;
        this->eMonth = month;
        this->eDay = day;
}
int Event::year() const{
	return this->eYear;
}
int Event::month() const{
	return this->eMonth;
}
int Event::day() const{
	return this->eDay;
}
vector<string> leading_zeros(int year, int day, int month){
 	string st_year = to_string(year);
        string st_day = to_string(day);
        string st_month = to_string(month);
	if(year < 10){
                string zero = "000";
                st_year.insert(0, zero);
        }
        else if(year < 100){
                string zero = "00";
                st_year.insert(0, zero);
        }
        else if(year < 1000){
                string zero = "0";
                st_year.insert(0, zero);
        }
        if(day < 10){
                string zero = "0";
                st_day.insert(0,zero);
        }
	if(month < 10){
		string zero = "0";
                st_month.insert(0,zero);
        }
        vector<string> ret_array;
        ret_array.push_back(st_year);
	ret_array.push_back(st_month);
        ret_array.push_back(st_day);
        return ret_array;
}
ostream &operator<<(ostream &stream, const Event &eve) {
        vector<string> output = leading_zeros(eve.year(), eve.day(), eve.month());
	return stream << output[0] << '-' << output[1] << '-' << output[2];
}
