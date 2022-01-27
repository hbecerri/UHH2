import matplotlib.pyplot as plt
from sys import argv
x = []
y = []
for line in open(argv[1], 'r'):
    lines = [i for i in line.split()]
    x.append(lines[0])
    y.append(float(lines[1]))

#plt.title("Students Marks")
#plt.xlabel('Roll Number')
#plt.ylabel('Marks')
#plt.yticks(y)
plt.ylim([0.0001,-0.0001])
plt.plot(x, y, marker = 'o', c = 'g')

plt.savefig("plots.pdf")  
