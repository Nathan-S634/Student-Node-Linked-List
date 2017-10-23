#pragma once
#ifndef std_list_student_h
#define std_list_student_h

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include "student.h"
#include <list>
#include "sli_student.h"

class std_list_Student {
public:
	std_list_Student();
	std_list_Student(sli_studentList& sli);
	std_list_Student(std::string filename);
	size_t size() const;
	dstudentNode* front() const;
	dstudentNode* back() const;
	void save_file(std::string filename);
	void prepend(dstudentNode* node);//done
	void prepend(std::string lname, std::string fname, double gpa, int cwid);//done
	void append(dstudentNode* node);//done
	void append(std::string lname, std::string fname, double gpa, int cwid);//done
	void append(student & st);//done
	void deleteAt(size_t index);
	void insertAt(size_t index, dstudentNode* node);
	void insertAt(size_t index, const std::string & lname, const std::string & fname, double gpa, int cwid);
	void reverse();
	void display();
	void display_reverse();
	void pop_front();
	void pop_back();
	void rotateright(size_t n);
	void rotateleft(size_t n);
	void deleteList();
	double gpa_average() const; //done

	static void test();
	static void test_link_worker();

	friend std::ostream& operator<<(std::ostream& os, const std_list_Student& sl);

private:
	std::list<dstudentNode *> worker_;
};

#endif // !std_list_student_h