import sys
import random
import string

def get_random_string(length):
    letters = "ACGT"
    result_str = ''.join(random.choice(letters) for i in range(length))
    return result_str

for i in range(int(sys.argv[1])):
    print(get_random_string(2))
