#include "translate.h"
#include <iostream>
#include <cstring>
#include <algorithm>
#include <sstream>
using namespace std;


vector<int> formatType(string date){
vector<int> return_data;
try{    
	vector<string> check_for_periods;
	vector<string> check_for_hyphens;
	try{
		check_for_periods = split(date,'.');
	}
	catch(runtime_error &e){
		throw;
	}
	try{
		check_for_hyphens = split(date,'-');
	}
	catch(runtime_error &e){
                throw;
        }
	if(check_for_periods.size() == 2){
		date_periods(date, return_data);
	}
	else if(check_for_hyphens.size() == 3){
		date_hyphens(date, return_data);
	}
	else if(check_for_periods.size() > 2){
		string error = "Invalid date provided, too many periods- " + date;
		throw runtime_error(error);
	}
        else if(check_for_hyphens.size() > 3){
		string error = "Invalid date provided, too many hypens- " + date;
                throw runtime_error(error);
	}
	else{
		try{
        		check_string(date, return_data);
		}
        	catch(runtime_error &e){
                	throw;
        	}
	}
}
 catch(runtime_error &e){
                throw;
        }
	return return_data;
}
vector<string> split(string date, char delim){
        vector<string> temp_array;
try{       
stringstream stringstream(date);
        string tempstring;
        unsigned int check_size = 0;
        while(getline(stringstream,tempstring,delim)){
	        check_size += tempstring.size();
	        temp_array.push_back(tempstring);
        }
	if(delim == '-'){
		check_size += 1;
	}
	check_size += 1;
	if( (check_size != date.size() ) && ( (delim == '.')||(delim == '-') ) ){
		if(temp_array.size() > 1){
			string error = "Invalid date provided- " + date;
                	throw runtime_error(error);
		}
        }

}
 catch(runtime_error &e){
                throw;
        }
        return temp_array;
}	
void date_periods(string date, vector<int> &return_data){
try{
	try{
                check_nonnumbers(date,'.');
        }
        catch(runtime_error &e){
                throw;
        }
	vector<string> numbers;
	try{
		numbers = split(date,'.');
	}
	catch(runtime_error &e){
		throw;
	}
	return_data.push_back(string_to_int(numbers[0]));
	return_data.push_back(string_to_int(numbers[1]));
}
 catch(runtime_error &e){
                throw;
        }
}
void date_hyphens(string date, vector<int> &return_data){
try{	
	try{
		check_nonnumbers(date,'-');    
        }
        catch(runtime_error &e){
                throw;
        }
	vector<string> numbers;
	try{
        	numbers = split(date,'-');
	}
        catch(runtime_error &e){
                throw;
        }
	return_data.push_back(string_to_int(numbers[0]));
        return_data.push_back(string_to_int(numbers[1]));
	return_data.push_back(string_to_int(numbers[2]));
}
 catch(runtime_error &e){
                throw;
        }
}
void check_string(string date, vector<int> &return_data){
try{
	string old_date = date; 
	transform(date.begin(),date.end(),date.begin(),::toupper);
	const char today[] = "TODAY";
	const char tomorrow[] = "TOMORROW";
	const char yesterday[] = "YESTERDAY";
	const char * prov_string = date.c_str();
	if( !(strcmp(prov_string, today) ) ){
		return_data.push_back(1);
	}
	else if( !(strcmp(prov_string, tomorrow) ) ){
		return_data.push_back(2);
	}
	else if( !(strcmp(prov_string, yesterday) ) ){
		return_data.push_back(3);
	}
	else{
		string error = "Invalid date provided- perhaps you spelled today, yesterday or tomorrow incorrectly? -" + date;
                throw runtime_error(error);
	}
}
 catch(runtime_error &e){
                throw;
        }
}

