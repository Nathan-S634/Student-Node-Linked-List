

#include "std_list_student.h"

dstudentNode::dstudentNode(const student & st, dstudentNode * next, dstudentNode * prev) :
	st_(st), next_(next), prev_(prev) {}

 dstudentNode::dstudentNode(const std::string& lname, const std::string& fname, double gpa, int cwid, dstudentNode* next, dstudentNode* prev) :
	st_(lname, fname, gpa, cwid), next_(next), prev_(prev) {}
 std::ostream& operator<<(std::ostream& os, const dstudentNode& node) {
	 return os << node.prev_ << "<-prev" << "(" << &node << ")" << node.st_ << "next->" << node.next_;
 }
std_list_Student::std_list_Student() {}
std_list_Student::std_list_Student(sli_studentList& sli) {
	//append all elements in sli list
	sli_studentNode* p = sli.head_;
	while (p != nullptr) {
		append(p->st_);
		//delete p->st_;
		p = p->next_;
	}
}
std_list_Student::std_list_Student(std::string filename) {
	std::ifstream file1(filename);
	std::string line;
	const char *token_s = ",=";
	if (file1.is_open()) {
		while (std::getline(file1, line)) {
			std::string lname = strtok(&line[0], token_s);
			std::string fname = strtok(NULL, token_s);
			std::string gpa = strtok(NULL, token_s);
			std::string cwid = strtok(NULL, token_s);
			append(lname, fname, stod(gpa), stoi(cwid));
		}
	}
	file1.close();
}
size_t std_list_Student::size() const
{
	return worker_.size();
}
void std_list_Student::save_file(std::string filename) {
	std::ofstream file1(filename);
	if (file1.is_open()) {
		char *token = ",=";
		for (dstudentNode * p : worker_) {
			file1 << p->st_.lname() << token << p->st_.fname() << token << p->st_.gpa() << token << p->st_.cwid() << std::endl;
		}
		file1.close();
	}
	else {
		std::cout << "Unable to open file\n";
	}
}


void std_list_Student::prepend(dstudentNode* node) {
	worker_.push_front(node);
}
void std_list_Student::prepend(std::string lname, std::string fname, double gpa, int cwid) {
	prepend(new dstudentNode(lname, fname, gpa, cwid));
}
void std_list_Student::append(dstudentNode* node) {
	worker_.push_back(node);
}
void std_list_Student::append(std::string lname, std::string fname, double gpa, int cwid) {
	append(new dstudentNode(lname, fname, gpa, cwid));
}
void std_list_Student::append(student & st) {
	append(new dstudentNode(st));
}
void std_list_Student::deleteAt(size_t index) {
	auto it = worker_.begin();
	if (index < worker_.size()) {
		std::advance(it, index);
		worker_.erase(it);
	}
}
void std_list_Student::insertAt(size_t index, dstudentNode* node) {
	auto it = worker_.begin();
	if (index >= worker_.size()) {
		append(node);
	}
	else {
		std::advance(it, index);
		worker_.insert(it, node);
	}
}
void std_list_Student::insertAt(size_t index, const std::string & lname, const std::string & fname, double gpa, int cwid) {
	insertAt(index, new dstudentNode(lname, fname, gpa, cwid, nullptr, nullptr));
}
void std_list_Student::reverse() {
	worker_.reverse();
}
void std_list_Student::display() {
	std::cout << *this;
}

void std_list_Student::display_reverse() {
	for (auto i = worker_.crbegin(); i != worker_.crend(); ++i) {
			std::cout << **i <<"\n";
		}
}
dstudentNode* std_list_Student::front()const {
	return (worker_.front());
}
dstudentNode* std_list_Student::back()const {
	return (worker_.back());
}
void std_list_Student::pop_front() {
	worker_.pop_front();
}
void std_list_Student::pop_back() {
	worker_.pop_back();
}
void std_list_Student::rotateleft(size_t n) {
	prepend(back());
	pop_back();
}
void std_list_Student::rotateright(size_t n){
	append(front());
	pop_front();
}

