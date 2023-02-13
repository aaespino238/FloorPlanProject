#include "LinkedBinaryTree.h"
#include "Room.h"
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

class FloorPlan
{
    LinkedBinaryTree plan;

public:
    FloorPlan(void)
        : plan()
    {
    }

    void addRoot(Room A)
    {
        plan.addRoot();
        *(plan.root()) = A;
        return;
    }

    LinkedBinaryTree & getTree(void)
    {
       return plan; 
    }

    LinkedBinaryTree::Position getRoot(void)
    {
        return (plan.root());
    }

    void rightOf(Room A, Room B) //place room A to the right of room B
    {
        LinkedBinaryTree::Position p = plan.preorderFind(B);
        plan.expandExternal(p);
        p.left(B);
        p.right(A);
        Room vertCut(0,0,'/', true, 0, 2);
        *p = vertCut;
        return;
    }

    void leftOf(Room A, Room B) //place room A to the left of room B
    {
        rightOf(B,A);
        return;
    }

    void above(Room A, Room B) //place room A above room B
    {
        LinkedBinaryTree::Position p = plan.preorderFind(B);
        plan.expandExternal(p);
        p.left(B);
        p.right(A);
        Room horizCut(0,0,'-', true, 0, 1);
        *p = horizCut;
        return;
    }

    void under(Room A, Room B) //place room A under room B
    {
        above(B,A);
        return;
    }

    void makeXVector(vector<vector<Room>> & vec)
    {
        plan.makeXVector(vec);
        return;
    }

    void printDimensions(vector<vector<Room>> vec)
    {
        Room temp;
        for(size_t i = 0; i < vec.size(); ++i)
        {
            cout << "Level " << i << ":" << endl; 
            for(size_t j = 0; j < vec[i].size(); ++j)
            {
                temp = vec[i][j];
                cout << "Name: " << temp.name << endl;
                cout << "Width: " << temp.width << endl;
                cout << "Height: " << temp.height << endl;
                cout << "Cut: ";
                if(temp.cut == 1)
                {
                    cout << "Horizontal" << endl;
                }
                else if (temp.cut == 2)
                {
                    cout << "Vertical" << endl;
                }
                else
                {
                    cout << "None" << endl;
                }
                cout << "x-coordinate: " << temp.xcoord << endl;
                cout << endl;
            }
        }
        return;
    }

    void printTree(vector<vector<Room>> & vec)
    {
        plan.printTree(vec);
        return;
    }

    Room compact(LinkedBinaryTree::Position p)
    {
        if(!p.isExternal())
        {
            p.left(compact(p.left()));
            p.right(compact(p.right()));
            if((*p).cut == 1) //horizontal cut
            {
                (*p).width = max((*p.left()).width, (*p.right()).width);
                (*p).height = (*p.left()).height + (*p.right()).height;
            }
            if((*p).cut == 2) //vertical cut
            {
                (*p).width = (*p.left()).width + (*p.right()).width;
                (*p).height = max((*p.left()).height, (*p.right()).height);
            }
            return *p;
        }
        else
        {
            return *p;
        }
        return *p;
    }
};