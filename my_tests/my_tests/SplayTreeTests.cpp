#include "gtest/gtest.h"
#include "SplayTree.h"

#include <iostream>
#include <cstdio>
#include <vector>

namespace
{
    struct Pair
    {
        int value;
        int height;
    };
} // anonymous namespace

// ------------------------------------------------------------------------
TEST(SplayNode, StaticAllocation)
{
    const int init_value{ 555 };

    splay::Node node_def;
    EXPECT_EQ(0, node_def.number);
    EXPECT_EQ(nullptr, node_def.left);
    EXPECT_EQ(nullptr, node_def.right);

    splay::Node node_with_param(init_value);
    EXPECT_EQ(init_value, node_with_param.number);
    EXPECT_EQ(nullptr, node_with_param.left);
    EXPECT_EQ(nullptr, node_with_param.right);
}

// ------------------------------------------------------------------------
TEST(SplayNode, DynamicAllocation)
{
    const int init_value{ 555 };

    splay::Node* node_def = new splay::Node();
    EXPECT_NE(nullptr, node_def);
    EXPECT_EQ(0, node_def->number);
    EXPECT_EQ(nullptr, node_def->left);
    EXPECT_EQ(nullptr, node_def->right);
    delete node_def;

    splay::Node* node_with_param = new splay::Node(init_value);
    EXPECT_NE(nullptr, node_with_param);
    EXPECT_EQ(init_value, node_with_param->number);
    EXPECT_EQ(init_value, node_with_param->number);
    EXPECT_EQ(nullptr, node_with_param->left);
    EXPECT_EQ(nullptr, node_with_param->right);
    delete node_with_param;
}

// ------------------------------------------------------------------------
TEST(SplayTree, EmptyTree)
{
    {
        splay::Tree tree;
        EXPECT_EQ(nullptr, tree.get_root());
        EXPECT_EQ(0, tree.height());
    }

    {
        splay::Tree* ptr_tree = new splay::Tree();
        EXPECT_EQ(nullptr, ptr_tree->get_root());
        EXPECT_EQ(0, ptr_tree->height());
        delete ptr_tree;
    }
}

// --- Right ------------------------------------------------------------------------
//    (1)
//      \
//      (2)
//        \
//        (3)
TEST(SplayTree, Insert_Rightt)
{
    std::vector<Pair> data = { {3, 1}, {2, 2}, {1, 3} };
    splay::Tree tree;
    EXPECT_EQ(0, tree.height());
    EXPECT_EQ(nullptr, tree.get_root());
    for (const auto d : data)
    {
        EXPECT_TRUE(tree.insert(d.value));
        EXPECT_EQ(d.height, tree.height());
        EXPECT_NE(nullptr, tree.get_root());
        EXPECT_FALSE(tree.insert(d.value));
    }
}

// --- Left ------------------------------------------------------------------------
//      (3)
//      /
//    (2)
//    /
//  (1)
TEST(SplayTree, Insert_Left)
{
    std::vector<Pair> data = { {1, 1}, {2, 2}, {3, 3} };
    splay::Tree tree;
    EXPECT_EQ(0, tree.height());
    EXPECT_EQ(nullptr, tree.get_root());
    for (const auto d : data)
    {
        EXPECT_TRUE(tree.insert(d.value));
        EXPECT_EQ(d.height, tree.height());
        EXPECT_NE(nullptr, tree.get_root());
        EXPECT_FALSE(tree.insert(d.value));
    }
}

// --- Center ------------------------------------------------------------------------
//      (2)
//      / \
//    (1) (3)
TEST(SplayTree, Insert_Center)
{
    std::vector<Pair> data = { {1, 1}, {3, 2}, {2, 2} };
    splay::Tree tree;
    EXPECT_EQ(0, tree.height());
    EXPECT_EQ(nullptr, tree.get_root());
    for (const auto d : data)
    {
        EXPECT_TRUE(tree.insert(d.value));
        EXPECT_EQ(d.height, tree.height());
        EXPECT_NE(nullptr, tree.get_root());
        EXPECT_FALSE(tree.insert(d.value));
    }
}

// ------------------------------------------------------------------------
TEST(SplayTree, Search_EmptyTree)
{
    splay::Tree tree;
    EXPECT_EQ(0, tree.height());
    EXPECT_EQ(nullptr, tree.get_root());

    EXPECT_EQ(nullptr, tree.search(0));

    EXPECT_EQ(0, tree.height());
    EXPECT_EQ(nullptr, tree.get_root());
}

