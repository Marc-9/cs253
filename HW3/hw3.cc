#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <ctime>
using namespace std;

void log(int x);
void log(char * x);
void log(string x);
int check_opt(vector<bool> & booleans, int argc, char * argv[]);
void check_value(string argument, vector<bool> &booleans);
void read_format(string format, vector<bool> &booleans);
vector<string> check_files(int num_args, int argc, char * argv[]);
void prelim_check(string date);
vector<int> secondary_check(string date);
void date_periods(string date, vector<int> &return_data);
void date_hyphens(string date, vector<int> &return_data);
void check_string(string date, vector<int> &return_data);
vector<string> split(string date, char delim);
void check_nonnumbers(string date, char delim);
int string_to_int(string string_int);
void read_input(vector<bool> &booleans);
void read_input_file(string file, vector<bool> &booleans);
void iso_output(vector<int> &my_dates, vector<bool> booleans);
void string_output(vector<int> &my_dates, vector<bool> booleans);
void standard_output(vector<int> &my_dates, vector<bool> booleans);
void tertiary_check(vector<int> &my_dates, int check);
bool check_leapyear(int year, int day);
string program_name;


class output{
        public:
                static string format;
		static string error_string;
                vector<bool> state_check;
                output(){
                        state_check = {0,0,0,0,0,0,0};
                }

};

string output::error_string = "null";
string output::format = "null";

int main(int argc, char *argv[]){
	output output_class;
	program_name = argv[0];
	//{f,v,i,hw1,no_more_arg,files,read -f format}
	int num_args = check_opt(output_class.state_check,argc,argv);
	//If niether output format is specified do the default
	if(!(output_class.state_check[0] || output_class.state_check[2])){
		output_class.state_check[3] = 1;
	}
	if((output_class.state_check[0]) && (output_class.state_check[2])){
		cerr << program_name << "- Error: Two different input types f and i provided\n";
		exit(1);
	}
	vector<string> file_names;
	//Read in file names if the arguments were provided
	if(output_class.state_check[5]){
		file_names = check_files(num_args, argc, argv);
		if(output_class.state_check[1]){
			for(auto v:file_names){
				cout << "*** Processing " << v << '\n';
				read_input_file(v, output_class.state_check);
			}
		}
		else{
			for(auto v:file_names){
                                read_input_file(v, output_class.state_check);
                        }
		}
	}
	else if(output_class.state_check[1]){
		cout << "*** Processing standard input" << '\n';
		read_input(output_class.state_check);
	}
	else{
		read_input(output_class.state_check);
	}	
	
	return 1;

}


int check_opt(vector<bool> & booleans,int argc, char * argv[]){
	if(argc == 1){
		booleans[3] = 1;
		booleans[4] = 1;
		return argc;
	}
	else{
		int counter = 1;
		while(counter < argc){
			if(booleans[6]){
				read_format(argv[counter], booleans);
				counter++;
				continue;
			}
			check_value(argv[counter], booleans);
			if(booleans[4]){
                                return counter;
                        }
			counter++;
		}
		return argc;
	}
			
} 

void check_value(string argument, vector<bool> &booleans){
	if(argument[0] != '-'){
		booleans[5] = 1;
		booleans[4] = 1;
		return;
	}
	if(argument.size() > 2){
		if(argument[1] == 'f'){
			booleans[0] = 1;
			read_format(argument.substr(2), booleans);			
			return;
		}
		for(unsigned i = 1; i < argument.size(); i++){
			string temp = "-";
			temp += argument[i];
			check_value(temp, booleans);
		}
	}
	else{
		switch(argument[1]){
			case 'f': 
				if(booleans[0] == 1){
					cerr << program_name << "- Error: You may only provide the -f flag once\n";
					exit(1);
				}
				booleans[0] = 1;
				booleans[6] = 1;
				break;
			case 'v': booleans[1] = 1;
				break;
			case 'i': booleans[2] = 1;
				break;
			default:cerr << program_name << "- Error: Invalid Option- " << argument[1] << '\n';
				exit(1);
		}
	}
}

void read_format(string format, vector<bool> &booleans){
	output for_string;
	for_string.format = format;
	booleans[6] = 0;
}

vector<string> check_files(int num_args, int argc, char * argv[]){
	vector<string> dates_name;
	while(num_args < argc){
		ifstream myfile(argv[num_args]);
		if(myfile){
			dates_name.push_back(argv[num_args]);
			num_args++;
		}
		else{
			cerr << program_name << "- Error: File- " << argv[num_args] << " does not exist" << '\n';
			exit(1);
		}
	}	
	return dates_name;
}

void prelim_check(string date){
	if(date.empty()){
		cerr << program_name <<" - Error: Line is Empty\n";
		exit(1);
	}
	vector<string> check_for_spaces = split(date,' ');
        if(check_for_spaces.size() != 1){
                cerr  << program_name <<" - Error: Line has spaces in it- " << date <<"\n";
                exit(1);
        }
	return;
}

