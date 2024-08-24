#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// 3 6 2
/*

    set of intervals
    [{0,8}]

    map of differences
    [{8, 1}]

    find its upper bound, i.e. the interval whose itv.first > el
    itv--
    // itv.first <= el 
    if el < itv.second // 3 < 8
        map[itv.second - itv.first]-- // m[{8, 0}]
        remove if frequency is zero // m[]
        split interval => remove itv from array // s[]
                          and add [{itv.first, el} {el, itv.second}] // s[{0, 3}, {4, 8}]
        map[el - itv.first]++ // m[{3, 1}]
        map[itv.second - el]++ // m[{3, 1}, {5, 1}]

    print first element in pair of end of map // 5
    
*/

int main()
{

    int i, x, n;
    cin >> x >> n;

    map<int,int> intervals, differences;
    intervals.insert({0, x});
    differences[x] = 1;
    while(n--) {
        int currentIndex;
        cin >> currentIndex;

        auto ptr = intervals.upper_bound(currentIndex);
        ptr--;

        if(currentIndex < ptr->second) {
            int l = ptr->first;
            int r = ptr->second;
            differences[r-l]--;

            if(differences[r-l] == 0) {
                differences.erase(r-l);
            }

            intervals.erase(l);

            intervals.insert({l, currentIndex});
            intervals.insert({currentIndex, r});

            differences[currentIndex - l]++;
            differences[r - currentIndex]++;

        }

        cout << differences.rbegin()->first << " ";
    }
    cout << "\n";

    return 0;
}