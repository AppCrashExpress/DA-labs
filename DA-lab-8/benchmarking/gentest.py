import sys

def list_to_line(orig_list):
    str_list = ' '.join([str(e) for e in orig_list])
    str_list += '\n'
    return str_list

def gen_test(m_size, n_size, filename = "test.txt"):
    with open(filename, "w") as test_file: 
        test_file.write(f"{m_size} {n_size}\n")

        for i in range(n_size - 1):
            equation = [0] * (n_size + 1)
            equation[i] = 1
            equation[n_size] = 1
            test_file.write(list_to_line(equation))
        
        equation = [1] * (n_size + 1)
        equation[n_size - 1] = 0
        for i in range(m_size - n_size):
            test_file.write(list_to_line(equation))

        equation = [0] * (n_size + 1)
        equation[n_size - 1] = 1
        equation[n_size] = 1
        test_file.write(list_to_line(equation))


if __name__ == "__main__":
    if len(sys.argv) < 3:
        print(f"Usage: {sys.argv[0]} m_size n_size [filename]")
    else:     
        m_size = int(sys.argv[1])
        n_size = int(sys.argv[2])
        filename = "test.txt"

        if (len(sys.argv) > 3):
            filename = sys.argv[3]

        gen_test(m_size, n_size, filename)
