#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// 1 2
// 2 4
// 4 4
/*

    I approach
    - sort all the intervals according to the starting time
    - traverse the intervals store the ending times in min heap or min priority queue along with the room number that is using
    - if current interval's starting time is greater than the minimum ending time of any interval, it means it starts later than that interval whose ending time is minimum and we can use its room
    - otherwise, we don't have any room left and we would store current interval with another room, and store the maximum number of rooms in ans variable

    sort all intervals
    minheap = []

    ans = 0
    for interval in intervals:
        if minHeap is empty || minHeap.minimumEndingTime >= interval.StartingTime:
            ans++
            roomUsed[interval] = ans
            minHeap.insert({interval.endingTime, minHeap.size + 1})
        else
            lastEndingTime, lastRoomUsed = minHeap.minimum
            roomUsed[interval] = lastRoomUsed
            minHeap.pop
            minHeap.insert({interval.endingTime, lastRoomUsed})

    
    WA1 - was not sorting intervals

*/

int main()
{

    int i, n;
    cin >> n;

    int ans = 0;
    array<int,3> a[n];

    for(i=0;i<n;i++) {
        cin >> a[i][0] >> a[i][1];
        a[i][2] = i;
    }

    sort(a, a+n);

    // for(i=0;i<n;i++) {
    //     cout << "(" << a[i][0] << " , " << a[i][1] << ") - ";
    // }
    // cout << "\n";

    // vector<int> roomUsed(n);
    // priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> minHeap;
    // set<int> availableRooms;
    // for(i=0;i<n;i++) {
    //     if(minHeap.empty() || minHeap.top().first >= a[i][0]) {
    //         if(availableRooms.empty()) {
    //             ans++;
    //             roomUsed[a[i][2]] = ans;
    //             minHeap.push({a[i][1], ans});
    //         }
    //         else {
    //             int lastRoomUsed = *(availableRooms.begin());
    //             availableRooms.erase(availableRooms.begin());
    //             roomUsed[a[i][2]] = lastRoomUsed;
    //             minHeap.push({a[i][1], lastRoomUsed});
    //         }
    //     }
    //     else {
    //         while(!(minHeap.empty() || minHeap.top().first >= a[i][0])) {
    //             availableRooms.insert(minHeap.top().second);
    //             minHeap.pop();
    //         }
    //         int lastRoomUsed = *(availableRooms.begin());
    //         availableRooms.erase(availableRooms.begin());
    //         roomUsed[a[i][2]] = lastRoomUsed;
    //         minHeap.push({a[i][1], lastRoomUsed});
    //     }
    // }
     
    vector<int> roomUsed(n);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> minHeap;
    for(i=0;i<n;i++) {
        if(minHeap.empty() || minHeap.top().first >= a[i][0]) {
            ans++;
            roomUsed[a[i][2]] = ans;
            minHeap.push({a[i][1], ans});
        }
        else {
            int lastRoomUsed = minHeap.top().second;
            minHeap.pop();
            roomUsed[a[i][2]] = lastRoomUsed;
            minHeap.push({a[i][1], lastRoomUsed});
        }
    }
 

    cout << ans << "\n";
    for(int it : roomUsed) {
        cout << it << " ";
    }
    cout << "\n";
    
    return 0;
}