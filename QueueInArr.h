// 
// QueueInArr.h
// Queue internally stored as an array

#ifndef QUEUE_IN_ARR_H_
#define QUEUE_IN_ARR_H_

template <class T>
class QueueInArr
{
private:
   T *arr;   // dynamic allocated array where queue is stored
   int front, back;   // front and back of the queue
   int size;   // queue size

   const static int DEFAULT_SIZE = 25;
   const static int MAX_SIZE = 1000;
   const static int MIN_SIZE = 1;

public:
   QueueInArr(int size = DEFAULT_SIZE);
   virtual ~QueueInArr() { deAllocateArr(); }
   QueueInArr(const QueueInArr<T> &qia) : arr(NULL) { *this = qia; }

   const QueueInArr<T> &operator=(const QueueInArr<T> &rhs);
   template <class T>
   friend std::ostream &operator<<(std::ostream &os, const QueueInArr<T> &qia);

   bool enqueue(T t);
   bool dequeue(T &t);
   bool peek(T &t) const;
   bool isEmpty() const { return front < 0; }

private:
   void allocateArr();
   void deAllocateArr();

   static bool isValidSize(int size);
   // use to increment index while keeping in bound 
   int indexIncrement(int &index);
};

template <class T>
void QueueInArr<T>::allocateArr()
{
   if (arr != NULL)
      deAllocateArr();
   arr = new T[size];
}

template <class T>
void QueueInArr<T>::deAllocateArr()
{
   if (arr == NULL)
      return;
   delete[] arr;
   arr = NULL;
}

template <class T>
bool QueueInArr<T>::isValidSize(int size)
{
   return size >= MIN_SIZE && size <= MAX_SIZE;
}

template <class T>
int QueueInArr<T>::indexIncrement(int &index)
{
   index = (index + 1) % size;
   return index;
}

template <class T>
QueueInArr<T>::QueueInArr(int size) : front(-1), back(0), arr(NULL)
{
   if (isValidSize(size))
      this->size = size;
   else
      this->size = DEFAULT_SIZE;
   allocateArr();
}

template <class T>
const QueueInArr<T> &QueueInArr<T>::operator=(const QueueInArr<T> &rhs)
{
   if (this != &rhs)
   {
      deAllocateArr();
      size = rhs.size;
      allocateArr();

      front = rhs.front;
      back = rhs.back;
      if (!rhs.isEmpty())
         if (front == back)
            for (int i = 0; i < size; i++)
               arr[i] = rhs.arr[i];
         else
            for (int i = front; i != back; indexIncrement(i))
               arr[i] = rhs.arr[i];
   }
   return *this;
}

template <class T>
bool QueueInArr<T>::enqueue(T t)
{
   // full case, return immediately
   if (front == back)
      return false;

   // set front to 0 if isEmpty
   if (isEmpty())
      front = 0;
   // enqueue
   arr[back] = t;
   indexIncrement(back);
   return true;
}

template <class T>
bool QueueInArr<T>::dequeue(T &t)
{
   if (!peek(t))   // return immediately if fail to peek(empty)
      return false;
   indexIncrement(front);
   if (front == back)   // if now empty, reset front and back
   {
      front = -1;
      back = 0;
   }
   return true;
}

template <class T>
bool QueueInArr<T>::peek(T &t) const
{
   if (isEmpty())
      return false;
   t = arr[front];
   return true;
}

template <class T>
std::ostream &operator<<(std::ostream &os, const QueueInArr<T> &qia)
{
   os << "--------- Here's the Queue ---------\n\n";

   if (qia.isEmpty())
      os << "*** empty queue ***";
   else
   {
      QueueInArr<T> copyQueue(qia);
      while (!copyQueue.isEmpty())
      {
         T t;
         copyQueue.dequeue(t);
         os << "[ " << t << " ] ";
      }
   }

   os << "\n\n-------- end of Queue --------";
   return os;
}

#endif /* QUEUE_IN_ARR_H_ */
