import matplotlib.pylab as plt
import sys

MAX_VAL = 2e7

BIGGER_SIZE = 20
FONT_SIZE = 15
SMALL_SIZE = 12

def make_plot(path_input, path_graph, proc, name, x_val):
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

    if x_val == -1:
        x_val = i
 
    plt.rc('font', size=BIGGER_SIZE, family='serif')
    plt.figure()
    plt.title(proc + ': ' + name)
    plt.xlim(1, x_val)
    plt.xscale('log')
    plt.plot(regret1, label='Jugador 1')
    plt.plot(regret2, label='Jugador 2')
    if (proc == 'A'):
        plt.ylabel('Regret (max)')
    plt.xlabel('Iteraciones')
    plt.legend()
    plt.subplots_adjust(bottom=0.15, left=0.15, right=0.85)
    plt.savefig(path_graph)

    return x_val

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

    x_val = -1
    for i in range(3):
        path_input_list[pos_input] = procs[i]
        path_graph_list[pos_graph] = procs[i]
        path_input = ''.join(path_input_list)
        path_graph = ''.join(path_graph_list)
        x_val = make_plot(path_input, path_graph, procs[i], names[i], x_val)
