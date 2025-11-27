TASK: Heuristic for a Robot Moving in a Warehouse With Obstacles (but diagonal allowed)

You have a 2D grid representing a warehouse floor.
A robot moves from a start cell to a goal cell.
Movement rules:

The robot may move in 8 directions (N, S, E, W, NE, NW, SE, SW)

Each move (straight or diagonal) costs 1

This is like a king moving on a chessboard.

👉 Your task:

Implement a heuristic function:

int heuristic(int x1, int y1, int x2, int y2);


that estimates the cost from the robot position (x1, y1) to goal (x2, y2).

⚠️ Requirements:

The heuristic must be admissible

The heuristic must consider that diagonal moves are allowed

The heuristic should give a closer estimate than Manhattan, but still safe

The heuristic must run in constant time
  int heuristic(int x1, int y1, int x2, int y2)
{
    return max(abs(x1 - x2), abs(y1 - y2));
}
