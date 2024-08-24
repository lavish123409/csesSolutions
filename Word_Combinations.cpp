#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
void __print(int x) {cerr << x;}
void __print(long x) {cerr << x;}
void __print(long long x) {cerr << x;}
void __print(unsigned x) {cerr << x;}
void __print(unsigned long x) {cerr << x;}
void __print(unsigned long long x) {cerr << x;}
void __print(float x) {cerr << x;}
void __print(double x) {cerr << x;}
void __print(long double x) {cerr << x;}
void __print(char x) {cerr << '\'' << x << '\'';}
void __print(const char *x) {cerr << '\"' << x << '\"';}
void __print(const string &x) {cerr << '\"' << x << '\"';}
void __print(bool x) {cerr << (x ? "true" : "false");}
 
template<typename T, typename V>
void __print(const pair<T, V> &x) {cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}';}
template<typename T>
void __print(const T &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? "," : ""), __print(i); cerr << "}";}
void _print() {cerr << "]\n";}
template <typename T, typename... V>
void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}

template<typename T>
void printa(T a[], int l, int r) {int f = 0; cerr << '{'; for (int i=l;i<=r;i++) cerr << (f++ ? "," : ""), __print(a[i]); cerr << "}]\n";}
template<typename T>
void printma(T a[], T b[], int l, int r, function<ll(ll,ll)> merge) {int f = 0; cerr << '{'; for (int i=l;i<=r;i++) cerr << (f++ ? "," : ""), __print(merge(a[i],b[i])); cerr << "}]\n";}
// #define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#define debug(x...) cerr << "[" << #x << "] = ["; _print(x)
#define debuga(x, l, r) cerr << "[" << #x << "] = ["; printa(x, l, r)
#define debugma(x, y, l, r, merge) cerr << "[" << #x << "," << #y << "] = ["; printma(x, y, l, r, merge)
#else
#define debug(x...)
#define debuga(x, l, r)
#define debugma(x, y, l, r, merge)
#endif
 
/*
 
    I approach
    we can use Trie + DP for the question
    use Trie to store all words in the dictionary
    then, do recursion form starting index that how many strings we can make from starting index
    traverse the string and keep checking whether the current prefix is present in the dictionary using Trie
    if current prefix is present, recurse form next index to find how many strings we can make from that index

    RE1 - n was not initialized with ength of string while making dp vector

    WA (wherever) - it was because of the wrong mod=1e7+9

    TLE (wherever) - it was because using set would increase the complexity by log factor and unordered_set is O(n^2) in searching or inserting in worst case
    and In trie solution TLE was coming because of the fact that for every character in inner loop, we were adding it to the string and then searching the complete string
    instead, we can search all strings while traversing in inner loop and break the loop if at some point the trie does not contain the node, because if does not contain some prefix of a string, then it cannot contain complete string
    



*/
string ps = "\n";

class Trie {
private:
    struct Node {
        Node** chars;
        bool flag;
    };

    Node* makeNode() {
        Node* node = new Node();
        node->chars = new Node*[26];
        // memset(node->chars, 0, sizeof(node->chars));
        for(int i=0;i<26;i++) {
            node->chars[i] =  0;
        }
        node->flag = 0;

        return node;
    }

public:

    Node* root;

    Trie() {
        root = makeNode();
    }

    void addWord(string& s) {
        // debug("yo");
        int n = s.size();
        Node* ptr = root;

        for(int i=0;i<n;i++) {
            // debug(i, s[i]);
            if(ptr->chars[s[i] - 'a'] == 0) {
                ptr->chars[s[i] - 'a'] = makeNode();
                ptr->chars[s[i] - 'a']->flag = 0;
            }
            ptr = ptr->chars[s[i] - 'a'];
        }
        ptr->flag = 1;
    }

    bool findString(string& s) {
        int n = s.size();
        Node* ptr=root;

        for(int i=0;i<n;i++) {
            // debug(i, s[i]);
            if(ptr->chars[s[i] - 'a'] == 0) {
                return 0;
            }
            ptr = ptr->chars[s[i] - 'a'];
        }

        return ptr->flag;
    }
};

// int recurse(string& s, int in, int n, set<string>& diction, vector<int>& dp) {
int recurse(string& s, int in, int n, Trie* diction, vector<int>& dp) {
    debug(in);
    if(in == n) {
        return 1;
    }

    if(dp[in] != -1) {
        return dp[in];
    }

    dp[in] = 0;
    string cword;
    for(int i=in;i<n;i++) {
        cword.push_back(s[i]);
        // if(diction.count(cword)) {
        if(diction->findString(cword)) {
            dp[in] += recurse(s, i+1, n, diction, dp);
            dp[in] %= int(1e9+7);
        }
    }

    return dp[in];
}

