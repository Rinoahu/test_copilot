#!usr/bin/env python
import sys

# this function is used to reorder the vector
def reorder(x, bw=8):
    N = len(x)
    M = (N + bw - 1) // bw
    y = [0] * N
    for j in range(M):
        for i in range(bw):
            y[i+j*bw] = x[i*M +j]

    return y


def reorder2(x, bw=8):
    N = len(x)
    M = (N + bw - 1) // bw
    y = [0] * N
    for i in range(N):
        y[i] = x[i%bw*M+i//bw]

    return y



N,  bw = map(eval, sys.argv[1:3])


#x = range((N + bw - 1)// bw * bw)
x = range(N)
y = reorder2(x, bw)

for i in range(0, N, bw):
    print(y[i: i+bw])

