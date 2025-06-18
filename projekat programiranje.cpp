#include <bits/stdc++.h>

using namespace std;

const int N = 8;

int mat[N][N];                  // matrica 8x8 (0 prohodno, 1 prepreka)
bool visited[N][N];            // da ne posecuje isto polje ponovo
int distanceMat[N][N];         // matrica u koju se uipisuju rastojanja od pocetne pozicije

int dx[] = { -1, 0, 1, 0 };     // kretanje po X
int dy[] = { 0, 1, 0, -1 };     // kretanje po Y

bool isValid(int x, int y) {
    return x >= 0 && x < N && y >= 0 && y < N &&
           mat[x][y] == 0 && !visited[x][y];
}

void bfs(int startX, int startY) {
    queue<pair<int, int>> q;
    q.push({ startX, startY });
    visited[startX][startY] = true;
    distanceMat[startX][startY] = 0; //u red ubacuje startnu poziciju i upisuje 0 potrebnih koraka

    while (!q.empty()) {
        auto [x, y] = q.front(); //ispituje prvi element iz reda
        q.pop();                 //izbacuje ga

        for (int dir = 0; dir < 4; ++dir) {  //isprobava sve pravce
            int nx = x + dx[dir];
            int ny = y + dy[dir];

            if (isValid(nx, ny)) {                              //ako je polje prohodno
                visited[nx][ny] = true;                         //oznaci kao poseceno
                distanceMat[nx][ny] = distanceMat[x][y] + 1;    //u matricu koraka upisi potreban broj koraka do tog polja
                q.push({ nx, ny });                             //polje ubaci u red
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
            if (x != 0 && x != 1) {                                    //ispitujemo da li je uneti broj 1 ili 0
                cout << "Greska: dozvoljeni su samo brojevi 0 i 1!" << endl;   
                return 1;
            }
            mat[i][j] = x;
        }

    if (mat[0][0] == 1 || mat[N - 1][N - 1] == 1) {                     //ispitujemo da li su pocetna i krajnja pozicija prohode
        cout << "Greska: pocetna i krajnja pozicija moraju biti 0 (prohodne)!" << endl;
        return 1;
    }

    bfs(0, 0); //pozivamo bfs

    if (visited[N - 1][N - 1]) {
        cout << "Najkraci broj koraka: " << distanceMat[N - 1][N - 1] << endl; //ako je bfs stigao do pozicije (N-1)(N-1) ispisi broj koraka
    } else {
        cout << "Nema moguceg puta od (0,0) do (7,7)." << endl; //ako nije.. nema moguceg resenja za unetu matricu
    }

    return 0;
}
