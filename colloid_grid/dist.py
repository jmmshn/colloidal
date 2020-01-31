from numpy import *

data=loadtxt("positions/000017.dat") 

for itr1 in range(4):
    for itr2 in range(4):
        if itr1 != itr2:
            print itr1, itr2
            p1=data[itr1,:2];
            p2=data[itr2,:2];
            print linalg.norm(p1-p2)
