import math

def gcd(*args):
    if len(args) == 1:
        return args[0]
    b = args[-1]
    a = args[-2]
    arg = args[:-2]
    if a%b == 0:
        return gcd(*arg, b)

    return gcd(*arg, b, a%b)

def lcm_two(a, b):
    return a * b // gcd(a,b)

def lcm(*args):
    if len(args) == 1:
        return args[0]
    b = args[-1]
    a = args[-2]
    arg = args[:-2]
    return lcm(*arg, a * b // gcd(a,b))

if __name__ == '__main__':
    print('gcd')
    a = gcd(20, 540, 56, 120)
    b = math.gcd(20, math.gcd(540, math.gcd(56, 120)))
    print(a == b, '\t', a, '\t', b)

    print('lcm')
    a = lcm_two(3, 4)
    print(a, ' -> should be 12')

    a = lcm(3, 4, 5)
    print(a, ' -> should be 3 * 4 * 5 = 60')
