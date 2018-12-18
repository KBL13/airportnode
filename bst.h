/*Tips - use queues, declare queue of bstnode, insert root and print it then take in childrens and pop the front, */



#ifndef COP4530_BST_H
#define COP4530_BST_H

#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <list>
#include <vector>
#include <string>
#include <sstream>
#include <utility>
#include <queue>

using namespace std;
namespace cop4530
{
template <typename T>
class BST 
{
public:
    
    BST(int th=default_threshold_value); 
    BST(const string input, int th=default_threshold_value); 
    BST(const BST& rhs); // copy constructor. 
    BST(BST&& rhs); // move constructor. 
    ~BST();
    void buildFromInputString(const string input);
    // operators

    // copy assignment operator
    const BST & operator= (const BST &);

    // move assignment operator
    const BST & operator=(BST &&);

    bool empty(); // return true if there is no element in the queue; return false otherwise 

    void printInOrder() const;// print out the elements in the tree in the in-order traversal.
    void printLevelOrder() const;// print out the elements in the tree in the level-order traversal.
    int numOfNodes() const;// return the number of nodes in the tree.
    int height() const;// return the height of the tree.
    void makeEmpty();// delete all nodes from the tree (make the tree empty)
    void insert(const T& v);// insert v into the tree.
    void insert(T &&v);// insert v into the tree (move instead of copy)
    void remove(const T& v);// delete value v from the tree.
    bool contains(const T& v);// search to determine if v is the tree.

private:
    struct BSTnode
    {
        T element;
        BSTnode *left;
        BSTnode *right;
        int height;
        int searchcount;

        BSTnode( const T & ele, BSTnode *lt, BSTnode *rt, int h = 0 )
          : element{ ele }, left{ lt }, right{ rt }, height{ h } { }
        
        BSTnode( T && ele, BSTnode *lt, BSTnode *rt, int h = 0 )
          : element{ std::move( ele ) }, left{ lt }, right{ rt }, height{ h } { }
    };

    int threshold; 
    BSTnode *root;

    void printInOrder(BSTnode *t) const
    {
        if( t != nullptr )
        {
            printInOrder(t->left);
            cout << t->element << " ";
            printInOrder(t->right);
        }
    }

    void printLevelOrder(BSTnode *t) const //Found and need to modify
    {
        if (t != nullptr)
        {
            queue<BSTnode*> x;
            x.push(t);
            while (!x.empty())
            {
                BSTnode * temp = x.front();
                x.pop();
                cout<< temp->element << " ";

                if (temp->left) 
                {
                    x.push(temp->left);
                }
                if (temp->right)
                {
                    x.push(temp->right);
                }
            }
        }
    }

    void makeEmpty(BSTnode* &t)
    {
        if( t != nullptr )
        {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        t = nullptr;
    }

    void insert(const T& v, BSTnode *&t)
    {   
        //std::cout << "INSERT" << std::endl;
        if( t == nullptr)
        {

            t = new BSTnode{v, nullptr, nullptr};
            t->searchcount = 0;
        }
        else if(v < t->element)
        {
            insert(v, t->left);
        }
        else if(t->element < v)
        {
            insert(v, t->right);
        } 
        else
        {

        }
    }

    void insert(T&& v, BSTnode *&t)
    {
        if(t == nullptr)
        {
            t = new BSTnode{std::move(v), nullptr, nullptr};
        }
        else if(v < t->element)
        {
            insert(std::move(v), t->left);
        }
        else if(t->element < v)
        {
            insert( std::move(v), t->right );
        }
        else
        {

        }
    }

    void remove(const T& v, BSTnode *&t)
    {
        if( t == nullptr )
        {
            //Item not found; do nothing
        }
        
        if(v < t->element)
        {
            remove(v, t->left);
        }
        else if(t->element < v)
        {
            remove(v, t->right);
        }
        else if( t->left != nullptr && t->right != nullptr ) // Two children
        {
            t->element = findMin(t->right)->element;
            remove(t->element, t->right);
        }
        else
        {
            BSTnode *oldNode = t;
            t = ( t->left != nullptr ) ? t->left : t->right;
            delete oldNode;
        }
    }

    static const int default_threshold_value = 1;

    BSTnode * findMin(BSTnode *t) const // support/helper function
    {
        if(t == nullptr)
        {
            return nullptr;
        }
        if(t->left == nullptr)
        {
            return t;
        }

        return findMin(t->left);
    }

    BSTnode * findMax( BSTnode *t ) const
    {
        if(t != nullptr)
        {
            while( t->right != nullptr )
            {
                t = t->right;
            }
        }
        return t;
    }

    int max( int lhs, int rhs ) const
    {
        return lhs > rhs ? lhs : rhs;
    }

    bool contains(const T& v, BSTnode *&t, BSTnode *&p)
    {
        if( t == nullptr )
        {
            return false;
        }
        else if( v < t->element )
        {
            return contains( v, t->left, t);
        }
        else if( t->element < v )
        {
            return contains( v, t->right, t);
        }
        else
        {
            t->searchcount++;
            if (threshold == t->searchcount)
            {
                if (t == p->left)
                {
                    rotateWithLeftChild(p);
                }
                else if(t == p)
                {
                    //t->searchcount = 0;//Do nothing if it is the rootnode
                }
                else
                {
                    rotateWithRightChild(p);
                }
            }
            t->searchcount = 0;
            return true;    // Match    
        }
    }
    
    int numOfNodes(BSTnode *t) const //Found and need modify
    {
        if (t == nullptr)
        {
            return 0;
        }
        else
        {
            return 1 + numOfNodes(t->right) + numOfNodes(t->left);
        }
    }

    int height(BSTnode *t) const
    {
        if (t == nullptr)
        {
            return -1;
        }
        else
        {
            int left = height(t->left);
            int right = height(t->right);

            if(left < right)
            {
                return right + 1;
            } 
            else 
            {
                return left + 1;
            }
        }
    }

    BSTnode * clone(BSTnode *t) const
    {
        if( t == nullptr )
        {
            return nullptr;
        }
        else
        {
            return new BSTnode{t->element, clone(t->left), clone(t->right), t->height};
        }
    }

    void rotateWithLeftChild(BSTnode * & k2 )
    {
        BSTnode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2 = k1;
    }

    void rotateWithRightChild(BSTnode * & k1)
    {
        BSTnode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1 = k2;
    }

};

#include "bst.hpp"
}
#endif
