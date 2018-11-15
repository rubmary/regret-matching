import matplotlib.pylab as plt
import sys

def make_plot(path_input, path_graph, proc):
	file = open(path_input)
	lines = file.readlines()
	file.close()
	regret1 = [float(lines[i].split()[0]) for i in range(len(lines))]
	regret2 = [float(lines[i].split()[1]) for i in range(len(lines))]
	plt.figure()
	plt.title('Procedimiento ' + proc)
	plt.xscale('log')
	plt.plot(regret1)
	plt.plot(regret2)
	plt.ylabel('Regret (max)')
	plt.xlabel('Iteraciones')
	plt.savefig(path_graph)

if __name__ == "__main__":
	name = sys.argv[1]
	path_input_list = list('../regret/'   + name + '/procedimiento- ')
	path_graph_list = list('../graficas/' + name + '/procedimiento- ')
	pos_input = len(path_input_list) - 1
	pos_graph = len(path_graph_list) - 1

	path_input_list = path_input_list + list('.txt')
	path_graph_list = path_graph_list + list('.png')
	procs = ['A', 'B', 'C']
	for i in procs:
		path_input_list[pos_input] = i
		path_graph_list[pos_graph] = i
		path_input = ''.join(path_input_list)
		path_graph = ''.join(path_graph_list)
		make_plot(path_input, path_graph, i)

