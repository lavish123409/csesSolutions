#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

string ps = "\n";

// void printPQ(auto pq) {
//     cout << "[";
//     while(!pq.empty()) {
//         int d = pq.top().first;
//         int u = pq.top().second;
//         pq.pop();
//         cout << "(" << d << " : " << u << ") , ";
//     }
//     cout << "]\n";
// }

/*

    brute force 
    stat from first member, and choose 

*/

// const int MAXN = 2e5+5;
// const int MAXD = 30;
// int anc[MAXN][MAXD];


void dfs(vector<int> adj[], int u, vector<bool>& vis, stack<int>& visTime) {

    vis[u] = 1;
    for(int v : adj[u]) {
        if(!vis[v]) {
            dfs(adj, v, vis, visTime);
        }
    }

    visTime.push(u);
}

void dfsRev(vector<int> adjT[], int u, vector<bool>& vis, vector<int>& sccIndex, int currentSCCIndex) {
    sccIndex[u] = currentSCCIndex;
    vis[u] = 1;

    for(int v : adjT[u]) {
        if(!vis[v]) {
            dfsRev(adjT, v, vis, sccIndex, currentSCCIndex);
        }
    }
}

void dfsSCCwise(vector<int> adj[], int u, vector<bool>& vis, vector<int> &sccNo, stack<int> &topSort) {

    vis[u] = 1;
    for(int v : adj[u]) {
        if(!vis[v]) {
            dfsSCCwise(adj, v, vis, sccNo, topSort);
        }
    }

    topSort.push(sccNo[u]);
}

bool setTrue(vector<int> adj[], int u, vector<bool>& vis, vector<int> &sccNo, int remainingToppings, int m, vector<char>& ans) {

    vis[u] = 1;
    if(ans[abs(u - m)] == 0) {
        ans[abs(u - m)] = (u - m) < 0 ? '-' : '+';
        remainingToppings--;
        if(remainingToppings == 0) {
            return 1;
        }
    }
    for(int v : adj[u]) {
        if(sccNo[u] == sccNo[v] && !vis[v] && setTrue(adj, v, vis, sccNo, remainingToppings, m, ans))
            return 1;
    }
    for(int v : adj[u]) {
        if(sccNo[u] != sccNo[v] && !vis[v] && setTrue(adj, v, vis, sccNo, remainingToppings, m, ans))
            return 1;
    }

    return 0;
}

int main()
{
    ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
    
    int i, n, m;
    cin >> n >> m;

    int totalNodes = 2 * m + 1;
    vector<int> adj[totalNodes], adjT[totalNodes];

    // in implication graph, if u->v, then 
    //                       - if u is true, v have to be true
    //                       - if u is false, v can be true or false
    for(i=0;i<n;i++) {
        char sign1;
        int topping1;

        cin >> sign1 >> topping1;
        if(sign1 == '-') {
            topping1 *= -1;
        }

        char sign2;
        int topping2;

        cin >> sign2 >> topping2;
        if(sign2 == '-') {
            topping2 *= -1;
        }

        adj[-topping1 + m].push_back(topping2 + m);
        adj[-topping2 + m].push_back(topping1 + m);
        
        adjT[topping2 + m].push_back(-topping1 + m);
        adjT[topping1 + m].push_back(-topping2 + m);
        
    }

    // for(i=0;i<totalNodes;i++) {
    //     cout << i-m << " : ";
    //     for(int v : adj[i]) {
    //         cout << v-m << " , ";
    //     }
    //     cout << "\n";
    // }
    
    // for(i=0;i<totalNodes;i++) {
    //     cout << i-m << " : ";
    //     for(int v : adjT[i]) {
    //         cout << v-m << " , ";
    //     }
    //     cout << "\n";
    // }

    // find scc index for every node
    vector<int> sccNo(totalNodes, -1);
    vector<bool> vis(totalNodes);
    stack<int> lastVisitedNode, topSort;
    for(i=0;i<totalNodes;i++) {
        if(i != m && !vis[i]) { // we have to leave (0 + m) node because, 0 node would not be there only -i and +i would be there
            dfs(adj, i, vis, lastVisitedNode);
        }
    }
    topSort = lastVisitedNode;

    vis = vector<bool>(totalNodes);
    int currentSCCIndex = 0;
    while(!lastVisitedNode.empty()) {
        int u = lastVisitedNode.top();
        lastVisitedNode.pop();

        if(!vis[u]) {
            dfsRev(adjT, u, vis, sccNo, currentSCCIndex);
            currentSCCIndex++;
        }
    }

    // for(i=1;i<=m;i++) {
    //     cout << -i << " : "  << sccNo[-i + m] << " = ";
    //     cout << i << " : "  << sccNo[i + m] << "\n";
    // }

    vector<char> ans(m+1);
    for(i=1;i<=m;i++) {
        if(sccNo[-i + m] == sccNo[i + m]) {
            cout << "IMPOSSIBLE\n";
            return 0;
        }
        ans[i] = sccNo[i+m] > sccNo[-i+m] ? '+' : '-'; // if scc index of +ve value is greater (scc index determines which scc comes first in topological sort,i.e, there is a path from lower scc to higher scc)
                                                       // it means +ve value can take true, and negative value would not be effected
                                                       // if +ve value would have been on left, then every value on right including -ve one, had to be true
    }
    
    // vis = vector<bool>(totalNodes);
    // int lastNode = -1;
    // stack<int> topSort;
    // for(i=0;i<totalNodes;i++) {
    //     if(i != m && !vis[i]) {
    //         dfsSCCwise(adj, i, vis, sccNo, topSort);
    //     }
    // }

    // vis = vector<bool>(totalNodes);
    // vector<char> ans(m+1);
    // while(!topSort.empty()) {
    //     int u = topSort.top();
    //     topSort.pop();

    //     if(!vis[u]) {
    //         cout << u-m << " <-\n";
    //         if(setTrue(adj, u, vis, sccNo, m, m, ans)) break;
    //     }
    // }

    for(i=1;i<=m;i++) {
        cout << ans[i] << " ";
    }
    cout << "\n";
    return 0;

}