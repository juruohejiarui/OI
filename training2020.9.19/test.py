a = 1
fl = open("../test.out", mode='w')
for i in range(1, 200000):
    a = a * 2
    fl.write(str(a))
    