f = open("input.txt", "r")
l_in = f.readlines()
l_in = [e[:-1] for e in l_in]

password = 0
sum = 50
for e in l_in:
    if e[0] == 'R':
        sense = +1
    else:
        sense = -1
    val = int(e[1:])
    sum = (sum + val * sense) % 100

    if sum == 0:
        password += 1

print(password)
