//
//  inorder.h
//  interview
//
//  Created by Bhattacharjee, Abhijit on 3/23/18.
//  Copyright © 2018 Bhattacharjee, Abhijit. All rights reserved.
//

#ifndef inorder_h
#define inorder_h
#include <memory>
#include <vector>
#include <list>
#include <queue>
#include <iterator>
#include <functional>
#include <initializer_list>
#include <limits>
/*
      0
    1    2
  3   4 5  6
 
 
 */
namespace BinTree {
    template<typename Ty>
    class TreeIterator: std::iterator<std::forward_iterator_tag, Ty> {
        typedef TreeIterator<Ty> iterator;
        typename Ty::allocator_type& arr;
        typename Ty::ptr_type index = 0;
    private:
        std::vector<size_t> inorder_;
        auto inorder(size_t index = 0) {
            if (index >= arr.size()) {
                return;
            }
            inorder(index * 2 + 1);
            inorder_.push_back(index);
            inorder(index * 2 + 2);
        }
    public:
        TreeIterator(typename Ty::allocator_type& arr,
                     typename Ty::ptr_type index): arr(arr), index(index) {
            inorder_.reserve(arr.size());
        }
        iterator operator++(int) {
            auto prev_index = index;
            index++;
            return iterator(arr, prev_index);
        }
        iterator operator++() {
            index++;
            return index;
        }
        bool operator==(iterator rhs) {
            return index == rhs.index;
        }
        bool operator!=(iterator rhs) {
            return index != rhs.index;
        }
        typename Ty::elem_type operator* () {
            if (inorder_.size() == 0) {
                inorder();
            }
            return arr[inorder_[index]];
        }
        typename Ty::ptr_type operator-> () {
            return index;
        }
    };
    class Tree {
    public:
        typedef int elem_type;
        typedef std::vector<elem_type> allocator_type;
        typedef size_t ptr_type;
        typedef BinTree::TreeIterator<Tree> iterator;
    private:
        allocator_type arr;
        /*
                  0
             1         2
          3     4    5    6
         7 8   9
         
         
         */
        ptr_type root = 0;
        
    public:
        Tree(std::initializer_list<elem_type> arr): arr(arr.begin(), arr.end()) {}
        auto common_ancestor(elem_type node1, elem_type node2) {
            std::queue<size_t> q4Node1, q4Node2;
            auto search_node = [&](elem_type node) {
                std::queue<size_t> queue;
                std::function<bool(size_t)> helper = [&](size_t index) {
                    if (arr[index] == node ) {
                        queue.push(index);
                        return true;
                    }
                    if (index >= arr.size()) {
                        return false;
                    }
                    if (helper(index * 2 + 1) || helper(index * 2 + 2)) {
                        queue.push(index);
                        return true;
                    }
                    return false;
                };
                helper(0);
                return queue;
            };
            q4Node1 = search_node(node1);
            q4Node2 = search_node(node2);
            for(auto idx1 = q4Node1.front(), idx2 = q4Node2.front();;) {
                if (idx1 == idx2) {
                    return arr[idx1];
                } else if (idx1 > idx2) {
                    q4Node1.pop();
                    idx1 = q4Node1.front();
                } else {
                    q4Node2.pop();
                    idx2 = q4Node2.front();
                }
            }
        }
        auto valid() {
            bool isValid = true;
            std::function<elem_type(size_t)> helper = [&](size_t index) {
                if (2*index + 1 >= arr.size() || 2*index + 2 >= arr.size() || isValid == false) {
                    return arr[index];
                }
                auto lmax = helper(2 * index + 1);
                auto rmax = helper(2 * index + 2);
                if (lmax > arr[index] || arr[index] > rmax) {
                    isValid = false;
                }
                return rmax;
            };
            helper(0);
            return isValid;
        }
        auto begin() {
            return BinTree::TreeIterator<Tree>(arr, root);
        }
        auto end() {
            return BinTree::TreeIterator<Tree>(arr, arr.size());
        }
    };
    int Main() {
        auto tree = BinTree::Tree({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
        for(auto it = tree.begin(); it != tree.end(); it++) {
            std::cout <<  *it << ", ";
        }
        assert(tree.common_ancestor(5, 7) == 0);
        assert(tree.common_ancestor(3, 4) == 1);
        assert(tree.common_ancestor(3, 3) == 3);
        assert(BinTree::Tree({10, 5, 15, 1, 7}).valid() == true);
        assert(BinTree::Tree({10, 5, 15, 1, 11}).valid() == false);
        assert(BinTree::Tree({10, 5, 15, 6, 7}).valid() == false);
        return 0;
    }
};

#endif /* inorder_h */
