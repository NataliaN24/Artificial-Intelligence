#include<iostream>
#include <stdexcept> 

template<typename T>
class Stack
{
	T* data;
	size_t capacity;
	size_t topIndex;

	void copyFrom(const Stack<T>& other);
	void moveFrom(Stack<T>&& other)noexcept;
	void free();

public:
	Stack();
	Stack(const Stack<T>& other);
	Stack(Stack<T>&& other)noexcept;
	Stack<T>& operator=(const Stack<T>& other);
	Stack<T>& operator=(Stack<T>&& other)noexcept;
	~Stack();

	Stack(size_t capacity);
	void push(const T& element);
	void push(T&& element);
	void pop();
	bool isEmpty()const;
	size_t size()const;
	T& peek();

	

};

template<typename T>
void Stack<T>::copyFrom(const Stack<T>& other)
{
	capacity = other.capacity;
	topIndex = other.topIndex;
	data = new T[capacity];
	for (size_t i = 0; i < topIndex; i++)
	{
		data[i] = other.data[i];
	}
}

template<typename T>
void Stack<T>::moveFrom(Stack<T>&& other) noexcept
{
	capacity = other.capacity;
	topIndex = other.topIndex;
	data = other.data;

	other.capacity = 0;
	other.topIndex = 0;
	other.data = nullptr;
}

template<typename T>
void Stack<T>::free()
{
	delete[]data;
	data = nullptr;
	capacity = 0;
	topIndex = 0;
}

template<typename T>
Stack<T>::Stack()
{
	capacity = 4;
	data = new T[capacity];
	topIndex = 0;

}

template<typename T>
Stack<T>::Stack(const Stack<T>& other)
{ 
	copyFrom(other);
}

template<typename T>
Stack<T>::Stack(Stack<T>&& other) noexcept
{
	moveFrom(std::move(other));
}

template<typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template<typename T>
Stack<T>& Stack<T>::operator=(Stack<T>&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

template<typename T>
Stack<T>::Stack(size_t capacity)
{
	this->capacity = capacity;
	this->data = new T[capacity];
	topIndex = 0;
}

template<typename T>
void Stack<T>::push(const T& element)
{
	if (topIndex == capacity)
	{
		throw std::overflow_error("Stack overflow");
	}
	data[topIndex++] = element;
}

template<typename T>
void Stack<T>::push(T&& element)
{
	if (topIndex == capacity)
	{
		throw std::overflow_error("Stack overflow");
	}
	data[topIndex++] = std::move(element);
}

template<typename T>
void Stack<T>::pop()
{
	if (topIndex == 0)
	{
		throw std::underflow_error("Stack underflow");
	}
	topIndex--;

}

template<typename T>
T& Stack<T>::peek()
{
	if (topIndex == 0) {
		throw std::underflow_error("Stack underflow");
	}
	return data[topIndex - 1];
}

template<typename T>
Stack<T>::~Stack()
{
	free();
}

template<typename T>
bool Stack<T>::isEmpty() const
{
	return topIndex == 0;
}

template<typename T>
size_t Stack<T>::size() const
{
	return topIndex;
}
