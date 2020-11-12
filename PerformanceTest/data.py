# A simple script to create random and semi-random data
# to be used in perfomance tests between three binary trees: BST, AVL and RB.

from random import shuffle, randint

N = 1000000

# Random Data
randomData = []
for i in range(N):
    randomData.append(i)
shuffle(randomData)

# Semi-random Data
semiRandomData = []
for i in range(i):
    if randint(0, 9) != 0:
        semiRandomData.append(i)
    else:
        semiRandomData.append(-i)

# Save data in files
f = open("random-data", "w")
for item in randomData:
    f.write(str(item) + '\n')
f.close()

f = open("semi-random-data", "w")
for item in semiRandomData:
    f.write(str(item) + '\n')
f.close()