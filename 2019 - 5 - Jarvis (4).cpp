#include<iostream>
#include<vector>

#define REP(a, b) for(int a = 0; a < b; a++)

using namespace std;


int n;
long long k;

int m[503][503];
int bio[503][503];

int ciklus;
vector<int> red;


int main() {
    cin >> n >> k;
    REP(i, n) {
        REP(j, n) {
            cin >> m[i][j];
            m[i][j]--;
        }
    }
    int ciklus = 1;
    red.push_back(1);
    REP(i, n) {
        if (m[0][i] == 1) bio[0][i] = ciklus;
    }

    int opt = 1;
    int tuz = 0;
    while (!bio[opt][tuz]) {
        bio[opt][tuz] = ciklus + 1;
        ciklus++;
        red.push_back(opt + 1);
        int slj = m[opt][tuz];
        tuz = opt;
        opt = slj;
    }
    int poc = bio[opt][tuz] - 1;
    ciklus = ciklus - poc;

    k--;

    if (k <= poc) cout << red.at(k);
    else {
        cout << red.at(poc + (k - poc) % ciklus);
    }

    return 0;
}
