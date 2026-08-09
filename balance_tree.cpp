//#include here
// balance_tree.cpp
// This file contains the implementation of the balance tree algorithm
#include "balance_tree.h"
#include <stdexcept>
template<class T>
bool BinaryTree<T>::search(const T& value) const
{
       std::shared_ptr<BinaryTreeNode<T>> current = root;
       if(current.get() == nullptr)
       {
            return false;
       }

       while(current.get() != nullptr)
       {
        
            if(current.get()->data == value)
            {
                return true;
            }
            else if (current.get()->data > value)
            {
                current = std::make_shared<BinaryTreeNode<T>>(current.get()->left);
            }
            else
            {
                current = std::make_shared<BinaryTreeNode<T>>(current.get()->right);
            }
       }
       return false;
}


template<class T>
void BinaryTree<T>::insert(const T& value)
{
    auto newNode = std::make_shared<BinaryTreeNode<T>>(new BinaryTreeNode<T>(value));//new pointer tp the new node
    //if the tree is empty, set the root to the new node
    if(root.get() == nullptr)
    {
        root = newNode;
        return ;
    }

    auto target = std::make_shared<BinaryTreeNode<T>>(root.get());//the insert target position
    if(target.get()->data == value)
    {
        target.get()->data = value;
    }
    else if (target.get()-data < value && target.get()->right.get() != nullptr)
    {
        target = std::make_shared<BinaryTreeNode<T>>(target.get()->right);
    }
    else if (target.get()->data > value && target.get()->left.get() != nullptr)
    {
        target = std::make_shared<BinaryTreeNode<T>>(target.get()->left);
    }
    else if (target.get()->data < value && target.get()->right.get() == nullptr)
    {
        target.get()->right = newNode;
        target.get()->right.get()->parent = target;
    }
    else if (target.get()->data > value && target.get()->left.get() == nullptr)
    {
        target.get()->left = newNode;
        target.get()->left.get()->parent = target;
    }
}

template<class T>
void BinaryTree<T>::remove(const T& value)
{
    // Implement the remove function for the binary tree
    // This function should find the node with the given value and remove it from the tree
    // You may need to handle different cases such as removing a leaf node, a node with one child, or a node with two children

    if(!search(value))
    {
        throw std::runtime_error("value not found in the tree");
    }

    auto target = std::make_shared<BinaryTreeNode<T>>(root.get());
    while(target.get()->data != value)
    {
        if(target.get()->data < value)
        {
            target = std::make_shared<BinaryTreeNode<T>>(target.get()->right);
        }
        else
        {
            target = std::make_shared<BinaryTreeNode<T>>(target.get()->left);
        }
    }

    if(target.get()->right == nullptr)
    {
        target.get()->left.get()->parent = target.get()->parent;
        target.get()->parent.get()->left = target.get()->left;
    }
    else if(target.get()->left == nullptr)
    {
        target.get()->right.get()->parent = target.get()->parent;
        target.get()->parent.get()->right = target.get()->right;
    }
    else
    {
        auto successor = std::make_shared<BinaryTreeNode<T>>(target.get()->right);
        while(successor.get()->left != nullptr)
        {
            successor = std::make_shared<BinaryTreeNode<T>>(successor.get()->left);
        }
        target.get()->data = successor.get()->data;
        if(successor.get()->parent.get()->left == successor)
        {
            successor.get()->parent.get()->left = successor.get()->right;
            if(successor.get()->right != nullptr)
            {
                successor.get()->right.get()->parent = successor.get()->parent;
            }
        }
        else
        {
            successor.get()->parent.get()->right = successor.get()->right;
            if(successor.get()->right != nullptr)
            {
                successor.get()->right.get()->parent = successor.get()->parent;
            }
        }
    }
}