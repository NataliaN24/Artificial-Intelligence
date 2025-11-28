Task: Simulate a Customer Service Queue

You have a queue of people waiting to be served.

You will receive commands of 3 types:

1. ADD X

Add person with ID X to the back of the queue.

2. SERVE

Serve (remove) the person at the front of the queue.
If the queue is empty → print "EMPTY".

3. FRONT

Print the ID of the person at the front of the queue.
If empty → print "EMPTY".

You must process all commands in order.

#include<iostream>
#include<stack>
#include<string>
#include<queue>
using namespace std;

int main()
{
	int n;
	cin >> n;

	
	queue<int>person;
	while (n--)
	{
		string s;
		cin >> s;
		if (s == "ADD")
		{
			int x;
			cin >> x;
			person.push(x);
		}

		else if (s == "SERVE")
		{
			if (person.empty())
			{
				cout << "EMPTY";
			}
			else {
				person.pop();
			}

		}
		else if (s == "FRONT")
		{
			if (person.empty())
			{
				cout << "EMPTY";
			}
			else
			{
				cout << person.front() << endl;
			}
			
		}
	}

}
