#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// 广度优先搜索
class Solution1
{
public:
    bool validPath(int n, vector<vector<int>> &edges, int source, int destination)
    {
        vector<vector<int>> adj(n);
        vector<bool> visited(n, false);
        for (auto &edge : edges)
        {
            int u = edge[0];
            int v = edge[1];
            adj[u].emplace_back(v);
            adj[v].emplace_back(u);
        }
        queue<int> q;
        q.push(source);
        visited[source] = true;
        while (!q.empty())
        {
            int vertex = q.front();
            q.pop();
            if (vertex == destination)
            {
                visited[destination] = true;
                break;
            }
            for (int next : adj[vertex])
            {
                if (!visited[next])
                {
                    q.push(next);
                    visited[next] = true;
                }
            }
        }
        return visited[destination];
    }
};

// 深度优先搜索
class Solution2
{
public:
    bool dfs(int source, int destination, vector<vector<int>> &adj, vector<bool> &visited)
    {
        if (source == destination)
        {
            return true;
        }
        visited[source] = true;
        for (int next : adj[source])
        {
            if (!visited[next] && dfs(next, destination, adj, visited))
            {
                return true;
            }
        }
        return false;
    }

    bool validPath(int n, vector<vector<int>> &edges, int source, int destination)
    {
        vector<vector<int>> adj(n);
        for (auto &edge : edges)
        {
            int x = edge[0], y = edge[1];
            adj[x].emplace_back(y);
            adj[y].emplace_back(x);
        }
        vector<bool> visited(n, false);
        return dfs(source, destination, adj, visited);
    }
};



// 并查集
class UnionFind
{
public:
    UnionFind(int n)
    {
        parent = vector<int>(n);
        rank = vector<int>(n);
        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
        }
    }

    void uni(int x, int y)
    {
        int rootx = find(x);
        int rooty = find(y);
        if (rootx != rooty)
        {
            if (rank[rootx] > rank[rooty])
            {
                parent[rooty] = rootx;
            }
            else if (rank[rootx] < rank[rooty])
            {
                parent[rootx] = rooty;
            }
            else
            {
                parent[rooty] = rootx;
                rank[rootx]++;
            }
        }
    }

    int find(int x)
    {
        if (parent[x] != x)
        {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    bool connect(int x, int y)
    {
        return find(x) == find(y);
    }

private:
    vector<int> parent;
    vector<int> rank;
};

class Solution3
{
public:
    bool validPath(int n, vector<vector<int>> &edges, int source, int destination)
    {
        if (source == destination)
        {
            return true;
        }
        UnionFind uf(n);
        for (auto edge : edges)
        {
            uf.uni(edge[0], edge[1]);
        }
        return uf.connect(source, destination);
    }
};