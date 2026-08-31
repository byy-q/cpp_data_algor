//This is the header file for the balance tree data structure implementation. 
//It contains the class definition and function declarations for the balance tree algorithm.
//the balance binary search tree,a basic tree structure of the AVltree and red-black tree, is a self-balancing binary search tree.
#ifndef BALANCE_TREE_H__
#define BALANCE_TREE_H__
#include<memory>//smart pointer
#include<iostream>
#include<vector>
#include<algorithm>
template<class T>
struct  BinaryTreeNode
{
    
    T data;
    std::shared_ptr<BinaryTreeNode<T>> left;
    std::shared_ptr<BinaryTreeNode<T>> right;
    std::shared_ptr<BinaryTreeNode<T>> parent;

    BinaryTreeNode(const T& value = 0) : data(value), left(nullptr), right(nullptr), parent(nullptr) {}
};

//The claim of the binartTree class
template<class T>
struct BinaryTree
{
    public:
        BinaryTree() : root(nullptr){}
        void insert(const T& value);
        void remove(const T& value);
        bool search(const T& value) const;
        ~BinaryTree();
        void inorderTraversal();

    private:
        
        std::shared_ptr<BinaryTreeNode<T>> root;
                
};


//AVLtree Node
template<class T>
struct AVLtreeNode
{
    T data;
    AVLtreeNode* left;
    AVLtreeNode* right;
    AVLtreeNode* parent;
    typedef enum{LUNBALANCED = -2,Lheavy = -1,BALANCE = 0,Rheavy = 1,RUNBALANCED = 2}BalanceFactor;
    BalanceFactor balanceFactor;
    int height;
    AVLtreeNode(const T& value = 0) : data(value),height(1), left(nullptr), right(nullptr), parent(nullptr), balanceFactor(BALANCE) {}
};

//class AVLtree
template<class T>
class AVLtree
{
    public:
        AVLtree() : root(nullptr){}
        ~AVLtree() = default;
        void insert(const T& value);
        void remove(const T& value);
        AVLtreeNode<T>* search(const T& value) const;
        bool contains(const T& value) const;
        AVLtreeNode<T>* getRoot() const { return root; }
        
    private:
        AVLtreeNode<T>* root;
        void Delete(const T& value);
        void postOrderTraversal(AVLtreeNode<T>* node,void (*visit)(AVLtreeNode<T>*));
        void updateHeight(AVLtreeNode<T>* node);
        void updataBalanceFactor(AVLtreeNode<T>* node);
        void LLrotate(AVLtreeNode<T>* node);
        void RRrotate(AVLtreeNode<T>* node);
        void LRrotate(AVLtreeNode<T>* node);
        void RLrotate(AVLtreeNode<T>* node);
        void R0rotate(AVLtreeNode<T>* node);
        void R1rotate(AVLtreeNode<T>* node);
        void R2rotate(AVLtreeNode<T>* node);
        void L0rotate(AVLtreeNode<T>* node);
        void L1rotate(AVLtreeNode<T>* node);
        void L2rotate(AVLtreeNode<T>* node);
};


template<class T>
AVLtreeNode<T>* AVLtree<T>::search(const T& value) const
{
    AVLtreeNode<T>* current = root;
    AVLtreeNode<T>* last = nullptr;
    while (current != nullptr)
    {
        last = current;
        if (value == current->data)
            return current;
        else if (value < current->data)
            current = current->left;
        else
            current = current->right;
    }
    return last;
}

template<class T>
bool AVLtree<T>::contains(const T& value) const
{
    AVLtreeNode<T>* node = search(value);
    return node != nullptr && node->data == value;
}

template<class T>
void AVLtree<T>::insert(const T& value)
{
    AVLtreeNode<T>* newNode = new(std::nothrow) AVLtreeNode<T>(value);
    if(newNode == nullptr)
    {
        std::cerr << "Memory allocation failed for new node." << std::endl;
        return;
    }

    if(root == nullptr)
    {
        root = newNode;
        return;
    }

    AVLtreeNode<T>* parent = search(value);
    if(parent->data > value) // new node insert on the left side of the parent
    {
        parent->left = newNode;
        newNode->parent = parent;
    }
    else if(parent->data < value) // new node insert on the right side of the parent
    {
        parent->right = newNode;
        newNode->parent = parent;
    }

    postOrderTraversal(root, updateHeight);
    postOrderTraversal(root, updataBalanceFactor);

    AVLtreeNode<T>* unbalanceNode = newNode->parent;
    while (unbalanceNode != nullptr && unbalanceNode->balanceFactor != AVLtreeNode<T>::LUNBALANCED
        && unbalanceNode->balanceFactor != AVLtreeNode<T>::RUNBALANCED)
    {
        unbalanceNode = unbalanceNode->parent;
    }
    if (unbalanceNode == nullptr)
        return;

    if (unbalanceNode->balanceFactor == AVLtreeNode<T>::LUNBALANCED)
    {
        if (newNode->data < unbalanceNode->left->data)
            LLrotate(unbalanceNode);
        else
            LRrotate(unbalanceNode);
    }
    else if (unbalanceNode->balanceFactor == AVLtreeNode<T>::RUNBALANCED)
    {
        if (newNode->data > unbalanceNode->right->data)
            RRrotate(unbalanceNode);
        else
            RLrotate(unbalanceNode);
    }
    return;
}

