#include <iostream>
#include <vector>
#include <memory>
#include <cstdio>
#include <fstream>
#include <cassert>
#include <functional>
#include <ctime>
#include <list>
#include <cstdlib>
#include <algorithm>
#include "defs.h"
#include "utils.h"
#include "kargermincut.h"




int main(int, char**)
{
   GraphType graph {};

   std::srand(std::time(0));
   auto minCut = std::numeric_limits<int>::max();
   auto N = 100;
   for (int i = 0; i < N; i++)
   {
      //buildGraph("sample.txt", graph);
      buildGraph("kargerMinCut.txt", graph);
      auto karMinCut = kargerMinCut(graph);
      if (karMinCut < minCut)
      {
         minCut = karMinCut;
      }
   }
   std::cout << "Min. cut for this graph after " << N << " tries is " << minCut << std::endl;
   return 0;
}
