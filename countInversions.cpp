// Count Inversions
// A simple program to count the number of inversions in an array
// The program is written as a part of Courseera Algorithms class
// It is a simple application of divide and conquer algo, and the prograuns on O(nlog(n)) time

#include <iostream>
#include <string.h>

using namespace std;

long long countInversions(int *array, int length) {
  // Termination condition
  if(length == 1) { return 0;}
  
  int * arrayLeft = array;
  int arrayLeftLength = length/2;
  int * arrayRight = array+arrayLeftLength;
  int arrayRightLength = length-length/2;
  
  // Recursively find inversions in subsets
  long long leftInversions = countInversions(arrayLeft,arrayLeftLength);
  long long rightInversions = countInversions(arrayRight,arrayRightLength);
  long long totalInversions = leftInversions + rightInversions;
  
  // Find inversions in left and right array
  int * tempArray = new int[length];
  int a=0,b=0;
  for(int i=0;i<length;i++) {
    if((a<arrayLeftLength)&&(b<arrayRightLength)){
      if(arrayLeft[a]<arrayRight[b]){
        tempArray[i] = arrayLeft[a];
        a++;
      }
      else{
        tempArray[i] = arrayRight[b];
        b++;
        totalInversions += arrayLeftLength - a;
      }
    }
    else if(!(a<arrayLeftLength)) {
      while(b<arrayRightLength){
        tempArray[i] = arrayRight[b];
        b++;
        i++;
      }
    }
    else if(!(b<arrayRightLength)) {
      while(a<arrayLeftLength){
        tempArray[i] = arrayLeft[a];
        a++;
        i++;
      }
    }
  }
      
  // Copy the temp array to array and return the total number of inversions
  memcpy((void *)array, (const void *)tempArray, length*sizeof(int));
  delete(tempArray);
  return totalInversions;
}

int main() {
  int * array;
  int length=100000;
  array = new int[length];
  for(int i=0;i<length;i++) {
    cin>>array[i];
  }
  cout<<countInversions(array,length);
  delete(array);
  return 0;
}
