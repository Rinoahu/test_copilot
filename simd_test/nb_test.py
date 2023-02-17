#!usr/bin/env python
from numba import njit
import numpy as np

def find_instr(func, keyword, sig=0, limit=2**30):
    count = 0
    for l in func.inspect_asm(func.signatures[sig]).split('\n'):
        if keyword in l:
            count += 1
            print(l)
            if count >= limit:
                break
    if count == 0:
        print('No instructions found')


@njit
def sqdiff(x):
    N = len(x)
    y = np.empty(N, dtype='int16')
    bw = 16
    #for i in range(1, N):
    for i in range(bw, N):
        y[i] = x[i-bw]-1
        #y[i] = x[i-16] - 1

    return y

x32 = np.random.randn(2**30).astype('int16')
sqdiff(x32)
print('int16:')
find_instr(sqdiff, keyword='mm', sig=0)

sqdiff.signatures[0]
