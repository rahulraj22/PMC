#include <bits/stdc++.h>

using namespace std;

// Function to add an edge between vertices u and v
void addEdge(vector<vector<int>>& adj, int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
}

// Function to check if the current partitions A and B form a perfect matching cut
bool isPerfectMatchingCut(const vector<vector<int>>& adj, const vector<int>& A, const vector<int>& B) {
    for (int u : A) {
        int count = 0;
        for (int v : adj[u]) {
            if (find(B.begin(), B.end(), v) != B.end()) {
                count++;
            }
        }
        if (count != 1) {
            return false;
        }
    }

    for (int u : B) {
        int count = 0;
        for (int v : adj[u]) {
            if (find(A.begin(), A.end(), v) != A.end()) {
                count++;
            }
        }
        if (count != 1) {
            return false;
        }
    }

    return true;
}

// Recursive function to find a perfect matching cut
bool findPerfectMatchingCut(const vector<vector<int>>& adj, vector<int>& A, vector<int>& B, int undetermined) {
    if (undetermined == -1) {
        return isPerfectMatchingCut(adj, A, B);
    }

    bool found = false;

    // Try adding the undetermined vertex to partition A
    A.push_back(undetermined);
    found = findPerfectMatchingCut(adj, A, B, -1);
    A.pop_back();

    if (found) return true;

    // Try adding the undetermined vertex to partition B
    B.push_back(undetermined);
    found = findPerfectMatchingCut(adj, A, B, -1);
    B.pop_back();

    return found;
}

// Function to find an undetermined vertex in the graph
int getUndeterminedVertex(int V, const vector<int>& A, const vector<int>& B) {
    for (int v = 0; v < V; ++v) {
        if (find(A.begin(), A.end(), v) == A.end() && find(B.begin(), B.end(), v) == B.end()) {
            return v;
        }
    }
    return -1;
}

// Function to check if a perfect matching cut exists
bool hasPerfectMatchingCut(int V, const vector<vector<int>>& adj) {
    vector<int> A, B;
    int undetermined = getUndeterminedVertex(V, A, B);
    return findPerfectMatchingCut(adj, A, B, undetermined);
}

int main() {
    int V = 6; // Number of vertices in the graph
    vector<vector<int>> adj(V);

    // Adding edges to the graph
    addEdge(adj, 0, 1);
    addEdge(adj, 0, 2);
    addEdge(adj, 1, 3);
    addEdge(adj, 2, 4);
    addEdge(adj, 3, 5);
    addEdge(adj, 4, 5);

    // Checking if a perfect matching cut exists
    bool result = hasPerfectMatchingCut(V, adj);
    if (result) {
        cout << "The graph has a perfect matching cut." << endl;
    } else {
        cout << "The graph does not have a perfect matching cut." << endl;
    }

    return 0;
}
