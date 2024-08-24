#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

class DSU {
public:
    vector<int> par, rank;
    int n;
    
    DSU(int n) {
        this->n = n;
        par = vector<int>(n+1, -1);
        rank = vector<int>(n+1, 1);
    }

    int getParent(int n)
    {
        if(par[n] == -1)
            return n;
        return par[n] = getParent(par[n]);
    }

    void join(int a, int b)
    {
        a = getParent(a);
        b = getParent(b);

        if(a != b)
        {
            if(rank[a] > rank[b])
                swap(a, b);

            par[b] = a;
            rank[a] += rank[b];
        }
    }
};


int main()
{
    int i, j, n, m;
    cin >> n >> m;

    DSU dsu(n);
    // vector<int> graph[n];
    for(i=0;i<m;i++)
    {
        int u, v;
        cin >> u >> v;

        dsu.join(u, v);
    }

    vector<int> ans;
    for(i=1;i<dsu.par.size();i++)
        if(dsu.par[i] == -1)
            ans.push_back(i);

    // if(ans.size() == 1)
    //     cout << "0\n";
    // else
    // {
    //     cout << ans[0] << ""
    // }
    cout << ans.size() - 1 << "\n";
    for(i=1;i<ans.size();i++)
        cout << ans[0] << " " << ans[i] << "\n";

    return 0;
}