void std_list_Student::deleteList() {
	worker_.empty();
}
double std_list_Student::gpa_average() const{
	double average = 0;
	for (dstudentNode *p : worker_) {
		average = average + p->st_.gpa();
	}
	return (average/worker_.size());
}

std::ostream& operator<<(std::ostream& os, const std_list_Student& sl) {
	for (dstudentNode * p : sl.worker_) {
		os << *p << std::endl;
	}
	os << "{"<<"average gpa="<<sl.gpa_average()<<", size="<<sl.size()<<"}"<<std::endl;
	return os;
}
void convert_sli() {
	std::cout << "\n=====================================================\n";
	std::cout << "STUDENT LIST LAB ====================================\n";
	std::cout << "... singly-linked list\n\n";
	student anon;
	student al("Einstein", "Albert", 2.5, 12345);
	std::cout << "anonymous is: " << anon << "\n";
	std::cout << "al is: " << al << "\n\n";
	// make new sli_studentList, add new students and one existing
	sli_studentList sli;
	sli_prepend(sli, "Newton", "Isaac", 4.0, 54321);
	sli_append(sli, "Planck", "Max", 3.9, 23451);
	sli_append(sli, "Edison", "Thomas", 3.9, 34512);
	sli_append(sli, new sli_studentNode(al));

	sli_insertAt(sli, 0, new sli_studentNode("Gauss", "Karl F.", 3.8, 45123));
	sli_insertAt(sli, 4, new sli_studentNode("Wright", "Wilbur", 3.4, 51234));

	sli_display(sli); // display the students in the list

	std::cout << "converting to double linked list ====================================\n";
	std_list_Student dli_fromsli(sli);
	std::cout << dli_fromsli;
	dli_fromsli.display_reverse();
	std::cout << "\nend single to double link test\n";
}
void test_append() {
	std_list_Student a;
	/*for (int i = 0; i < 25; ++i)*/
	//{
	//	a.prepend("last1", "first1", 4.2, 1234);
	//}
	a.append("3append", "first", 3.4, 34556);
	a.append("2append", "first", 3.4, 34556);
	a.append("1append", "first", 3.4, 34556);
	std::cout << a;
	a.rotateright(1);
	a.rotateright(1);
	a.rotateright(1);
	std::cout << a;
	a.rotateleft(1);
	std::cout << a;
	std_list_Student b("testing.txt");
	std::cout << b;
	//a.display_reverse();
}

