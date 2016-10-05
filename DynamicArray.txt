// Programmer: Dhanush Patel
// Programmer's ID: 1553428

#ifndef DynamicArray_h
#define DynamicArray_h

#include <algorithm>
using namespace std;

template <typename V>
class DynamicArray
{
    V* values;
    int cap;
    V dummy;

public:
    DynamicArray(int=2);
    DynamicArray(const DynamicArray<V>&);
    ~DynamicArray(){delete [] values;}
    int capacity() const {return cap;}
    void capacity(int);
    V operator[](int) const;
    V& operator[](int);
    DynamicArray<V>& operator=(const DynamicArray<V>&);
};

template <typename V>
DynamicArray<V>::DynamicArray(int cap)
{
  this->cap = cap;
  values = new V[cap];

  for (int index = 0; index < cap; index++){
    values[index] = V();
  }
}

template <typename V>
V DynamicArray<V>::operator[](int index) const
{
  if (index < 0 || index >= cap)
    return V(); // a copy
  return values[index]; // a copy
}

template <typename V>
V& DynamicArray<V>::operator[](int index)
{
  if (index < 0){
    return dummy; // a copy
  }
  else if (index >= cap){
    capacity(2 * index);
  }
  return values[index]; // a copy
}

template <typename V>
void DynamicArray<V>::capacity(int newCap){
  V* temp = new V[newCap];

  // get the lesser of the new and old capacities
  int limit = min(newCap,cap);

  // copy the contents
  for (int i = 0; i < limit; i++){
    temp[i] = values[i];
  }

  // set added values to their defaults
  for (int i = limit; i < cap; i++){
    temp[i] = V();
  }

  // deallocate original array
  delete [] values;

  // switch newly allocated array into the object
  values = temp;

  // update the capacity
  cap = newCap;
}

template <typename V>
DynamicArray<V>::DynamicArray(const DynamicArray<V>& original)
{
  cap = original.cap; // still copy
  values = new V[cap]; // not copy, is new
  for (int i = 0; i < cap; i++){ // contents copy original to new
    values[i] = original.values[i];
  }
}

template <typename V>
DynamicArray<V>& DynamicArray<V>::operator=(const DynamicArray<V>& original)
{
  if (this != &original) //check if copy or not, better not be tho
  {
    // same as destructor
    delete [] values;

    // same as copy constructor
    cap = original.cap;
    values = new V[cap]; // not copy, is new
    for (int i = 0; i < cap; i++){ // contents copy original to new
      values[i] = original.values[i];
    }
  }
  return *this; // return self reference
}

#endif