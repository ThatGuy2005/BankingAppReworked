#pragma once
#ifndef DATE_H
#define DATE_H

struct Date
{
	int year;
	int mount;
	int day;
	int hour;
	int minute;
	friend std::ostream& operator<<(std::ostream& out, const Date& obj)
	{
		out << obj.hour << ':' << obj.minute << ": " << obj.mount << '/' << obj.day << '/' << obj.year << " | ";
		return out;
	}
	inline std::string convert()
	{
		std::string s;
		s = std::to_string(hour) + ':' + std::to_string(minute) + ": " + std::to_string(mount)
			+ '/' + std::to_string(day) + '/' + std::to_string(year) + " | ";
		return s;
	}
};

#endif