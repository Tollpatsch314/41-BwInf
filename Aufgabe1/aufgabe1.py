import sys

originFile = open("Alice_im_Wunderland.txt", encoding="utf-8")
searchFile = open(sys.argv[1], encoding="utf-8")

origin = originFile.read().translate(str.maketrans("", "", "!.»«,()_-[]")) # deleting all punctuation and satzzeichen
search = searchFile.read()

originWords = origin.split()
searchWords = search.split()

searchIndices = [] # saves all indices where words are given

solutions = [] # saves the solutions

# saving the indeces
for i in range(len(searchWords)):
    if searchWords[i] != "_":
        searchIndices.append(i)

# goind throught the text
for origIndex in range(len(originWords)):
    fit = True
    for searchIndex in searchIndices:
        if (origIndex+searchIndex < len(originWords)) and (originWords[origIndex+searchIndex].upper() != searchWords[searchIndex].upper()):
            fit = False
            break
    if fit == True:
        solution = ""
        for j in range(len(searchWords)):
            solution += originWords[origIndex+j] + " "
        solutions.append(solution)
            
for sol in solutions:
    print(f'Lösung: {sol}')