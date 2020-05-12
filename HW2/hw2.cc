#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
using namespace std;

void noarg(int argc);
void check_arg(int argc, string arg1);
void check_first_argument(string arg1, vector<bool> &arg);
void check_second_argument(string arg2, vector<bool> &arg);
void put_args_in_vec(char * argv[],vector<int> &numbers, int min, int max);
bool is_hex(string hex);
bool is_binary(string boolean);
bool is_oct(string oct);
bool only_dig(string dig);
int binary_to_dec(string binary);
int pow_int(int power, int accum);
int do_math(vector<int> &numbers, vector<bool> &arg);
int add(vector<int> &numbers);
int subtract(vector<int> &numbers);
int multiply(vector<int> &numbers);
int divide(vector<int> &numbers);
int distance_from(vector<int> &numbers);
void final_conversion(vector<bool> &arg, int sum);

string program_name;

int main(int argc, char* argv[]){
	// Declare global variable of program name for error output
	program_name = argv[0];
	// Check if no input was given
	noarg(argc);
	string arg1 = argv[1];
	// Checks if only two arguments were given
	check_arg(argc, arg1);
	// Create vector or arguments so we know what output to gove and what action to perform
	//[0]: hex, [1]: octave, [2]: decimal, [3]: addition, [4]: subtraction, [5]: multiplication,
	// [6]: division, [7]: distance from 45, [8]: special trigger
	vector<bool> arguments{0,0,0,0,0,0,0,0};
	// Checks first argument
	check_first_argument(arg1, arguments);
	// Variable to keep track of what argument we are on
	int min = 2;
	// Argument 8 tells us if the output flag was triggered or not
	// This way we dont check an extra argument
	if(!arguments[8]){
		string arg2 = argv[2];
		check_second_argument(arg2, arguments);
		min = 3;
	}
		
	vector<int> numbers;
	// Put arguments into a vector
	put_args_in_vec(argv, numbers, min, argc);
	
	// Does math on all the inputs in the vector
	int output = do_math(numbers, arguments);
	// Converts decimal sum to neccessary output
	final_conversion(arguments, output);
	return 0;
}

void noarg(int argc){
	if(argc == 1){
		cerr << program_name << "- No arguments provided" << '\n';
		exit(1);
	}
	return;
}

void check_arg(int argc,string arg1){
	if(argc == 2){
		cerr << program_name << "- Not enough arguments provided- " << arg1 << '\n';
		exit(1);
	}
	return;
}
		

void check_first_argument(string arg1, vector<bool> &arg){
	// String compare function returns 0 if its the same so I had to do !
	if(!(arg1.compare("-h"))){
		arg[0] = 1;
		return;
	}
	else if(!(arg1.compare("-o"))){
		arg[1] = 1;
		return;
	}
	else if(!(arg1.compare("-d"))){
		arg[2] = 1;
		return;
	}
	else{
		// Just because there is no flag doesnt mean the input is wrong, so send that argument to the second argument check
		// Also sets the boolean trigger on
		arg[8] = 1;
		check_second_argument(arg1, arg);
		// If no error is given then set the default flag
		arg[2] = 1;
		return;
	}
	
}

void check_second_argument(string arg2, vector<bool> &arg){
	if(!(arg2.compare("+"))){
		arg[3] = 1;
		return;
	}
	else if(!(arg2.compare("-"))){
		arg[4] = 1;
		return;
	}
	else if(!(arg2.compare("*"))){
		arg[5] = 1;
		return;
	}
	else if(!(arg2.compare("/"))){
		arg[6] = 1;
		return;
	}
	else if(!(arg2.compare("@"))){
                arg[7] = 1;
                return;
	}
	else{
		// No arthimetic symbol was given this is an error
		cerr << program_name <<  "- Improper argument given " << arg2 << '\n';
		exit(1);
	}

}

void put_args_in_vec(char * argv[],vector<int> &numbers, int min, int max){	
	size_t anystring;
	// Puts the rest of the arguments into a vector, but first the input type must be determined then converted to an int
	for(int i = min; i < max; i++){
		int x;
		stringstream stream;
		stream << argv[i];
		if(is_hex(argv[i])){
			stream >> hex >> x;
			numbers.push_back(x);
			continue;
		}
		else if(is_oct(argv[i])){
			stream >> oct >> x;
			numbers.push_back(x);
			continue;
		}
		else if(is_binary(argv[i])){
			x= binary_to_dec(argv[i]);
			numbers.push_back(x);
			continue;
		}
		else if(only_dig(argv[i])){
			cerr << program_name << " - Error: You provided an invalid input- " << argv[i] << "\n";
			exit(1);
		}
			
		// If its not any of the above types its an int or an error, so stoi will let us know
                try{
                int num_arg = stoi(argv[i], &anystring);
                        if((num_arg < 0)){
                                cerr << program_name <<" - Error: You provided an invalid input- " << argv[i] << "\n";
                        exit(1);
                        }
			numbers.push_back(num_arg);
                }
                catch(const invalid_argument &error){
                        cerr << program_name <<" - Error: Invalid argument- " << argv[i] << "\n";
                        exit(1);
                 }      
                catch(const out_of_range & error){
                        cerr << program_name << " - Error: The number you provided was out of range- " << argv[i] << "\n";
                        exit(1);
                }
                        
        }
}

