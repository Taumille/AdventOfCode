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
    goal = int(e[1:])
    val = 0
    while val != goal:
        sum = (sum + 1 * sense) % 100
        val +=1

        if sum == 0:
            password += 1

print(password)
