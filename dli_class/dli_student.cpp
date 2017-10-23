#include "dli_student.h"

studentList::studentList() : size_(0), head_(nullptr), tail_(nullptr) {}
studentList::studentList(sli_studentList& sli) {
	//append all elements in sli list
	sli_studentNode* p = sli.head_;
	while (p != nullptr) {
		append(p->st_);
		//delete p->st_;
		p = p->next_;
	}
}
studentList::studentList(std::string filename) {
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
void studentList::save_file(std::string filename) {
	std::ofstream file1(filename);
	if (file1.is_open()) {
		dstudentNode *p = head_;
		char *token = ",=";
		while (p != nullptr) {
			file1 << p->st_.lname() << token << p->st_.fname() << token << p->st_.gpa() << token << p->st_.cwid() << std::endl;;
			p = p->next_;
		}
		file1.close();
	}
	else {
		std::cout << "Unable to open file\n";
	}
}
dstudentNode* studentList::operator [] (int i) {
	if (i >= size_) {
		return nullptr;
	}
	else {
		int start = 0;
		dstudentNode* p = head_;
		while (start < i) {
			p = p->next_;
			++start;
		}
		return p;
	}
}
void studentList::print(int index) {
	dstudentNode* p = (*this)[index];
	if (p != nullptr) {
		std::cout << *p;
	}
}
void studentList::prepend(dstudentNode* node) {
	if (size_ == 0) {
		head_ = node;
		tail_ = node;
		++size_;
	}
	else {
		dstudentNode *tmp = head_;
		head_ = node;
		node->next_ = tmp;
		tmp->prev_ = node;
		++size_;
	}
}
void studentList::prepend(std::string lname, std::string fname, double gpa, int cwid) {
	prepend(new dstudentNode(lname, fname, gpa, cwid));
}
void studentList::append(dstudentNode* node) {
	if (size_ == 0) {
		prepend(node);
		return;
	}
	else {
		dstudentNode *select = (*this)[size_ - 1]; //select end of list
		select->next_ = node;
		tail_ = node;
		node->prev_ = select;
		node->next_ = nullptr;
		++size_;
	}
}
void studentList::append(std::string lname, std::string fname, double gpa, int cwid) {
	append(new dstudentNode(lname, fname, gpa, cwid));
}
void studentList::append(student & st) {
	append(new dstudentNode(st));
}
void studentList::deleteAt(size_t index) {
	if (size_ == 0) {//nothing to delete
		return;
	}
	else if (index >= size_) {//index out of range
		return;
	}
	else if ((*this)[index] == tail_) { //select back of list to delete
		dstudentNode* back = pop_back();
		delete back;
	}
	else if ((*this)[index] == head_) {//select front of list to delete
		dstudentNode* front = pop_front();
		delete front;
	}
	else { //selecting something in the middle of the list
		dstudentNode* select = (*this)[index];
		dstudentNode* select_next = (*this)[index + 1];
		dstudentNode* select_prev = ((index > 0) ? (*this)[index - 1] : nullptr);

		select_prev->next_ = select_next;
		select_next->prev_ = select_prev;
		--size_;
		delete select;
	}
}
void studentList::insertAt(size_t index, dstudentNode* node) {//needs complete recode
	if (size_ == 0 || index == 0) { //seelcted front of list
		prepend(node);
		return;
	}
	else if (index >= size_)//select index greater than list so append
	{
		append(node);
		return;
	}
	else {
		dstudentNode* select = (*this)[index - 1]; // index in is at least one
		dstudentNode* temp = select->next_;
		select->next_ = node;
		temp->prev_ = node;
		node->prev_ = select;
		node->next_ = temp;
		++size_;
	}
}
void studentList::insertAt(size_t index, const std::string & lname, const std::string & fname, double gpa, int cwid) {
	insertAt(index, new dstudentNode(lname, fname, gpa, cwid, nullptr, nullptr));
}
void studentList::reverse() {
	dstudentNode* temp_sw = nullptr;
	dstudentNode* temp = nullptr;
	dstudentNode* select = head_;
	tail_ = head_;
	while (select != nullptr) {
		temp = select->next_;
		temp_sw = select->prev_;
		select->prev_ = select->next_;
		select->next_ = temp_sw;
		head_ = select;

		select = temp;
	}
}
void studentList::display() {
	std::cout << *this;
}

void studentList::display_reverse() {
	dstudentNode* p = tail_;
	while (p != nullptr) {
		std::cout << *p << std::endl;
		p = p->prev_;
	}
}
dstudentNode* studentList::pop_front() {
	if (size_ == 0) {
		return nullptr;
	}
	else if (size_ == 1) {
		dstudentNode* p = head_;
		head_ = nullptr;
		tail_ = nullptr;
		p->next_ = nullptr;
		p->prev_ = nullptr;
		--size_;
		return p;
	}
	else {
		dstudentNode* p = head_;
		head_ = head_->next_;
		head_->prev_ = nullptr;

		p->next_ = nullptr;
		p->prev_ = nullptr;
		--size_;
		return p;
	}
}
dstudentNode* studentList::pop_back() {
	if (size_ == 0) {
		return nullptr;
	}
	else if (size_ == 1) {
		dstudentNode* p = tail_;
		head_ = nullptr;
		tail_ = nullptr;
		p->next_ = nullptr;
		p->prev_ = nullptr;
		--size_;
		return p;
	}
	else {
		dstudentNode* p = tail_;
		tail_ = tail_->prev_;
		tail_->next_ = nullptr;

		p->next_ = nullptr;
		p->prev_ = nullptr;
		--size_;
		return p;
	}
}
void studentList::rotateleft(size_t n) {
	int i = 0;
	while (i++ < n) {
		dstudentNode* p = pop_front();
		if (p != nullptr) {
			append(p);
		}
	}
}
void studentList::rotateright(size_t n)
{
	int i = 0;
	while (i++ < n) {
		dstudentNode* p = pop_back();
		if (p != nullptr) {
			prepend(p);
		}
	}
}

void studentList::deleteList() {
	if (size_ == 0) {
		return;
	}
	dstudentNode *p = (*this)[0];
	while (p != nullptr) {
		dstudentNode* temp = p;
		p = p->next_;
		delete temp;
	}
	head_ = nullptr;
	tail_ = nullptr;
}
double studentList::gpa_average(dstudentNode * node) {
	if (node == nullptr) {
		return 1;
	}
	else if (node == head_) {
		return ((node->st_.gpa() + gpa_average(node->next_)) / size_);
	}
	else {
		return ((node->st_.gpa()) + gpa_average(node->next_));
	}
}

std::ostream& operator<<(std::ostream& os, const studentList& sl) {
	dstudentNode* p = sl.head_;
	double average = 0;
	while (p != nullptr) {
		os << *p << std::endl;
		average = average + (p->st_.gpa());
		p = p->next_;
	}
	os << "{" << "average gpa=" << (average / sl.size_) << ", size=" << sl.size_ << "}" << std::endl;
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

	studentList dli_fromsli(sli);
	std::cout << dli_fromsli;
	dli_fromsli.display_reverse();
	std::cout << "\nend single to double link test\n";
}
void test_append() {
	studentList a;
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
	studentList b("testing.txt");
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

	// make new studentList, add new students and one existing
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

	// make new studentList, add new students and one existing
	studentList dli;
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
	studentList dli_from_sli(sli);
	sli_display(sli);
	dli_from_sli.display();

	//std::cout << "try to convert an sli to a dli...\n"; //will be added in a new class later
	//studentList sli_from_dli;
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
	//studentList dli2;
	//dli2.append("0_last", "first", 2.6, 12345);
	//dli2.append("1_last", "first", 2.6, 12345);
	//dli2.append("2_last", "first", 2.6, 12345);
	//dli2.display();
	//dli2.display_reverse();
	//dli2.deleteAt(2);
	//dli2.display();
	//dli2.display_reverse();
	//delete &dli2;

	studentList dli2;
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
void studentList::test() {
	convert_sli();
	test_append();
	test_for_lab_5();
	test_insert_delete();
	refactor_test();
}