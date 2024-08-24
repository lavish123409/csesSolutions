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

    queue<int> q;
    int par[n+1];

    memset(par, -1, sizeof(par));
    q.push(1);
    par[1] = -2;

    int ans = 0;
    while(!q.empty())
    {
        int cqs = q.size();
        while(cqs--)
        {
            int u = q.front();
            q.pop();

            if(u == n)
            {
                cout << ans+1 << "\n";
                printReverse(par, u);
                cout << n << "\n";
                return 0;
            }

            for(int v : graph[u])
                if(par[v] == -1)
                {
                    q.push(v);
                    par[v] = u;
                }
        }
        ans++;
    }

    cout << "IMPOSSIBLE\n";

    return 0;
}