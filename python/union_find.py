from typing import TypeVar, Generic, Callable

T = TypeVar('T')
class UnionFind(Generic[T]):
    def __init__(self, n: int, func: Callable[[T, T], T], default_value: T):
        self.parents = [i for i in range(n)]
        self.weights = [1 for _ in range(n)]
        self.values = [default_value for _ in range(n)]
        self.func = func

    def find(self, u: int) -> int:
        if self.parents[u] == u:
            return u
        else:
            self.parents[u] = self.find(self.parents[u])
            return self.parents[u]
        
    def getVal(self, u: int) -> T:
        return self.values[self.find(u)]
    
    def setVal(self, u: int, val: T):
        self.values[self.find(u)] = val

    def join(self, u: int, v: int):
        pu, pv = self.find(u), self.find(v)
        wu, wv = self.weights[pu], self.weights[pv]
        if (wu < wv):
            return self.join(v, u)
        self.weights[pu] += wv
        self.parents[pv] = pu
        self.values[pu] = self.func(self.values[pu], self.values[pv])