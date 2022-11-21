import sys
 
# get all starting indices of vowel groups in a word
def getGroupIndices(word):
    vowels = "aeiouäüö"
    groupIndices = []
    groupIndex = -1
    wordIndex = 0
    while wordIndex < len(word):
        if word[wordIndex] in vowels:
            groupIndex = wordIndex
            while wordIndex < len(word) and word[wordIndex] in vowels:
                wordIndex += 1
            groupIndices.append(groupIndex)
        wordIndex += 1
    
    return groupIndices

wordFile = open(sys.argv[1], encoding="utf-8")
words = wordFile.read().split("\n")

endGroups = []
# getting all end groups
for word in words:
    groupIndices = getGroupIndices(word)
    govIndex = 0
    if len(groupIndices) == 0:
        endGroups.append(None)
    else:
        if len(groupIndices) == 1:
            govIndex = groupIndices[0]
        else:
            govIndex = groupIndices[len(groupIndices)-2]
        
        # at least half the letters in important group
        if govIndex >= (len(word) * 0.5):
            endGroups.append(None)
        else:
            endGroup = ""
            endIndex = govIndex
            while endIndex < len(word):
                endGroup += word[endIndex]
                endIndex += 1
            endGroups.append(endGroup)                

# checking for every word if it rhymes with another one
solutions = []
primEndIndex = 0
while primEndIndex < len(endGroups):
    if endGroups[primEndIndex]:
        secEndIndex = primEndIndex+1
        while secEndIndex < len(endGroups):
            if endGroups[secEndIndex]:
                if endGroups[primEndIndex].upper() == endGroups[secEndIndex].upper():
                    # SS = ß!
                    if (words[primEndIndex].upper() not in words[secEndIndex].upper() and words[secEndIndex].upper() not in words[primEndIndex].upper()):
                        solutions.append(f'{words[primEndIndex]}, {words[secEndIndex]}')
            secEndIndex += 1
    primEndIndex+=1

for sol in solutions:
    print(f'Lösung: {sol}')