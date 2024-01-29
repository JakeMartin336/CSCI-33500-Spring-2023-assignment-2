//Jacob Martin
//BST.h for Homework 2.

#ifndef HOMEWORK2_BINARY_SEARCH_TREE_H_
#define HOMEWORK2_BINARY_SEARCH_TREE_H_

#include "dsexceptions.h"
#include <iostream>
#include <algorithm>

// BinarySearchTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class BinarySearchTree
{
  public:
    BinarySearchTree( ) : root{ nullptr }
    {
    }

    /**
     * Copy constructor
     */
    BinarySearchTree( const BinarySearchTree & rhs ) : root{ nullptr }
    {
        root = clone( rhs.root );
    }

    /**
     * Move constructor
     */
    BinarySearchTree( BinarySearchTree && rhs ) : root{ rhs.root }
    {
        rhs.root = nullptr;
    }
    
    /**
     * Destructor for the tree
     */
    ~BinarySearchTree( )
    {
        makeEmpty( );
    }

    /**
     * Copy assignment
     */
    BinarySearchTree & operator=( const BinarySearchTree & rhs )
    {
        BinarySearchTree copy = rhs;
        std::swap( *this, copy );
        return *this;
    }
        
    /**
     * Move assignment
     */
    BinarySearchTree & operator=( BinarySearchTree && rhs )
    {
        std::swap( root, rhs.root );       
        return *this;
    }
    
    
    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMin( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMin( root )->element;
    }

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMax( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMax( root )->element;
    }

    /**
     * Returns true if x is found in the tree.
     */
    bool contains( const Comparable & x ) const
    {
        return contains( x, root );
    }

    /**
    * Returns acronyms of x in the tree.
    */
    std::vector<std::string> find( const Comparable & x ) 
    {
        return find( x, root );
    }

    /**
    * Returns amount of recursive calls in the tree.
    */
    int findCount( const Comparable & x ) 
    {
        return findCount( x, root, 0);
    }


    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty( ) const
    {
        return root == nullptr;
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTree( ) const
    {
        if( isEmpty( ) )
	  std::cout << "Empty tree" << std::endl;
        else
            printTree(root);
    }

    /**
     * Make the tree logically empty.
     */
    void makeEmpty( )
    {
        makeEmpty( root );
    }

    /**
    * Insert x into the tree; duplicates are ignored.
    */
    void insert( const Comparable & x )
    {
        insert( x, root );
    }
     
    /**
    * Insert x into the tree; duplicates are ignored.
    */
    void insert( Comparable && x )
    {
        insert( std::move( x ), root );
    }
    
    /**
    * Remove x from the tree. Nothing is done if x is not found.
    */
    int remove( const Comparable & x )
    {
        int final = 0; //creating an int that keeps track of recursive calls
        return remove( x, root, final );
    }

    int getNumberOfNodes() 
    {
        return NumberNodes(root);
    }

    /**
    * Returns the total depth of the tree.
    */
    int getTotalDepth() 
    {
        return TotalDepth(root, 0);
    }
    /**
    * finding a node in the tree that matches Comparable passed
    * returning the vector that matches 
    */
    std::string getEnzymeAcronym(const Comparable & x)
    {
        std::string result;
        std::vector<std::string> temp = find( x, root );
        for (size_t i = 0; i < temp.size(); i++) {
            result += temp[i];
            result += " ";
        }
        return result;
    }


  private:
    struct BinaryNode
    {
        Comparable element;
        BinaryNode *left;
        BinaryNode *right;

        BinaryNode( const Comparable & theElement, BinaryNode *lt, BinaryNode *rt )
          : element{ theElement }, left{ lt }, right{ rt } { }
        
        BinaryNode( Comparable && theElement, BinaryNode *lt, BinaryNode *rt )
          : element{ std::move( theElement ) }, left{ lt }, right{ rt } { }
    };

    BinaryNode *root;
    /**
     * calculating the number of nodes in the tree
    */
    int NumberNodes(BinaryNode * &t) 
    {
        if(t == nullptr)
            return 0;
        else
            return (1 + NumberNodes(t->left) + NumberNodes(t->right));
    }

    
    /**
    * Internal method to count total depth of the tree.
    * Returns the depth as a integer
    */
    int TotalDepth(BinaryNode *&t, int depth) 
    {
        if(t == nullptr)
            return 0;
        else
            return depth + TotalDepth(t->left, depth + 1) + TotalDepth(t->right, depth + 1); 
    }



    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( const Comparable & x, BinaryNode * & t )
    {
        if( t == nullptr )
            t = new BinaryNode{ x, nullptr, nullptr };
        else if( x < t->element )
            insert( x, t->left );
        else if( t->element < x )
            insert( x, t->right );
        else
            t->element.Merge(x);;  // Duplicate; do nothing
    }
    
    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( Comparable && x, BinaryNode * & t )
    {
        if( t == nullptr )
            t = new BinaryNode{ std::move( x ), nullptr, nullptr };
        else if( x < t->element )
            insert( std::move( x ), t->left );
        else if( t->element < x )
            insert( std::move( x ), t->right );
        else
            t->element.Merge(x);;  // Duplicate; do nothing
    }

    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    int remove( const Comparable & x, BinaryNode * & t, int count)
    {
        if( t == nullptr )
            return count * -1;   // Item not found; do nothing
        if( x < t->element )
            return remove( x, t->left, count + 1 );
        else if( t->element < x )
            return remove( x, t->right, count + 1 );
        else if( t->left != nullptr && t->right != nullptr ) // Two children
        {
            t->element = findMin( t->right, count )->element;
            return remove( t->element, t->right, count + 1 );
        }
        else
        {
            BinaryNode *oldNode = t;
            t = ( t->left != nullptr ) ? t->left : t->right;
            delete oldNode;
        }
        return count;
    }

    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    BinaryNode * findMin( BinaryNode *t, int& count ) const
    {
        count++;
        if( t == nullptr )
            return nullptr;
        if( t->left == nullptr )
            return t;
        return findMin( t->left, count );
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    BinaryNode * findMax( BinaryNode *t ) const
    {
        if( t != nullptr )
            while( t->right != nullptr )
                t = t->right;
        return t;
    }


    /**
    * Internal method to find the sequence in a subtree t.
    * Return acronyms of the item as a vector.
    */
    std::vector<std::string> find(const Comparable & x, BinaryNode *t) 
    {
        if(t == nullptr) 
        {
            std::vector<std::string> result;
            result.push_back("Not Found");
            return result;
        }
        else if (x < t->element)
            return find(x, t->left);
        else if (t->element < x)
            return find(x, t->right);
        else
            return t->element.getArcos();
    }

    /**
    * Internal method to find the amount of recursive calls to find x in a subtree t.
    * Returns the total as a integer.
    */
    int findCount(const Comparable & x, BinaryNode *t, int count) 
    {
        if(t == nullptr)
            return count * -1;
        else if (x < t->element)
            return findCount(x, t->left, count + 1);
        else if (t->element < x)
            return findCount(x, t->right, count + 1);
        else
            return count;
    }


    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the subtree.
     */
    bool contains( const Comparable & x, BinaryNode *t ) const
    {
        if( t == nullptr )
            return false;
        else if( x < t->element )
            return contains( x, t->left );
        else if( t->element < x )
            return contains( x, t->right );
        else
            return true;    // Match
    }
/****** NONRECURSIVE VERSION*************************
    bool contains( const Comparable & x, BinaryNode *t ) const
    {
        while( t != nullptr )
            if( x < t->element )
                t = t->left;
            else if( t->element < x )
                t = t->right;
            else
                return true;    // Match

        return false;   // No match
    }
*****************************************************/

    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty( BinaryNode * & t )
    {
        if( t != nullptr )
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = nullptr;
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     */
    void printTree(BinaryNode *t) const
    {
        if( t != nullptr )
        {
            printTree(t->left);
	        std::cout << t->element << std::endl;
            printTree(t->right);
        }
    }

    /**
     * Internal method to clone subtree.
     */
    BinaryNode * clone( BinaryNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        else
            return new BinaryNode{ t->element, clone( t->left ), clone( t->right ) };
    }

    int height( BinaryNode *t ) const
    {
        return t == nullptr ? -1 : t->height;
    }

    int max( int lhs, int rhs ) const
    {
        return lhs > rhs ? lhs : rhs;
    }

};

#endif  // HOMEWORK2_BINARY_SEARCH_TREE_H_
