#include "Date.h"

class TimePeriod
{
	Date start;
	Date end;
	void fixTimePeriod();
	void copyFrom(const TimePeriod& other);
public:
	TimePeriod();
	TimePeriod(const TimePeriod& other);
	TimePeriod(int, int, int, int, int, int);
	TimePeriod& operator=(const TimePeriod& other);
	void setStart(int, int, int);
	void setEnd(int, int, int);
	void print();
	void read(ifstream& f);
	void write(ofstream& f);
};

TimePeriod::TimePeriod() :start(2000, 1, 1), end(2000, 1, 1) {}

TimePeriod::TimePeriod(int startYear, int startMonth, int startDay, int endYear, int endMonth, int endDay) :
	start(startYear, startMonth, startDay), end(endYear, endMonth, endDay)
{
	fixTimePeriod();
}

TimePeriod::TimePeriod(const TimePeriod& other)
{
	copyFrom(other);
}

TimePeriod& TimePeriod::operator=(const TimePeriod& other)
{
	copyFrom(other);
	return *this;
}

void TimePeriod::copyFrom(const TimePeriod& other)
{
	start = other.start;
	end = other.end;
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
}
void TimePeriod::setEnd(int endYear, int endMonth, int endDay)
{
	end.setDay(endDay);
	end.setMonth(endMonth);
	end.setYear(endYear);
}

void TimePeriod::print()
{
	start.print();
	cout << endl;
	end.print();
	cout << endl;
}

void TimePeriod::read(ifstream& f)
{
	start.read(f);
	end.read(f);
}

void TimePeriod::write(ofstream& f)
{
	start.write(f);
	end.write(f);
}