#!/opt/local/bin/python
# coding: utf8

# http://stackoverflow.com/questions/2573135/python-progression-path-from-apprentice-to-guru

s = []
for x in range(0, 10):
    s.append(x**2)
print(s)

s = list(map(lambda x: x**2, range(0, 10)))
print(s)

s = [x**2 for x in range(0, 10)]
print(s)
    
s = [(x, x**2, x**3) for x in range(0, 10)]
print(s)

