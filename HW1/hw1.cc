#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <ctime>
#include <cstdlib>
using namespace std;
vector<string> split(string date, char delim);
vector<int> check_bounds(vector<string> dates);
void is_blank(string x);
void check_nonnumbers(string date);
void check_arguments(vector<string> array);
void date_output(int year, int day, bool is_leap, string error_string);
bool check_leapyear(int year, int day, string error_string);
vector<int> get_month(int day, bool is_leap);
int get_day_of_week(int d, int y);
vector<string> leading_zeros(int year, int day);
void check_period(string date);
string program_name;
int main(int, char *argv[]){
	// Create Global Variable of Program Name for error output
	program_name = argv[0];
	// Variable to store the original string passed in through standard input
	string date;
	// While loop will continue to run untill there are no more lines or there is an error
	while(getline(cin,date)){
		// If input is a blank line output error
		is_blank(date);
		// Will check string char by char for anything other than a numerical value or period
		check_nonnumbers(date);
		// Had bug where input of just a period was deemed valid, this function checks if the input is a period and nothing else
		check_period(date);
		// Splits input by the delimeter of a period and outputs values into a vector of strings
		vector<string> dates_output = split(date, '.');
		//Checks if use gave more than one arguments i.e 2020.10.2020.1
		check_arguments(dates_output);
		// Converts the strings to an int and verifies the ints are within the bounds given and then returns a vector of int
		vector<int> output = check_bounds(dates_output);
		// Creates boolean true if the given year is a leap year and false otherwise, very important for figuring out the dates
		bool is_leap = check_leapyear(output[0],output[1], date);
		// Give the program the two int values and whether or not its a leap year and it will print accordingly
		date_output(output[0],output[1],is_leap, date);	
	        dates_output.clear();
		output.clear();
	}
	return 0;
}
void is_blank(string x){
	if(x.empty()){
		cerr << program_name <<" - Error: Line is Empty\n";
		exit(1);
	}
	else{
		return;
	}
}
void check_period(string date){
	if(date.size() == 1){
		if(date[0] == '.'){
			cerr << program_name <<" - Error: Inavlid Argument- " << date << '\n';
			exit(1);
		}
	}
	return;
}
void check_nonnumbers(string date){
	// First check if the input has spaces
	vector<string> check_for_spaces = split(date,' ');
	if(check_for_spaces.size() != 1){
		cerr  << program_name <<" - Error: Line has spaces in it- " << date <<"\n";
                exit(1);
        }
	// Loop through string and check each char
	for(unsigned i = 0; i < date.size(); i++){
		if(((date[i] < '0') || (date[i] > '9')) && (date[i] != '.')){
			cerr << program_name <<" - Error: Line has non numbers- " << date << "\n";
			exit(1);
		}
	}
	check_for_spaces.clear();
	return;

}
void check_arguments(vector<string> array){
	if(array.size()!= 2){
                cerr << program_name <<" - Error: Improper number of arguments- ";
		// I need to output the incorrect line without knowing how many arguments it has, hence the for loop
		if(array.size() == 1){
			cerr << array[0] << ".\n";
		}
		else{
			cout << "You should never reach here, but if there is a bug let me know\n";
		}
		exit(1);
        }
	return;
}
bool check_leapyear(int year, int day, string error_string){
	bool isleap = false;
	if((year % 4 == 0)){
		isleap = true;
		if((year % 100 == 0)){
			isleap = false;
			if((year % 400 == 0)){
				isleap = true;
			}
		}
	}
	// Another check of bounds needs to be done after finding out whether or not the year is a leapyear
	if(!isleap){
		if(day >= 366){
			cerr << program_name <<" - Error: The year provided is not a leap year yet you provided more than 365 days- " << error_string << "\n";
			exit(1);
		}
	}
	return isleap;
}
vector<string> split(string date, char delim){
	// Array will hold the delimited strings
	vector<string> temp_array;
	// Stringstream allows me to treat the string as standard input
	stringstream stringstream(date);
	// Tempstring is only used to hold the delimited string and push to the vector array
	string tempstring;
	// Important variable for another error checked explained below
	unsigned int check_size = 0;
	while(getline(stringstream,tempstring,delim)){
		check_size += tempstring.size();
		temp_array.push_back(tempstring);
	}
	// This check down below is because I had a bug where if a user gave an input like 120.2. the split function ignored the last period and gave this as a valid input, I now check if the size of my check_size variable is equal to the original inut plus 1 (for the period that was removed)
	check_size += 1;
	if((check_size != date.size()) && (delim == '.')){
		cerr << program_name <<" - Error: Improper number of arguments- " << date << '\n';
		exit(1);
	}
		

	return temp_array;
}
vector<int> check_bounds(vector<string> dates){
	// Null pointer as needed per cplusplus
	size_t anystring;
	// The return vector that holds the string converted int
	vector<int> output;
	int year;
	int day;
	// Stoi throws an error, so I try and catch it if its given
	try{
		year = stoi(dates[0], &anystring);
		if((year <= 0) || (year > 9999)){
                        cerr << program_name <<" - Error: The Year given is out of range- " << dates[0] << "." << dates[1] << "\n";
                        exit(1);
                }
                output.push_back(year);
	}
	catch(const invalid_argument &error){
		cerr << program_name <<" - Error: Invalid argument- " << dates[0] << "." << dates[1] << "\n";
		exit(1);
	}
	catch(const out_of_range & error){
                cerr << program_name << " - Error: The Year given is out of range- " << dates[0] << "."
<< dates[1] << "\n";
		exit(1);
        }
	try{
		day = stoi(dates[1],&anystring);
		if((day >= 367) || (day <= 0)){
                        cerr << program_name <<" - Error: The Day given is out of range- " << dates[0] << "." << dates[1] << "\n";
                        exit(1);
                }
                output.push_back(day);
	}
	catch(const invalid_argument &error){
                cerr << program_name <<" - Error: Invalid argument- " << dates[0] << "." << dates[1] << "\n";
		exit(1);
        }
	catch(const out_of_range & error){
		cerr << program_name << " - Error: The Day given is out of range- " << dates[0] << "." << dates[1] << "\n";
		exit(1);
	} 
	return output;
	
}
vector<int> get_month(int day, bool is_leap, vector<int> data){
	// I know this is not the most efficient but the methods provided were being quite fidgity
	// Below will return the numbered month indexed at 0, the variable i will add 1 after feb if its a leap year
	int i = 0;
	if(is_leap){
		i = 1;
	}
	if((1 <= day) && (day <= 31)){
		data.push_back(0);
		data.push_back(day);
	}
	else if((32 <= day) && (day <= (59+i))){
		data.push_back(1);
		data.push_back(day-31);
	}
	else if(((60+i) <= day) && (day <= (90+i))){
		data.push_back(2);
		data.push_back(day-(59+i));
	}
	else if(((91+i) <= day) && (day <= (120+i))){
		data.push_back(3);
		data.push_back(day-(90+i));
	}
	else if(((121+i) <= day) && (day <= (151+i))){
		data.push_back(4);
		data.push_back(day-(120+i));
	}
	else if(((152+i) <= day) && (day <= (181+i))){
                data.push_back(5);
		data.push_back(day-(151+i));
        }
        else if(((182+i) <= day) && (day <= (212+i))){
                data.push_back(6);
		data.push_back(day-(181+i));
        }
        else if(((213+i) <= day) && (day <= (243+i))){
                data.push_back(7);
		data.push_back(day-(212+i));
        }
	else if(((244+i) <= day) && (day <= (273+i))){
                data.push_back(8);
		data.push_back(day-(243+i));
        }
        else if(((274+i) <= day) && (day <= (304+i))){
                data.push_back(9);
		data.push_back(day-(273+i));
        }
        else if(((305+i) <= day) && (day <= (334+i))){
                data.push_back(10);
		data.push_back(day-(304+i));
        }
	else{
		data.push_back(11);
		data.push_back(day-(334+i));
	}
	return data;
}
int get_day_of_week(int d, int y, string error_string){
	// To get the day of the week I use an anchor date, calculate the days between the provided date and anchor date then mod that value by 7
	// I then modify the day of week number of my anchor date (indexed at 0) to get the day of the week of the date provided
	//Anchor is January 1,1800 Wed
	int anchor_day_of_week = 2;
	int anchor_year = 1800;
	if((d == 1) && y == anchor_year){
		return anchor_day_of_week;
	}
	int total_days = 0;
	int min = 0;
	// If the provided year is less than the anchor year we need to count up the days up to the anchor date
	if(anchor_year > y){
		int max = anchor_year - y - 1;
		while(max > min){
			if(check_leapyear(y, 5, error_string)){
				total_days += 366;
			}	
			else{
				total_days += 365;
			}
			y++;
			min++;
		}
		// Adds 366 to the total days if its a leap year and 365 otherwise
		if(check_leapyear(y+1, 5, error_string)){
			total_days += ((366-d)+1);
		}
		else{
			total_days += ((365-d)+1);
		}
		anchor_day_of_week -= (total_days % 7);
		// Weird bug where if the date was one after (wed) it returned tues, ths fixed it
		if((anchor_day_of_week == -4) || (anchor_day_of_week == 8)){
                	return 3;
       		 }
	}
	// Same fucntion as before just counting from anchor years to the provided date
	// Perhaps the two functions could have been joined into one
	else if(y > anchor_year){
		int max = y - anchor_year;
		while(max > min){
                        if(check_leapyear((anchor_year), 5, error_string)){
                                total_days += 366;
                        }
                        else{
                                total_days += 365;
                        }
                        anchor_year++;
                        min++;
                }
                total_days += (d-1);
		anchor_day_of_week += (total_days % 7);
        }
	else{
		total_days = d-1;
		anchor_day_of_week += (total_days % 7);
	}
	if(anchor_day_of_week > 6){
		return anchor_day_of_week - 7;
	}
	else if(anchor_day_of_week < 0){
		return anchor_day_of_week + 7;
	}
	else{
		return anchor_day_of_week;
	}
}
vector<string> leading_zeros(int year, int day){
	// Since stoi gets rid of leading zeroes, I add those back to match the input
	string st_year = to_string(year);
	string st_day = to_string(day);
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
	vector<string> ret_array;
	ret_array.push_back(st_year);
	ret_array.push_back(st_day);
	return ret_array;
}
void date_output(int year, int day, bool is_leap, string error_string){
	vector<int> data;
	data = get_month(day, is_leap, data);
	int day_of_week = get_day_of_week(day, year, error_string);
	// Since the above two fucntions get the day of week and month (indexed at 0) I need the arrays below to spit out the correct answer
	vector<string> months{"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
	vector<string> days{"Mon","Tue","Wed","Thu","Fri","Sat","Sun"};
	vector <string> year_day;
	year_day = leading_zeros(year, data[1]);
	cout << days[day_of_week] << ' '<< year_day[1] << ' ' <<  months[data[0]] << ' ' << year_day[0] << '\n';
	return;
	
}



