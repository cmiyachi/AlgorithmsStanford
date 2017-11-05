#pragma once

#include "defs.h"
#include <iostream>
#include <fstream>
#include <sstream>

void buildGraph(const char* fileName, GraphType& graph)
{
   // clear the graph first
   graph.clear();

   std::ifstream file (fileName);
   if (!file)
   {
      std::cerr << "Unable to open" << fileName << std::endl;
      return;
   }

   std::string line = "";
   int index = 1;
   while (getline(file, line))
   {
      // rvalue move semantics!
      graph.push_back(std::make_unique<Vertex>(index));
      index++;

      // add neighbours
      std::stringstream ss (line);
      int n = 0;
      bool first = true;
      while (ss >> n)
      {
         // skip the first
         if (first)
         {
            first = false;
            continue;
         }
         graph.back()->addNeighbour(n);
      }
   }
}

void printGraph(GraphType& graph)
{
   for (const auto& pvec : graph)
   {
      if (pvec->isAlreadySeen())
      {
         std::cout << "- (" << pvec->index << "," << pvec->mergedIndex << ") ";
      }
      else
      {
         std::cout << pvec->index << " ";
      }
      auto& nlist = pvec->neighbours;
      std::for_each(nlist.begin(), nlist.end(), [](auto x) { std::cout << x << " "; });
      std::cout << '\n';
   }
   std::cout << "====\n";
}

