#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// 3 8 2 1 5
/*

    3 2 1 
    8 5
    = 2

    [
        9 1
        5
    ]

    for cube in cubeList:
        ind = upper bound (towers, cube)

        if(ind == towers.end()):
            towers.push(cube)
        else:
            towers[ind] = cube

    print towers.size
*/

int main()
{

    int i, n;
    cin >> n;

    int a[n];
    for(i=0;i<n;i++) {
        cin >> a[i];
    }

    vector<int> towers;

    for(i=0;i<n;i++) {
        int ind = upper_bound(towers.begin(), towers.end(), a[i]) - towers.begin();
        if(ind == towers.size()) {
            towers.push_back(a[i]);
        }
        else {
            towers[ind] = a[i];
        }
    }

    cout << towers.size() << "\n";

    return 0;
}