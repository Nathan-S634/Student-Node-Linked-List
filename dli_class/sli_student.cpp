#include "sli_student.h"

sli_studentNode::sli_studentNode(const std::string& lname, const std::string& fname, double gpa, int cwid, sli_studentNode* next) :
	st_(lname, fname, gpa, cwid), next_(next) {}
sli_studentNode::sli_studentNode(const student& st, sli_studentNode *next) :
	st_(st), next_(next) {}

std::ostream& operator<<(std::ostream& os, const sli_studentNode& node) {
	return os << "(" << &node << ")" << node.st_ << "next->" << node.next_;
}
sli_studentList::sli_studentList() :
	head_(nullptr), size_(0) {}
void sli_prepend(sli_studentList& sli, sli_studentNode* node) {
	node->next_ = sli.head_;
	sli.head_ = node;
	++sli.size_;
}
void sli_prepend(sli_studentList& sli, const std::string & lname, const std::string & fname, double gpa, int cwid) {
	sli_prepend(sli, new sli_studentNode(lname, fname, gpa, cwid, nullptr));
}

void sli_append(sli_studentList& sli, sli_studentNode* node) {
	if (sli.size_ == 0) {
		sli_prepend(sli, node);
	}
	else {
		sli_studentNode *sli_c = sli.head_;
		while (sli_c->next_ != nullptr) {
			sli_c = sli_c->next_;
		}
		++sli.size_;
		sli_c->next_ = node;
	}
}
void sli_append(sli_studentList& sli, const std::string & lname, const std::string & fname, double gpa, int cwid) {
	sli_append(sli, new sli_studentNode(lname, fname, gpa, cwid, nullptr));
}
void sli_display(sli_studentList& sli) {
	sli_studentNode* sli_c = sli.head_;
	while (sli_c != nullptr) {
		std::cout << *sli_c << std::endl;
		sli_c = sli_c->next_;
	}
}
sli_studentNode * sli_pop_back(sli_studentList & sli) {
	sli_studentNode * p = sli.head_;
	if (sli.size_ == 0) {
		return nullptr;
	}
	else {
		sli_studentNode* prev = nullptr;
		while (p->next_ != nullptr) {
			prev = p;
			p = p->next_;
		}
		--sli.size_;
		prev->next_ = nullptr;
		p->next_ = nullptr;
		return p;
	}
}
sli_studentNode * sli_pop_front(sli_studentList &sli) {
	sli_studentNode* p = sli.head_;
	if (sli.size_ == 0) {
		return nullptr;
	}
	else {
		p = sli.head_;
		sli.head_ = sli.head_->next_;
		--sli.size_;
		p->next_ = nullptr;
		return p;
	}
}
void sli_rotateleft(sli_studentList & sli, size_t n) {
	int i = 0;
	while (i < n) {
		sli_studentNode* p = sli_pop_front(sli);
		if (p != nullptr) {
			sli_append(sli, p);
			++i;
		}
	}
}
void sli_rotateright(sli_studentList & sli, size_t n) {
	int i = 0;
	while (i < n) {
		sli_studentNode* p = sli_pop_back(sli);
		if (p != nullptr) {
			sli_prepend(sli, p);
			++i;
		}
	}
}
void sli_reverse(sli_studentList& sli) {
	sli_studentNode* next = nullptr;
	sli_studentNode* temp = nullptr;
	sli_studentNode* select = sli.head_;
	while (select != nullptr) {
		temp = select->next_;
		select->next_ = next;
		sli.head_ = select;

		next = select;
		select = temp;
	}
}
void sli_insertAt(sli_studentList& sli, size_t index, sli_studentNode* node) {
	if (index <= sli.size_) {
		if (index == 0) {
			sli_prepend(sli, node);
			return;
		}
		else {
			sli_studentNode *tmp = sli.head_;
			while (tmp != nullptr && index > 1) {
				tmp = tmp->next_;
				--index;
			}
			node->next_ = tmp->next_;
			tmp->next_ = node;
			++sli.size_;
		}
	}
	else {
		sli_append(sli, node);
	}
}
void sli_insertAt(sli_studentList& sli, size_t index_, const std::string & lname, const std::string & fname, double gpa, int cwid) {
	sli_insertAt(sli, index_, new sli_studentNode(lname, fname, gpa, cwid, nullptr));
}
void sli_deleteAt(sli_studentList& sli, size_t index) {
	sli_studentNode* tmp = sli.head_;
	if (index == 0 && sli.size_ > 0) {
		sli.head_ = tmp->next_;
		--sli.size_;
	}
	else if (index <= sli.size_) {
		while (index > 1) {
			tmp = tmp->next_;
			--index;
		}
		--sli.size_;
		tmp->next_ = tmp->next_->next_;
	}
}