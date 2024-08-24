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

    I approach
    much like older problem

    - find cycle index for every vertex
    - find cycle distance for every vertex
    - ans is cycle distance + cycle index's length

    
*/

// const int MAXN = 2e5+5;
// const int MAXD = 30;
// int anc[MAXN][MAXD];

int main()
{
    ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
    
    int planetNum;
    cin >> planetNum;

    int p;
    vector<int> next(planetNum);
    vector<vector<int>> before(planetNum);
    for(p=0;p<planetNum;p++) {
        cin >> next[p];

        next[p]--;
        before[next[p]].push_back(p);
    }

    vector<int> cycleIndex(planetNum, -2);
    vector<map<int,int>> cycles;
    for(p=0;p<planetNum;p++) {
        if(cycleIndex[p] != -2) continue;

        vector<int> path;
        int currNode=p;
        while(cycleIndex[currNode] == -2) {
            cycleIndex[currNode] = -3;
            path.push_back(currNode);
            currNode = next[currNode];
        }

        map<int,int> cycle;
        bool isInCycle = 0;
        int nodeNoInCycle = 0;
        for(int node : path) {
            isInCycle = isInCycle || (node == currNode);
            if(isInCycle) {
                cycle[node] = nodeNoInCycle++;
            }
            cycleIndex[node] = isInCycle ? cycles.size() : -1;
        }
        cycles.push_back(cycle);
    }
    // for(int i=0;i<planetNum;i++) {
    //     cout << i << " = " << cycleIndex[i] << "; ";
    // }
    // cout << "\n";

    // for(int i=0;i<cycles.size();i++) {
    //     cout << i << " : ";
    //     for(auto it : cycles[i]) {
    //         cout << "(" << it.first << " , " << it.second << ") - ";
    //     }
    //     cout << "\n";
    // }

    vector<array<int,2>> cycleDist(planetNum);
    for(p=0;p<planetNum;p++) {
        if(cycleIndex[p] != -1) {
            cycleDist[p] = {0, cycleIndex[p]};
            continue;    
        }
        if(cycleIndex[next[p]] == -1) continue;

        cycleDist[p] = {1, cycleIndex[next[p]]};
        vector<int> stack(before[p]);
        while(!stack.empty()) {
            int currNode = stack.back();
            stack.pop_back();

            cycleDist[currNode][0] = cycleDist[next[currNode]][0] + 1;
            cycleDist[currNode][1] = cycleDist[next[currNode]][1];
            stack.insert(stack.end(), before[currNode].begin(), before[currNode].end());
        }
    }
    // for(int i=0;i<planetNum;i++) {
    //     cout << i << " = " << cycleDist[i][0] << " , " << cycleDist[i][1] << "; ";
    // }
    // cout << "\n";

    for(p=0;p<planetNum;p++) {
        cout << cycleDist[p][0] + cycles[cycleDist[p][1]].size() << " ";
    }
    cout << "\n";

    return 0;

}