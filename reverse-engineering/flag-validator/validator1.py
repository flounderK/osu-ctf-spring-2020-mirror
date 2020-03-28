def secretop( key, b=7109340815511137277436103227634468226488145274050):
    a = int(key)
    s = []

    while a != 0 and b != 0:
        a = a // 3
        z1 = a
        b = b // 6

        if b == 0:
            z1 += 2
        else:
            z1 += 1

        s.append(z1 // 3)

    f = 0
    for value in s[::-1]:
        f = f * 3
        f += value
    
    return f

for i in range(99999, 999999):
    if secretop(i) == 135082787268816958421202995954498890820092905902643:
        print(i)
        quit()
