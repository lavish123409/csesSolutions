#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void printReverse(int par[], int n)
{
    if(par[n] == -2)
        return;

    printReverse(par, par[n]);
    cout << par[n] << " ";
}

bool is2ColoringPossible(vector<int> adj[], int u, int clr[], int cclr)
{
    if(clr[u] != -1) {
        return clr[u] == cclr;
    }

    clr[u] = cclr;
    for(int v : adj[u]) {
        if(!is2ColoringPossible(adj, v, clr, cclr == 1 ? 2 : 1)) {
            return 0;
        }
    }

    return 1;
}

int main()
{
    int i, j, n, m;
    cin >> n >> m;

    vector<int> graph[n+1];
    for(i=0;i<m;i++)
    {
        int u, v;
        cin >> u >> v;

        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    int clr[n+1];
    memset(clr, -1, sizeof(clr));
    for(i=0;i<n;i++)
        if(clr[i] == -1 && !is2ColoringPossible(graph, i, clr, 1))
        {
            cout << "IMPOSSIBLE\n";
            return 0;
        }

    for(i=1;i<=n;i++)
        cout << clr[i] << " ";
    cout << "\n";

    return 0;
}