template<class T>
void AVLtree<T>::Delete(const T& value)
{
    AVLtreeNode<T>* target = search(value);
    if(target == nullptr || target->data != value)
    {
        std::cerr<<"Value not found in the tree."<<std::endl;
        return;
    }

    if(target->left == nullptr && target->right == nullptr)//leaf
        target ->parent->left == target ? target->parent->left = nullptr : target->parent->right = nullptr;
    else if(target->left == nullptr )
    {
        AVLtreeNode<T>* MINrightChild = target->right;
        while(MINrightChild->left != nullptr)
            MINrightChild = MINrightChild->left;
        target->data = MINrightChild->data;
        MINrightChild->data = value;
        Delete(MINrightChild->data);
    }
    else 
    {
        AVLtreeNode<T>* MAXleftChild = target->left;
        while(MAXleftChild->right != nullptr)
            MAXleftChild = MAXleftChild->right;
        target->data = MAXleftChild->data;
        MAXleftChild->data = value;
        Delete(MAXleftChild->data);
    }
}
template<class T>
void AVLtree<T>::remove(const T& value)
{
    Delete(value);
    postOrderTraversal(root,updateHeight);
    postOrderTraversal(root,updataBalanceFactor);
    std::vector<AVLtreeNode<T>*> unbalanceNodes;
    AVLtreeNode<T>* current = root;
    while(current != nullptr)
    {
        unbalanceNodes.push_back(current);
        if(value < current->data)
            current = current->left;
        else if(value > current->data)
            current = current->right;
        else
            break;
    }
    //unbalanceNodes contains the path from root to the node that was deleted
    for(int i = unbalanceNodes.size() - 1;i >= 0;i--)
    {
        if(unbalanceNodes[i]->balanceFactor == AVLtreeNode<T>::LUNBALANCED && value > unbalanceNodes[i]->data && unbalanceNodes[i]->left -> balanceFactor 
            == AVLtreeNode<T>::BALANCE)
        {
            R0rotate(unbalanceNodes[i]);
            break;
        }
        else if(unbalanceNodes[i]->balanceFactor == AVLtreeNode<T>::LUNBALANCED && value > unbalanceNodes[i]->data && unbalanceNodes[i]->left -> balanceFactor 
            == AVLtreeNode<T>::Lheavy)
        {
            R1rotate(unbalanceNodes[i]);
            
        }
        else if(unbalanceNodes[i]->balanceFactor == AVLtreeNode<T>::LUNBALANCED && value > unbalanceNodes[i]->data && unbalanceNodes[i]->left -> balanceFactor 
            == AVLtreeNode<T>::Rheavy)
        {
            R2rotate(unbalanceNodes[i]);
        }
        else if(unbalanceNodes[i]->balanceFactor == AVLtreeNode<T>::RUNBALANCED && value < unbalanceNodes[i]->data && unbalanceNodes[i]->right -> balanceFactor 
            == AVLtreeNode<T>::BALANCE)
        {
            L0rotate(unbalanceNodes[i]);
            break;
        }
        else if(unbalanceNodes[i]->balanceFactor == AVLtreeNode<T>::RUNBALANCED && value < unbalanceNodes[i]->data && unbalanceNodes[i]->right -> balanceFactor 
            == AVLtreeNode<T>::Rheavy)
        {
            L1rotate(unbalanceNodes[i]);
        }
        else if(unbalanceNodes[i]->balanceFactor == AVLtreeNode<T>::RUNBALANCED && value < unbalanceNodes[i]->data && unbalanceNodes[i]->right -> balanceFactor 
            == AVLtreeNode<T>::Lheavy)
        {
            L2rotate(unbalanceNodes[i]);
        }
    }
}

