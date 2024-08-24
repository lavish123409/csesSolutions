#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// 2 5 1 4 8 3 2 5
/*

    brute force
    for every element
    - start from that index and traverse left
    - if any element observed is smaller, then print its position

    O(n*n)

    - take a stack
    - for every element, find which is smaller element in the stack
        - if top element of stack is greater than current element, pop it
        - otherwise, this our answer
    - push current element to stack
    
*/

void printStack(stack<array<int,2>> st) {
    cout << "[";
    while(!st.empty()) {
        cout << "(" << st.top()[0] << "," << st.top()[1] << ") - ";
        st.pop();
    }
    cout << "]\n";
}


int main()
{

    int i, n, x;
    cin >> n;

    int a[n];
    for(i=0;i<n;i++) {
        cin >> a[i];
    }

    stack<array<int,2>> st;
    for(i=0;i<n;i++) {
        while(!st.empty() && st.top()[0] >= a[i]) {
            st.pop();
        }

        if(st.empty()) {
            cout << "0 ";
        }
        else {
            cout << st.top()[1] << " ";
        }

        st.push({a[i], i+1});
        // printStack(st);
    }
    cout << "\n";
    return 0;
}