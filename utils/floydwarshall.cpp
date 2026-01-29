#include <bits/stdc++.h>
using namespace std;

void floywarshall(vector<vector<int>>& cost, int n) {
	int i, j, k;
	
	for(k=0;k<n;k++) {
		for(i=0;i<n;i++) {
			for(j=0;j<n;j++) {
				if(cost[i][k] != INT_MAX && cost[k][j] != INT_MAX) {
					cost[i][j] = min(cost[i][j], cost[i][k] + cost[k][j]); // shortest route from i to j will have shortest route from i to k and k to j
				}
				// if(cost[i][j] == INT_MAX) {
				// 	cout << "INF , ";
				// }
				// else {
				// 	cout << cost[i][j] << "   , ";
				// }
				// cout << ( ? "INF" : cost[i][j]) << " , ";
			}
			// cout << "\n";
		}
		// cout << "=================================================================\n";
	}

	// For detecting negative cycle
	// for(i=0;i<n;i++) {
	// 	if(cost[i][i] < 0) cout << "Negative cycle exist\n";
	// }
}

// Q. If we are doing cost[i][j] = min(cost[i][j], cost[i][k] + cost[k][j]), it means cost[i][k] is shortest using k-1 vertices
// 	  but what if cost[i][k] can be shorter if we took vertex x > k?
// A. The main idea of the algorithm is that the shortest path between any 2 vertices would contain atmost n vertices, so that's 
// 	  why we are running the loop of k n times. So, that after n times we will get the shortest path between any 2 vertices. So, if 
// 	  cost[i][k] can be shorter if we took vertex x > k, it means cost[i][k] = cost[i][x] + cost[x][k], and similarly for 
// 	  cost[i][j] = cost[i][x] + cost[x][j]

// We can use Djikstra algo for all the vertices for finding all pairs shortest paths, but its complexity will be O(V * (V + E) * log(V))
// which is log(V) more than FLoyd Warshall, and it will fail for negative cycles also.

int main() {

	int i, n, m;
	cin >> n >> m;

	vector<vector<int>> adjM(n, vector<int>(n, INT_MAX));

	for(i=0;i<m;i++) {
		int u, v, w;
		cin >> u >> v >> w;
		u--, v--;

		adjM[u][v] = min(adjM[u][v], w);
	}

	floywarshall(adjM, n);

	return 0;
}