// ------------------------------------------------------------------------
//   (1)                (3)
//     \                / 
//     (2)  ==(3)==>  (2)
//       \            /
//       (3)        (1)
TEST(SplayTree, Search_PositiveCase_RightToLeft)
{
    // Initialization
    std::vector<Pair> data = { {3, 1}, {2, 2}, {1, 3} };
    splay::Tree tree;
    EXPECT_EQ(0, tree.height());
    EXPECT_EQ(nullptr, tree.get_root());
    for (const auto d : data)
    {
        EXPECT_TRUE(tree.insert(d.value));
        EXPECT_EQ(d.height, tree.height());
        EXPECT_NE(nullptr, tree.get_root());
        EXPECT_FALSE(tree.insert(d.value));
    }

    // -----------------
    const int init_root_value{ 1 };
    const int key{ 3 };
    EXPECT_NE(nullptr, tree.get_root());
    EXPECT_EQ(init_root_value, tree.get_root()->number);
    splay::Node* result = tree.search(key);
    EXPECT_NE(nullptr, result);
    EXPECT_EQ(key, result->number);
    EXPECT_NE(nullptr, tree.get_root());
    EXPECT_EQ(key, tree.get_root()->number);
}

// ------------------------------------------------------------------------
//   (1)
//     \              (2)
//     (2)  ==(3)==>  / \
//       \          (1)  (3)
//       (3)
TEST(SplayTree, Search_PositiveCase_RightToCentral)
{
    // Initialization
    
    std::vector<Pair> data = { {3, 1}, {2, 2}, {1, 3} };
    splay::Tree tree;
    EXPECT_EQ(0, tree.height());
    EXPECT_EQ(nullptr, tree.get_root());
    for (const auto d : data)
    {
        EXPECT_TRUE(tree.insert(d.value));
        EXPECT_EQ(d.height, tree.height());
        EXPECT_NE(nullptr, tree.get_root());
        EXPECT_FALSE(tree.insert(d.value));
    }

    // -----------------
    const int init_root_value{ 1 };
    const int key{ 2 };
    EXPECT_NE(nullptr, tree.get_root());
    EXPECT_EQ(init_root_value, tree.get_root()->number);
    splay::Node* result = tree.search(key);
    EXPECT_NE(nullptr, result);
    EXPECT_EQ(key, result->number);
    EXPECT_NE(nullptr, tree.get_root());
    EXPECT_EQ(key, tree.get_root()->number);
}

// ------------------------------------------------------------------------
//   (1)                (3)
//     \                / 
//     (2)  ==(5)==>  (2)
//       \            /
//       (3)        (1)
TEST(SplayTree, Search_NegativeCase_RightToLeft)
{
    // Initialization
    std::vector<Pair> data = { {3, 1}, {2, 2}, {1, 3} };
    splay::Tree tree;
    EXPECT_EQ(0, tree.height());
    EXPECT_EQ(nullptr, tree.get_root());
    for (const auto d : data)
    {
        EXPECT_TRUE(tree.insert(d.value));
        EXPECT_EQ(d.height, tree.height());
        EXPECT_NE(nullptr, tree.get_root());
        EXPECT_FALSE(tree.insert(d.value));
    }

    // -----------------
    const int init_root_value{ 1 };
    const int wanted_key{ 5 };
    const int real_key{ 3 };
    EXPECT_NE(nullptr, tree.get_root());
    EXPECT_EQ(init_root_value, tree.get_root()->number);
    splay::Node* result = tree.search(wanted_key);
    EXPECT_EQ(nullptr, result);
    EXPECT_NE(nullptr, tree.get_root());
    EXPECT_EQ(real_key, tree.get_root()->number);
}

// ------------------------------------------------------------------------
TEST(SplayTree, Erase_EmptyTree)
{
    splay::Tree tree;
    EXPECT_EQ(0, tree.height());
    EXPECT_EQ(nullptr, tree.get_root());

    EXPECT_FALSE(tree.erase(0));

    EXPECT_EQ(0, tree.height());
    EXPECT_EQ(nullptr, tree.get_root());
}

