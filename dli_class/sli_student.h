#pragma once
#ifndef sli_student_h
#define sli_student_h

#include <iostream>
#include <string>
#include "student.h"
struct sli_studentNode {
	sli_studentNode(const std::string& lname, const std::string& fname, double gpa, int cwid, sli_studentNode* next = nullptr);
	sli_studentNode(const student& st, sli_studentNode *next = nullptr);

	friend std::ostream& operator<<(std::ostream& os, const sli_studentNode& node);

	student st_;
	sli_studentNode* next_;
};

struct sli_studentList {
	sli_studentList();

	sli_studentNode* head_;
	size_t size_;
};
void sli_prepend(sli_studentList& sli, sli_studentNode* node);
void sli_prepend(sli_studentList& sli, const std::string & lname, const std::string & fname, double gpa, int cwid);

void sli_append(sli_studentList& sli, sli_studentNode* node);
void sli_append(sli_studentList& sli, const std::string & lname, const std::string & fname, double gpa, int cwid);
void sli_display(sli_studentList& sli);
sli_studentNode * sli_pop_back(sli_studentList & sli);
sli_studentNode * sli_pop_front(sli_studentList &sli);
void sli_rotateleft(sli_studentList & sli, size_t n);
void sli_rotateright(sli_studentList & sli, size_t n);
void sli_reverse(sli_studentList& sli);
void sli_insertAt(sli_studentList& sli, size_t index, sli_studentNode* node);
void sli_insertAt(sli_studentList& sli, size_t index_, const std::string & lname, const std::string & fname, double gpa, int cwid);
void sli_deleteAt(sli_studentList& sli, size_t index);

#endif // !sli_student_h