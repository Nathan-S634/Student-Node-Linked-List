#pragma once
#ifndef dli_student_h
#define dli_student_h


#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include "student.h"
#include <list>
#include "sli_student.h"

struct dstudentNode {
	dstudentNode(const std::string& lname, const std::string& fname, double gpa, int cwid, dstudentNode* next=nullptr, dstudentNode* prev=nullptr);
	dstudentNode(const student& st, dstudentNode *next=nullptr, dstudentNode* prev = nullptr);
	friend std::ostream& operator<<(std::ostream& os, const dstudentNode& node);
	student st_;
	dstudentNode* next_;
	dstudentNode* prev_;
};


class studentList {
public:
	studentList();
	studentList(sli_studentList& sli);
	studentList(std::string filename);
	size_t size() const;
	dstudentNode* head() const;
	void save_file(std::string filename);
	dstudentNode* operator [] (int i);
	void print(int index);
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
	dstudentNode* pop_front();
	dstudentNode* pop_back();
	void rotateright(size_t n);
	void rotateleft(size_t n);
	void deleteList();
	double gpa_average(dstudentNode* node);
	
	static void test();
	static void test_link_worker();
	
	
	

	friend std::ostream& operator<<(std::ostream& os, const studentList& sl);

private:
	size_t size_;
	dstudentNode * head_;
	dstudentNode * tail_;
	std::list<dstudentNode *> worker_;
};

#endif // !dli_student_h