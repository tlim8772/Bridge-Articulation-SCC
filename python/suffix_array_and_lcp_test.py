import unittest
from suffix_array_and_lcp import *

class Test(unittest.TestCase):
    def test1(self):
        s = "aaa"
        f = FindSuffixArrayAndLCP(s)
        ans = f.getSuffixArray()
        self.assertEqual(ans, [2,1,0])

    def test2(self):
        s = "abaab"
        f = FindSuffixArrayAndLCP(s)
        ans = f.getSuffixArray()
        self.assertEqual(ans, [2,3,0,4,1])

    def test3(self):
        s = "abcbcba"
        f = FindSuffixArrayAndLCP(s)
        ans = f.getSuffixArray()
        self.assertEqual(ans, [6,0,5,3,1,4,2])

    def test4(self):
        s = "aabbcc"
        f = FindSuffixArrayAndLCP(s)
        _, lcp = f.getSuffixArrayAndLCP()
        self.assertEqual(lcp, [0,1,0,1,0,1])

    def test5(self):
        s = "gatagaca"
        f = FindSuffixArrayAndLCP(s)
        _, lcp = f.getSuffixArrayAndLCP()
        self.assertEqual(lcp, [0,1,1,1,0,0,2,0])

    def test6(self):
        s = "MISSISSIPPI"
        f = FindSuffixArrayAndLCP(s)
        sa, lcp = f.getSuffixArrayAndLCP()
        self.assertEqual(sa, [10,7,4,1,0,9,8,6,3,5,2])
        self.assertEqual(lcp, [0,1,1,4,0,0,1,0,2,1,3])

if __name__ == '__main__':
    unittest.main()