vector<int> secondary_check(string date){
	vector<string> check_for_periods = split(date,'.');
	vector<string> check_for_hyphens = split(date,'-');
	vector<int> return_data;
	if(check_for_periods.size() == 2){
		date_periods(date, return_data);
	}
	else if(check_for_hyphens.size() == 3){
		date_hyphens(date, return_data);
	}
	else if(check_for_periods.size() > 2){
                cerr << program_name <<" - Error: Too many arguments given- " << date <<"\n";
        	exit(1);
	}
        else if(check_for_hyphens.size() > 3){
      		cerr << program_name <<" - Error: Too many arguments given- " << date <<"\n";
		exit(1); 
	 }
	else{
		check_string(date, return_data);
	}
	return return_data;
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
	if(delim == '-'){
		check_size += 1;
	}
	check_size += 1;
	if( (check_size != date.size() ) && ( (delim == '.')||(delim == '-') ) ){
		if(temp_array.size() > 1){
                	cerr << program_name <<" - Error: Improper number of arguments- " << date << '\n';
               		exit(1);
		}
        }


        return temp_array;
}
void date_periods(string date, vector<int> &return_data){
	check_nonnumbers(date, '.');
	vector<string> numbers = split(date,'.');
	return_data.push_back(string_to_int(numbers[0]));
	return_data.push_back(string_to_int(numbers[1]));
	return;
}

void date_hyphens(string date, vector<int> &return_data){
	check_nonnumbers(date, '-');
	vector<string> numbers = split(date,'-');
        return_data.push_back(string_to_int(numbers[0]));
        return_data.push_back(string_to_int(numbers[1]));
	return_data.push_back(string_to_int(numbers[2]));
        return;
}

void check_string(string date, vector<int> &return_data){
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
		cerr << program_name << " - Error: Invalid Input given- " << old_date << '\n';
		exit(1);
	}
}

void check_nonnumbers(string date, char delim){
        // First check if the input has spaces
        vector<string> check_for_spaces = split(date,' ');
        if(check_for_spaces.size() != 1){
                cerr  << program_name <<" - Error: Line has spaces in it- " << date <<"\n";
                exit(1);
        }
        // Loop through string and check each char
        for(unsigned i = 0; i < date.size(); i++){
                if(((date[i] < '0') || (date[i] > '9')) && (date[i] != delim)){
                        cerr << program_name <<" - Error: Line has non numbers- " << date << "\n";
                        exit(1);
                }
        }
        check_for_spaces.clear();
        return;

}

void tertiary_check(vector<int> &dates, int check){
	output for_error;
	if(check == 1){
		check_leapyear(dates[0], dates[1]);
		if((dates[0] > 9999) || dates[0] <= 0){
			cerr << program_name << " - Error: Year out of range " << for_error.error_string << '\n';
			exit(1);
		}
		else if((dates[1] <= 0) || (dates[1] >= 367)){
			cerr << program_name << " - Error: Day out of range " << for_error.error_string << '\n';
                        exit(1);
                }
	}
	else if(check == 2){
		if((dates[0] > 9999) || dates[0] <= 0){
                        cerr << program_name << " - Error: Year out of range " << for_error.error_string << '\n';
                        exit(1);
                }
		if((dates[1] > 12) || (dates[1] <= 0)){
			cerr << program_name << " - Error: Month out of range " << for_error.error_string << '\n';
                        exit(1);
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
					cerr << program_name << " - Error: Number of days is too large for the month " << for_error.error_string << '\n';
					exit(1);
				}
				break;
			case 4:
			case 6:
			case 9:
			case 11:
				if(dates[2] > 30){
					cerr << program_name << " - Error: Number of days is too large for the month " << for_error.error_string << '\n';
					exit(1);
				}
				break;
			default:
				if(check_leapyear(dates[0],5)){
					if(dates[2] > 29){
						cerr << program_name << " - Error: Number of days is too large for the month " << for_error.error_string << '\n';
                                        exit(1);
                                	}
				}
				else{
					if(dates[2] > 28){
                                                cerr << program_name << " - Error: Number of days is too large for the month " << for_error.error_string << '\n';
                                        exit(1);
                                        }
				}
				break;
		}			
			
	}

}

bool check_leapyear(int year, int day){
        bool isleap = false;
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
		output for_error2;
                if(day >= 366){
                        cerr << program_name <<" - Error: The year provided is not a leap year yet you provided more than 365 days: "<< for_error2.error_string <<'\n';
                        exit(1);
                }
        }
        return isleap;
} 

int string_to_int(string string_int){
	// Null pointer as needed per cplusplus
        size_t anystring;
        // The return vector that holds the string converted int
        int int_string = 0;
        // Stoi throws an error, so I try and catch it if its given
        try{
                int_string = stoi(string_int, &anystring);
        }
        catch(const invalid_argument &error){
        	cerr << program_name <<" - Error: Invalid argument- " << string_int << '\n';
                exit(1);
        }
        catch(const out_of_range & error){
                cerr << program_name << " - Error: Out of Range- " << string_int << '\n';
                exit(1);
        }
        return int_string;

}

