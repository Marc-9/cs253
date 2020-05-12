#ifndef Schedule_H_INCLUDED
#define Schedule_H_INCLUDED

#include <istream>
#include <string>
#include <vector>
#include "Event.h"
#include <iterator>
class Schedule{
	 private:
                void sort();
                std::vector<Event> myEvents;
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
		using iterator = decltype(myEvents)::const_iterator;
		iterator begin() const;
		iterator end() const;
};
std::ostream &operator<<(std::ostream &, const Schedule &);
#endif