vector<vector<int>> trie;
vector<bool> isEndingNode;
int totalTrieNodes = 0;

void addString(string& s) {
    int cnode = 0;
    for(char& ch : s) {
        if(!trie[cnode][ch - 'a']) {
            trie[cnode][ch - 'a'] = ++totalTrieNodes;
        }
        cnode = trie[cnode][ch - 'a'];
    }
    isEndingNode[cnode] = 1;
}

bool findString(string& s) {
    int cnode = 0;
    for(char& ch : s) {
        if(!trie[cnode][ch - 'a']) {
            return 0;
        }
        cnode = trie[cnode][ch - 'a'];
    }

    return isEndingNode[cnode];
}

void solve() {
    
    string s;
    cin >> s;

    int i, n=s.size(), ts;
    cin >> ts;

    // Trie* diction = new Trie();
    // Trie diction;
    // set<string> diction;
    for(i=0;i<ts;i++) {
        // debug("yo");
        string word;
        cin >> word;

        addString(word);
        // diction->addWord(word);
        // diction.addWord(word);
        // diction.insert(word);
    }

    // string tst = "c";
    // cout << diction.findString(tst) << " <- \n";
    vector<int> dp(n+1, 0);
    dp[n] = 1;
    // cout << recurse(s, 0, n, diction, dp) << "\n";
    for(i=n-1;i>=0;i--) {
        // string cword;
        debug(i);
        int cnode = 0;
        for(int j=i;j<n;j++) {
            debug(j, s[j]);
            if(!trie[cnode][s[j] - 'a']) break;
            cnode = trie[cnode][s[j] - 'a'];

            if(isEndingNode[cnode]) {
                dp[i] += dp[j+1];
                dp[i] %= int(1e9+7);
            }
            debug(cnode, dp[j+1]);
            debug(dp);

            // cword.push_back(s[j]);
            // if(diction->findString(cword)) {
            // if(findString(cword)) {
            //     // if(j == n-1) {
            //     //     dp[i]++;
            //     // }
            //     // else {
            //     dp[i] += dp[j+1];
            //     // }
            //     dp[i] %= int(1e9+7);
            // }
        }
    }

    cout << dp[0] << "\n";

}

int main()
{
    trie = vector<vector<int>>(int(1e6+5), vector<int>(26));
    isEndingNode = vector<bool>(int(1e6+5));
    ios_base::sync_with_stdio(false);
	cin.tie(NULL);
    cout.tie(NULL);
    // int t;
    // cin >> t;
 
    // while(t--)
    // {
        solve();
    // }
 
    return 0;
}

// #include <bits/stdc++.h>
// using namespace std;

// #define ll long long
// const int mod = 1e9 + 7;

// // Declare the DP array and the Trie data structure
// vector<int> dp(5005);
// vector<vector<int> > trie(1e6 + 5, vector<int>(26));
// vector<bool> isEndOfWord(1e6 + 5);
// int trieNodeCount = 0;

// // Function to insert a word into the Trie
// void insertWordInTrie(string& word)
// {
//     int currentNode = 0;
//     for (char& ch : word) {
//         if (!trie[currentNode][ch - 'a'])
//             trie[currentNode][ch - 'a'] = ++trieNodeCount;
//         currentNode = trie[currentNode][ch - 'a'];
//     }
//     isEndOfWord[currentNode] = true;
// }

// // Function to count the number of ways to form the string
// // from index 'start'
// int countWays(int start, string& S)
// {
//     int currentNode = 0, ways = 0;
//     for (int i = start; i < S.size(); i++) {
//         if (!trie[currentNode][S[i] - 'a'])
//             return ways;
//         currentNode = trie[currentNode][S[i] - 'a'];
//         // If a word ends here, add the number of ways from the next index
//         if (isEndOfWord[currentNode])
//             ways = (ways + dp[i + 1]) % mod; 
//     }
//     return ways;
// }

// void solve(string& S, int K, string word[])
// {
//     for (int i = 0; i < K; i++) {
//         // Insert each word into the Trie
//         insertWordInTrie(word[i]); 
//     }
//     // Base case: One way to form an empty string
//     dp[S.size()] = 1; 
//     for (int i = S.size() - 1; i >= 0; i--) {
//         // Fill the DP table from right to left
//         dp[i] = countWays(i, S);
//     }
//     // The answer is the number of ways to form the string from index 0
//     cout << dp[0]; 
// }
// // Driver Code
// int main()
// {
//     // Input from user
//     // string S = "ababc";
//     // int K = 4;
//     // string arr[] = { "ab", "abab", "c", "cb" };
//     string S;
//     cin >> S;

//     int K;
//     cin >> K;

//     string arr[K];
//     for(int i = 0;i<K;i++) {
//         cin >> arr[i];
//     }

//     solve(S, K, arr);
//     return 0;
// }
