import random
import string

def RandomString(length=10):
    letters = string.ascii_lowercase
    return ''.join(random.choice(letters) for i in range(length))

LONG_LONG = 18446744073709551615

insert = open("tbbtpy", "w+")
search = open("searchTbbtpy", "w+")
#delete = open("deleteTbbtpy", "w+")

for i in range(100000):
    key = RandomString()
    insert.write(f"+ {key} {i}\n")
    search.write(f"{key}\n")
#    delete.write(f"- {key}\n")
    print(f"- {key}")