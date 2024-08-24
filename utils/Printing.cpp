#include <bits/stdc++.h>

typedef long long ll;
using namespace std;

void printAdj(vector<pair<int,int>> adj[], int tn) {
    cout << "[\n";
    for(int i=0;i<tn;i++) {
        cout << i << " : ";
        for(auto v : adj[i]) {
            cout << "(" << v.first << " , " << v.second << ") - ";
        }
        cout << "\n";
    }
    cout << "]\n";
}

void printLastLayer(ll segTree[], int in, int cl, int cr) {
    if(cl == cr) {
        cerr << segTree[in] << " ";
        return;
    }

    int m = cl + (cr - cl) / 2;
    printLastLayer(segTree, 2*in+1, cl, m);
    printLastLayer(segTree, 2*in+2, m+1, cr);
}

void printBT(ll segTree[], int in, const std::string& prefix, bool isLeft, int cl, int cr)
{
    if( cl != cr )
    {
        std::cerr << prefix;

        std::cerr << (isLeft ? "├──" : "└──" );

        // print the value of the node
        std::cerr << segTree[in] << std::endl;

        // enter the next tree level - left and right branch
        int m = cl + (cr - cl) / 2;
        printBT( segTree, 2*in+1, prefix + (isLeft ? "│   " : "    "), true, cl, m);
        printBT( segTree, 2*in+2, prefix + (isLeft ? "│   " : "    "), false, m+1, cr);
    }
    else {
        std::cerr << prefix;

        std::cerr << (isLeft ? "├──" : "└──" );

        // print the value of the node
        std::cerr << segTree[in] << std::endl;
    }
}

void printBT(ll segTree[], int in, int cl, int cr)
{
    printBT(segTree, in, "", false, cl, cr);
}