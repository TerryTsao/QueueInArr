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

      // test enqueue and dequeue first
      myQueue.enqueue("Hello");
      myQueue.enqueue("world!");
      cout << myQueue << "\n\n";
      {
         string str;
         myQueue.peek(str);
         cout << "I've peek the first in myQueue. It's \""
            << str << "\".\n";
         str = "";
         myQueue.dequeue(str);
         cout << str << " dequeued\n";
      }

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
      cout << myQueue << "\n\n";

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
      cout << myQueue << "\n\n";

      cout << "Repopulating once more:\n\n";
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
      cout << myQueue << "\n\n";
   }

   cout << "========== Display copyQueue =========\n\n";
   cout << copyQueue << "\n\n";
   if (!copyQueue.enqueue("Should not work"))
      cout << "copyQueue is full as excepted.\n";

   return 0;
}