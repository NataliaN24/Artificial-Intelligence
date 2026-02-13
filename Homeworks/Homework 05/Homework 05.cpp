#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>

using namespace std;

class TicTacToe {
private:
    vector<vector<char>> board;
    char currentPlayer;
    char humanPlayer;
    char agentPlayer;
    bool isJudgeMode;
    bool isGameMode;

    int evaluateTerminal() {

        for (int i = 0; i < 3; i++) {
            if (board[i][0] != '_' && board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
                return (board[i][0] == 'X') ? 1 : -1;
            }
        }

        for (int j = 0; j < 3; j++) {
            if (board[0][j] != '_' && board[0][j] == board[1][j] && board[1][j] == board[2][j]) {
                return (board[0][j] == 'X') ? 1 : -1;
            }
        }

        if (board[0][0] != '_' && board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
            return (board[0][0] == 'X') ? 1 : -1;
        }
        if (board[0][2] != '_' && board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
            return (board[0][2] == 'X') ? 1 : -1;
        }

        bool isFull = true;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == '_') {
                    isFull = false;
                    break;
                }
            }
            if (!isFull) break;
        }

        return isFull ? 0 : -2;
    }

    bool isTerminal() {
        return evaluateTerminal() != -2;
    }

    char getWinner() {
        int result = evaluateTerminal();
        if (result == 1) return 'X';
        if (result == -1) return 'O';
        if (result == 0) return 'D';
        return 'N';
    }

    vector<int> minimax(char player, int depth, int alpha, int beta) {
        int terminalValue = evaluateTerminal();

        if (terminalValue != -2) {
            if (terminalValue == 1) {
                return { 10 - depth, -1, -1 };
            }
            else if (terminalValue == -1) {
                return { depth - 10, -1, -1 };
            }
            else {
                return { 0, -1, -1 };
            }
        }

        if (player == 'X') {
            int maxValue = INT_MIN;
            int bestRow = -1, bestCol = -1;

            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (board[i][j] == '_') {
                        board[i][j] = 'X';
                        vector<int> result = minimax('O', depth + 1, alpha, beta);
                        int value = result[0];
                        board[i][j] = '_';

                        if (value > maxValue) {
                            maxValue = value;
                            bestRow = i;
                            bestCol = j;
                        }
                        else if (value == maxValue && i == 1 && j == 1) {

                            bestRow = i;
                            bestCol = j;
                        }

                        alpha = max(alpha, value);
                        if (beta <= alpha) {

                            return { maxValue, bestRow, bestCol };
                        }
                    }
                }
            }

            return { maxValue, bestRow, bestCol };
        }

        else {
            int minValue = INT_MAX;
            int bestRow = -1, bestCol = -1;

            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (board[i][j] == '_') {
                        board[i][j] = 'O';
                        vector<int> result = minimax('X', depth + 1, alpha, beta);
                        int value = result[0];
                        board[i][j] = '_';

                        if (value < minValue) {
                            minValue = value;
                            bestRow = i;
                            bestCol = j;
                        }
                        else if (value == minValue && i == 1 && j == 1) {

                            bestRow = i;
                            bestCol = j;
                        }

                        beta = min(beta, value);
                        if (beta <= alpha) {

                            return { minValue, bestRow, bestCol };
                        }
                    }
                }
            }

            return { minValue, bestRow, bestCol };
        }
    }

    pair<int, int> findBestMove(char player) {
        vector<int> result = minimax(player, 0, INT_MIN, INT_MAX);
        return { result[1], result[2] };
    }

    bool makeMove(int row, int col, char player) {

        row--;
        col--;

        if (row < 0 || row >= 3 || col < 0 || col >= 3) {
            return false;
        }

        if (board[row][col] != '_') {
            return false;
        }

        board[row][col] = player;
        return true;
    }

    void printBoard() {
        cout << "+---+---+---+" << endl;
        for (int i = 0; i < 3; i++) {
            cout << "|";
            for (int j = 0; j < 3; j++) {
                cout << " " << board[i][j] << " |";
            }
            cout << endl;
            cout << "+---+---+---+" << endl;
        }
    }

    void readBoard() {
        string line;

        getline(cin, line);

        board.clear();
        board.resize(3, vector<char>(3));

        for (int i = 0; i < 3; i++) {
            getline(cin, line);

            int col = 0;
            for (size_t j = 0; j < line.length() && col < 3; j++) {
                if (line[j] == 'X' || line[j] == 'O' || line[j] == '_') {
                    board[i][col] = line[j];
                    col++;
                }
            }

            getline(cin, line);
        }
    }

public:
    TicTacToe() {
        board.resize(3, vector<char>(3, '_'));
        isJudgeMode = false;
        isGameMode = false;
    }

    void runJudgeMode() {
        isJudgeMode = true;
        string turn, player;
        cin >> turn >> player;
        currentPlayer = player[0];

        cin.ignore();

        readBoard();

        if (isTerminal()) {
            cout << -1 << endl;
            return;
        }

        pair<int, int> move = findBestMove(currentPlayer);

        cout << (move.first + 1) << " " << (move.second + 1) << endl;
    }

    void runGameMode() {
        isGameMode = true;
        string first, firstPlayerStr, human, humanPlayerStr;
        cin >> first >> firstPlayerStr;
        char firstPlayer = firstPlayerStr[0];
        cin >> human >> humanPlayerStr;
        humanPlayer = humanPlayerStr[0];
        agentPlayer = (humanPlayer == 'X') ? 'O' : 'X';

        cin.ignore();

        readBoard();

        int xCount = 0, oCount = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == 'X') xCount++;
                if (board[i][j] == 'O') oCount++;
            }
        }

        if (xCount == oCount) {
            currentPlayer = firstPlayer;
        }
        else {
            currentPlayer = (firstPlayer == 'X') ? 'O' : 'X';
        }

        if (isTerminal()) {
            char winner = getWinner();
            if (winner == 'X') {
                cout << "WINNER: X" << endl;
            }
            else if (winner == 'O') {
                cout << "WINNER: O" << endl;
            }
            else {
                cout << "DRAW" << endl;
            }
            return;
        }

        while (!isTerminal()) {
            if (currentPlayer == humanPlayer) {
                int row, col;
                cin >> row >> col;

                while (!makeMove(row, col, humanPlayer)) {
                    cin >> row >> col;
                }

                printBoard();
                currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
            }
            else {

                pair<int, int> move = findBestMove(agentPlayer);
                makeMove(move.first + 1, move.second + 1, agentPlayer);

                printBoard();
                currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
            }
        }

        char winner = getWinner();
        if (winner == 'X') {
            cout << "WINNER: X" << endl;
        }
        else if (winner == 'O') {
            cout << "WINNER: O" << endl;
        }
        else {
            cout << "DRAW" << endl;
        }
    }

    void run() {
        string mode;
        cin >> mode;

        if (mode == "JUDGE") {
            runJudgeMode();
        }
        else if (mode == "GAME") {
            runGameMode();
        }
    }
};

int main() {
    TicTacToe game;
    game.run();
    return 0;
}
