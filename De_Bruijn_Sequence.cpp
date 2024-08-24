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

    we can observe that, any string b would follow a, iff last_digit(a) == first_digit(b)
    we can make a graph where there is a directed edge, a->b for the above condition
    and then we can find a path, which connects all the vertices
    the path length should be n-1, and we can print all vertices in order according to the path

    problem - we would have to find hamiltonian path, for the constructed graph having complexity 2^(number of nodes), and here the number of nodes = 2^n, where n is length of sequence

    GFG solution - 
    we can construct graph of n-1 length string, and edges with one character
    0 -0-> 0
    0 -1-> 1
    1 -0-> 0
    1 -1-> 1
    here, every vertex have equal indegree and outdegree, so we can construct a eularian cycle
    so, the idea is that if n=3, then we would put strings of length 2 first and then add the character by traversing that edge
    00 1
    now, the new string of n-1 length would become
    01
    and we can take any other character by taking edge


*/

// const int MAXN = 2e5+5;
// const int MAXD = 30;
// int anc[MAXN][MAXD];

void dfs(vector<pair<int,int>> adj[], int u, int out[], vector<int> &path) {
    while(out[u] > 0) {
        out[u]--;
        path.push_back(adj[u][out[u]].second);
        dfs(adj, adj[u][out[u]].first, out, path);
    }
}

void printAdj(vector<pair<int,int>> adj[], int tn) {
    for(int i=0;i<tn;i++) {
        cout << i << " : ";
        for(auto v : adj[i]) {
            cout << "(" << v.first << " , " << v.second << ") - ";
        }
        cout << "\n";
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
    
    int i, n;
    cin >> n;

    int tn = (1 << (n-1));
    int mask = tn-1;
    vector<pair<int,int>> adj[tn];
    int out[tn];
    for(i=0;i<tn;i++) {
        adj[i].push_back({(i << 1) & mask, 0});
        adj[i].push_back({(i << 1 ^ 1) & mask, 1});
        out[i] = 2;
    }

    printAdj(adj, tn);

    vector<int> path;
    dfs(adj, 0, out, path);

    // cout << "00";
    for(i=0;i<n-1;i++) {
        cout << 0;
    }
    for(int ch : path) {
        cout << ch;
    }
    cout << "\n";

    return 0;

}