'''
tarjan scc algorithm
if it is a back edge, we take visit[next]
if it is a tree (in directed graphs, is a directed tree) we take low[next]

a node remains in the stack iff it has some 'back path' to a node earlier in the stack
if visit[v] == low[v] means it is the 'root' of this scc (root can change depend on dfs order)
'''

class FindSCC:
    def __init__(self, n: int, edges: list[tuple[int,int]]):
        self.n = n
        self.visit = [-1 for _ in range(n)]
        self.low = [n for _ in range(n)]
        self.in_stack = [False for _ in range(n)]
        self.stack = []
        self.id = 0

        self.adj = [[] for _ in range(n)]
        for e in edges:
            self.adj[e[0]].append(e[1])
        
        for lst in self.adj:
            lst.sort()

        self.sccs = []


    def dfs(self, v: int, p: int):
        self.visit[v] = self.low[v] = self.id
        self.id += 1
        self.stack.append(v)
        self.in_stack[v] = True

        for next in self.adj[v]:
            if next == p:
                continue
            elif self.visit[next] == -1:
                self.dfs(next, v)
                self.low[v] = min(self.low[v], self.low[next])
            elif not self.in_stack[next]:
                # because it is pointing to a scc that has been popped, so ignore
                continue
            else:
                # we are at a back edge
                self.low[v] = min(self.low[v], self.visit[next])

        if self.visit[v] == self.low[v]:
            scc = []
            while True:
                u = self.stack.pop()
                self.in_stack[u] = False
                scc.append(u)
                if u == v:
                    break
            self.sccs.append(scc)
    
    def get_sccs(self):
        for i in range(self.n):
            if self.visit[i] != -1:
                continue
            self.dfs(i, i)
        
        for scc in self.sccs:
            scc.sort()
        self.sccs.sort()
        
        return self.sccs
                    


