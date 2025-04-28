// Author: Ridham Garg

class Solution {
public:

    // Helper function to perform BFS traversal and find maximum path length from start node
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
