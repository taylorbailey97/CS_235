/***********************************************************************
 * Header:
 *    Set
 * Summary:
 *    This class contains the notion of an Stack: a bucket to hold
 *    buffer for the user. This is just a starting-point for more advanced
 *    constainers such as the Stack, set, stack, queue, deque, and map
 *    which we will build later this semester.
 *
 *    This will contain the class definition of:
 *       Set             : similar to std::Set
 * Author
 *    Caleb and Taylor
 ************************************************************************/

#ifndef SET_H
#define SET_H

#include <cassert>  // because I am paranoid

// a little helper macro to write debug code
#ifdef NDEBUG
#define Debug(statement)
#else
#define Debug(statement) statement
#endif // !NDEBUG

// Allowing the set-tests file to access private variables
#ifdef UNIT_TESTING
int main(int argc, const char* argv[]);
#endif
using namespace std;
namespace custom 
{

template <class T>
class set 
{
   public:
   set() { numCapacity = 0; numElements = 0; buffer = NULL;}
   set(int numCapacity)   throw (const char *);
   set(const set & rhs)           throw (const char *);
   ~set() { delete [] buffer; }
   set & operator= (const set & rhs) throw (const char *);
   set & operator|| (const set & rhs) throw (const char *);
   set & operator- (const set & rhs) throw (const char *);
   set & operator&& (const set & rhs) throw (const char *);
   int size() { return numElements; }
   bool empty() { return !numElements; }
   void clear() { numElements = 0; }
   int capacity() { return numCapacity; }
   void insert(T t);

   class iterator;
   iterator find(T t);
   void erase(iterator it);
   iterator begin()      { return iterator (buffer);               }
   iterator end()        { return iterator (buffer + numElements); }

   //private:
   T * buffer;
   int numElements;
   int numCapacity;
   void resize(int numCapacity);
   int findIndex(T t);
};

/**************************************************
 * Set ITERATOR
 * An iterator through Set
 *************************************************/
template <class T>
class set <T> :: iterator
{
public:
   // constructors, destructors, and assignment operator
   iterator()      : ptr(NULL)      {              }
   iterator(T * p) : ptr(p)         {              }
   iterator(const iterator & rhs) { *this = rhs; }
   iterator & operator = (const iterator & rhs)
   {
      this->ptr = rhs.ptr;
      return *this;
   }

   // equals, not equals operator
   bool operator != (const iterator & rhs) const { return rhs.ptr != this->ptr; }
   bool operator == (const iterator & rhs) const { return rhs.ptr == this->ptr; }

   iterator & operator + (int value) { ptr = ptr + value; return *this; }

   // dereference operator
         T & operator * ()       { return *ptr; }
   const T & operator * () const { return *ptr; }

   // prefix increment
   iterator & operator ++ ()
   {
      if (!(ptr == NULL))
         ptr++;
      return *this;
   }

   // postfix increment
   iterator operator ++ (int postfix)
   {
      iterator tmp(*this);
      if (!(ptr == NULL))
      {
         ptr++;
      }
      return tmp;
   }

   iterator & operator -- ()
   {
      if (!(ptr == NULL))
         ptr--;
      return *this;
   }

   // postfix increment
   iterator operator -- (int postfix)
   {
      iterator tmp(*this);
      if (!(ptr == NULL))
         ptr--;
      return tmp;
   }
   

