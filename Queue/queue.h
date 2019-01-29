/***********************************************************************
 * Header:
 *    Queue
 * Summary:
 *    This class contains the notion of an Stack: a bucket to hold
 *    buffer for the user. This is just a starting-point for more advanced
 *    constainers such as the Stack, set, stack, queue, deque, and map
 *    which we will build later this semester.
 *
 *    This will contain the class definition of:
 *       Queue             : similar to std::Queue
 * Author
 *    Caleb and Taylor
 ************************************************************************/

#ifndef QUEUE_H
#define QUEUE_H

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


template <class T>
class queue 
{
    public:
    T * buffer;
    int numPush;
    int numPop;
    int numCapacity;
    void resize(int numCapacity);
    int iHead() 
    { 
        if (numCapacity != 0)
            return numPop % numCapacity;
        return 0;
    }
    int iTail() 
    {
        if (numCapacity != 0)
            return (numPush - 1) % numCapacity; 
        return 0;
    }

    
    queue() { numCapacity = 0; numPop = 0; numPush = 0; buffer = NULL; }
    queue(int numCapacity) 
    { 
        this->numCapacity = numCapacity;
        numPop = 0;
        numPush = 0; 
        resize(numCapacity); 
    }
    queue(queue & rhs) 
    { 
        if (rhs.capacity() != capacity())
       {
          this->numCapacity = rhs.size();
          resize(this->numCapacity);
       }

        this->numPop = rhs.numPop;
        this->numPush = rhs.numPush;
        
       for (int i = 0; i < size(); i++)
        this->buffer[i] = rhs.buffer[i];

    }
    ~queue() { delete [] buffer; }

    queue & operator = (const queue <T> & rhs) throw (const char *);
    int size() const { return numPush - numPop; }
    void clear();
    int capacity() const { return numCapacity; } 
    bool empty() { return !(numPush - numPop); }
    void push(T t);
    void pop();
    T & front();
    T & back();

};
    /*******************************************
    * Stack :: Assignment
    *******************************************/
    template <class T>
    queue <T> & queue <T> :: operator = (const queue <T> & rhs)
              throw (const char *)
    {
       // we can only copy Stacks of equal size. Stacks are not this way!
       if (rhs.capacity() != capacity())
       {
          this->numCapacity = rhs.size();
          resize(this->numCapacity);
       }

        numPop = 0;
        numPush = rhs.size();
        this->numCapacity = rhs.size();

       for (int i = 0; i < size(); i++)
          buffer[i] = rhs.buffer[i];
       return *this;
    }

    template <class T>
    void queue <T> :: clear() 
    {
        this->numPop = 0;
        this->numPush = 0;
    }

    template <class T>
    void queue <T> :: push(T t)
    {
        if (size() == 0)
        {
            resize(1);
        }
        if (size() == capacity())
        {
            resize((capacity() * 2));
        }
        numPush++;
        buffer[iTail()] = t;
    }

    template <class T>
    void queue <T> :: pop()
    {
        if (!empty())
        {
            numPop++;
        }
    }

    template <class T>
    T & queue <T> :: front()
    {
        if (empty())
        {
            throw "Error: asking for front of empty queue.";
        }
        return buffer[iHead()];
    }

    template <class T>
    T & queue <T> :: back()
    {
        if (empty())
        {
            throw "Error: asking for back of empty queue.";
        }
        return buffer[iTail()];
    }

    template <class T>
    void queue <T> :: resize(int numCapacity)
    {
        try
        {
            if (numCapacity == 0)
            {
                buffer = NULL;
                numPush = 0;
                numPop = 0;
                this->numCapacity = numCapacity;
            }
            if (numCapacity > 0)
            {
                T * temp = new T[numCapacity];
                for (int i = 0; i < size(); i++)
                {
                    temp[i] = buffer[(iHead() + i) % this->numCapacity];
                }
                delete [] buffer;
                this->numCapacity = numCapacity;
                if (size() > capacity())
                {
                    numPush = numCapacity;    
                }
                else
                    numPush = size();
                numPop = 0;
                buffer = temp;
            }
            
        }
        catch (std::bad_alloc)
        {
            throw "ERROR: Unable to allocate new buffer for Stack";
        }
    }

};

#endif



