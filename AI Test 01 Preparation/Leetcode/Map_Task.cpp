TASK: Count word frequencies in a sentence

Given a sentence of words (separated by spaces):

✔ Use unordered_map<string,int> to count how many times each word appears
✔ Then use map<string,int> to print them sorted alphabetically
Input:
apple orange banana apple orange apple kiwi

Expected Output (alphabetical order from map):
apple 3
banana 1
kiwi 1
orange 2

  #include<iostream>
#include<stack>
#include<string>
#include<queue>
#include<map>
#include<unordered_map>
using namespace std;

int main()
{
	string s;
	unordered_map<string, int>um;
	while (cin >> s)
	{
		if (s == "STOP")
			break;
		um[s]++;
	}
	map<string, int>res;
	for (auto& p : um)
	{
		res[p.first] = p.second;
	}
	for (auto& p : res)
	{
		cout << p.first << " " << p.second << " \n";
	}

}
