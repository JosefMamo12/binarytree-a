#pragma once
#include <iostream>
#include "BinaryTree.hpp"

using namespace std;

namespace ariel
{
    template <class T>
    class Node
    {
    public:
        T value;
        Node *right;
        Node *left;

    public:
        Node(T &v)
            : value(v), right(nullptr), left(nullptr)
        {
        }
    };
}
