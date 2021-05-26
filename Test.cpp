
#include "doctest.h"
#include "BinaryTree.hpp"
using namespace ariel;

#include <string>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;

TEST_CASE("empty tree and only root")
{
    BinaryTree<int> t;
    CHECK_THROWS(t.begin());
    CHECK_THROWS(t.begin_preorder());
    CHECK_THROWS(t.begin_inorder());
    CHECK_THROWS(t.begin_postorder());
    CHECK_THROWS(t.end());
    CHECK_THROWS(t.end_preorder());
    CHECK_THROWS(t.end_inorder());
    CHECK_THROWS(t.end_postorder());
    CHECK_THROWS(t.add_right(1, 2));
    CHECK_THROWS(t.add_left(1, 2));
    //only root
    t.add_root(1);
    BinaryTree<int>::pre_iterator i1;
    BinaryTree<int>::in_iterator i2;
    BinaryTree<int>::post_iterator i3;

    CHECK(t.end() == i2);
    CHECK(t.end_preorder() == i1);
    CHECK(t.end_inorder() == i2);
    CHECK(t.end_postorder() == i3);
    CHECK_THROWS(i1++);
    CHECK_THROWS(i2++);
    CHECK_THROWS(i3++);
    CHECK_THROWS(++i1);
    CHECK_THROWS(++i2);
    CHECK_THROWS(++i3);
    i1 = t.begin_preorder();
    i2 = t.begin_inorder();
    i3 = t.begin_postorder();
    i1++;
    ++i2;
    i3++;
    CHECK(t.end() == i2);
    CHECK(t.end_preorder() == i1);
    CHECK(t.end_inorder() == i2);
    CHECK(t.end_postorder() == i3);
}
TEST_CASE("stright tree")
{
    BinaryTree<int> t;
    t.add_root(0);
    for (int i = 0; i < 30; i++)
    {
        t.add_right(i, i + 1);
    }
    int i = 0;
    for (auto it = t.begin_preorder(); it != t.end_preorder(); ++it)
    {
        CHECK_EQ(*it, i++);
    }
    i = 0;
    for (auto it = t.begin_inorder(); it != t.end_inorder(); ++it)
    {
        CHECK_EQ(*it, i++);
    }
    i = 30;
    for (auto it = t.begin_postorder(); it != t.end_postorder(); ++it)
    {
        CHECK_EQ(*it, i--);
    }
}
TEST_CASE("random tree")
{
    srand(time(NULL));
    BinaryTree<char> t;
    t.add_root('a');

    //add 24 new random nodes to the tree
    vector<char> emplace_letter;
    for (char i = 'b'; i <= 'z'; i++)
    {
        emplace_letter.emplace_back(i);
    }
    for (int i = 0; i < 25; i++)
    {
        const size_t letter = (size_t)rand() % emplace_letter.size();
        int mone = 0;
        for (auto &i : t)
        {
            mone++;
        }
        int place = rand() % mone;
        const int right = rand() % 2;
        const char insert = emplace_letter.at(letter);
        auto iter = t.begin_preorder();
        while (place > 0)
        {
            ++iter;
            --place;
        }
        const char position = *iter;
        if (right)
        {
            CHECK_NOTHROW(t.add_right(position, insert));
            auto it = emplace_letter.begin();
            while (*it != insert)
            {
                ++it;
            }
            emplace_letter.erase(it);
        }
        else
        {
            CHECK_NOTHROW(t.add_left(position, insert));
            auto it = emplace_letter.begin();
            while (*it != insert)
            {
                ++it;
            }
            emplace_letter.erase(it);
        }
    }
}