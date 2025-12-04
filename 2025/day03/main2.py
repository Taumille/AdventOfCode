def convert_to_num(l):
    l.reverse()
    n = 0
    while len(l):
        n *= 10
        n += l.pop()
    return n

f = open("input.txt", "r")
l_in = f.readlines()

sum = 0
for line in l_in:
    line_int = [int(e) for e in line[:-1]]
    box = [0 for _ in range(12)]
    restricted_index = 0

    for i in range(11):
        print(f"Line : {restricted_index} {i+1-12}")
        box[i] = max(line_int[restricted_index:i+1-12])
        restricted_index = line_int.index(box[i], restricted_index)+1
        print(f"{box} : {line_int[restricted_index:i+1-12]}")
    box[11] = max(line_int[restricted_index:])
    print(f"{box}")
    print("\n\n")
    sum += convert_to_num(box)

print(sum)
