#include "Date.hpp"

class TimePeriod
{
	Date start;
	Date end;
	void fixTimePeriod();
public:
	TimePeriod();
	TimePeriod(int, int, int, int, int, int);
	void setStart(int, int, int);
	void setEnd(int, int, int);
	void setTimePeriod(int, int, int, int, int, int);
	void print(bool) const;
	void writeToFile(ofstream& f) const;
	void readFromFile(ifstream& f);
};

TimePeriod::TimePeriod() :start(2000, 1, 1), end(2000, 1, 1) {}

TimePeriod::TimePeriod(int startYear, int startMonth, int startDay, int endYear, int endMonth, int endDay) :
	start(startYear, startMonth, startDay), end(endYear, endMonth, endDay)
{
	fixTimePeriod();
}

void TimePeriod::fixTimePeriod()
{
	if (end.getYear() < start.getYear())
		end.setYear(start.getYear());
	else if (end.getYear() == start.getYear() and end.getMonth() < start.getMonth())
		end.setMonth(start.getMonth());
	else if (end.getYear() == start.getYear() and end.getMonth() == start.getMonth() and end.getDay() < start.getDay())
		end.setDay(start.getDay());
}

void TimePeriod::setStart(int startYear, int startMonth, int startDay)
{
	start.setDay(startDay);
	start.setMonth(startMonth);
	start.setYear(startYear);

	fixTimePeriod();
}
void TimePeriod::setEnd(int endYear, int endMonth, int endDay)
{
	end.setDay(endDay);
	end.setMonth(endMonth);
	end.setYear(endYear);

	fixTimePeriod();
}
void TimePeriod::setTimePeriod(int startYear, int startMonth, int startDay, int endYear, int endMonth, int endDay)
{
	start.setDay(startDay);
	start.setMonth(startMonth);
	start.setYear(startYear);

	end.setDay(endDay);
	end.setMonth(endMonth);
	end.setYear(endYear);

	fixTimePeriod();
}

void TimePeriod::print(bool oneRow = false) const
{
	if (oneRow)
		cout << "From ";
	start.print();
	if (oneRow)
		cout << " to ";
	else
		cout << endl;
	end.print();
	if(!oneRow)
		cout << endl;
}

void TimePeriod::writeToFile(ofstream& f) const
{
	if (!f.is_open())
	{
		cout << "TimePeriod::writeToFile() : Error, open file before writing to it\n";
		return;
	}
	start.writeToFile(f);
	end.writeToFile(f);
}
void TimePeriod::readFromFile(ifstream& f)
{
	if (!f.is_open())
	{
		cout << "TimePeriod::readFromFile() : Error, open file before reading from it\n";
		return;
	}
	start.readFromFile(f);
	end.readFromFile(f);
	//fixTimePeriod();
}