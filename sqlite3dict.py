#!/usr/bin/env python

import sqlitedict
from sqlite_object import SqliteDict, SqliteList, SqliteSet
import sys

try:
    n = int(eval(sys.argv[1]))
except:
    n = 10

#ht = sqlitedict.SqliteDict('tmp.sql')
ht = SqliteDict(filename='tmp.sql', persist=True, commit_every=2**20)

for i in range(n):
    ht[i] = i
    if i % 1000000 == 1:
        print(i)
        ht.commit()

ht.commit()

print(list(ht.keys())[-10:])

#ht.close()
