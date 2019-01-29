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

#ifndef STACK_H
#define STACK_H

#include <cassert>  // because I am paranoid

// a little helper macro to write debug code
#ifdef NDEBUG
#define Debug(statement)
#else
#define Debug(statement) statement
#endif // !NDEBUG

#ifdef UNIT_TESTING
int main(int argc, const char* argv[]);
#endif



namespace custom
{

/************************************************
 * Stack
 * A class that holds stuff
 ***********************************************/
template <class T>
class Stack
{
public:
   // constructors and destructors
   Stack() { numCapacity = 0; numElements = 0; buffer = NULL; } 
   Stack(int numElements)                  throw (const char *);
   Stack(const Stack & rhs)        throw (const char *);
  ~Stack()                         { delete [] buffer;   }
   Stack & operator = (const Stack & rhs) throw (const char *);
   
   // standard container interfaces
   // Stack treats size and max_size the same
   
   int  size()     const { return numElements;                 }
   int  capacity() const { return numCapacity;                 }
   
   // friend declaration to be placed in the public section of your class definition
   #ifdef UNIT_TESTING
   friend int ::main(int argc, const char* argv[]);
   #endif

   // a debug utility to display the Stack
   // this gets compiled to nothing if NDEBUG is defined
   void push(const T t);
   void display() const; 
   bool empty() const;
   void clear();
   void pop();
   T &top() const;


   //friend int main(int argc, const char* argv[]);
   private:
   T * buffer;              // dynamically allocated Stack of T
   int numElements; 
   int numCapacity;       // both the capacity and the number of elements
   void resize(const int numCapacity);
};


/*******************************************
 * Stack :: Assignment
 *******************************************/
template <class T>
Stack <T> & Stack <T> :: operator = (const Stack <T> & rhs)
          throw (const char *)
{
   // we can only copy Stacks of equal size. Stacks are not this way!
   if (rhs.capacity() != capacity())
   {
      this->numCapacity = rhs.size();
      resize(this->numCapacity);
   }

   //assert(numCapacity == rhs.numCapacity);
   this->numElements = rhs.size();
   for (int i = 0; i < numElements; i++)
      buffer[i] = rhs.buffer[i];
   numElements = rhs.numElements;
   return *this;
}

/*******************************************
 * Stack :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
Stack <T> :: Stack(const Stack <T> & rhs) throw (const char *)
{
   assert(rhs.numCapacity >= 0);
   assert(rhs.numElements >= 0);
      
   // do nothing if there is nothing to do
   if (rhs.numCapacity == 0 && rhs.numElements)
   {
      this->numElements = 0;
      this->numCapacity = 0;
      buffer = NULL;
      return;
   }

   // copy over the capacity
   this->numCapacity = rhs.numElements;
   numElements = rhs.numElements;

   // attempt to allocate
   try
   {
      buffer = new T[rhs.numCapacity];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }
   

   // copy the items over one at a time using the assignment operator
   for (int i = 0; i < numElements; i++)
      buffer[i] = rhs.buffer[i];
   for (int i = numElements; i < numCapacity; i++) 
         buffer[i] = T();
}

/**********************************************
 * Stack : NON-DEFAULT CONSTRUCTOR
 * Preallocate the Stack to "capacity"
 **********************************************/
template <class T>
Stack <T> :: Stack(int numCapacity) throw (const char *)
{
   assert(numCapacity >= 0);
   
   // do nothing if there is nothing to do.
   // since we can't grow an Stack, this is kinda pointless
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
      throw "ERROR: Unable to allocate buffer";
   }

      
   // copy over the stuff
   this->numCapacity = numCapacity;
   this->numElements = numCapacity;
}

template <class T>
void Stack<T> :: push(const T t) 
{


   if (this->numCapacity == 0) 
   {
      this->resize(1);
   }
   else if (this->numCapacity == this->numElements) 
   {
      this->resize(this->numCapacity * 2);
   }
   this->buffer[this->numElements++] = t;

}

template <class T>
void Stack<T> ::  resize(int numCapacity) 
{
   try
   {
      if (numCapacity == 0)
      {
         this->numCapacity = 0;
         this->numElements = 0;
         this->buffer = NULL;
      }
      else if (numCapacity > 0)
      {
         this->numCapacity = numCapacity;
         if (numElements > numCapacity)
            for (int i = numElements; i > numCapacity; i--)
                  numElements--;
         T *tempbuffer = new T[numCapacity]; 
         for (int i = 0; i < numElements; i++)
            tempbuffer[i] = buffer[i]; 
         for (int i = numElements; i < numCapacity; i++) 
            tempbuffer[i] = T(); 
         delete [] buffer; 
         buffer = tempbuffer;
      }
   } 
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate new buffer for Stack";
   }


} 

template <class T>
void Stack<T> :: pop()
{
      if( numElements)
         numElements --;
}

template <class T>
T &Stack<T> :: top() const
{
    if (numElements)
       return buffer[numElements - 1]; 
    throw " ERROR: Unable to reference the element from an empty stack";
   
}




/********************************************
 * Stack : DISPLAY
 * A debug utility to display the contents of the Stack
 *******************************************/
template <class T>
void Stack <T> :: display() const
{
#ifndef NDEBUG
   std::cerr << "Stack<T>::display()\n";
   std::cerr << "\tnum = " << numElements << "\n";
   for (int i = 0; i < numElements; i++)
      std::cerr << "\tbuffer[" << i << "] = " << buffer[i] << "\n";
#endif // NDEBUG
}

template <class T>
bool Stack<T> :: empty() const 
{
   return (numElements == 0);
}

template <class T>
void Stack<T> :: clear()
{
   this->numElements = 0;
}

}; // namespace custom

#endif // Stack_H