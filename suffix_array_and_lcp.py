

class FindSuffixArrayAndLCP:
    def __init__(self, s: str):
        self.s = s
        self.suffixArray: list[int] = [0 for _ in range(len(s))]
        self.lcp: list[int] = [0 for _ in range(len(s))]
        return
    
    '''
    for 2^(p - 1), the suffixes are sorted already
    '''
    @staticmethod
    def helper(p: int, lst: list[list[int]]) -> None:
        prev = lst[0][1:]
        lst[0][1] = 1
        for i in range(1, len(lst)):
            temp = lst[i][1:]
            lst[i][1] = lst[i - 1][1] if lst[i][1:] == prev else lst[i - 1][1] + 1
            prev = temp

        idxToPos = [0 for _ in range(len(lst))]
        for i in range(len(lst)):
            idxToPos[lst[i][0]] = i
        
        for arr in lst:
            nextIdx = arr[0] + (1 << (p - 1))
            arr[2] = 0 if nextIdx >= len(lst) else lst[idxToPos[nextIdx]][1]

        lst.sort(key=lambda x: x[1:])
    
    def getSuffixArray(self) -> list[int]:
        # elem of lst is [index of start of suffix, order1, order2]
        # remember, 0 is reserved for empty string, a non empty string cannot have order 0
        lst = [[i, ord(self.s[i]), 0] for i in range(len(self.s))]
        lst.sort(key=lambda x: x[1:])

        p = 1
        while True:
            FindSuffixArrayAndLCP.helper(p, lst)
            if p >= len(self.s):
                break
            p <<= 1

        for i in range(len(lst)):
            self.suffixArray[i] = lst[i][0]
        
        return self.suffixArray
        
    def getLCP(self) -> list[int]:
        idxToPos = [0 for _ in range(len(self.s))]
        for i, si in enumerate(self.suffixArray):
            idxToPos[si] = i

        h = 0
        for i in range(len(self.s)):
            pos = idxToPos[i]
            if pos == 0:
                self.lcp[pos] = 0
                continue

            prevIdx = self.suffixArray[pos - 1]
            while h < len(self.s) - max(i, prevIdx):
                if (self.s[i + h] == self.s[prevIdx + h]):
                    h += 1
                else:
                    break

            self.lcp[pos] = h
            h = max(h - 1, 0)
        
        return self.lcp
    
    def getSuffixArrayAndLCP(self):
        return [self.getSuffixArray(), self.getLCP()]