void test_for_lab_5() {
	std::cout << "\n================================================================\n";
	std::cout << "STUDENT LIST LAB w/REVERSAL and ROTATION =======================\n";
	std::cout << "... singly-linked list\n\n";

	student anon;
	student al("Einstein", "Albert", 2.5, 12345);

	std::cout << "anonymous is: " << anon << "\n";
	std::cout << "al is: " << al << "\n\n";

	// make new std_list_Student, add new students and one existing
	sli_studentList sli;
	sli_prepend(sli, "Newton", "Isaac", 4.0, 54321);
	sli_append(sli, "Planck", "Max", 3.9, 23451);
	sli_append(sli, "Edison", "Thomas", 3.9, 34512);
	sli_append(sli, new sli_studentNode(al));

	sli_insertAt(sli, 0, new sli_studentNode("Gauss", "Karl F.", 3.8, 45123));
	sli_insertAt(sli, 4, new sli_studentNode("Wright", "Wilbur", 3.4, 51234));

	sli_display(sli); // display the students in the list

	sli_reverse(sli);
	std::cout << "after reversing in place, the list is...\n";
	sli_display(sli);

	std::cout << "rotate left by one...\n";
	sli_rotateleft(sli, 1);
	sli_display(sli);
	std::cout << "rotate left by two...\n";
	sli_rotateleft(sli, 1);
	sli_display(sli);
	std::cout << "rotate left by three...\n";
	sli_rotateleft(sli, 1);
	sli_display(sli);

	std::cout << "rotate right by three...\n";
	sli_rotateright(sli, 3);
	sli_display(sli);

	std::cout << "\n================================================================\n";
	std::cout << "================================================================\n";
	std::cout << "STUDENT LIST LAB w/REVERSAL and ROTATION =======================\n";
	std::cout << "... doubly-linked list\n\n";

	student jeanluc("Picard", "Jean-Luc", 3.9, 13245);

	std::cout << "jean-luc is: " << jeanluc << "\n\n";

	// make new std_list_Student, add new students and one existing
	std_list_Student dli;
	dli.prepend("Riker", "Will", 3.7, 11223);

	dli.append("LaForge", "Geordie", 3.6, 51124);
	dli.append("Data", "Lt. Cmdr.", 4.0, 55543);
	dli.append(new dstudentNode(jeanluc));

	dli.insertAt(0, new dstudentNode("Crusher", "Beverly", 3.5, 11122));
	dli.insertAt(4, new dstudentNode("Worf", "Lieutenant", 3.4, 33434));

	dli.display(); // display the students in the list

	dli.reverse();
	std::cout << "after reversing doubly-linked list in place...\n";
	dli.display();

	std::cout << "rotate left by one...\n";
	dli.rotateleft(1);
	dli.display();

	std::cout << "rotate left by two...\n";
	dli.rotateleft(1);
	dli.display();

	std::cout << "rotate left by three...\n";
	dli.rotateleft(1);
	dli.display();
	std::cout << "rotate right by three...\n";
	dli.rotateright(3);
	dli.display();

	std::cout << "try to convert an sli to a dli...\n";
	std_list_Student dli_from_sli(sli);
	sli_display(sli);
	dli_from_sli.display();

	//std::cout << "try to convert an sli to a dli...\n"; //will be added in a new class later
	//std_list_Student sli_from_dli;
	//dli_toSingle(dli, sli_from_dli);
	//dli_display(dli);
	//sli_display(sli_from_dli);

	//std::cout << "test delete entire sli (in this case, sli_from_dli) ...\n";
	//sli_delete(sli_from_dli);
	//sli_display(sli_from_dli);
	std::cout << "\ntest delete entire dli (in this case, dli_from_sli) ...\n";
	dli_from_sli.deleteList();
	dli_from_sli.display();

	std::cout << "\t\t...done.\n";
}

void test_insert_delete() {
	//std_list_Student dli2;
	//dli2.append("0_last", "first", 2.6, 12345);
	//dli2.append("1_last", "first", 2.6, 12345);
	//dli2.append("2_last", "first", 2.6, 12345);
	//dli2.display();
	//dli2.display_reverse();
	//dli2.deleteAt(2);
	//dli2.display();
	//dli2.display_reverse();
	//delete &dli2;

	std_list_Student dli2;
	dli2.append("0_last", "first", 2.6, 12345);
	dli2.append("1_last", "first", 2.6, 12345);
	dli2.append("2_last", "first", 2.6, 12345);
	dli2.insertAt(1, "insert", "first", 2.6, 12345);
	dli2.display();
	std::cout << std::endl;
	dli2.display_reverse();
}
void refactor_test() {
	sli_studentList sli;
	sli_prepend(sli, "Newton", "Isaac", 4.0, 54321);
	sli_append(sli, "Planck", "Max", 3.9, 23451);
	sli_append(sli, "Edison", "Thomas", 3.9, 34512);
	sli_display(sli);
}

void std_list_Student::test() {
	convert_sli();
	test_append();
	test_for_lab_5();
	test_insert_delete();
	refactor_test();
}

void std_list_Student::test_link_worker()
{
	std_list_Student dli;
	dli.append("last1", "first1", 3.23, 5344);
	dli.append("last2", "first1", 3.23, 5344);
	dli.append("last3", "first1", 3.23, 5344);
	dli.insertAt(5,"insert1", "first1", 3.23, 5344);
	dli.deleteAt(2);
	dli.display();
	dli.reverse();
	dli.display();
	dli.rotateright(1);
	dli.display();
	dli.display_reverse();
}



