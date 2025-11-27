Implement an admissible heuristic for grid-based pathfinding

You are given a 2D grid representing a map.
Movement is allowed up, down, left, right only (no diagonals).
This means A* should use a heuristic that never overestimates the true cost.

👉 Your task:

Implement a heuristic function:

int heuristic(int x1, int y1, int x2, int y2);


where:

(x1, y1) = current position of the agent

(x2, y2) = goal position

✔ Requirements:

The heuristic must be admissible for 4-direction movement.

The heuristic must be based on a real distance function.

The heuristic must be simple to compute efficiently.
 
  
  int heuristic(int x1, int y1, int x2, int y2)
{
    return abs(x1 - x2) + abs(y1 - y2);
}
  int main()
{
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;

    cout << heuristic(x1, y1, x2, y2);

    return 0;
}

