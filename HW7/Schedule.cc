#include "Schedule.h"
#include <iostream> 
#include <fstream>
using namespace std;

Schedule::Schedule(istream &myStream){
	string strEvent;
	while(myStream >> strEvent){
		try{
                        myEvents.push_back(Event(strEvent));
                }
                catch(runtime_error &e){
                        myStream.setstate(ios::failbit);
                        throw;
                }
	}
	sort();
}
Schedule::Schedule(const string filename){
        ifstream myStream(filename);
	if(!myStream){
		string error = "Invalid filename provided- " + filename;
		throw runtime_error(error);
	}
	string strEvent;
	while(myStream >> strEvent){
		try{
                        myEvents.push_back(Event(strEvent));
                }
                catch(runtime_error &e){
                        myStream.setstate(ios::failbit);
                        throw;
                }
        }
        sort();
	
}
size_t Schedule::size() const{
	return myEvents.size();
}
Schedule::~Schedule(){
//	int max = size();
//	cout << max << endl;
//	for(int i = 0; i < max; i++){
//		myEvents[i].~Event();
//	}
//	delete this;
}
Schedule::Schedule(const Schedule &rhs){
	for(size_t i = 0; i < rhs.myEvents.size(); i++){
		this->myEvents.push_back(rhs.myEvents[i]);
	}
}
Schedule &Schedule::operator=(const Schedule &rhs){
	for(size_t i = 0; i < rhs.myEvents.size(); i++){
                this->myEvents.push_back(rhs.myEvents[i]);
        }
	return *this;
}
void Schedule::read(istream &mystream){
	string strEvent;
        while(mystream >> strEvent){
                try{
			myEvents.push_back(Event(strEvent));
        	}
		catch(runtime_error &e){
			mystream.setstate(ios::failbit);
			throw;
		}
	}
        sort();
}
void Schedule::clear(){
	int max = this->size();
        for(int i = 0; i < max; i++){
                myEvents[i].~Event();
        }
        myEvents.clear();
}
bool Schedule::empty() const{
	return (size()==0);
}
const Event &Schedule::operator[](const size_t i) const{
        return myEvents[i];
}
void Schedule::sort(){
	for(size_t i = 0; i < this->size(); i++){
		for(size_t j = i+1; j < this->size(); j++){
			int earliestYear = myEvents[i].year();
                	int earliestMonth = myEvents[i].month();
                	int earliestDay = myEvents[i].day();
			if(myEvents[j].year() < earliestYear){
				Event tempEvent = myEvents[i];
				myEvents[i] = myEvents[j];
				myEvents[j] = tempEvent;	
			}
			else if(myEvents[j].year() == earliestYear){
				if(myEvents[j].month() < earliestMonth){
					Event tempEvent = myEvents[i];
                                	myEvents[i] = myEvents[j];
                                	myEvents[j] = tempEvent;
				}
				else if(myEvents[j].month() == earliestMonth){
					if(myEvents[j].day() < earliestDay){
						Event tempEvent = myEvents[i];
                                		myEvents[i] = myEvents[j];
                                		myEvents[j] = tempEvent;
					}
					else if(myEvents[j].day() == earliestDay){
						cout << "Same date\n";
					}
				}
			}
		}
	}
}
Schedule::iterator Schedule::begin() const{
	return myEvents.begin();
}
Schedule::iterator Schedule::end() const{
        return myEvents.end();
}
ostream &operator<<(ostream &stream, const Schedule &sched) {
	for(size_t i = 0; i < sched.size(); i++){
                stream << sched[i] << '\n';
        }
	return stream;
}
