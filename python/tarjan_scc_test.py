import unittest
import sys
from tarjan_scc import *

class Test(unittest.TestCase):
    def test1(self):
        n = 3
        edges = [(0,1),(1,2),(2,0)]
        finder = FindSCC(n, edges)
        ans = finder.get_sccs()
        self.assertEqual(ans, [[0,1,2]])

    def test2(self):
        n = 3
        edges = [(0,1),(1,2)]
        finder = FindSCC(n, edges)
        ans = finder.get_sccs()
        self.assertEqual(ans, [[0],[1],[2]])

    def test3(self):
        n = 5
        edges = [(0,1),(1,2),(2,0),(1,3),(3,4)]
        finder = FindSCC(n, edges)
        ans = finder.get_sccs()
        self.assertEqual(ans, [[0,1,2],[3],[4]])

    def test4(self):
        n = 7
        edges = [(0,1),(1,2),(2,0),(1,3),(3,2),(2,4),(3,5),(5,4),(4,6),(6,5)]
        finder = FindSCC(n, edges)
        ans = finder.get_sccs()
        self.assertEqual(ans, [[0,1,2,3],[4,5,6]])

    def test5(self):
        n = 1000
        edges = []
        for i in range(n):
            for j in range(i + 1, n):
                edges.append((i,j))
        finder = FindSCC(n, edges)
        ans = finder.get_sccs()
        self.assertEqual(ans, [[i] for i in range(n)] )


if __name__ == '__main__':
    sys.setrecursionlimit(100000)
    unittest.main()