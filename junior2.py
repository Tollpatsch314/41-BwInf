from sys import argv

class Node:
    def __init__(self, number):
        self.number = number
        self.children = []

def getAll(tree):
    if tree:
        if tree.number not in foundChildren:
            foundChildren.append(tree.number)
            for child in tree.children:
                getAll(child)

origin = open(argv[1]).read()
pairs = origin.split('\n')

count = 0
for pair in pairs:
    pair = [int(pair.split()[0]), int(pair.split()[1])] # integerizing
    if max(pair) > count: 
        count = max(pair)

containers = []
for i in range(1, count+1):
    containers.append(Node(i))

for pair in pairs:
    containers[int(pair.split()[0])-1].children.append(containers[int(pair.split()[1])-1])

found = False
for container in containers:
    foundChildren = []
    getAll(container)
    if len(foundChildren) == count:
        found = True
        print(f'Der schwerste Container ist {container.number}')
if found == False:
    print("Der schwerste Container ist nicht feststellbar")