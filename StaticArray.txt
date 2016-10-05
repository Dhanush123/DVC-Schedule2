// Programmer: Dhanush Patel
// Programmer's ID: 1553428

#ifndef StaticArray_h
#define StaticArray_h

template <typename V, int CAP>
class StaticArray
{
  V values[CAP];
  V dummy;

  public:
  StaticArray();
  int capacity() const {return CAP;}
  V operator[](int) const;
  V& operator[](int);
};

template <typename V, int CAP>
StaticArray<V, CAP>::StaticArray()
{
  for (int index = 0; index < CAP; index++)
    values[index] = V();
}

template <typename V, int CAP>
V StaticArray<V, CAP>::operator[](int index) const
{
  if (index < 0 || index >= CAP)
    return V(); // a copy
  return values[index]; // a copy
}

template <typename V, int CAP>
V& StaticArray<V, CAP>::operator[](int index)
{
  if (index < 0 || index >= CAP)
    return dummy; // a mutable reference
  return values[index]; // a mutable reference
}

#endif