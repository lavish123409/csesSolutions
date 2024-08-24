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

ll findShortestPath(map<int,int> adj[], int n, pair<int,int>& maximumWeightEdgeInPath) {

    maximumWeightEdgeInPath = {-1,-1};

    vector<ll> mndis(n, LONG_LONG_MAX);
    priority_queue<tuple<ll,int,int,int>, vector<tuple<ll,int,int,int>>, greater<tuple<ll,int,int,int>>> mnq;

    mndis[0] = 0;
    mnq.push({0, 0, -1, -1});

    while(!mnq.empty()) {
        ll cdis = get<0>(mnq.top());
        int u = get<1>(mnq.top());
        int mwu = get<2>(mnq.top());
        int mwv = get<3>(mnq.top());
        mnq.pop();

        if(u == n-1) {
            // ans.push_back(cdis);
            // if(ans.size() == k) {
            //     break;
            // }
            maximumWeightEdgeInPath.first = mwu;
            maximumWeightEdgeInPath.second = mwv;
            return cdis;
        }

        for(auto [v, w] : adj[u]) {
            if(mndis[u] != LONG_LONG_MAX && mndis[v] >= mndis[u] + w) {
            // if(mndis[u] != LONG_LONG_MAX) {
                mndis[v] = mndis[u] + w;
                if(mwu == -1 || mwv == -1 || w >= adj[mwu][mwv]) {
                    mnq.push({mndis[v], v, u, v});
                }
                else {
                    mnq.push({mndis[v], v, mwu, mwv});
                }
                // int mwu = maximumWeightEdgeInPath.first;
                // int mwv = maximumWeightEdgeInPath.second;
                // if(maximumWeightEdgeInPath == make_pair(-1, -1) || w > adj[mwu][mwv]) {
                //     maximumWeightEdgeInPath.first = u;
                //     maximumWeightEdgeInPath.second = v;
                // }
            }
        }
    }

    return -1;
}

int main()
{
    int i, n, m, k, j;
    cin >> n >> m >> k;

    vector<pair<int,int>> adj[n];
    // map<int,int> adj[n];
    for(i=0;i<m;i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;

        adj[u].push_back({v, w});
        // adj[u].insert({v, w});
    }

    vector<vector<ll>> mndis(n, vector<ll>(k, LONG_LONG_MAX));
    priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<pair<ll,int>>> mnq;

    mndis[0][0] = 0;
    mnq.push({0, 0});

    while(!mnq.empty()) {
        ll cdis = mnq.top().first;
        int u = mnq.top().second;
        mnq.pop();

        if(cdis > mndis[u][k-1]) continue;

        // if(u == n-1) {
        //     // ans.push_back(cdis);
        //     // if(ans.size() == k) {
        //     //     break;
        //     // }
        //     maximumWeightEdgeInPath.first = mwu;
        //     maximumWeightEdgeInPath.second = mwv;
        //     return cdis;
        // }

        // cout << u << " : ";
        for(auto [v, w] : adj[u]) {
            if(mndis[v][k-1] > cdis + w) {
                // cout << v  << " - " << w << " : ";
                mndis[v][k-1] = cdis + w;
                mnq.push({mndis[v][k-1], v});
                // cout << mndis[v][k-1] << "\n";

                // sort(mndis[v].begin(), mndis[v].end(), [](ll a, ll b) {
                //     // cout << a << " , " << b << " : ";
                //     // cout << "c1: " << (a == LONG_LONG_MAX) << " - ";
                //     // cout << "c2: " << (b != LONG_LONG_MAX) << " - ";
                //     // cout << "c3: " << (a < b) << "\n";
                //     // return a == LONG_LONG_MAX || b != LONG_LONG_MAX || (a < b);

                //     if(a != LONG_LONG_MAX && b != LONG_LONG_MAX) {
                //         return a < b;
                //     }
                //     else {
                //         return a == LONG_LONG_MAX;
                //     }
                // });
                sort(mndis[v].begin(), mndis[v].end());
            }
        }
        // for(i=0;i<n;i++) {
        //     for(j=0;j<k;j++) {
        //         cout << mndis[i][j] << " ";
        //     }
        //     cout << "\n";
        // }
    }

    for(ll dis : mndis[n-1]) {
        cout << dis << " ";
    }

    // while(k--) {
    //     pair<int,int> maximumWeightInPath;
    //     cout << findShortestPath(adj, n, maximumWeightInPath) << " ";

    //     int mwu = maximumWeightInPath.first;
    //     int mwv = maximumWeightInPath.second;
    //     cout << mwu+1 << " , " << mwv+1 << " = " << adj[mwu][mwv] << "\n";
    //     adj[mwu][mwv] = int(1e9+1);
    // }

    // for(ll dis : ans) {
    //     cout << dis << " ";
    // }
    cout << "\n";

    return 0;

}

// #include <bits/stdc++.h>
// #define endl "\n"
// using namespace std;
// #define int long long int
 
// int n, m, k;
// vector<vector<pair<int,int>>> g;
// vector<vector<int>> dist; 
// const int INF = 9e15;
 
// void dij()
// {
	
// 	priority_queue <
// 	  pair<int,int>, 
// 	  vector<pair<int,int>>, 
// 	  greater<pair<int,int>>
// 	> pq; 
 
// 	pq.push({0,1});
 
// 	while(!pq.empty())
// 	{
// 		int u = pq.top().second;
// 		int d = pq.top().first;
// 		pq.pop();
		
// 		if(dist[u][k-1] < d) continue;
 
// 		for(auto e: g[u])
// 		{
// 			int v = e.first;
// 			int c = e.second;
 
// 			if(dist[v][k-1] > c+d) 
// 			{
// 				dist[v][k-1] = c+d;
// 				pq.push({dist[v][k-1], v});
// 				sort(dist[v].begin(), dist[v].end());
// 			}
// 		}
// 	}
// }
 
// int32_t main()
// {
// 	ios_base::sync_with_stdio(false);
// 	cin.tie(NULL);
// 	cin >> n >> m >> k;
// 	g.resize(n+1);
// 	dist.resize(n+1);
// 	for(int i = 1; i <= n; i++)
// 	{
// 		dist[i].resize(k);
// 		for(int j = 0; j <k; ++j)
// 		{
// 			dist[i][j] = INF;
// 		}
// 	}
// 	dist[1][0] = 0;
// 	for(int i = 0; i < m; ++i)
// 	{
// 		int u, v, c;
// 		cin >> u >> v >> c;
// 		g[u].push_back({v,c});
// 	}
	
// 	dij();
 
// 	for(int i = 0; i < k; ++i)
// 	{
// 		cout << dist[n][i] << " ";
// 	}
// }