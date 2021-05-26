#pragma once
#include "BinaryTree.hpp"
#include <iostream>
#include <queue>
#include <vector>
#include <list>
#include "Node.hpp"

using namespace std;

namespace ariel
{
    template <class T>
    class Preorder
    {
    private:
        Node<T> *m_pointer;
        queue<Node<T> *> st;
        unsigned int size = 0;

    public:
        T &operator*()
        {
            return m_pointer->value;
        }

        T *operator->() const
        {
            return &(m_pointer->value);
        }
        const Preorder operator++(int)
        {
            Preorder tmp = *this;
            m_pointer = st.front();
            st.pop();
            return tmp;
        }
        Preorder &operator++()
        {
            m_pointer = st.front();
            st.pop();
            return *this;
        }
        bool operator==(const Preorder &rhs) const
        {
            return m_pointer == rhs.m_pointer;
        }

        bool operator!=(const Preorder &rhs) const
        {
            return m_pointer != rhs.m_pointer;
        }
        Preorder(Node<T> *root)
        {
            if (root != nullptr)
            {
                fillStack(root);
                m_pointer = st.front();
                st.pop();
            }
            else
            {
                m_pointer = nullptr;
            }
        }
        void fillStack(Node<T> *root)
        {
            if (root == nullptr)
                return;
            st.push(root);
            size++;
            fillStack(root->left);
            fillStack(root->right);
        }
    };

}