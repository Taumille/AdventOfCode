#!/bin/python

import random


def parse(data, rules, book):
    nb = 0
    rule = [0, 0]
    sprint = []
    consecutiveCR = 0
    parsing_rule = True

    for e in data:
        if e <= "9" and e >= "0":
            consecutiveCR = 0
            nb = nb*10+int(e)
        elif e == "|":
            rule[0] = nb
            nb = 0
        elif e == ",":
            sprint += [nb]
            nb = 0
        elif e == '\n':
            if consecutiveCR == 0 and parsing_rule:
                consecutiveCR += 1
                rule[1] = nb
                rules += [[rule[0], rule[1]]]
                nb = 0
            elif not (parsing_rule):
                sprint += [nb]
                book += [sprint]
                nb = 0
                sprint = []
            else:
                parsing_rule = False
    sprint += [nb]
    book += [sprint]


def putafter(r, b):
    i0 = b.index(r[0])
    i1 = b.index(r[1])

    for i in range(i1, i0):
        b[i] = b[i+1]
    b[i0] = r[1]

if __name__ == "__main__":
    with open('input.txt', 'r') as file:
        data = file.read().rstrip()

    rules = []
    book = []
    notlist = []

    parse(data, rules, book)

    for i in range(len(book)):
        print((i, len(book)))
        for rule in rules:
            if (rule[0] in book[i]):
                # print(f"Searching {rule[1]} in {}")
                if (rule[1] in book[i][0:book[i].index(rule[0])]):
                    if not (i in notlist):
                        notlist += [i]

    result = 0
    for i in range(len(book)):
        if not (i in notlist):
            result += book[i][int((len(book[i])-1)/2)]

    print(f"Part 1 : {result}")

    accurate_rule = 0
    nb_return = 0

    nsbook = []

    for i in notlist:
        nsbook += [book[i]]

    for i in range(len(nsbook)):
        for r in rules:
            if (r[0] in nsbook[i]):
                if (r[1] in nsbook[i][0:nsbook[i].index(r[0])]):
                    putafter(r, nsbook[i])

    result = 0
    for i in range(len(nsbook)):
        result += nsbook[i][int((len(nsbook[i])-1)/2)]

    print(f"Part 2 : {result}")
