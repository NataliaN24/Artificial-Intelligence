#include<iostream>
#include <stdexcept> 

template<typename T>
class Queue
{
	T* data;
	size_t capacity;
	size_t front;
	size_t rear;
	size_t count;

	void copyFrom(const Queue<T>& other);
	void moveFrom(Queue<T>&& other)noexcept;
	void free();

public:
	Queue();
	Queue(const Queue<T>& other);
	Queue(Queue<T>&& other)noexcept;
	Queue<T>& operator=(const Queue<T>& other);
	Queue<T>& operator=(Queue<T>&& other)noexcept;
	~Queue();

	Queue(size_t capacity);
	void enqueue(const T& element);
	void enqueue(T&& element);
	void dequeue();
	bool isEmpty()const;
	bool isFull()const;
	size_t size()const;
	T& peek();

	

};

template<typename T>
void Queue<T>::copyFrom(const Queue<T>& other)
{
	capacity = other.capacity;
	front = other.front;
	rear = other.rear;
	data = new T[capacity];
	for (size_t i = 0; i < count; i++)
	{
		data[i] = other.data[(front+i)%capacity];
	}
}

template<typename T>
void Queue<T>::moveFrom(Queue<T>&& other) noexcept
{
	capacity = other.capacity;
	front = other.front;
	rear = other.rear;
	data = other.data;

	other.capacity = 0;
	other.topIndex = 0;
	other.front = 0;
	other.rear = 0;
	other.data = nullptr;
	
}

template<typename T>
void Queue<T>::free()
{
	delete[]data;
	data = nullptr;
	capacity = 0;
	front = 0;
	rear = 0;
}

template<typename T>
Queue<T>::Queue()
{
	capacity = 4;
	data = new T[capacity];
	front = 0;
	rear = 0;
	size = 0;

}

template<typename T>
Queue<T>::Queue(const Queue<T>& other)
{ 
	copyFrom(other);
}

template<typename T>
Queue<T>::Queue(Queue<T>&& other) noexcept
{
	moveFrom(std::move(other));
}

template<typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template<typename T>
Queue<T>& Queue<T>::operator=(Queue<T>&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

template<typename T>
Queue<T>::Queue(size_t capacity)
{
	this->capacity = capacity;
	this->data = new T[capacity];
	front = 0;
	rear = 0;
	count = 0;
}

template<typename T>
void Queue<T>::enqueue(const T& element)
{
	if (isFull())
	{
		throw std::overflow_error("Queue overflow");
	}
	data[rear] = element;
	rear = (rear + 1) % capacity;
	++count;
}

template<typename T>
void Queue<T>::enqueue(T&& element)
{
	if (isFull())
	{
		throw std::overflow_error("Queue overflow");
	}
	data[rear] = std::move(element);
	rear = (rear + 1) % capacity;
	++count;
}

template<typename T>
void Queue<T>::dequeue()
{
	if (isEmpty())
	{
		throw std::underflow_error("Queue underflow");
	}
	front = (front + 1) % capacity;
	--count;

}

template<typename T>
T& Queue<T>::peek()
{
	if (isEmpty())
	{
		throw std::underflow_error("Queue underflow");
	}
	return data[front];
}

template<typename T>
Queue<T>::~Queue()
{
	free();
}

template<typename T>
bool Queue<T>::isEmpty() const
{
	return count == 0;
}

template<typename T>
bool Queue<T>::isFull() const
{
	return count==capacity;
}

template<typename T>
size_t Queue<T>::size() const
{
	return count;
}