template<class T>
void AVLtree<T>::updataBalanceFactor(AVLtreeNode<T>* node)
{
    int leftHeight = node->left ? node->left->height : 0;
    int rightHeight = node->right ? node->right->height : 0;
    node->balanceFactor = static_cast<typename AVLtreeNode<T>::BalanceFactor>(leftHeight - rightHeight);
}


template<class T>
void AVLtree<T>::updateHeight(AVLtreeNode<T>* node)
{
    node->height = std::max(node->left == nullptr? 0 :node->left->height,node->right == nullptr? 0 : node->right->height) + 1;
}

template<class T>
void AVLtree<T>::postOrderTraversal(AVLtreeNode<T>* node, void (*visit)(AVLtreeNode<T>*))
{
    if (node == nullptr)
        return;
    postOrderTraversal(node->left, visit);
    postOrderTraversal(node->right, visit);
    visit(node);
}


template<class T>
void AVLtree<T>::LLrotate(AVLtreeNode<T>*node)
{
    AVLtreeNode<T>* Lnode = node->left;
    AVLtreeNode<T>* LRnode = Lnode->right;
    AVLtreeNode<T>* parent = node->parent;
    if(parent == nullptr)
    {
        root = Lnode;
    }
    else if(parent->data > node->data)
    {
        parent->left = Lnode;
    }
    else
    {
        parent->right = Lnode;
    }
    Lnode->parent = parent;
    if (LRnode)
        LRnode->parent = node;
    node->left = LRnode;
    Lnode->right = node;
    node->parent = Lnode;
}

template<class T>
void AVLtree<T>::LRrotate(AVLtreeNode<T>* node)
{
    AVLtreeNode<T>* Lnode = node->left;
    AVLtreeNode<T>* parent = node->parent;
    AVLtreeNode<T>* LRnode = Lnode->right;
    if (LRnode == nullptr)
        return;

    if (parent == nullptr)
        root = LRnode;
    else if (parent->data > node->data)
        parent->left = LRnode;
    else
        parent->right = LRnode;

    LRnode->parent = parent;
    node->left = LRnode->right;
    if (LRnode->right)
        LRnode->right->parent = node;
    LRnode->left = Lnode;
    Lnode->parent = LRnode;
    Lnode->right = nullptr;
    node->parent = LRnode;
    LRnode->right = node;
}


template<class T>
void AVLtree<T>::RRrotate(AVLtreeNode<T>* node)
{
    AVLtreeNode<T>* Rnode = node->right;
    AVLtreeNode<T>* RLnode = Rnode->left;
    AVLtreeNode<T>* parent = node->parent;
    if(parent == nullptr)
    {
        root = Rnode;
    }
    else if(parent->data > node->data)
    {
        parent->left = Rnode;
    }
    else
    {
        parent->right = Rnode;
    }
    Rnode->parent = parent;
    if (RLnode)
        RLnode->parent = node;
    node->right = RLnode;
    Rnode->left = node;
    node->parent = Rnode;
}

template<class T>
void AVLtree<T>::RLrotate(AVLtreeNode<T>* node)
{
    AVLtreeNode<T>* Rnode = node->right;
    AVLtreeNode<T>* parent = node->parent;
    AVLtreeNode<T>* RLnode = Rnode->left;
    if (RLnode == nullptr)
        return;

    if (parent == nullptr)
        root = RLnode;
    else if (parent->data > node->data)
        parent->left = RLnode;
    else
        parent->right = RLnode;

    RLnode->parent = parent;
    node->right = RLnode->left;
    if (RLnode->left)
        RLnode->left->parent = node;
    RLnode->right = Rnode;
    Rnode->parent = RLnode;
    Rnode->left = nullptr;
    node->parent = RLnode;
    RLnode->left = node;
}

template<class T>
void AVLtree<T>::R0rotate(AVLtreeNode<T>* node)
{
    LLrotate(node);
}

template<class T>
void AVLtree<T>::R1rotate(AVLtreeNode<T>* node)
{
    LLrotate(node);
}

template<class T>
void AVLtree<T>::R2rotate(AVLtreeNode<T>* node)
{
    LRrotate(node);
}

template<class T>
void AVLtree<T>::L0rotate(AVLtreeNode<T>* node)
{
    RRrotate(node);
}

template<class T>
void AVLtree<T>::L1rotate(AVLtreeNode<T>* node)
{
    RRrotate(node);
}

template<class T>
void AVLtree<T>::L2rotate(AVLtreeNode<T>* node)
{
    RLrotate(node);
}


#endif // BALANCE_TREE_H__