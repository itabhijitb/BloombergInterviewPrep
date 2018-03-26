#pragma once
#include <forward_list>
#include <initializer_list>
#include <tuple>
#include <vector>
#include <algorithm>
#include <memory>
#include <cassert>
namespace CopyList {

	template<typename T>
	class ArbidListIter
		: public std::iterator<std::forward_iterator_tag, T>
	{
		typedef ArbidListIter<T>  iterator;
		std::shared_ptr<T> pos_;
	public:
		ArbidListIter() : pos_(nullptr) {}
		ArbidListIter(std::shared_ptr<T> v) : pos_(v) {}
		~ArbidListIter() {}

		iterator  operator++(int) /* postfix */ { 
			auto prev_pos_ = pos_;
			pos_ = pos_->next.pos_;
			return prev_pos_;
		}
		iterator& operator++()    /* prefix */ { 
			pos_ = pos_->next.pos_;
			return *this; 
		}
		reference operator* () const { return *pos_; }
		std::shared_ptr<T>   operator->() const { return pos_; }
		iterator  operator+ (difference_type v)   const { return pos_ + v; }
		bool      operator==(const iterator& rhs) const { return pos_ == rhs.pos_; }
		bool      operator!=(const iterator& rhs) const { return pos_ != rhs.pos_; }
	};
	struct Node {
		ArbidListIter<Node> next = nullptr;
		ArbidListIter<Node> arbid = nullptr;
		int elem = 0;
		Node(int elem) : elem(elem) {
		};
	};
	class ArbidList {
		
		typedef ArbidListIter<Node > iterator;
		iterator root = nullptr;
	public:
		ArbidList(std::initializer_list<int> il) {
			std::vector<iterator> arbidPtr;
			for (auto& elem : il) {
				if (root ==end()) {
					root = std::make_shared<Node>(elem);
				} else {
					push_front(elem);
				}
				arbidPtr.push_back(begin());
			}
			std::random_shuffle(arbidPtr.begin(), arbidPtr.end());
			auto it_ap = arbidPtr.begin();
			for (auto & elem : *this) {
				elem.arbid = *(it_ap++);
				std::cout << elem.elem << '\t' << elem.arbid->elem << std::endl;
			}
		}
		iterator begin() {
			return iterator(root);
		}
		iterator begin() const {
			return iterator(root);
		}
		iterator end() const {
			return iterator(nullptr);
		}
		void push_front(const Node&  node) {
			auto &pNewNode = std::make_shared<Node>(node.elem);
			pNewNode->next = root;
			root = pNewNode;
		}
		bool insert(iterator pos, Node node) {
			auto &pNewNode = std::make_shared<Node>(node.elem);
			if (pos != end()) {
				pNewNode->next = pos->next;
				pos->next = pNewNode;
				return true;
			}
			else {
				return false;
			}
		}
		Node& front() {
			return *root;
		}
		bool operator==(const ArbidList& rhs) const {
			auto& it = begin();
			bool result = true;
			for (auto& elem : rhs) {
				result = it->arbid->elem == elem.arbid->elem;
				result &= it->elem == elem.elem;
				std::cout << it->arbid->elem << '\t' << elem.arbid->elem << '\t' << it->elem << '\t' << elem.elem << std::endl;
				it++;
			}
			return result;
		}
		ArbidList clone() {
			ArbidList clone{};
			clone.push_front(front());
			auto it_clone = clone.begin();
			it_clone->arbid = begin();
			auto& it_ll = next(begin());
			root->next = it_clone;
			for (; it_ll != end(); ) {
				clone.insert(it_clone, *it_ll);
				it_clone++;
				it_clone->arbid = it_ll;
				it_ll++->next = it_clone;
			}
			for (auto & it_clone = clone.begin(); it_clone != clone.end(); it_clone++) {
				it_clone->arbid = next(it_clone->arbid->arbid);
				std::cout << it_clone->elem << '\t' << it_clone->arbid->elem << std::endl;
			}
			return clone;
		}

		ArbidList clone1() {
			ArbidList clone{};
			for (auto& it = begin();it != end(); it = next(next(it))) {
				insert(it, Node(*it));
			}
			for (auto& it = begin(); it != end(); it = next(next(it))) {
				it->next->arbid = it->arbid->next;
			}
			auto clone_root = next(begin());
			for (auto& it_orig = begin(), it_clone = next(it_orig);
				it_orig != end() && it_clone != end();
				it_orig = next(next(it_orig)), it_clone = next(next(it_clone))) {
				it_orig->next = it_clone->next;
				it_clone->next = it_orig->next->next;
				if (it_orig == end() || it_clone == end()) {
					break;
				}
			}
			return clone;
		}
	};

	int Main() {
		CopyList::ArbidList al{ 3, 1, 4, 5, 9, 2, 6, 7, 8 };
		CopyList::ArbidList clone = al.clone1();
		//assert(clone == al);
		return 0;
	}
}