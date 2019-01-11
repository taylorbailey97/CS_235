/***********************************************************************
 * Header:
 *    Vector
 * Summary:
 *    This class contains the notion of an Vector: a bucket to hold
 *    data for the user. This is just a starting-point for more advanced
 *    constainers such as the vector, set, stack, queue, deque, and map
 *    which we will build later this semester.
 *
 *    This will contain the class definition of:
 *       Vector             : similar to std::Vector
 *       Vector :: iterator : an iterator through the Vector
 * Author
 *    Br. Helfrich
 ************************************************************************/

#ifndef VECTOR_H
#define VECTOR_H

#include <cassert>  // because I am paranoid

// a little helper macro to write debug code
#ifdef NDEBUG
#define Debug(statement)
#else
#define Debug(statement) statement
#endif // !NDEBUG

namespace custom
{

/************************************************
 * Vector
 * A class that holds stuff
 ***********************************************/
template <class T>
class Vector
{
public:
   // constructors and destructors
   Vector(int num)                  throw (const char *);
   Vector(const Vector & rhs)        throw (const char *);
  ~Vector()                         { delete [] data;   }
   Vector & operator = (const Vector & rhs) throw (const char *);
   
   // standard container interfaces
   // Vector treats size and max_size the same
   
   int  size()     const { return num;                 }
   int  max_size() const { return num;                 }
   
   // Vector-specific interfaces
   // what would happen if I passed -1 or something greater than num?
   T & operator [] (int index)       throw (const char *)
   {
      return data[index];
   }
   const T & operator [] (int index) const throw (const char *)
   {
      return data[index];
   }
   
   // the various iterator interfaces
   class iterator;
   iterator begin()      { return iterator (data); }
   iterator end();

   // a debug utility to display the Vector
   // this gets compiled to nothing if NDEBUG is defined
   Vector & assign(const Vector <T> rhs) const;
   void push_back(const T t);
   void display() const; 
   
   
private:
   T * data;              // dynamically allocated Vector of T
   int num; 
   int numCapacity;       // both the capacity and the number of elements
};

/**************************************************
 * Vector ITERATOR
 * An iterator through Vector
 *************************************************/
template <class T>
class Vector <T> :: iterator
{
public:
   // constructors, destructors, and assignment operator
   iterator()      : p(NULL)      {              }
   iterator(T * p) : p(p)         {              }
   iterator(const iterator & rhs) { *this = rhs; }
   iterator & operator = (const iterator & rhs)
   {
      this->p = rhs.p;
      return *this;
   }

   // equals, not equals operator
   bool operator != (const iterator & rhs) const { return rhs.p != this->p; }
   bool operator == (const iterator & rhs) const { return rhs.p == this->p; }

   // dereference operator
         T & operator * ()       { return *p; }
   const T & operator * () const { return *p; }

   // prefix increment
   iterator & operator ++ ()
   {
      p++;
      return *this;
   }

   // postfix increment
   iterator operator ++ (int postfix)
   {
      iterator tmp(*this);
      p++;
      return tmp;
   }
   
private:
   T * p;
};


/********************************************
 * Vector :: END
 * Note that you have to use "typename" before
 * the return value type
 ********************************************/
template <class T>
typename Vector <T> :: iterator Vector <T> :: end ()
{
   return iterator (data + num);
}

/*******************************************
 * Vector :: Assignment
 *******************************************/
template <class T>
Vector <T> & Vector <T> :: operator = (const Vector <T> & rhs)
          throw (const char *)
{
   // we can only copy Vectors of equal size. Vectors are not this way!
   if (rhs.size() != size())
   {
      throw "ERROR: Unable to copy Vectors of different sizes";
   }

   assert(num == rhs.num);
   for (int i = 0; i < num; i++)
      data[i] = rhs.data[i];

   return *this;
}

/*******************************************
 * Vector :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
Vector <T> :: Vector(const Vector <T> & rhs) throw (const char *)
{
   assert(rhs.num >= 0);
      
   // do nothing if there is nothing to do
   if (rhs.num == 0)
   {
      num = 0;
      data = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[rhs.num];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }
   
   // copy over the capacity
   num = rhs.num;

   // copy the items over one at a time using the assignment operator
   for (int i = 0; i < num; i++)
      data[i] = rhs.data[i];
}

/**********************************************
 * Vector : NON-DEFAULT CONSTRUCTOR
 * Preallocate the Vector to "capacity"
 **********************************************/
template <class T>
Vector <T> :: Vector(int num) throw (const char *)
{
   assert(num >= 0);
   
   // do nothing if there is nothing to do.
   // since we can't grow an Vector, this is kinda pointless
   if (num == 0)
   {
      this->num = 0;
      this->data = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[num];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }

      
   // copy over the stuff
   this->num = num;
}

template <class T>
Vector <T> & Vector <T> :: assign(const Vector rhs) const
{
   if (rhs.size() != size())
   {
      throw "ERROR: Unable to copy Vectors of different sizes";
   }
   this.numCapacity = rhs.numCapacity;
   assert(num == rhs.num);
   for (int i = 0; i < num; i++)
      data[i] = rhs.data[i];

   return *this;
}

void push_back(const T t) 
{

   if (this->size() == )
   {
      throw "ERROR: Unable allocate a new buffer for vector";
   }

   if (this.numCapacity == 0) 
   {
      this.numCapacity = 1;
   }
   if (this.numCapacity > this.num) 
   {
      this.numCapacity = this.numCapacity * 2;
   }
   

}

/********************************************
 * Vector : DISPLAY
 * A debug utility to display the contents of the Vector
 *******************************************/
template <class T>
void Vector <T> :: display() const
{
#ifndef NDEBUG
   std::cerr << "Vector<T>::display()\n";
   std::cerr << "\tnum = " << num << "\n";
   for (int i = 0; i < num; i++)
      std::cerr << "\tdata[" << i << "] = " << data[i] << "\n";
#endif // NDEBUG
}

}; // namespace custom

#endif // Vector_H

