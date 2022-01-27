import matplotlib.pyplot as plt
from sys import argv
x = []
y = []
for line in open(argv[1], 'r'):
    lines = [i for i in line.split()]
    x.append(lines[0])
    y.append(float(lines[1]))


plt.ylabel(r'$\frac{\alpha}{\alpha_{nominal}}$', fontsize=20)

if("ttbar1" in argv[1]):
    plt.xlabel(r'$\Delta|y| < 0$')
if("ttbar2" in argv[1]):
    plt.xlabel(r'$\Delta|y| > 0$')
plt.ylim([0.75,1.25])
plt.plot(x, y, marker = 'o', c = 'g')
plt.axvline(x=99.5)
plt.axvline(x=105.5)
plt.axvline(x=109.5)
plt.text(35, 1.2, 'PDF || q2 || FSR/ISR || hdamp', horizontalalignment='center',verticalalignment='center',fontsize=16, color='red')
#plt.text(101, 1.2, 'q2', horizontalalignment='center',verticalalignment='center',fontsize=16, color='red')
#plt.text(106, 1.2, 'FSR/ISR', horizontalalignment='center',verticalalignment='center',fontsize=16, color='red')
#plt.text(111, 1.2, 'hdamp', horizontalalignment='center',verticalalignment='center',fontsize=16, color='red')
plt.savefig("plots.pdf")  
