import sys

ALPHABET_SIZE = 122 - 97

def gen_line(line_no):
    res = ""
    while line_no > ALPHABET_SIZE + 1:
        res += "z"
        line_no = line_no - ALPHABET_SIZE - 1

    res += (chr(96 + line_no))

    return res

if __name__ == "__main__":
    count = int(sys.argv[1])

    for i in range(1, count + 1):
        print(gen_line(i))
