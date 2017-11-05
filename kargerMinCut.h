#pragma once
#include "defs.h"
#include "utils.h"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <list>

int kargerMinCutRecursive(std::vector<int>& remainingVertices,
                          std::vector<std::pair<int, int>>& remainingEdges)
{
   std::size_t len = remainingVertices.size();
   // base case
   if (len == 2)
   {
      return remainingEdges.size();
   }

   // randomly choose an edge
   std::size_t noEdges = remainingEdges.size();
   auto edgeIndex = std::fmod(std::rand(), noEdges);
   auto& edge = remainingEdges[edgeIndex];
   auto persist = std::min(edge.first, edge.second);
   auto toRemove = std::max(edge.first, edge.second);

   // remove the vertex
   remainingVertices.erase(std::find(remainingVertices.begin(), remainingVertices.end(), toRemove));

   // remove the edges
   auto end = std::remove_if(remainingEdges.begin(),
                             remainingEdges.end(),
                             [per=persist, rem=toRemove] (auto& edge)
                             {
                                 if (edge.first == rem) edge.first = per;
                                 if (edge.second == rem) edge.second = per;
                                 if (edge.first == edge.second) return true;
                                 return false;
                             });
   remainingEdges.erase(end, remainingEdges.end());

   // recursive call.
   return kargerMinCutRecursive(remainingVertices, remainingEdges);
}

int kargerMinCut(GraphType& graph)
{
   // build a vector of remaining vertices
   std::vector<int> remainingVertices {};
   std::for_each(graph.begin(),
                 graph.end(),
                 [&vec=remainingVertices](auto& pvec) { vec.push_back(pvec->index);});

   // build a vector of edges. since it is undirected graph, edge is from smaller to larger index
   std::vector<std::pair<int, int>> remainingEdges {};
   for (auto& pvertex : graph)
   {
      std::vector<int>& neighbours = pvertex->neighbours;
      std::for_each(neighbours.begin(),
                    neighbours.end(),
                    [index=pvertex->index, &elist=remainingEdges](int x)
                    {
                       if (x < index)
                          elist.emplace_back(std::make_pair(x, index));
                    });
   }
   return kargerMinCutRecursive(remainingVertices, remainingEdges);
}
