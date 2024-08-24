#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

string ps = "\n";

void printReverse(int par[], int n)
{
    if(par[n] == 0) {
        cout << n << " ";
        return;
    }
    printReverse(par, par[n]);
    cout << n << " ";
}

bool isCyclePossible(vector<int> graph[], int u, int pn, int n, int par[], int vis[], vector<int>& ans)
{
    // ps.push_back('\t');
    // cout << ps << u << " , " << pn;
    if(par[u] != -1) {
        // printReverse(par, pn);
        // cout << u << "\n";
        int i = pn;
        ans.push_back(u);
        while(i != u)
        {
            ans.push_back(i);
            i = par[i];
        }
        // ps.pop_back();
        return 1;
    }

    par[u] = pn;
    vis[u] = 1;
    for(int v : graph[u]) {
        if(v != pn) {
            if(isCyclePossible(graph, v, u, n, par, vis, ans)) {
                return 1;
            }
        }
    }
    par[u] = -1;

    // ps.pop_back();
    return 0;
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

    // for(i=1;i<=n;i++)
    // {
    //     cout << i << " -> ";
    //     for(int v : graph[i]) {
    //         cout << v << " , ";
    //     }
    //     cout << "\n";
    // }

    int par[n+1], vis[n+1]={0};
    memset(par, -1, sizeof(par));
    vector<int> ans;

    for(i=1;i<=n;i++) {
        if(!vis[i] && isCyclePossible(graph, i, 0, n, par, vis, ans))
            break;
    }

    if(i > n) {
        cout << "IMPOSSIBLE\n";
    }
    else {
        reverse(ans.begin(), ans.end());
        cout << ans.size() + 1 << "\n";
        for(int it : ans) {
            cout << it << " ";
        }
        cout << ans[0] << "\n";
    }
    return 0;
}