import time
import sys
import os

# Handle the fact that this code may not
# be in the same directory as the solution code
sys.path.insert(0, os.getcwd())

from listortho import ListOrthographer
from trieortho import TrieOrthographer

VERBOSE = False

def time_orthographers(lo, to, test_words):

    for (name, ortho) in [('ListOrthographer',lo), ('TrieOrthographer',to)]:
        print(f'Number of words in {name}: {ortho.num_words()}')

    times = {'ListOrthographer': [], 'TrieOrthographer': []}
    for (name, ortho) in [('ListOrthographer',lo), ('TrieOrthographer',to)]:
        for word in test_words:
            time0 = time.time()
            b = ortho.contains(word)
            time1 = time.time()
            time_delta = time1-time0
            if VERBOSE:
                print(f'testing if {name} contains "{word}": {b}')
                print(f'{time_delta:.3e}')
            times[name].append(time_delta)

    avg_lo = sum(times["ListOrthographer"]) / len(times["ListOrthographer"])
    avg_to = sum(times["TrieOrthographer"]) / len(times["TrieOrthographer"])

    print()
    if avg_to < avg_lo:
        pct = ((avg_lo-avg_to)/avg_to) * 100
        print(f"On average, the ListOrthographer took {pct:.2f}% more time than the TrieOrthographer")
    elif avg_to > avg_lo:
        pct = ((avg_to-avg_lo)/avg_lo) * 100
        print(f"On average, the TrieOrthographer took {pct:.2f}% more time than the ListOrthographer")
    else:
        print(f"On average, the TrieOrthographer and the ListOrthographer performed the same")


if __name__ == "__main__":
    if len(sys.argv) == 2 and sys.argv[1] == "-v":
        VERBOSE = True

    print('*** Timing orthographers with "m-words.txt"\n')

    lo = ListOrthographer()
    to = TrieOrthographer()

    lo.insert_from_file('m-words.txt')
    to.insert_from_file('m-words.txt')

    time_orthographers(lo, to, ['mistletoe', 'molasses', 'meteor'])

    print('\n*** Timing orthographers with "web2.shuf" (this might take a while)\n')

    lo = ListOrthographer()
    to = TrieOrthographer()

    if VERBOSE:
        print('building ListOrthographer...')
    # We're going to cheat here and create the words list
    # directly, bypassing insert, so we don't have to
    # check for duplicates, etc. Otherwise it takes
    # too long to build the orthographer!
    with open('web2.shuf') as f:
        set_words = set()
        for word in f.readlines():
            word = word.strip()
            if word.islower():
                set_words.add(word)
        lo.words = list(set_words)

    if VERBOSE:
        print('done building ListOrthographer')
        print('building TrieOrthographer...')

    to.insert_from_file('web2.shuf')

    if VERBOSE:
        print('done building TrieOrthographer')

    time_orthographers(lo, to, ['mistletoe', 'molasses', 'meteor', 'aardvark', 'zoology', 'rapscallion', 'xxxyyy'])

