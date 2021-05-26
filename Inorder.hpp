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
    class Inorder
    {
    private:
        Node<T> *m_pointer;
        queue<Node<T> *> st;
        u_int size = 0;

    public:
        T &operator*()
        { 
            return m_pointer->value;
        }

        T *operator->() const
        {
            return &(m_pointer->value);
        }
        const Inorder operator++(int)
        {
            Inorder tmp = *this;
            m_pointer = st.front();
            st.pop();
            return tmp;
        }
        Inorder &operator++()
        {
            m_pointer = st.front();
            st.pop();
            return *this;
        }
        bool operator==(const Inorder &rhs) const
        {
            return m_pointer == rhs.m_pointer;
        }

        bool operator!=(const Inorder &rhs) const
        {
            return m_pointer != rhs.m_pointer;
        }
        Inorder(Node<T> *root)
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
            fillStack(root->left);
            st.push(root);
            size++;
            fillStack(root->right);
        }
    };

}