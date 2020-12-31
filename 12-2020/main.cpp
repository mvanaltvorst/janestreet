#include <iostream>

using namespace std;

// GRID 1
const int INPUTGRID1[7][7] = {
    {-1, -1,  4, -1, -1, -1, -1},
    {-1, -1, -1,  6, -1, -1, -1},
    { 5, -1, -1, -1, -1, -1, -1},
    {-1,  3, -1, -1, -1,  6, -1},
    {-1, -1, -1, -1, -1, -1,  2},
    {-1, -1, -1,  1, -1, -1, -1},
    {-1, -1, -1, -1,  4, -1, -1}
};
const int INNV1[7] = { 5,  4, -1, -1, -1,  7,  5};
const int INEV1[7] = { 7,  4, -1, -1, -1,  7,  6};
const int INSV1[7] = { 5,  7, -1, -1, -1,  3,  6};
const int INWV1[7] = { 5,  7, -1, -1, -1,  5,  7};

// GRID 2
const int INPUTGRID2[7][7] = {
    {-1,  2, -1, -1, -1, -1, -1},
    { 2, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1,  3, -1},
    {-1, -1, -1, -1,  3, -1, -1},
    {-1, -1, -1,  3, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1,  1}
};
const int INNV2[7] = {-1, -1,  5,  6, -1,  6,  7};
const int INEV2[7] = { 6,  6,  4, -1, -1, -1, -1};
const int INSV2[7] = { 6,  7,  5, -1, -1, -1, -1};
const int INWV2[7] = {-1, -1,  5,  6, -1,  7,  6};

// GRID 3
const int INPUTGRID3[7][7] = {
    {-1, -1, -1, -1,  4, -1, -1},
    {-1,  6, -1, -1, -1, -1, -1},
    { 4, -1, -1, -1, -1, -1,  6},
    {-1, -1, -1, -1, -1, -1, -1},
    { 6, -1, -1, -1, -1, -1,  4},
    {-1, -1, -1, -1, -1,  6, -1},
    {-1, -1,  4, -1, -1, -1, -1}
};
const int INNV3[7] = { 7, -1, -1,  5, -1,  7, -1};
const int INEV3[7] = {-1, -1, -1,  5, -1, -1, -1};
const int INSV3[7] = {-1,  7, -1,  3, -1, -1,  5};
const int INWV3[7] = {-1, -1, -1,  7, -1, -1, -1};

 //GRID 4
const int INPUTGRID4[7][7] = {
    {-1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1,  3},
    {-1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1,  4, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1},
    {-1, -1,  3, -1, -1, -1, -1}
};
const int INNV4[7] = {-1, -1, -1, -1, -1, -1, -1};
const int INEV4[7] = {-1,  6, -1,  4, -1,  2, -1};
const int INSV4[7] = {-1,  6, -1,  5, -1,  4, -1};
const int INWV4[7] = { 1,  2,  3,  4,  5,  6,  7};

class Grid {
    private:
        int piecesLeft[7];
        int rowSum[7];
        int rowPieces[7];
        int columnSum[7];
        int columnPieces[7];
        int nv[7], ev[7], sv[7], wv[7];
        pair<int, int> parent[7][7];
        bool isTurn[7][7];
        pair<int, int> nextCoordinate[7][7];
        bool visited[7][7];
        
