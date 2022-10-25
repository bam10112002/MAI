

def a(x):
    return 1/(2**x*0.69-2*x)

def f(x):
    return (2**x - x**2 - 0.5)

def psi(x):
    return x + a(x) * (2**x-x**2-0.5)

x = 5
for i in range(500):
    x = psi(x)
    print(x)

print(x)
