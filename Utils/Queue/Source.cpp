#include "Queue.hpp"


int main() 
{
	try
    {
		Queue<int> myQueue(5);

		myQueue.enqueue(10);
		myQueue.enqueue(20);
		myQueue.enqueue(30);

		std::cout << "Queue size: " << myQueue.size() << std::endl;
		std::cout << "Front element: " << myQueue.peek() << std::endl;

		myQueue.dequeue();

		std::cout << "Queue size after dequeue: " << myQueue.size() << std::endl;
		std::cout << "Front element after dequeue: " << myQueue.peek() << std::endl;
	}
	catch (const std::exception& e) 
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	return 0;
}