        bool checkFinal() {
            if (!checkRowStrong(3)) return false;
            if (!checkColumnStrong(3)) return false;
            if (!checkNV(3)) return false;
            if (!checkEV(3)) return false;
            if (!checkSV(3)) return false;
            if (!checkWV(3)) return false;
            if (!checkConnectedness()) return false;
            if (!checkTwoByTwo(3, 3)) return false;
            print();
            return true;
        }
        bool checkNV(int j) {
            if (nv[j] == -1) return true;
            for (int i = 0; i < 7; i++) {
                if (grid[i][j] >= 1) {
                    return grid[i][j] == nv[j];
                }
            }
            return false;
        }
        bool checkNVWeak() {
            for (int j = 0; j < 7; j++) {
                if (nv[j] == -1) continue;
                for (int i = 0; i < 7; i++) {
                    if (grid[i][j] == 0) continue;
                    if (grid[i][j] == -1) break;
                    if (grid[i][j] != nv[j]) return false;
                    break;
                }
            }
            return true;
        }
        bool checkSV(int j) {
            if (sv[j] == -1) return true;
            for (int i = 6; i >= 0; i--) {
                if (grid[i][j] >= 1) {
                    return grid[i][j] == sv[j];
                }
            }
            return false;
        }
        bool checkSVWeak() {
            for (int j = 0; j < 7; j++) {
                if (sv[j] == -1) continue;
                for (int i = 6; i >= 0; i--) {
                    if (grid[i][j] == 0) continue;
                    if (grid[i][j] == -1) break;
                    if (grid[i][j] != sv[j]) return false;
                    break;
                }
            }
            return true;
        }
        bool checkTwoByTwo(int i, int j) {
            if (grid[i][j] <= 0) return true;
            pair<int, int> neighbourPairs[4][3] = {
                {{1, 0}, {0, 1}, {1, 1}},
                {{1, 0}, {0, -1}, {1, -1}},
                {{-1, 0}, {0, -1}, {-1, -1}},
                {{-1, 0}, {0, 1}, {-1, 1}},
            };
            for (int k = 0; k < 4; k++) {
                int filled = 0;
                for (auto d : neighbourPairs[k]) {
                    int ni = i + d.first, nj = j + d.second;
                    if (ni < 0 || ni >= 7 || nj < 0 || nj >= 7) break;
                    if (grid[ni][nj] <= 0) break;
                    filled++;
                }
                if (filled == 3) return false;
            }
            return true;
        }
        bool checkConnectedness() {
            for (int i = 0; i < 7; i++) {
                for (int j = 0; j < 7; j++) {
                    visited[i][j] = false;
                }
            }
            for (int i = 0; i < 7; i++) {
                for (int j = 0; j < 7; j++) {
                    if (grid[i][j] >= 1) {
                        connectednessDFS(i, j);
                        goto outer;
                    }
                }
            }
outer:
            for (int i = 0; i < 7; i++) {
                for (int j = 0; j < 7; j++) {
                    if (grid[i][j] != 0) {
                        if (!visited[i][j]) return false;
                    }
                }
            }
            return true;
        }
        void connectednessDFS(int i, int j) {
            visited[i][j] = true;
            pair<int, int> directions[4] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
            for (auto d : directions) {
                int ni = i + d.first;
                int nj = j + d.second;
                if (ni < 0 || ni >= 7 || nj < 0 || nj >= 7) continue;
                if (grid[ni][nj] == 0) continue;
                if (visited[ni][nj]) continue; 
                connectednessDFS(ni, nj);
            }
        }
        bool checkEV(int i) {
            if (ev[i] == -1) return true;
            for (int j = 6; j >= 0; j--) {
                if (grid[i][j] >= 1) {
                    return grid[i][j] == ev[i];
                }
            }
            return false;
        }
        bool checkEVWeak() {
            for (int i = 0; i < 7; i++) {
                if (ev[i] == -1) continue;
                for (int j = 6; j >= 0; j--) {
                    if (grid[i][j] == 0) continue;
                    if (grid[i][j] == -1) break;
                    if (grid[i][j] != ev[i]) return false;
                    break;
                }
            }
            return true;
        }
        bool checkWV(int i) {
            if (wv[i] == -1) return true;
            for (int j = 0; j < 7; j++) {
                if (grid[i][j] >= 1) {
                    return grid[i][j] == wv[i];
                }
            }
            return false;
        }
        bool checkWVWeak() {
            for (int i = 0; i < 7; i++) {
                if (wv[i] == -1) continue;
                for (int j = 0; j < 7; j++) {
                    if (grid[i][j] == 0) continue;
                    if (grid[i][j] == -1) break;
                    if (grid[i][j] != wv[i]) return false;
                    break;
                }
            }
            return true;
        }
        void initCoordinateOrder() {
            // We do the dfs in a spiral from outside to inside
            // so we can take advantage of the side views earlier.
            // Just create a table to get from one coordinate to the next,
            // and log which coordinates are turns in the spiral
            int i = 3, j = 3;
            int di = 0, dj = -1;
            int maxi = 3, mini = 3, maxj = 3, minj = 3;
            for (int k = 0; k < 48; k++) {
                nextCoordinate[i+di][j+dj] = make_pair(i, j);
                i += di;
                j += dj;
                if (i > maxi) {
                    maxi = i;
                    int buffer = dj;
                    dj = di;
                    di = -buffer;
                    isTurn[i][j] = true;
                }
                if (i < mini) {
                    mini = i;
                    int buffer = dj;
                    dj = di;
                    di = -buffer;
                    isTurn[i][j] = true;
                }
                if (j > maxj) {
                    maxj = j;
                    int buffer = dj;
                    dj = di;
                    di = -buffer;
                    isTurn[i][j] = true;
                }
                if (j < minj) {
                    minj = j;
                    int buffer = dj;
                    dj = di;
                    di = -buffer;
                    isTurn[i][j] = true;
                }
            }
            nextCoordinate[3][3] = make_pair(3, 3);
        }
        bool dfs(int i, int j) {
            if (i == 3 && j == 3) return checkFinal();
            if (i != -1) {
                if (!checkTwoByTwo(i, j)) return false;
                if (isTurn[i][j]) {
                    if (i == j || i == j+1) {
                        if (!checkColumnStrong(j)) return false;
                        if (!checkNV(j)) return false;
                        if (!checkSV(j)) return false;
                        if (!checkNVWeak()) return false;
                        if (!checkEVWeak()) return false;
                        if (!checkSVWeak()) return false;
                        if (!checkWVWeak()) return false;
                    } else {
                        if (!checkRowStrong(i)) return false;
                        if (!checkEV(i)) return false;
                        if (!checkWV(i)) return false;
                        if (!checkNVWeak()) return false;
                        if (!checkEVWeak()) return false;
                        if (!checkSVWeak()) return false;
                        if (!checkWVWeak()) return false;
                    }
                    if (!checkConnectedness()) return false;
                }
                int oldi = i, oldj = j;
                i = nextCoordinate[oldi][oldj].first;
                j = nextCoordinate[oldi][oldj].second;
            } else {
                i = 0; j = 0;
            }
            if (!isFillable(i, j)) return dfs(i, j);
            for (int value = 0; value <= 7; value++) {
                if (value >= 1 && piecesLeft[value-1] == 0) continue;
                grid[i][j] = value;
                if (value >= 1) {
                    rowSum[i] += value;
                    columnSum[j] += value;
                    rowPieces[i]++;
                    columnPieces[j]++;
                    piecesLeft[value-1]--;
                }
                if (dfs(i, j)) return true;
                if (value >= 1) {
                    rowSum[i] -= value;
                    columnSum[j] -= value;
                    rowPieces[i]--;
                    columnPieces[j]--;
                    piecesLeft[value-1]++;
                }
            }
            grid[i][j] = -1;
            return false;
        }
        bool checkRowStrong(int i) {
            return (rowPieces[i] == 4) && (rowSum[i] == 20) && checkEV(i) && checkWV(i);
        }
        bool checkColumnStrong(int j) {
            return (columnPieces[j] == 4) && (columnSum[j] == 20) && checkNV(j) && checkSV(j);
        }
        bool isFillable(int i, int j) {
            return grid[i][j] == -1;
        }
    public:
        int grid[7][7];
        Grid(const int inGrid[7][7], const int inNV[7], const int inEV[7], const int inSV[7], const int inWV[7]) {
            for (int i = 0; i < 7; i++) {
                rowSum[i] = 0;
                columnSum[i] = 0;
                rowPieces[i] = 0;
                columnPieces[i] = 0;
                piecesLeft[i] = i+1;
                nv[i] = inNV[i];
                ev[i] = inEV[i];
                sv[i] = inSV[i];
                wv[i] = inWV[i];
            }
            for (int i = 0; i < 7; i++) {
                for (int j = 0; j < 7; j++) {
                    isTurn[i][j] = false;
                    int value = inGrid[i][j];
                    grid[i][j] = value;
                    if (value >= 1) {
                        rowSum[i] += value;
                        columnSum[j] += value;
                        rowPieces[i]++;
                        columnPieces[j]++;
                        piecesLeft[value - 1]--;
                    }
                }
            }
            initCoordinateOrder();
        }
        void solve() {
            dfs(-1, -1);
        }
        void print() {
            for (int i = 0; i < 7; i++) {
                for (int j = 0; j < 7; j++) {
                    if (grid[i][j] == 0) cout << ".\t";
                    else {
                        cout << grid[i][j] << '\t';
                    }
                }
                cout << endl;
            }
            cout << endl;
        }
        void add(Grid other) {
            for (int i = 0; i < 7; i++) {
                for (int j = 0; j < 7; j++) {
                    grid[i][j] += other.grid[i][j];
                }
            }
        }
        int valuesSquared() {
            int acc = 0;
            for (int i = 0; i < 7; i++) {
                for (int j = 0; j < 7; j++) {
                    acc += grid[i][j] * grid[i][j];
                }
            }
            return acc;
        }
};

int main() {
    // solve all grids
    Grid grid1(INPUTGRID1, INNV1, INEV1, INSV1, INWV1);
    Grid grid2(INPUTGRID2, INNV2, INEV2, INSV2, INWV2);
    Grid grid3(INPUTGRID3, INNV3, INEV3, INSV3, INWV3);
    Grid grid4(INPUTGRID4, INNV4, INEV4, INSV4, INWV4);
    grid1.solve();
    grid2.solve();
    grid3.solve();
    grid4.solve();
    // sum all grids into grid 1
    grid1.add(grid2);
    grid1.add(grid3);
    grid1.add(grid4);
    grid1.print();
    cout << grid1.valuesSquared() << endl;
}