void check_nonnumbers(string date, char delim){
try{
        vector<string> check_for_spaces;
 	try{
                check_for_spaces = split(date,' ');
        }
        catch(runtime_error &e){
                throw;
        }	
        if(check_for_spaces.size() != 1){
		string error = "Invalid date provided, a space was detected- " + date;
                throw runtime_error(error);
	}
        // Loop through string and check each char
        for(unsigned i = 0; i < date.size(); i++){
                if(((date[i] < '0') || (date[i] > '9')) && (date[i] != delim)){
			string error = "Invalid date provided, both numbers and chars included- " + date;
                	throw runtime_error(error);
		}
        }
        check_for_spaces.clear();
}
 catch(runtime_error &e){
                throw;
        }
}
int string_to_int(string string_int){
        int int_string = 0;
try{
	size_t anystring;
        try{
                int_string = stoi(string_int, &anystring);
        }
        catch(const invalid_argument &error){
		string error2 = "Invalid datum processed- " + string_int;
                throw runtime_error(error2);
	}
        catch(const out_of_range & error){
		string error2 = "Invalid datum processed- " + string_int;
                throw runtime_error(error2);
	}
}
catch(runtime_error &e){
                throw;
        }
        return int_string;

}
void boundsCheck(vector<int> &dates, int check){
try{
	if(check == 1){
		check_leapyear(dates[0], dates[1]);
		if((dates[0] > 9999) || dates[0] <= 0){
			string error = "Provided date is out of range- " + dates[0] + '.' + dates[1];
                	throw runtime_error(error);
		}
		else if((dates[1] <= 0) || (dates[1] >= 367)){
			string error = "Provided date is out of range- " + dates[0] + '.' + dates[1];
                        throw runtime_error(error);
		}
	}
	else if(check == 2){
		if((dates[0] > 9999) || dates[0] <= 0){
			string error = "Provided date is out of range- " + dates[0] + '-' + dates[1] + '-' + dates[2];
                        throw runtime_error(error);
		}
		if((dates[1] > 12) || (dates[1] <= 0)){
			string error = "Provided date is out of range- " + dates[0] + '-' + dates[1] + '-' + dates[2];
                        throw runtime_error(error);
		}
		switch(dates[1]){
			case 1:
			case 3:
			case 5:
			case 7:
			case 8:
			case 10:
			case 12: 
				if(dates[2] > 31){
					string error = "Provided date is out of range- " + dates[0] + '-' + dates[1] + '-' + dates[2];
                       	 		throw runtime_error(error);
				}
				break;
			case 4:
			case 6:
			case 9:
			case 11:
				if(dates[2] > 30){
					string error = "Provided date is out of range- " + dates[0] + '-' + dates[1] + '-' + dates[2];
                                        throw runtime_error(error);
				}
				break;
			default:
				if(check_leapyear(dates[0],5)){
					if(dates[2] > 29){
						string error = "Provided date is out of range- " + dates[0] + '-' + dates[1] + '-' + dates[2];
                                        	throw runtime_error(error);
					}
				}
				else{
					if(dates[2] > 28){
						string error = "Provided date is out of range- " + dates[0] + '-' + dates[1] + '-' + dates[2];
                                        	throw runtime_error(error);
					}
				}
				break;
		}			
			
	}

}
catch(runtime_error &e){
                throw;
        }
}

bool check_leapyear(int year, int day){
        bool isleap = false;
try{        
	if((year % 4 == 0)){
                isleap = true;
                if((year % 100 == 0)){
                        isleap = false;
                        if((year % 400 == 0)){
                                return isleap;
                        }
                }
        }
        // Another check of bounds needs to be done after finding out whether or not the year is a leapyear
        if(!isleap){
                if(day >= 366){
			string error = "Given year is not a leap year yet more than 365 days were provided- " + year + '.' + day;
                        throw runtime_error(error);
		}
        }
}
catch(runtime_error &e){
                throw;
        }
        return isleap;
}
vector<int> doMKtimeString(vector<int> &dates){
	vector<int> returnInts;
	time_t rawtime;
  	struct tm * my_time;
	time(&rawtime);
  	my_time = localtime(&rawtime);
	if(dates[0] == 2){
		int day = my_time->tm_mday;
		my_time->tm_mday = day+1;
	}
	else if(dates[0] == 3){
		int day = my_time->tm_mday;
                my_time->tm_mday = day-1;
	}
	mktime(my_time); 
	returnInts.push_back(2020);
	returnInts.push_back((my_time->tm_mon) + 1);
	returnInts.push_back(my_time->tm_mday);
	return returnInts;
}
vector<int> doMKtime(vector<int> &dates){
	vector<int> returnInts;
	struct tm my_time;
        my_time.tm_sec = 0;
        my_time.tm_min = 0;
        my_time.tm_hour = 0;
        my_time.tm_mday = dates[1];
        my_time.tm_mon = 0;
        my_time.tm_year = dates[0] - 1900;
        my_time.tm_wday = 0;
        my_time.tm_yday = 0;
        my_time.tm_isdst = 0;
        mktime(&my_time);
	returnInts.push_back(dates[0]);
	returnInts.push_back((my_time.tm_mon) + 1);
        returnInts.push_back(my_time.tm_mday);
        return returnInts;
}
