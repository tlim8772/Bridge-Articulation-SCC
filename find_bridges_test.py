import unittest
from find_bridges import *

class Test(unittest.TestCase):
    def test1(self):
        n = 4
        edges = [(0,1),(0,2),(1,2),(2,3)]
        finder = FindBridges(n, edges)
        ans = finder.get_bridges()
        print(ans)
        self.assertEqual(ans, [(2,3)])

    def test2(self):
        n = 4
        edges = [(0,1),(1,2),(2,3),(3,0)]
        finder = FindBridges(n, edges)
        ans = finder.get_bridges()
        print(ans)
        self.assertEqual(ans, [])

    def test3(self):
        n = 6
        edges = [(0,1),(0,2),(1,2),(1,3),(3,4),(3,5),(4,5)]
        finder = FindBridges(n, edges)
        ans = finder.get_bridges()
        print(ans)
        self.assertEqual(ans, [(1,3)])



if __name__ == '__main__':
    unittest.main()
    