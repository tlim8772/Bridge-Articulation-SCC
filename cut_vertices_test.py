import unittest
from cut_vertices import *

class Test(unittest.TestCase):
    def test1(self):
        n = 9
        edges = [(0,1),(0,2),(1,2),(2,3),(2,5),(3,4),(5,6),(5,8),(6,7),(7,8)]
        finder = FindCutVertices(n, edges)
        ans = finder.get_cut_vertices()
        print(ans)
        self.assertEqual(ans, [2, 3, 5])

    def test2(self):
        n = 5
        edges = [(0,1),(0,2),(1,2),(2,3),(2,4),(3,4)]
        finder = FindCutVertices(n, edges)
        ans = finder.get_cut_vertices()
        print(ans)
        self.assertEqual(ans, [2])

    def test3(self):
        n = 6
        edges = [(0,1),(0,2),(1,3),(2,3),(2,4),(3,5)]
        finder = FindCutVertices(n, edges)
        ans = finder.get_cut_vertices()
        print(ans)
        self.assertEqual(ans, [2, 3])


if __name__ == '__main__':
    unittest.main()