'''
a bridge is always a tree edge
same thing, 
if back edge, take low[v] = min(low[v], visit[next])
if tree edge, take low[v] = min(low[v], low[next])
edge is a bridge iff (assume visit[u] < visit[v]) low[v] > visit[u]

'''
class FindBridges:
    def __init__(self, n: int, edges: list[tuple[int,int]]): 
        self.n = n
        self.visit = [-1 for _ in range(n)]
        self.low = [-1 for _ in range(n)]
        self.id = 0
        self.adj = [[] for _ in range(n)]
        self.edges: list[tuple[int,int]] = edges
        for e in edges:
            self.adj[e[0]].append(e[1])
            self.adj[e[1]].append(e[0])

    def dfs(self, v: int, p: int):
        self.visit[v] = self.low[v] = self.id
        self.id += 1

        for next in self.adj[v]:
            if next == p:
                continue

            if self.visit[next] != -1:
                self.low[v] = min(self.low[v], self.visit[next])
            else:
                self.dfs(next, v)
                self.low[v] = min(self.low[v], self.low[next])

    def get_bridges(self):
        self.dfs(0, 0)
        bridges = []
        for e in self.edges:
            u, v = e
            if self.visit[u] > self.visit[v]:
                u, v = v, u

            if self.low[v] > self.visit[u]:
                bridges.append((u, v))

        bridges.sort()
        return bridges