bool is_hex(string hex){
	if(hex.size() > 2){
		if(!hex.compare(0,2, "0x")){
			// Check position of chars to see if they anything else is included
			if(hex.find_first_not_of("0123456789abcdef", 2) == string::npos){
				return true;
			}
		}
	}
	return false;
}

bool is_binary(string boolean){
	if(boolean.size() > 2){
                if(!boolean.compare(0,2, "0b")){
			// Same process as hex
                        if(boolean.find_first_not_of("01", 2) == string::npos){
                                return true;
                        }
                }
        }
        return false;
}

bool is_oct(string oct){
	if(oct.size() > 1){
                if(!oct.compare(0,1, "0")){
			// Same process as hex but check after 1
                        if(oct.find_first_not_of("01234567", 1) == string::npos){
                                return true;
                        }
                }
        }
        return false;
}

bool only_dig(string dig){
	if(dig.find_first_not_of("0123456789") == string::npos){
        	return false;
        }
	return true;
}
// Pow function takes a float and returns a float, I though I would just make my own for ints
int pow_int(int power, int accum){
	if(power != 0){
		return(accum*pow_int(power-1, accum));
	}
	else{
		return 1;
	}
}

// Only input that doesnt have an easy conversion, so I have to go char by char and calculate decimal value from binary myself
int binary_to_dec(string binary){
	int x = 0;
	string newst = binary.substr(2,binary.size());
	for(unsigned i = 0; i < newst.size(); i++){
		if(newst[i] == '1'){
			int extra = i+1;
			x += pow_int(newst.size()-extra, 2);
		}
	} 
	return x;
}

// Just splitting each process into methods, it knows what math to do based on boolean vector arguments
int do_math(vector<int> &numbers, vector<bool> &arg){
	if(arg[3] == 1){
		return add(numbers);
	}
	else if(arg[4] == 1){
		return subtract(numbers);
	}
	else if(arg[5] == 1){
		return multiply(numbers);
	}
	else if(arg[6] == 1){
		return divide(numbers);
	}
	else if(arg[7] == 1){
		return distance_from(numbers);
	}
	else{
		cerr << program_name << " - Error: Somehow you entered an invalid argument\n";
		exit(1);
	}
}

int add(vector<int> &numbers){
	int sum = numbers[0];
	for(unsigned i = 1; i < numbers.size(); i++){
		sum += numbers[i];
	}
	return sum;
}

int subtract(vector<int> &numbers){
	int sum = numbers[0];
	for(unsigned i = 1; i < numbers.size(); i++){
		sum -= numbers[i];
        }
	return sum;
}

int multiply(vector<int> &numbers){
	int sum = numbers[0];
	for(unsigned i = 1; i < numbers.size(); i++){
		sum *= numbers[i];
        }
	return sum;
}

int divide(vector<int> &numbers){
	// Check for divide by 0 error
	int sum = numbers[0];
	if(sum == 0){
		cerr << program_name << " - Error: Division by 0 attempted: " << sum << '\n';
		exit(1);
	}
	for(unsigned i = 1; i < numbers.size(); i++){
		 if(numbers[i] == 0){
               		 cerr << program_name << " - Error: Division by 0 attempted: " << numbers[i] << '\n';
               		 exit(1);
       		 }
		sum /= numbers[i];
        }
	return sum;
}

int distance_from(vector<int> &numbers){
	int output = numbers[0];
	int sum = numbers[0] - 45;
	int compare = abs(sum);
	for(unsigned i = 0; i < numbers.size(); i++){
		int x = numbers[i] - 45;
		if(abs(x) > compare){
			output = numbers[i];
			compare = abs(x);
		}
		else if(abs(x) == compare){
			if(numbers[i] < output){
				output = numbers[i];
			}
		}
        }
	return output;
}

// Since we did all the math in decimal we need to convert back to whatever output was requested
void final_conversion(vector<bool> &arg, int sum){
	if(arg[2] == 1){
		cout << sum << '\n';
		return;
	}
	else if(arg[0] == 1){
		if(sum < 0){
			int x = abs(sum);
			cout << "-" << hex << x << '\n';
			return;
		}
		cout << hex << sum << '\n';
		return;
	}
	else if(arg[1] == 1){
		if(sum < 0){
			int x = abs(sum);
			cout << "-" << oct << x << '\n';
			return;
		}
		cout << oct << sum << '\n';
		return;
	}
	else{
                cerr << program_name << " - Error: Somehow you entered an invalid argument\n";
                exit(1);
        }
	
}
