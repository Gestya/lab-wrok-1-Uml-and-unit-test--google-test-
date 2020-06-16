#pragma once

#include <iostream>
#include <algorithm>

namespace splay
{

struct Node
{
    Node()
        : number(0)
        , left(nullptr)
        , right(nullptr)
    {
    }

    Node(int n)
        : number(n)
        , left(nullptr)
        , right(nullptr)
    {
    }

    int number { 0 };
    Node* left { nullptr };
    Node* right { nullptr };
}; // struct Node


class Tree
{
public:
    bool insert(int number)
    {
        if (!root)
        {
            root = new Node(number);;
            return true;
        }

        root = splay(number, root);

        if (number < root->number)
        {
            splay::Node* new_node = new Node(number);
            new_node->left = root->left;
            new_node->right = root;
            root->left = nullptr;
            root = new_node;
        }
        else if (number > root->number)
        {
            splay::Node* new_node = new Node(number);
            new_node->right = root->right;
            new_node->left = root;
            root->right = nullptr;
            root = new_node;
        }
        else
        {
            // such value is already exist
            return false;
        }

        return true;
    }

    Node* search(int number)
    {
        if (!root)
            return nullptr;

        root = splay(number, root);

        return (root->number == number) ? root : nullptr;
    }

    bool erase(int number)
    {
        if (!root)
            return false;

        Node* temp;
        root = splay(number, root);
        if (number != root->number)
            return false;
        else
        {
            if (!root->left)
            {
                temp = root;
                root = root->right;
            }
            else
            {
                temp = root;
                root = splay(number, root->left);
                root->right = temp->right;
            }
            delete temp;
            return true;
        }
    }

    int height() const
    {
        return height_(root);
    }

    Node* get_root()
    {
        return root;
    }

private:
    Node* root = {nullptr};

    Node* search_(int key, Node* node)
    {
        if (!node)
            return nullptr;
        if (key == node->number)
            return node;
        else if (key < node->number)
            return search_(key, node->left);
        else
            return search_(key, node->right);
    }

    int height_(const Node* node) const
    {
        if (!node)
            return 0;
        int left = (node->left) ? height_(node->left) : 0;
        int right = (node->right) ? height_(node->right) : 0;
        return  std::max(left + 1, right + 1);
    }

    Node* RR_rotate(Node* k2)
    {
        Node* k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        return k1;
    }

    Node* LL_rotate(Node* k2)
    {
        Node* k1 = k2->right;
        k2->right = k1->left;
        k1->left = k2;
        return k1;
    }

    Node* splay(int key, Node* node)
    {
        if (!node)
            return nullptr;

        Node header;
        Node* LeftTreeMax = &header;
        Node* RightTreeMin = &header;
        while (1)
        {
            if (key < node->number)
            {
                if (!node->left)
                    break;
                if (key < node->left->number)
                {
                    node = RR_rotate(node);
                    if (!node->left)
                        break;
                }
                RightTreeMin->left = node;
                RightTreeMin = RightTreeMin->left;
                node = node->left;
                RightTreeMin->left = nullptr;
            }
            else if (key > node->number)
            {
                if (!node->right)
                    break;
                if (key > node->right->number)
                {
                    node = LL_rotate(node);
                    if (!node->right)
                        break;
                }
                LeftTreeMax->right = node;
                LeftTreeMax = LeftTreeMax->right;
                node = node->right;
                LeftTreeMax->right = nullptr;
            }
            else
                break;
        }
        LeftTreeMax->right = node->left;
        RightTreeMin->left = node->right;
        node->left = header.right;
        node->right = header.left;
        return node;
    }
}; // class tree

} // namespace splay