// ------------------------------------------------------------------------
//      (5)
//      /            (3)
//    (3)  ==(5)==>  /
//    /            (1)
//  (1)
TEST(SplayTree, Erase_PositiveCase_EraceOnce)
{
    // Initialization
    std::vector<Pair> data = { {1, 1}, {3, 2}, {5, 3} };
    splay::Tree tree;
    EXPECT_EQ(0, tree.height());
    EXPECT_EQ(nullptr, tree.get_root());
    for (const auto d : data)
    {
        EXPECT_TRUE(tree.insert(d.value));
        EXPECT_EQ(d.height, tree.height());
        EXPECT_NE(nullptr, tree.get_root());
        EXPECT_FALSE(tree.insert(d.value));
    }

    // -----------------
    const int init_root_value{ 5 };
    const int erasing_value{ 5 };
    const int new_root_value{ 3 };
    EXPECT_NE(nullptr, tree.get_root());
    EXPECT_EQ(init_root_value, tree.get_root()->number);
    EXPECT_TRUE(tree.erase(erasing_value));
    EXPECT_NE(nullptr, tree.get_root());
    EXPECT_EQ(new_root_value, tree.get_root()->number);
}

// ------------------------------------------------------------------------
//      (5)
//      /            (3)
//    (3)  ==(5)==>  /  ==(1)==> (3) ==(3)==> null
//    /            (1)
//  (1)
TEST(SplayTree, Erase_PositiveCase_EraseAllKeys)
{
    // Initialization
    std::vector<Pair> data = { {1, 1}, {3, 2}, {5, 3} };
    splay::Tree tree;
    EXPECT_EQ(0, tree.height());
    EXPECT_EQ(nullptr, tree.get_root());
    for (const auto d : data)
    {
        EXPECT_TRUE(tree.insert(d.value));
        EXPECT_EQ(d.height, tree.height());
        EXPECT_NE(nullptr, tree.get_root());
        EXPECT_FALSE(tree.insert(d.value));
    }

    // -----------------
    const int init_root_value{ 5 };
    const int erasing_value1{ 5 };
    const int new_root_value1{ 3 };
    const int erasing_value2{ 1 };
    const int new_root_value2{ 3 };
    const int erasing_value3{ 3 };
    EXPECT_NE(nullptr, tree.get_root());
    EXPECT_EQ(init_root_value, tree.get_root()->number);
    EXPECT_TRUE(tree.erase(erasing_value1));
    EXPECT_NE(nullptr, tree.get_root());
    EXPECT_EQ(new_root_value1, tree.get_root()->number);
    EXPECT_TRUE(tree.erase(erasing_value2));
    EXPECT_NE(nullptr, tree.get_root());
    EXPECT_EQ(new_root_value2, tree.get_root()->number);
    EXPECT_TRUE(tree.erase(erasing_value3));
    EXPECT_EQ(nullptr, tree.get_root());
}

// ------------------------------------------------------------------------
//      (5)        (1)
//      /            \
//    (3)  ==(0)==>  (3)
//    /                \
//  (1)                (5)
TEST(SplayTree, Erase_NegativeCase)
{
    // Initialization
    std::vector<Pair> data = { {1, 1}, {3, 2}, {5, 3} };
    splay::Tree tree;
    EXPECT_EQ(0, tree.height());
    EXPECT_EQ(nullptr, tree.get_root());
    for (const auto d : data)
    {
        EXPECT_TRUE(tree.insert(d.value));
        EXPECT_EQ(d.height, tree.height());
        EXPECT_NE(nullptr, tree.get_root());
        EXPECT_FALSE(tree.insert(d.value));
    }

    // -----------------
    const int init_root_value{ 5 };
    const int erasing_value{ 0 };
    const int new_root_value{ 1 };
    EXPECT_NE(nullptr, tree.get_root());
    EXPECT_EQ(init_root_value, tree.get_root()->number);
    EXPECT_FALSE(tree.erase(erasing_value));
    EXPECT_NE(nullptr, tree.get_root());
    EXPECT_EQ(new_root_value, tree.get_root()->number);
}

