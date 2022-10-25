from cmath import sqrt
import matplotlib.pyplot as plt
import numpy as np
import math

a = 10
x = np.linspace(-a,a,a*100)
y = (abs((a**(2/3) - abs(x**2)**(1/3)))**(3/2)) * np.sign(a**(2/3) - abs(x**2)**(1/3))

fig, ax = plt.subplots()
ax.plot(x,y)
plt.show()