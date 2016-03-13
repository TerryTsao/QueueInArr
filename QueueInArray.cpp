#include <iostream>
#include <string>
#include <sstream>
#include "QueueInArr.h"

using namespace std;

int main()
{
   const int QUEUE_SIZE = 5;

   QueueInArr<string> myQueue(QUEUE_SIZE), copyQueue;

   cout << "============= test myQueue ============\n\n";
   {
      if (myQueue.isEmpty())
         cout << "myQueue is created empty.\n\n";
      for (int i = 0; ; i++)
      {
         ostringstream oss;
         oss << "str #" << i;
         if (myQueue.enqueue(oss.str()))
            cout << oss.str() << " added to myQueue.\n";
         else
            break;
      }

      cout << "\nmyQueue is full now.\n\n";
      cout << myQueue;

      cout << "cp myQueue copyQueue\n\n";
      copyQueue = myQueue;

      cout << "==============\n"
         << "Starting to dequeue myQueue:\n\n";
      while (!myQueue.isEmpty())
      {
         string str;
         if (myQueue.dequeue(str))
            cout << str << " dequeued.\n";
      }

      cout << "\nAn empty queue now.\n\n";
      cout << myQueue;
   }

   cout << "========== Display copyQueue =========\n\n";
   cout << copyQueue;
   if (!copyQueue.enqueue("Should not work"))
      cout << "copyQueue is full as excepted.\n";

   return 0;
}