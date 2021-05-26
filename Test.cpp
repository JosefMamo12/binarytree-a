#include "doctest.h"
#include <iostream>
#include <string>
#include "BinaryTree.hpp"
#include <time.h>
#include <vector>

using namespace std;
using namespace ariel;

TEST_CASE("Binarytree functions, functionality to being a generic")
{
    BinaryTree<int> int_tree;
    CHECK_THROWS(int_tree.add_right(5, 2)); /* should throw there is no root in this tree */
    CHECK_THROWS(int_tree.add_right(1, 2)); /* should throw there is no root in this tree */
    CHECK_NOTHROW(int_tree.add_root(5));    /* initialize a root */
    CHECK_NOTHROW(int_tree.add_right(5, 2));
    CHECK_NOTHROW(int_tree.add_left(5, 1));
    CHECK_THROWS(int_tree.add_left(3, 5));  /* there is no such a node with value 3 in this integer tree */
    CHECK_THROWS(int_tree.add_right(3, 5)); /* there is no such a node with value 3 in this tree */

    BinaryTree<char> char_tree;
    CHECK_THROWS(char_tree.add_right('5', '2')); /* should throw there is no root in this tree */
    CHECK_THROWS(char_tree.add_right('1', '2')); /* should throw there is no root in this tree */
    CHECK_NOTHROW(char_tree.add_root('5'));      /* initialize a root */
    CHECK_NOTHROW(char_tree.add_right('5', '2'));
    CHECK_NOTHROW(char_tree.add_left('5', '1'));

    BinaryTree<double> double_tree;
    CHECK_THROWS(double_tree.add_right(0.2, 1.5)); /* should throw there is no root in this tree */
    CHECK_THROWS(double_tree.add_right(1, 3.5));   /* should throw there is no root in this tree */
    CHECK_NOTHROW(double_tree.add_root(5.0));      /* initialize a root */
    CHECK_NOTHROW(double_tree.add_right(5.0, 1.2));
    CHECK_NOTHROW(double_tree.add_left(5.0, 43.21223));

    BinaryTree<string> str_tree;
    CHECK_THROWS(str_tree.add_right("0.2", "1.5")); /* should throw there is no root in this tree */
    CHECK_THROWS(str_tree.add_right("1", "3.5"));   /* should throw there is no root in this tree */
    CHECK_NOTHROW(str_tree.add_root("5.0"));        /* initialize a root */
    CHECK_NOTHROW(str_tree.add_right("5.0", "1.2"));
    CHECK_NOTHROW(str_tree.add_left("5.0", "blop"));
}
TEST_CASE("Iterators of the trees")
{
    SUBCASE("inorder iterator include the for range iterator")
    {
        BinaryTree<int> inoreder_integer_tree;
        inoreder_integer_tree.add_root(5)
            .add_right(5, 43)
            .add_left(5, -2)
            .add_right(-2, 11)
            .add_left(-2, 4)
            .add_left(43, 13)
            .add_right(43, 999);
        vector<int> excpected = {4, -2, 11, 5, 13, 43, 999};
        vector<int> actual;
        int first_number = *inoreder_integer_tree.begin_inorder();
        CHECK_EQ(first_number, 4);
        u_int i = 0;
        for (auto it = inoreder_integer_tree.begin_inorder(); it != inoreder_integer_tree.end_inorder(); ++it)
        {
            actual.resize(7);
            actual[i] = *it; // Checking the * operator
            i++;
        }
        for (i = 0; i < 7; i++)
        {
            CHECK(actual[i] == excpected[i]); // check if it is really in inorder format! as we see in the excpcted vector, full perfect tree with height of 3
        }
        inoreder_integer_tree.add_left(-2, 17); // override the leftest leaf
        first_number = *inoreder_integer_tree.begin_inorder();
        CHECK_EQ(first_number, 17); // so he should be the begin one

        /* for range checking with string tree */
        BinaryTree<string> inorder_string_tree;
        vector<string> expected_strings{"Josef", "String", "Tree", "Is", "The", "Best", "One"};
        inorder_string_tree.add_root("Josef")
            .add_left("Josef", "String")
            .add_left("String", "Tree")
            .add_left("Tree", "Is")
            .add_left("Is", "The")
            .add_left("The", "Best")
            .add_left("Best", "One");
        ;
        u_int checker = 0;
        for (const auto &z : inorder_string_tree)
        {
            CHECK_EQ(z, expected_strings[6 - checker]); // "One" is the most left sided leaf and the tree is only on his left side and root should be printed last
            checker++;
        }
    }
    SUBCASE("Preorder iterator")
    {
        u_int checker = 0;
        BinaryTree<char> preorder_char_tree;
        vector<char> expected_chars{'a', 'b', 'c', 'd', 'e', 'f', 'g', '(', ')', '#'};
        preorder_char_tree.add_root('a')
            .add_left('a', 'b')
            .add_left('b', 'c')
            .add_right('b', 'd')
            .add_right('a', 'e')
            .add_left('e', 'f')
            .add_left('f', 'g')
            .add_left('g', '(')
            .add_right('g', ')')
            .add_right(')', '#');
        cout << preorder_char_tree << endl;
        for (auto it = preorder_char_tree.begin_preorder(); it != preorder_char_tree.end_preorder(); it++) /* Checking here the the postfix ++ */
        {
            CHECK_EQ(expected_chars[checker], *it);
            checker++;
        }
        preorder_char_tree.add_root('*'); //Override the root
        char excpected_new_root = '*';
        char actual_new_root = *preorder_char_tree.begin_preorder();
        CHECK_EQ(excpected_new_root, actual_new_root);
        auto it = preorder_char_tree.begin_preorder();
        CHECK_EQ(preorder_char_tree.begin_preorder(), it++); // checking equal and  postfix++ functionality
        CHECK_NE(preorder_char_tree.begin_preorder(), it);   // checking if it changed to the second elemnt
        CHECK_EQ(expected_chars[1], *it);                    // see if it the real excpected second char
    }
    // SUBCASE("Postorder iterator")
    // {
    //     u_int checker = 0;
    //     BinaryTree<double> postorder_double_tree;
    //     vector<double> excpcted_double = {4, 11, -2.13, 13, 999, 43, 5.5};
    //     postorder_double_tree.add_root(5.5)
    //         .add_right(5.5, 43)
    //         .add_left(5.5, -2.13)
    //         .add_right(-2.13, 11)
    //         .add_left(-2.13, 4)
    //         .add_left(43, 13)
    //         .add_right(43, 999);
    //     for (auto it = postorder_double_tree.begin_postorder(); it != postorder_double_tree.end_postorder(); ++it)
    //     {
    //         cout << *it << endl;
    //         cout << excpcted_double[checker] << endl;
    //         //     if (*it == excpcted_double[checker])
    //         //     {
    //         //         cout << *it << " = " << excpcted_double[checker] << endl;
    //         //     }
    //         //     CHECK_EQ(excpcted_double[checker], *it);
    //         checker++;
    //     }
    //     cout << checker << endl;
    // }
}
