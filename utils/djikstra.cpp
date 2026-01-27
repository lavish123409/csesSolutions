#include <bits/stdc++.h>
using namespace std;

void djikstra(vector<array<int,2>> adj[], int n, int s, vector<int>& dis, vector<int>& par) {
	dis = vector<int>(n, INT_MAX);
	par = vector<int>(n, -1);
	priority_queue<array<int,2>, vector<array<int,2>>, greater<array<int,2>>> mnq;

	mnq.push({0, 0});

	while(!mnq.empty()) {
		int cdis = mnq.top()[0];
		int u = mnq.top()[1];
		mnq.pop();

		// if(u == n-1) return cdis; // if you want to return minimum distance to n-1

		// We are not writing like this because it will lead to many unnecessary larger path values in minHeap
		// if(dis[u] > cdis) {
        //     dis[u] = cdis;
        //     for(auto [v, w] : adj[u]) {
        //         mnq.push({cdis + w, v});
        //     }
        // }

		if(dis[u] < cdis) continue;

		for(auto [v, w] : adj[u]) {
			if(cdis + w < dis[v]) { // this is needed because we do not store unnecessary values in minHeap
				dis[v] = cdis + w; // for storing min distance; using this also we will stop many higher values path also
				par[v] = u; // for storing the parent; we can backtrack through the nodes to get the shortest path
				mnq.push({cdis + w, v});
			}
		}
	}
}

int main() {

	return 0;
}
