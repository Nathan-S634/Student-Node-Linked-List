#include "student.h"
dstudentNode::dstudentNode(const student & st, dstudentNode * next, dstudentNode * prev) :
	st_(st), next_(next), prev_(prev) {}

dstudentNode::dstudentNode(const std::string& lname, const std::string& fname, double gpa, int cwid, dstudentNode* next, dstudentNode* prev) :
	st_(lname, fname, gpa, cwid), next_(next), prev_(prev) {}
std::ostream& operator<<(std::ostream& os, const dstudentNode& node) {
	return os << node.prev_ << "<-prev" << "(" << &node << ")" << node.st_ << "next->" << node.next_;
}
student::student() : student("-", "-", 0, 0.0) {}
student::student(const std::string& lname, const std::string& fname, double gpa, size_t cwid) : lname_(lname), fname_(fname), gpa_(gpa), cwid_(cwid) {}
std::string student::fname() const { return fname_; }
std::string student::lname() const { return lname_; }
double student::gpa() const { return gpa_; }
int student::cwid() const { return cwid_; }
void student::gpa(double gpa) { gpa_ = gpa; }
std::ostream& operator <<(std::ostream& os, const student& st) {
	os << std::setprecision(2) << std::fixed;
	return os << "student[" << std::setw(18) << (st.lname_ + "," + st.fname_)
		<< ",gpa=" << std::setw(4) << st.gpa_ << ",cwid=" << st.cwid_ << "]";
}