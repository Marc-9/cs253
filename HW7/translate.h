#ifndef TRANSLATE_H_INCLUDED
#define TRANSLATE_H_INCLUDED
#include <string>
#include <vector>
std::vector<int> formatType(std::string date);
std::vector<std::string> split(std::string date, char delim);
void date_periods(std::string date, std::vector<int> &return_data);
void date_hyphens(std::string date, std::vector<int> &return_data);
void check_string(std::string date, std::vector<int> &return_data);
void check_nonnumbers(std::string date, char delim);
int string_to_int(std::string string_int);
void boundsCheck(std::vector<int> &dates, int check);
bool check_leapyear(int year, int day);
std::vector<int> doMKtimeString(std::vector<int> &dates);
std::vector<int> doMKtime(std::vector<int> &dates);
#endif
