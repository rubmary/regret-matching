from matplotlib.pylab import *
file_a = open('regret_a.txt')
file_b = open('regret_b.txt')
file_c = open('regret_c.txt')
lines_a = file_a.readlines()
lines_b = file_b.readlines()
lines_c = file_c.readlines()
regret1_a = [float(lines_a[i].split()[0]) for i in range(len(lines_a))]
regret2_a = [float(lines_a[i].split()[1]) for i in range(len(lines_a))]
regret1_b = [float(lines_b[i].split()[0]) for i in range(len(lines_b))]
regret2_b = [float(lines_b[i].split()[1]) for i in range(len(lines_b))]
regret1_c = [float(lines_c[i].split()[0]) for i in range(len(lines_c))]
regret2_c = [float(lines_c[i].split()[1]) for i in range(len(lines_c))]

def make_plot(x):
	if (x == 'a'):
		plot(regret1_a)
		plot(regret2_a)
	elif (x == 'b'):
		plot(regret1_b)
		plot(regret2_b)
	else:
		plot(regret1_c)
		plot(regret2_c)