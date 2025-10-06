'''
do a dfs, the edge used form a tree
case 1: 
    back edge (i.e edge not in dfs tree).
    then low[v] = min(low[v], visit[next])
    why visit[next] and not low[v] ? because we are interested in the 1st vertex that is 
    an ancestor of v that can be reached outside of this dfs subtree. If we take low[next]
    it could be next is a cut vertex, but can reach low[u] which is lower than visit[next]

case 2:
    tree edge (i.e edge used in dfs)
    low[v] = min(low[v], low[next])

if a vertex v is a articulation point, then there exist and edge to u
s.t visit[u] > visit[v] and low[v] >= visit[v]
'''

class FindCutVertices:
    def __init__(self, n: int, edges: list[tuple[int,int]]):
        self.n = n
        self.visit: list[int] = [-1 for _ in range(n)]
        self.low: list[int] = [n for _ in range(n)]
        self.id = 0
        
        self.edges = edges
        self.adj = [[] for _ in range(n)]
        for e in edges:
            self.adj[e[0]] += [e[1]]
            self.adj[e[1]] += [e[0]]

    def dfs(self, v: int, p: int):
        cnt = 0
        self.visit[v] = self.low[v] = self.id
        self.id += 1
        
        for next in self.adj[v]:
            if next == p:
                continue
            
            if self.visit[next] == -1:
                cnt += 1
                self.dfs(next, v)
                self.low[v] = min(self.low[v], self.low[next])
            else:
                self.low[v] = min(self.low[v], self.visit[next])
            
        if v == p and cnt > 1:
            self.cut_vertices[v] = True

    def get_cut_vertices(self):
        self.dfs(0, 0) # 0 is always the root of the dfs tree
        out = []
        for i in range(1, self.n):
            for next in self.adj[i]:
                if self.visit[next] > self.visit[i] and self.low[next] >= self.visit[i]:
                    out.append(i)
                    break
        return out



        

n = 9
edges = [(0,1),(0,2),(1,2),(2,3)]