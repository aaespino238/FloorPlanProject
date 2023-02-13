#include <list>
#include <iterator>
#include <iostream>
#include <vector>
#include "Room.h"

#ifndef LINKEDBINARYTREE_INC
#define LINKEDBINARYTREE_INC

using namespace std;

typedef Room Elem;
class LinkedBinaryTree
{
    friend class FloorPlan;
protected:
    //node declaration
        //we make it protected because they are internal aspects
        //of our implementation and we do not want to allow them to be
        //accessed directly
    struct Node 
    {
        Elem elt;
        Node* par;
        Node* left;
        Node* right;

        Node(void)
            : elt(), par(NULL), left(NULL), right(NULL)
        {
        }
    };
public:
    //position declaration
        //the position class is how we control the access to the Node structure
    class Position
    {
        Node* v;
    public:
        //default argument provided
        //default value provided overwritten if variable is passed
        Position(Node* _v = NULL)
            : v(_v)
        {
        }

        Elem& operator*()
        { return v->elt; }

        void left(const Elem & e)
        { v->left->elt = e; }

        Position left() const
        { return Position(v->left); }

        Position right() const
        { return Position(v->right); }

        void right(const Elem & e)
        { v->right->elt = e; }

        Position parent() const
        { return Position(v->par); }

        bool isRoot() const
        { return v->par == NULL; }

        bool isExternal() const
        { return v->left == NULL && v->right == NULL; }

        bool operator==(Node* a)
        {
            return v == a;
        }

        bool operator!=(Node* a)
        {
            return !(v==a);
        }
        
        friend class LinkedBinaryTree;
    };

    typedef list<Position> PositionList;
public:
    LinkedBinaryTree(void)
        : _root(NULL), n(0)
    {
    }

    int size() const
    {
        return n;
    }

    bool empty() const
    {
        return size() == 0;
    }

    Position root() const
    {
        return Position(_root);
    }

    PositionList positions() const
    {
        PositionList pl;
        preorder(_root, pl);
        return pl;
    }

    Position preorderFind(Elem e)
    {
        PositionList pl = positions();
        Position temp;
        for(PositionList::iterator q = pl.begin(); q != pl.end(); ++q)
          {
            if(*(*q) == e)
            {
              temp = *q;
            }
          }
        return temp;
    }

    void makeXVector(vector<vector<Room>> & vec)
    {
        size_t height = getHeight(root());
        vector<Room> temp;
        for(size_t i = 0; i <= height; ++i)
        {
            vec.push_back(temp);
        }
        size_t count = 0;
        findXCoord(root(), vec, count);
        return;
    }

    size_t getHeight(Position p)
    {
        if(p.isExternal())
        {
            return 0;
        }
        size_t h = 0;
        PositionList ch;
        ch.push_back(p.left());
        ch.push_back(p.right());
        for(PositionList::iterator q = ch.begin(); q != ch.end(); ++q)
        {
            h = max(h, getHeight(*q));
        }
        return 1 + h;
    }

    void printTree(vector<vector<Room>> tree)
    {
        size_t child_count, cursor, child1Pos, child2Pos, nodePos;
        Room temp;
        for(size_t i = 0; i < tree.size(); ++i)
        {
            cursor = child_count = 0;
            for(size_t j = 0; j < tree[i].size(); ++j)
            {
                temp = tree[i][j];
                nodePos = temp.xcoord;
                if(temp.isInternal())
                {
                    child1Pos = tree[i+1][child_count].xcoord;
                    child2Pos = tree[i+1][child_count+1].xcoord;
                    child_count += 2;
                    while(cursor < child1Pos)
                    {
                        cout << ' ';
                        ++cursor;
                    }
                    while(cursor < nodePos)
                    {
                        cout << "_";
                        ++cursor;
                    }
                    cout << temp.name;
                    ++cursor;
                    while(cursor <= child2Pos)
                    {
                        cout << "_";
                        ++cursor;
                    }
                }
                else
                {
                    while(cursor < nodePos)
                    {
                        cout << " ";
                        ++cursor;
                    }
                    ++cursor;
                    cout << temp.name;
                }
            }
            cout << endl;
            cursor = 0;
            if(i!=tree.size() - 1)
            {
                for(size_t k = 0; k < tree[i+1].size(); ++k)
                {
                    child1Pos = tree[i+1][k].xcoord;
                    while(cursor < child1Pos)
                    {
                        cout << " ";
                        ++cursor;
                    }
                    cout << "|";
                    ++cursor;
                }
                cout << endl;
            }
        }
    }

    void findXCoord(Position p, vector<vector<Room>> & vec, size_t & count, size_t lvl = 0)
    {
        if(!p.isExternal())
        {
            findXCoord(p.left(), vec, count, lvl+1);
        }
        (*p).setX(count);
        vec[lvl].push_back(*p);
        ++count;
        if(!p.isExternal())
        {
            findXCoord(p.right(), vec, count, lvl+1);
        }
        return;
    }

    void addRoot()
    {
        _root = new Node;
        n = 1;
    }

    void expandExternal(const Position& p)
    {
        Node* v = p.v;
        Node c;
        v->left = new Node;
        *(v->left) = c;
        v->left->par = v;
        v->right = new Node;
        *(v->right) = c;
        v->right->par = v;
        n += 2;
    }

protected:
    void preorder(Node *v, PositionList& pl) const
    {
        pl.push_back(Position(v));
        if(v->left != NULL)
        {
            preorder(v->left, pl);
        }
        if(v->right != NULL)
        {
            preorder(v->right, pl);
        }
        return;
    }

    void DestroyRecursive(Node* c)
    {
        if(c)
        {
            DestroyRecursive(c->left);
            DestroyRecursive(c->right);
            delete c;
        }
        return;
    }

    ~LinkedBinaryTree()
    {
        DestroyRecursive(_root);
    }
private:
    Node* _root;
    int n;
};

#endif