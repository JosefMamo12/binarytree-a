#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdexcept>
#include "Preorder.hpp"
#include "Inorder.hpp"
#include "Postorder.hpp"
#include <queue>
#include <algorithm>
#include "Node.hpp"

using namespace std;

namespace ariel
{
    template <class T>
    class BinaryTree
    {
        Node<T> *root;
        int max_depth;

    public:
        struct cell_display
        {
            string valstr;
            bool present;
            cell_display() : present(false) {}
            cell_display(std::string valstr) : valstr(valstr), present(true) {}
        };
        BinaryTree() : root(nullptr),max_depth(0){};
        int get_max_depth() const { return root ? root->max_depth() : 0; }
        BinaryTree &add_root(T val)
        {
            Node<T> *curr = new Node<T>(val);
            if (root == nullptr)
            {
                root = curr;
            }
            else
            {
                root->value = val;
            }
            return *this;
        }
        Node<T> *search_address(Node<T> *curr, T val)
        {
            if (curr == nullptr)
            {
                return nullptr;
            }
            if (curr->value == val)
            {
                return curr;
            }

            Node<T> *res1 = search_address(curr->left, val);
            if (res1)
            {
                return res1;
            }
            Node<T> *res2 = search_address(curr->right, val);
            return res2;
        }

        bool search(Node<T> *curr, T val)
        {

            if (curr == nullptr)
            {
                return false;
            }
            if (curr->value == val)
            {
                return true;
            }

            bool res1 = search(curr->left, val);
            if (res1)
            {
                return true;
            }
            bool res2 = search(curr->right, val);
            return res2;
        }
        BinaryTree &add_right(T existVal, T val_to_add)
        {
            if (search(root, existVal))
            {
                Node<T> *temp = search_address(root, existVal);
                if (temp->right == nullptr)
                {
                    Node<T> *newNode = new Node<T>(val_to_add);
                    temp->right = newNode;

                }
                else
                {
                    temp->right->value = val_to_add;
                }
            }
            else
            {
                throw invalid_argument("There is no such a Node");
            }
            return *this;
        }
        BinaryTree &add_left(T existVal, T val_to_add)
        {
            if (search(root, existVal))
            {
                Node<T> *temp = search_address(root, existVal);
                if (temp->left == nullptr)
                {
                    Node<T> *newNode = new Node<T>(val_to_add);
                    temp->left = newNode;
                }
                else
                {
                    temp->left->value = val_to_add;
                }
            }
            else
            {
                throw invalid_argument("There is no such a Node");
            }
            return *this;
        }
        
        friend ostream &operator<<(ostream &os, const BinaryTree<T> &a)
        {


            return os;
        }

        Inorder<T> begin()
        {
            return Inorder<T>(root);
        }
        Inorder<T> end()
        {
            return Inorder<T>(nullptr);
        }

        Inorder<T> begin_inorder()
        {
            return Inorder<T>(root);
        }
        Inorder<T> end_inorder()
        {
            return Inorder<T>(nullptr);
        }
        Preorder<T> begin_preorder()
        {
            return Preorder<T>(root);
        }
        Preorder<T> end_preorder()
        {
            return Preorder<T>(nullptr);
        }
        Postorder<T> begin_postorder()
        {
            return Postorder<T>(root);
        }
        Postorder<T> end_postorder()
        {
            return Postorder<T>(nullptr);
        }
        void destroy_recorsivaly(Node<T> *node)
        {
            if (node)
            {
                destroy_recorsivaly(node->left);
                destroy_recorsivaly(node->right);
                delete node;
            }
        }
        ~BinaryTree()
        {
            destroy_recorsivaly(root);
        }
    };
}