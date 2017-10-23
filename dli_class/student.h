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
	std::string fname()const;
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
struct dstudentNode {
	dstudentNode(const std::string& lname, const std::string& fname, double gpa, int cwid, dstudentNode* next = nullptr, dstudentNode* prev = nullptr);
	dstudentNode(const student& st, dstudentNode *next = nullptr, dstudentNode* prev = nullptr);
	friend std::ostream& operator<<(std::ostream& os, const dstudentNode& node);
	student st_;
	dstudentNode* next_;
	dstudentNode* prev_;
};

#endif // !student_h