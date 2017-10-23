#pragma once
#ifndef student_h
#define student_h
#include <iostream>
#include <string>
#include <iomanip>

class student {
public:
	student();
	student(const std::string& lname, const std::string& fname, double gpa, size_t cwid);
	std::string fname()const ;
	std::string lname()const;
	double gpa() const;
	int cwid() const;
	void gpa(double gpa);
	friend std::ostream& operator <<(std::ostream& os, const student& st);
private:
	std::string fname_;
	std::string lname_;
	double gpa_;
	int cwid_;
};

#endif // !student_h