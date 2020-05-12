#ifndef Schedule_H_INCLUDED
#define Schedule_H_INCLUDED

#include <istream>
#include <string>
#include <vector>
#include "Event.h"
class Schedule{
        public:
		Schedule() = default;
		Schedule(std::istream &);
		Schedule(const std::string);
		Schedule(const Schedule &);
		Schedule &operator=(const Schedule &);
		~Schedule();
		void read(std::istream &);
		void clear();
		size_t size() const;
		bool empty() const;
		const Event &operator[](const size_t i) const;
	private:
		std::vector<Event> myEvents;
		void sort();
};
	std::ostream &operator<<(std::ostream &, const Schedule &);
#endif
