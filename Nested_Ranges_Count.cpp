#include <bits/stdc++.h>
using namespace std;

typedef long long ll;


// For Ordered Set
// Header files, namespaces, 
// macros as defined above 
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds; 
  
template <typename T>
using ordered_set = tree<T, null_type,less_equal<T>, rb_tree_tag,tree_order_statistics_node_update> ;

// 1 6
// 2 4
// 4 8
// 3 6
// {1 6}, {2 4}, {3 6}, {4 8}
/*

    I approach
    - sort all intervals, according to condition: if start1 < start2 || start1 == start2 && end2 > end1
    - traverse left to right, and for every interval look on left, count how many intervals have >= current end time (contained)
        - take a set of end times and find lower bound on current end time
        - add current end time to set also
    - traverse right to left, and for every interval look on right, count how many intervals have <= current end time (contains)
        - take a set of end times and find upper bound on current end time and subtract 1 from it
        - add current end time to set also


    sort all intervals

    set of endTimes
    for interval in intervals (left to right):
        numberOfIntervalsContained = distance(lower_bound(endTimes, intervals.endTime), intervals.end)
        put numberOfIntervalsContained in ans
        endTimes.insert(interval.endTime)

    set of endTimes
    for interval in intervals (right to left):
        numberOfIntervalsContained = distance(upper_bound(endTimes, intervals.endTime), intervals.begin)
        put numberOfIntervalsContained in ans
        endTimes.insert(interval.endTime)

    TLE1 - distance complexity is O(n) for set iterators

    for now, solved using ordered set which gives index of a number in set

*/

int main()
{

    int i, n;
    cin >> n;

    // vector<array<int, 3>> a(n);
    array<int, 3> a[n];
    for(i=0;i<n;i++) {
        cin >> a[i][0] >> a[i][1];
        a[i][2] = i;
    }

    // sort(a.begin(), a.end());
    sort(a, a+n, [](array<int,3> a, array<int,3> b) {
        return a[0] < b[0] || (a[0] == b[0] && a[1] > b[1]);
    });

    vector<int> contained(n), contains(n);

    ordered_set<int> endTimes;
    for(i=0;i<n;i++) {
        // int ind = distance(lower_bound(endTimes.begin(), endTimes.end(), a[i][1]), endTimes.end());
        int ind = endTimes.order_of_key(a[i][1]);
        contained[a[i][2]] = endTimes.size() - ind;
        endTimes.insert(a[i][1]);
    }

    endTimes.clear();
    for(i=n-1;i>=0;i--) {
        // int ind = distance(endTimes.begin(), upper_bound(endTimes.begin(), endTimes.end(), a[i][1]));
        int ind = endTimes.order_of_key(a[i][1] + 1);
        contains[a[i][2]] = ind;
        endTimes.insert(a[i][1]);
    }

    for(int it : contains) {
        cout << it << " ";
    }
    cout << "\n";
    
    for(int it : contained) {
        cout << it << " ";
    }
    cout << "\n";
    
    return 0;
}