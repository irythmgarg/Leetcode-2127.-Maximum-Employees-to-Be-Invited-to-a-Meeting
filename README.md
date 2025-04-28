# Leetcode-2127.-Maximum-Employees-to-Be-Invited-to-a-Meeting

# Maximum Invitations Solution

## Author
Ridham Garg

## Problem Statement

Given a vector `favorite[]` representing a directed graph where each node points to its favorite node, your task is to calculate the maximum number of invitations that can be sent in such a way that all the favorite nodes of any node can be invited.

## Approach

This problem can be interpreted as a graph traversal problem. The idea is to find cycles in the graph, as these cycles represent mutual invitations where two nodes point to each other. We also need to find paths that extend from these cycles, allowing for additional invitations. The solution is based on graph traversal (BFS/DFS) to detect cycles and compute the maximum number of reachable nodes.

### Key steps:
1. **Graph Construction**: We reverse the direction of edges in the graph, so we can explore paths backward.
2. **Cycle Detection**: We track nodes as we traverse and use a map to detect when a cycle is formed.
3. **Cycle Handling**: For cycles of length 2 (happy couples), we count all the nodes in the cycle plus any reachable nodes that are not part of the cycle.
4. **BFS Traversal**: After detecting cycles, we use BFS to count the maximum number of nodes that can be reached from the cycle.

### Algorithm
1. Build the reversed graph from the `favorite[]` vector.
2. For each unvisited node, traverse until a cycle is found.
3. If a cycle of length 2 is found, calculate its contributions using BFS.
4. Return the maximum number of invitations possible, which will be the largest among the happy couples and longest cycles.

## Code
```cpp
class Solution {
public:

    int BFS(int start, unordered_map<int, vector<int>>& adj, vector<bool>& visited) {
        queue<pair<int, int>> que; // Queue stores {node, path length}
        que.push({start, 0});
        int maxDistance = 0;

        while(!que.empty()) {
            auto[currNode, dist] = que.front();
            que.pop();

            for(auto &ngbr : adj[currNode]) {
                if(!visited[ngbr]) {
                    visited[ngbr] = true;
                    que.push({ngbr, dist + 1});
                    maxDistance = max(maxDistance, dist + 1);
                }
            }
        }

        return maxDistance;
    }

    int maximumInvitations(vector<int>& favorite) {
        int n = favorite.size();
        unordered_map<int, vector<int>> adj;

        // Build reversed graph (edges from favorite to current node)
        for(int i = 0; i < n; i++) {
            int u = i;
            int v = favorite[i];
            adj[v].push_back(u);
        }

        int longestCycleEmplCount = 0; // Tracks maximum cycle length
        int happyCoupleEmplCount  = 0; // Sum for all 2-length cycles with branches

        vector<bool> visited(n, false);

        for(int i = 0; i < n; i++) {
            if(!visited[i]) {
                unordered_map<int, int> mp; // Stores node and distance from start

                int currNode = i;
                int currNodeCount = 0;

                while(!visited[currNode]) {
                    visited[currNode] = true;
                    mp[currNode] = currNodeCount;

                    int nextNode = favorite[currNode];
                    currNodeCount += 1;

                    if(mp.count(nextNode)) { // Cycle detected
                        int cycleLength = currNodeCount - mp[nextNode];
                        longestCycleEmplCount = max(longestCycleEmplCount, cycleLength);

                        if(cycleLength == 2) { // Special handling for cycles of length 2
                            vector<bool> visitedNodes(n, false);
                            visitedNodes[currNode] = true;
                            visitedNodes[nextNode] = true;
                            happyCoupleEmplCount += 2 + BFS(currNode, adj, visitedNodes) + BFS(nextNode, adj, visitedNodes);
                        }
                        break;
                    }
                    currNode = nextNode;
                }
            }
        }

        return max(happyCoupleEmplCount, longestCycleEmplCount);
    }
};
```

## Complexity Analysis
### Time Complexity
- **Building the reversed graph** takes O(n), where `n` is the size of the `favorite[]` vector.
- **Cycle detection and BFS traversal** will also take O(n), as we are visiting each node and its neighbors once.

Thus, the total time complexity is O(n).

### Space Complexity
- **Graph storage** requires O(n) space.
- **Visited nodes** and auxiliary data structures require O(n) space.

Hence, the total space complexity is O(n).

## Conclusion
The provided solution efficiently calculates the maximum invitations using BFS and cycle detection techniques, handling edge cases and ensuring optimal performance.

