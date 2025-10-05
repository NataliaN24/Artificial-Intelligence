#include"Stack.hpp"

int main()
{
	try 
    {
		Stack<int> myStack;

		myStack.push(10);
		myStack.push(20);
		myStack.push(30);

		std::cout << "Stack size: " << myStack.size() << std::endl;
		std::cout << "Top element: " << myStack.peek() << std::endl;

		myStack.pop();

		std::cout << "Stack size after pop: " << myStack.size() << std::endl;
		std::cout << "Top element after pop: " << myStack.peek() << std::endl;
	}
	catch (const std::exception& e)
    {
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	return 0;
}