   T * ptr;
};

/*******************************************
 * Set :: ASSIGNMENT OPERATOR
 *******************************************/
template <class T>
set <T> & set <T> :: operator =(const set <T> & rhs) throw (const char *)
{
   if (rhs.numCapacity == 0)
   {
      this->buffer = NULL;
      this->numCapacity = 0;
      this->numElements = 0;
      return *this;
   }   
   try 
   {
      this->buffer = new T[rhs.numCapacity];
      this->numElements = rhs.numElements;
      cout << "numCapacity: " << rhs.numElements << endl;
      this->numCapacity = rhs.numElements;
   }
   catch (bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }

   for (int i = 0; i < rhs.numElements; i++)
      this->buffer[i] = rhs.buffer[i];
   for (int i = this->numElements; i < this->numCapacity; i++)
      this->buffer[i] = T();

   return *this;
}


/*******************************************
 * Set :: UNION OPERATOR
 *******************************************/
template <class T>
set <T> & set <T> :: operator||(const set <T> & rhs) throw (const char *)
{
   //Create a set wich will be returned to ensure constance of lhs and rhs
      set<T>setReturn;
      //if there is nothing to union, end here
      if((rhs.numCapacity == 0) && (numCapacity == 0))
            return setReturn;
      //create a buffer to store unions in to help minimize memory size of seReturn *required for unit test
      T * unionBuffer = new T[rhs.numCapacity+numCapacity];
      int unionElements = 0;
      int iLhs = 0;
      int iRhs = 0;
      for(int i = 0;(iLhs < numElements) || (iRhs < rhs.numElements); i++)
      {
            //If you have reached the end of lhs, loop through and add the rest of rhs
            if(iLhs == numElements)
            {
                  unionBuffer[unionElements] = rhs.buffer[iRhs];
                  unionElements++;
                  iRhs++;
            }
            //If you have reached the end of lhs, loop through and add the rest of lhs
            else if(iRhs == rhs.numElements)
            {
                  unionBuffer[unionElements] = buffer[iLhs];
                  unionElements++;
                  iLhs++;
            }
            //If the value in lhs is also in rhs, add it once and itterate both sets
            else if(buffer[iLhs] == rhs.buffer[iRhs])
            {
                  unionBuffer[unionElements] = buffer[iLhs];
                  unionElements++;
                  iRhs++;
                  iLhs++;
            }
            //If the value in rhs is smaller than that in lhs, add it to the buffer and itterate rhs
            else if(buffer[iLhs] > rhs.buffer[iRhs])
            {
                  unionBuffer[unionElements] = rhs.buffer[iRhs];
                  unionElements++;
                  iRhs++;
            }
            //If the value in lhs is smaller than that in rhs, add it to the buffer and itterate lhs
            else if(buffer[iLhs] < rhs.buffer[iRhs])
            {
                  unionBuffer[unionElements] = buffer[iLhs];
                  unionElements++;
                  iLhs++;
            }
      }
      if (unionElements == 0)
      {
            //If there is nothing in the union, end here
            return setReturn;
      }
      //Put the buffer into setReturn, with minimum memory size.
      setReturn.numCapacity = unionElements;
      setReturn.numElements = unionElements;
      T *returnBuffer = new T[unionElements];
      for (int i = 0; i < unionElements; i++)
            returnBuffer[i] = unionBuffer[i];
      setReturn.buffer = returnBuffer;
      return setReturn;
}

/*******************************************
 * Set :: DIFFERENCE OPERATOR
 *******************************************/
template <class T>
set <T> & set <T> :: operator-(const set <T> & rhs) throw (const char *)
{
   set <T> difference;
   int indexLhs = 0;
   int indexRhs = 0;
   int numCap = 0;

   if (this->buffer == NULL && rhs.buffer == NULL)
      return difference;

   while (indexLhs < numElements)
   {
      if (indexRhs >= rhs.numElements)
      {
         difference.insert(buffer[indexLhs]);
         indexLhs++;
         numCap++;
      }
      else if (buffer[indexLhs] == rhs.buffer[indexRhs])
      {
         indexRhs++;
         indexLhs++;
      }
      if (rhs.buffer != NULL)
         if (buffer[indexLhs] > rhs.buffer[indexRhs])
         {
            indexRhs++;
         }
      else
      {
         // cout << "inserting: " << buffer[indexLhs] << endl;
         difference.insert(buffer[indexLhs]);
         // if (numCap > 2)
         //    cout << "difference buffer 2: " << difference.buffer[3] << endl;
         indexLhs++;
         numCap++;
      }
   }
   difference.numCapacity = numCap;
   difference.numElements = numCap;
   return difference;
}

/*******************************************
 * Set :: INTERSECTION OPERATOR
 *******************************************/
template <class T>
set <T> & set <T> :: operator&&(const set <T> & rhs) throw (const char *)
{
   set intersection;
   int indexLhs = 0;
   int indexRhs = 0;
   int numCap = 0;
   intersection.numElements = 0;

   while (indexLhs < numElements && indexRhs < rhs.numElements)
   {
       if (buffer[indexLhs] == rhs.buffer[indexRhs])
       {
         intersection.numElements = numCap++;
         intersection.insert(buffer[indexLhs]);
         indexRhs++;
         indexLhs++;
       }
       else if (buffer[indexLhs] < rhs.buffer[indexRhs])
       {
         indexLhs++;
       }
       else
       {
         indexRhs++;
       }
   }
   intersection.numCapacity = numCap;
   intersection.numElements = numCap;
   return intersection;
}

/*******************************************
 * Set :: NON-DEFAULT CONSTRUCTOR
 *******************************************/
template <class T>
set <T> :: set(int numCapacity) throw (const char *)
{
   //assert(numCapacity >= 0);
   
   // do nothing if there is nothing to do.
   // since we can't grow an Vector, this is kinda pointless
   if (numCapacity == 0)
   {
      this->numCapacity = 0;
      this->numElements = 0;
      this->buffer = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      buffer = new T[numCapacity];
   }
   catch (std::bad_alloc)
   {
      throw "Error: set sizes must be greater than or equal to 0.";
   }

   // copy over the stuff
   this->numCapacity = numCapacity;
   this->numElements = 0;

   for (int i = 0; i < numCapacity; i++)
   {
      buffer[i] = T();
   }
}

/*******************************************
 * Set :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
set <T> :: set(const set <T> & rhs) throw (const char *)
{
   if (rhs.numCapacity == 0)
   {
      this->buffer = NULL;
      this->numCapacity = 0;
      this->numElements = 0;
      return;
   }   
   try 
   {
      this->buffer = new T[rhs.numCapacity];
      this->numElements = rhs.numElements;
      cout << "numCapacity: " << rhs.numElements << endl;
      this->numCapacity = rhs.numElements;
   }
   catch (bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }

   for (int i = 0; i < rhs.numElements; i++)
      this->buffer[i] = rhs.buffer[i];
   for (int i = this->numElements; i < this->numCapacity; i++)
      this->buffer[i] = T();
}

/*******************************************
 * Set :: INSERT
 *******************************************/
template <class T>
void set <T> :: insert(T t)
{
   int iInsert = findIndex(t);
   if (this->numCapacity == 0) 
   {
      this->resize(1);
   }
   else if (this->numCapacity == this->numElements) 
   {
      this->resize(this->numCapacity * 2);
   }
   if (buffer[iInsert] != t)
   {
      int i = numElements;
      for (i ; i >= 1; i--)
      {
          if (buffer[i - 1] < t)
          {
              break;
          }
          buffer[i] = buffer[i - 1];
      }
      buffer[i] = t;
      numElements++;
   }
}

/*******************************************
 * Set :: FIND
 *******************************************/
template <class T>
typename set <T> :: iterator set <T> :: find(T t)
{
   int i = findIndex(t);
   if (i != numElements)
   {
      return iterator(buffer + i); 
   }

   return NULL;
}

/*******************************************
 * Set :: ERASE
 *******************************************/
template <class T>
void set <T> :: erase(iterator it)
{
   // int iErase = findIndex(*it);
   // if (buffer[iErase] == it)
   // {
   //    for (; iErase < numElements; iErase++)
   //    {
   //       buffer[iErase] = buffer[iErase + 1];
   //    }
   //    numElements--;
   // }
   // int i;

   // i = findIndex(*it);


   // if (i == -1)
   // {
   //    return;
   // }
   // if (i == (numElements -1))
   // {
   //    numElements--;
   //    return;
   // }

   // for (; i < numElements - 1; i++)
   // {
   //    buffer[i] = buffer[i + 1];
   // }

   // numElements--;
   // return;
}

/*******************************************
 * Set :: RESIZE
 *******************************************/
template <class T>
void set <T> :: resize(int numCapacity)
{
   if (numCapacity < 1)
   {
      this->numCapacity = 0;
      this->numElements = 0;
      this->buffer = NULL;
   }
   else
   {
      if (numCapacity < numElements)
      {
         numElements = numCapacity;
      }
      try
      {
         this->numCapacity = numCapacity;
         T *tempbuffer = new T[numCapacity];
         for (int i = 0; i < numElements; i++)
         {
            tempbuffer[i] = buffer[i];
         } 
         for (int i = numElements; i < numCapacity; i++)
         {
            tempbuffer[i] = T();
         }
         delete [] buffer;
         buffer = tempbuffer;
      } 
      catch (std::bad_alloc)
      {
         throw "ERROR: Bad memory allocation";
      }
   }
}

/*******************************************
 * Set :: FINDINDEX
 *******************************************/
template <class T>
int set <T> :: findIndex(T t)
{
   for (int i = 0; i < numElements; i++)
   {
      if (t == buffer[i])
      {
         return i;
      }
      if (t < buffer[i])
      {
         return i;
      }
   }
   return numElements;
}

}
#endif

