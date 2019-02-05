/***********************************************************************
 * Header:
 *    Stack
 * Summary:
 *    This class contains the notion of an Stack: a bucket to hold
 *    buffer for the user. This is just a starting-point for more advanced
 *    constainers such as the Stack, set, stack, queue, deque, and map
 *    which we will build later this semester.
 *
 *    This will contain the class definition of:
 *       Stack             : similar to std::Stack
 *       Stack :: iterator : an iterator through the Stack
 * Author
 *    Caleb and Taylor
 ************************************************************************/

#ifndef DEQUE_H
#define DEQUE_H

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
 * Deque
 * A class that holds stuff
 ***********************************************/
template <class T>
class deque
{
public:

   deque() { numCapacity = 0; iBack = -1; iFront = 0; buffer = NULL;}
   deque(int numCapacity)                       throw (const char *);
   deque(const deque & rhs)                     throw (const char *);
   ~deque() 
   {
      if (buffer != NULL)
         delete [] buffer;
   }
   deque & operator = (const deque <T> & rhs) throw (const char *);
   
      
   int size() const {return (iBack - iFront) + 1;}
   void clear();
   bool empty() { return !size(); }
   
   void push_back(const T t);
   void push_front(const T t);
   void pop_back();
   void pop_front();
   
   T & front();
   T & back();   
   
   //private:
   
   T * buffer;
   int iFront;
   int iBack;
   int numCapacity;
   void resize(int numCapacity);
   int capacity() {return numCapacity;}
   int iNormalize(int index) const;
   int iBackNormalize() const { return iNormalize(iBack); }
   int iFrontNormalize() const { return iNormalize(iFront); }

};
template <class T>
deque<T> :: deque(int numCapacity) throw (const char *)
{
   if (numCapacity >= 0)
   {
      this->iFront = 0;
      this->iBack = -1;
      this->buffer = new T[numCapacity];
      this->numCapacity = numCapacity;
   }
   else
   {
      throw "Error: deque sizes must be greater than or equal to 0.";
   }
}

template <class T>
deque<T> :: deque(const deque & rhs) throw (const char *)
{
   this->numCapacity = rhs.size();
   this->iFront = 0;
   this->iBack = (rhs.size() - 1);
   T * temp = new T[this->numCapacity];
   for (int i = 0; i <= numCapacity; i++)
   {
      temp[i] = rhs.buffer[rhs.iFrontNormalize() + i];
   }
   delete [] buffer;
   this->buffer = temp;
}

template <class T>
void deque<T> :: clear()
{
   iFront = 0;
   iBack = -1; 
}

template <class T>
void deque<T> :: push_back(const T t)
{
   if (numCapacity <= 0)
   {
      resize(1);
   }
   else if (numCapacity == size())
   {
      resize(numCapacity * 2);
   }
   iBack++;
   buffer[iBackNormalize()] = t;
}

template <class T>
void deque<T> :: push_front(const T t)
{
   if (numCapacity <= 0)
   {
      resize(1);
   }
   else if(numCapacity == size())
   {
      resize(numCapacity * 2);
   }
   iFront--;
   // std::cout << "iFront: " << iFrontNormalize() << std::endl;
   // std::cout << "Value passed: " << t << std::endl;
   buffer[iFrontNormalize()] = t;
}

template <class T>
void deque<T> :: pop_back()
{
   if (empty())
   {
      throw "Error: Can not pop an empty deque.";
   }
   iBack--;
}

template <class T>
void deque<T> :: pop_front()
{
   if (empty())
   {
      throw "Error: Can not pop an empty deque.";
   }

   iFront++;
}

template <class T>
void deque<T> :: resize(int numCapacity)
{
   if (numCapacity <= 0)
   {
      if (buffer != NULL)
      {
         delete [] buffer;
         buffer = NULL;
      }

      this->numCapacity = 0;
      iFront = 0;
      iBack = -1;
   }
   else
   {
      int numItemsToCopy = ((numCapacity < size()) ? numCapacity : size());
      int numItemsCopied = -1;
      T * newBuffer = new T[numCapacity];
      
      for (int i = 0; i < numItemsToCopy; i++)
      {
         int normalizedIndex = (iFrontNormalize() + i);
         newBuffer[i] = buffer[normalizedIndex];
         numItemsCopied++;
      }
      delete [] buffer;
      buffer = newBuffer;
      iFront = 0;
      iBack = numItemsCopied;
      this->numCapacity = numCapacity;
   }
}

template <class T>
int deque<T> :: iNormalize(int index) const
{
   if (numCapacity > 0)
   {
      return (index >= 0) ? (index % this->numCapacity) : (this->numCapacity - ((-1 - index) % this->numCapacity) - 1);
   }
   throw "Error: uninitialized deque.";
}

template <class T>
T& deque<T> :: front()
{
   if (empty())
   {
      throw "Error: deque is empty.";
   }
   return buffer[iFrontNormalize()];
}
template <class T>
T& deque<T> :: back()
{
   if (empty())
   {
      throw "Error: deque is empty.";
   }
   return buffer[iBackNormalize()];
}


}
#endif

