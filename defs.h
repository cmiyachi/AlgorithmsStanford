#pragma once
#include <vector>
#include <iostream>

class Vertex;
using GraphType = std::vector<std::unique_ptr<Vertex>>;

class Vertex
{
   public:
      Vertex(int _index)
         : index(_index)
      {
         // there are 200 vertices. Although the max number of edges is n(n-1)/2, reserving 1000
         neighbours.reserve(1000);
      }
      int index {0};
      int mergedIndex {0};
      std::vector<int> neighbours {};

      void addNeighbour(int n)
      {
         neighbours.push_back(n);
      }

      bool isAlreadySeen()
      {
         return mergedIndex != 0;
      }

      std::size_t degree()
      {
         return neighbours.size();
      }

      void mergeVertex(GraphType& graph, Vertex& v)
      {
         v.mergedIndex = index;
         neighbours.insert(neighbours.end(), v.neighbours.begin(), v.neighbours.end());
         // replace v.index with index in all the neighbours of v
         for (auto x : v.neighbours)
         {
            auto& nlist = graph[x - 1]->neighbours;
            std::for_each(nlist.begin(),
                          nlist.end(),
                          [d=index, &m=v](int& x) { if (x==m.index) x = d; });
         }
         // delete all the self loops in *this
         auto end = std::remove_if(neighbours.begin(), neighbours.end(), [i=index](int x) { return x == i; });
         neighbours.erase(end, neighbours.end());
      }
};
