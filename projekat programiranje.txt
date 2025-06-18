#include <bits/stdc++.h>

using namespace std;

const int N = 8;

int mat[N][N];                  // Матрица (0 = проходно, 1 = препрека)
bool visited[N][N];            // Да не посећујемо исту ћелију више пута
int distanceMat[N][N];         // Матрица растојања од старта

int dx[] = { -1, 0, 1, 0 };     // кретање по X
int dy[] = { 0, 1, 0, -1 };     // кретање по Y

bool isValid(int x, int y) {
    return x >= 0 && x < N && y >= 0 && y < N &&
           mat[x][y] == 0 && !visited[x][y];
}

void bfs(int startX, int startY) {
    queue<pair<int, int>> q;
    q.push({ startX, startY });
    visited[startX][startY] = true;
    distanceMat[startX][startY] = 0;

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        for (int dir = 0; dir < 4; ++dir) {
            int nx = x + dx[dir];
            int ny = y + dy[dir];

            if (isValid(nx, ny)) {
                visited[nx][ny] = true;
                distanceMat[nx][ny] = distanceMat[x][y] + 1;
                q.push({ nx, ny });
            }
        }
    }
}

int main() {
    cout << "Unesite matricu 8x8 (samo  0-slobodno polje  ili  1-prepreka):\n";

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j) {
            int x;
            cin >> x;
            if (x != 0 && x != 1) {
                cout << "Greska: dozvoljeni su samo brojevi 0 i 1!" << endl;
                return 1;
            }
            mat[i][j] = x;
        }

    if (mat[0][0] == 1 || mat[N - 1][N - 1] == 1) {
        cout << "Greska: pocetna i krajnja pozicija moraju biti 0 (prohodne)!" << endl;
        return 1;
    }

    bfs(0, 0);

    if (visited[N - 1][N - 1]) {
        cout << "Najkraci broj koraka: " << distanceMat[N - 1][N - 1] << endl;
    } else {
        cout << "Nema moguceg puta od (0,0) do (7,7)." << endl;
    }

    return 0;
}
