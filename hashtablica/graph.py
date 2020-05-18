import matplotlib.pyplot as plt
import csv
import sys
file = sys.argv[1]

x = []

y = []

with open(file, 'r') as values:
    plots = csv.reader(values, delimiter=',')
    for row in plots:
        x.append(int(row[0]))
        y.append(int(row[1]))


plt.bar(x, y)

plt.savefig("graph\\" + file[: -4] + ".pdf", dpi = 300, bbox_inches = 'tight')