// ------------------------------------------------------------------------
//      (5)                           (5)
//      /            (3)              /
//    (3)  ==(4)==>  / \  ==(4)==>  (3)  ==[REPEAT]==> ...
//    /            (1) (5)          /
//  (1)                           (1)
TEST(SplayTree, Erase_NegativeCase_Repeatedly)
{
    // Initialization
    std::vector<Pair> data = { {1, 1}, {3, 2}, {5, 3} };
    splay::Tree tree;
    EXPECT_EQ(0, tree.height());
    EXPECT_EQ(nullptr, tree.get_root());
    for (const auto d : data)
    {
        EXPECT_TRUE(tree.insert(d.value));
        EXPECT_EQ(d.height, tree.height());
        EXPECT_NE(nullptr, tree.get_root());
        EXPECT_FALSE(tree.insert(d.value));
    }

    // -----------------
    const int init_root_value{ 5 };
    const int erasing_value{ 4 };
    const int new_root_value_1{ 3 };
    const int new_root_value_2{ 5 };

    EXPECT_NE(nullptr, tree.get_root());
    EXPECT_EQ(init_root_value, tree.get_root()->number);
    for (int i = 0; i < 3; ++i)
    {
        EXPECT_FALSE(tree.erase(erasing_value));
        EXPECT_NE(nullptr, tree.get_root());
        EXPECT_EQ(new_root_value_1, tree.get_root()->number);
        EXPECT_FALSE(tree.erase(erasing_value));
        EXPECT_NE(nullptr, tree.get_root());
        EXPECT_EQ(new_root_value_2, tree.get_root()->number);
    }
}

// ------------------------------------------------------------------------
TEST(SplayTree, TheMostComplexScenario)
{
    // Empty tree
    splay::Tree tree;
    EXPECT_EQ(0, tree.height());
    EXPECT_EQ(nullptr, tree.get_root());

    // Add first element
    EXPECT_TRUE(tree.insert(21));
    EXPECT_EQ(1, tree.height());
    EXPECT_NE(nullptr, tree.get_root());
    EXPECT_FALSE(tree.insert(21));

    // Add a lot of elements
    std::vector<int> numbers{ 15, 12, 10, 20, 14, 26, 24, 17, 18, 27, 16 };
    for (const auto n : numbers)
    {
        EXPECT_TRUE(tree.insert(n));
        EXPECT_FALSE(tree.insert(n));
    }

    //---------------------------------------
    // And now does test the result tree
    //---------------------------------------

    // --- Root ---------------------
    splay::Node* root = tree.get_root();
    EXPECT_EQ(16, root->number);
    EXPECT_NE(nullptr, root->left);
    EXPECT_NE(nullptr, root->right);

    // --- Left ---------------------
    // 15
    splay::Node* node_15 = root->left;
    EXPECT_EQ(15, node_15->number);
    EXPECT_NE(nullptr, node_15->left);
    EXPECT_EQ(nullptr, node_15->right);
    // 14
    splay::Node* node_14 = node_15->left;
    EXPECT_EQ(14, node_14->number);
    EXPECT_NE(nullptr, node_14->left);
    EXPECT_EQ(nullptr, node_14->right);
    // 12
    splay::Node* node_12 = node_14->left;
    EXPECT_EQ(12, node_12->number);
    EXPECT_NE(nullptr, node_12->left);
    EXPECT_EQ(nullptr, node_12->right);
    // 10
    splay::Node* node_10 = node_12->left;
    EXPECT_EQ(10, node_10->number);
    EXPECT_EQ(nullptr, node_10->left);
    EXPECT_EQ(nullptr, node_10->right);

    // --- Right ---------------------
    // 26
    splay::Node* node_26 = root->right;
    EXPECT_EQ(26, node_26->number);
    EXPECT_NE(nullptr, node_26->left);
    EXPECT_NE(nullptr, node_26->right);
    // 27
    splay::Node* node_27 = node_26->right;
    EXPECT_EQ(27, node_27->number);
    EXPECT_EQ(nullptr, node_27->left);
    EXPECT_EQ(nullptr, node_27->right);
    // 18
    splay::Node* node_18 = node_26->left;
    EXPECT_EQ(18, node_18->number);
    EXPECT_NE(nullptr, node_18->left);
    EXPECT_NE(nullptr, node_18->right);
    // 17
    splay::Node* node_17 = node_18->left;
    EXPECT_EQ(17, node_17->number);
    EXPECT_EQ(nullptr, node_17->left);
    EXPECT_EQ(nullptr, node_17->right);
    // 20
    splay::Node* node_20 = node_18->right;
    EXPECT_EQ(20, node_20->number);
    EXPECT_EQ(nullptr, node_20->left);
    EXPECT_NE(nullptr, node_20->right);
    // 24
    splay::Node* node_24 = node_20->right;
    EXPECT_EQ(24, node_24->number);
    EXPECT_NE(nullptr, node_24->left);
    EXPECT_EQ(nullptr, node_24->right);
    // 21
    splay::Node* node_21 = node_24->left;
    EXPECT_EQ(21, node_21->number);
    EXPECT_EQ(nullptr, node_21->left);
    EXPECT_EQ(nullptr, node_21->right);
}