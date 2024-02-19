// KOLO 2018

#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <vector>
#include <iostream>
#include <ctime>
#include <unistd.h>

using namespace std;

#define TRACE(x) cerr << #x <<  " = " << x << endl
#define _ << " " <<
#define FOR(i, a, b) for (int i=(a); i<(b); i++)
#define REP(i, n) FOR(i, 0, n)

#define X first
#define Y second

typedef pair<int, int> P;
typedef long long ll;

const int MAX = 1<<20;

P edge[MAX];
vector <P> V[MAX]; //node, id
int L, R, m;
int bio[MAX];
int sol[MAX];

void dfs(int node) {
  for (; !V[node].empty(); ) {
    P tmp = V[node].back();
    V[node].pop_back();
    if (bio[tmp.Y]) continue;
    bio[tmp.Y] = (tmp.X < L || (tmp.X == L+R+1)) ? 1 : 2;
    dfs(tmp.X);
  }
}

void tour(const vector <int> &E) {
  for (auto it : E) {
    dfs(edge[it].X);
    dfs(edge[it].Y);
  }
}

int tid;
void add_edge(int a, int b) {
  V[a].push_back(P(b, tid));
  V[b].push_back(P(a, tid++));
}

void solve(vector <int> E, int pot) {
  for (auto it : E) {
    V[edge[it].X].push_back(P(edge[it].Y, it));
    V[edge[it].Y].push_back(P(edge[it].X, it));
  }

  int mxd=0;
  for (auto it : E)
    mxd = max(mxd, (int) max(V[edge[it].X].size(), V[edge[it].Y].size()));

  if (mxd <= 1) {
    for (auto it : E) {
      V[edge[it].X].clear();
      V[edge[it].Y].clear();
    }
    return;
  }

  tid = m;
  if (E.size() & 1) {
    int lijevi = -1, desni = -1;
    for (auto it : E) {
      if (V[edge[it].X].size() % 2) lijevi = edge[it].X;
      if (V[edge[it].Y].size() % 2) desni = edge[it].Y;
    }

    add_edge(lijevi, desni);
  }

  for (auto it : E) {
    if (V[edge[it].X].size() % 2)
      add_edge(edge[it].X, L+R);
    if (V[edge[it].Y].size() % 2)
      add_edge(edge[it].Y, L+R+1);
  }

  tour(E);
  vector <int> T[2];

  for (auto it : E) {
    assert(bio[it]);
    if (bio[it] == 1)
      sol[it] += pot;
    T[bio[it]-1].push_back(it);

    bio[it] = 0;
    V[edge[it].X].clear();
    V[edge[it].Y].clear();
  }

  FOR(i, m, tid)
    bio[i] = 0;

  solve(T[0], 2*pot);
  solve(T[1], 2*pot);
}

int main()
{
  scanf("%d%d%d", &L, &R, &m);

  vector <int> T;
  REP(i, m) {
    int a, b;
    scanf("%d%d", &a, &b); a--; b--; b += L;
    edge[i] = P(a, b);
    T.push_back(i);
  }

  solve(T, 1);
  int mxcl=1;

  REP(i, m) {
    sol[i]++;
    mxcl = max(mxcl, sol[i]);
  }

  printf("%d\n", mxcl);
  REP(i, m) printf("%d\n", sol[i]);

  return 0;
}
