#include "FloorPlan.h"
#include "Room.h"

using namespace std;

int main()
{
  vector<vector<Room>> vec;

  FloorPlan plan;

  //making room A of dimensions (5,8) and adding to FloorPlan object
  Room A(5, 8, 'A');
  plan.addRoot(A);
  //making room A of dimensions (5,8) and adding to FloorPlan object
  Room B(8, 14, 'B');
  plan.rightOf(B, A);

  plan.makeXVector(vec);
  plan.printDimensions(vec);
  plan.printTree(vec);

  Room C(4,8, 'C');
  plan.leftOf(A,C);
  Room D(12, 5, 'D');
  plan.above(D,B);
  Room E(18, 20, 'E');
  plan.under(A,E);

  plan.compact(plan.getRoot());
  vec.clear();
  plan.makeXVector(vec);
  plan.printDimensions(vec);
  plan.printTree(vec);
  
  return 0;
}