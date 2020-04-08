import numpy as np
import matplotlib.pyplot as plt

myLogValue = np.log10(9)

logValues = []

for x in range(1, 100):
	logValues.append(np.log10(x))

plt.plot(logValues)
plt.ylabel('output values')
plt.xlabel('input values')
plt.savefig('logPlot.png', transparent=False)
plt.show()
