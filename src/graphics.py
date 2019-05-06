import matplotlib.pylab as plt
import sys
MAX_VAL = 2e7

def make_plot(path_input, path_graph, proc, name):
    file = open(path_input)
    i = 0
    regret1 = []
    regret2 = []
    while i < MAX_VAL:
        line = file.readline()
        if not line:
            break
        regret1.append(float(line.split()[0]))
        regret2.append(float(line.split()[1]))
        i = i+1
    file.close()
    plt.figure()
    plt.title('Procedimiento ' + proc + ': ' + name)
    plt.xscale('log')
    plt.plot(regret1, label='Jugador 1')
    plt.plot(regret2, label='Jugador 2')
    plt.ylabel('Regret (max)')
    plt.xlabel('Iteraciones')
    plt.legend()
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
    names = [   'Regret condicional',
                'Vector invariante de probabilidad',
                'Regret incondicional']
    for i in range(3):
        path_input_list[pos_input] = procs[i]
        path_graph_list[pos_graph] = procs[i]
        path_input = ''.join(path_input_list)
        path_graph = ''.join(path_graph_list)
        make_plot(path_input, path_graph, procs[i], names[i])

