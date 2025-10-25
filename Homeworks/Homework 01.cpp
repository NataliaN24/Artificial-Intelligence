#include <iostream>
#include <vector>
#include <string>
using namespace std;

bool isGoal(const string& pattern, const string& goal)
{
    return pattern == goal;
}

bool DFS(string& pattern, const string& goal, vector<string>& path, bool& found)
{
    if (found)
    {
        return true;
    }
    path.push_back(pattern);

    if (isGoal(pattern, goal))
    {
        for (const auto& s : path)
        {
            cout << s << '\n';
        }

        found = true;
        return true;
    }

    int length = pattern.size();

    for (int i = 0; i < length; ++i)
    {
        if (pattern[i] == '>')
        {
            if (i + 1 < length && pattern[i + 1] == '_')
            {
                swap(pattern[i], pattern[i + 1]);
                if (DFS(pattern, goal, path, found))
                {
                    return true;
                }
                swap(pattern[i], pattern[i + 1]);
            }
            if (i + 2 < length && pattern[i + 1] != '_' && pattern[i + 2] == '_')
            {
                swap(pattern[i], pattern[i + 2]);
                if (DFS(pattern, goal, path, found))
                {
                    return true;
                }
                swap(pattern[i], pattern[i + 2]);
            }
        }
        else if (pattern[i] == '<')
        {
            if (i - 1 >= 0 && pattern[i - 1] == '_')
            {
                swap(pattern[i], pattern[i - 1]);
                if (DFS(pattern, goal, path, found))
                {
                    return true;
                }
                swap(pattern[i], pattern[i - 1]);
            }
            if (i - 2 >= 0 && pattern[i - 1] != '_' && pattern[i - 2] == '_') {
                swap(pattern[i], pattern[i - 2]);
                if (DFS(pattern, goal, path, found))
                {
                    return true;
                }
                swap(pattern[i], pattern[i - 2]);
            }
        }
    }

    path.pop_back();
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    string pattern = string(N, '>') + "_" + string(N, '<');
    string goal = string(N, '<') + "_" + string(N, '>');

    vector<string> path;
    bool found = false;

    DFS(pattern, goal, path, found);
    return 0;
}
