#ifndef EVENT_H_INCLUDED
#define EVENT_H_INCLUDED
#include <vector>
#include <string>
class Event{
        public:
		Event() = delete;
		Event(std::string date);
		// Copy Constructor
		Event(const Event &);
		// Assignment Operator
		Event &operator=(const Event &);	
		~Event() = default;
		void set(const int year, const int month, const int day);
		int year() const;
		int month() const;
		int day() const;
	private:
		int eYear;
		int eMonth;
		int eDay;
		std::vector<std::string> leading_zeros(int year, int day, int month);
};
std::ostream &operator<<(std::ostream &, const Event &);
#endif