void read_input_file(string file, vector<bool> &booleans){
	string date;
	vector<int> my_dates;

	ifstream myfile(file);
	while(getline(myfile,date)){
		prelim_check(date);
		my_dates = secondary_check(date);
                if(my_dates.size() == 1){
                        string_output(my_dates, booleans);
                }
                else if(my_dates.size() == 2){
                        standard_output(my_dates, booleans);
                }
                else if(my_dates.size() == 3){
                        iso_output(my_dates, booleans);
                }
                else{
                        cerr << "Impossible error" << '\n';
                }	
	}
}

void read_input(vector<bool> &booleans){
	string date;
        vector<int> my_dates;
	while(getline(cin,date)){
		output for_error;
        	for_error.error_string = date;	
        	prelim_check(date);
                my_dates = secondary_check(date);
                if(my_dates.size() == 1){
			string_output(my_dates, booleans);      
                }
		else if(my_dates.size() == 2){
			tertiary_check(my_dates, 1);
			standard_output(my_dates, booleans);
		}
		else if(my_dates.size() == 3){
			tertiary_check(my_dates, 2);
			iso_output(my_dates, booleans);
		}
		else{
			cerr << "Impossible error" << '\n';
		}
	}
}

void iso_output(vector<int> &my_dates, vector<bool> booleans){
	struct tm my_time;
	my_time.tm_sec = 0;
	my_time.tm_min = 0;
	my_time.tm_hour = 0;
	my_time.tm_mday = my_dates[2];
	my_time.tm_mon = my_dates[1] - 1;
	my_time.tm_year = my_dates[0] - 1900;
	my_time.tm_wday = 0;
	my_time.tm_yday = 0;
	my_time.tm_isdst = 0;
	mktime(&my_time);
 	char result[256];
	if(booleans[0] == 1){
		const char* mktime_output;
		output for_string;
        	mktime_output = for_string.format.c_str();
		strftime(result,sizeof(result), mktime_output, &my_time);
		cout << result << '\n';
	}
	else if(booleans[2]){
		const char* mktime_output = "%04Y-%m-%d";
		strftime(result,sizeof(result),mktime_output , &my_time);
		cout << result << '\n';
	}
	else{
		const char* mktime_output = "%a %b %d %04Y";
		strftime(result,sizeof(result),mktime_output , &my_time);
                cout << result << '\n';
	}
		
	
}

void string_output(vector<int> &my_dates, vector<bool> booleans){
	time_t rawtime;
  	struct tm * my_time;
	time(&rawtime);
  	my_time = localtime(&rawtime);
	if(my_dates[0] == 2){
		int day = my_time->tm_mday;
		my_time->tm_mday = day+1;
	}
	else if(my_dates[0] == 3){
		int day = my_time->tm_mday;
                my_time->tm_mday = day-1;
	}
	mktime(my_time);
	char result[256];
        if(booleans[0] == 1){
                const char* mktime_output;
                output for_string;
                mktime_output = for_string.format.c_str();
                strftime(result,sizeof(result), mktime_output, my_time);
                cout << result << '\n';
        }
        else if(booleans[2]){
                const char* mktime_output = "%04Y-%m-%d";
                strftime(result,sizeof(result), mktime_output, my_time);
                cout << result << '\n';
        }
        else{
                const char* mktime_output = "%a %b %d %04Y";
                strftime(result,sizeof(result),mktime_output , my_time);
                cout << result << '\n';
        }
}

void standard_output(vector<int> &my_dates, vector<bool> booleans){
	struct tm my_time;
        my_time.tm_sec = 0;
        my_time.tm_min = 0;
        my_time.tm_hour = 0;
        my_time.tm_mday = my_dates[1];
        my_time.tm_mon = 0;
        my_time.tm_year = my_dates[0] - 1900;
        my_time.tm_wday = 0;
        my_time.tm_yday = 0;
        my_time.tm_isdst = 0;
        mktime(&my_time);
        char result[256];
        if(booleans[0] == 1){
                const char* mktime_output;
                output for_string;
                mktime_output = for_string.format.c_str();
                strftime(result,sizeof(result), mktime_output, &my_time);
                cout << result << '\n';
        }
        else if(booleans[2]){
		const char* mktime_output = "%04Y-%m-%d";
                strftime(result,sizeof(result), mktime_output, &my_time);
                cout << result << '\n';
        }
        else{
		const char* mktime_output = "%a %b %d %04Y";
                strftime(result,sizeof(result),mktime_output , &my_time);
                cout << result << '\n';
        }
}
void log(int x){
	cout << x << '\n';
}

void log(char * x){
	cout << x << '\n'; 
}
void log(string x){
	cout << x << '\n';
}
