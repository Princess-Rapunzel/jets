import matplotlib.pyplot as plt
import numpy as np

def plot_mesh(_nodes, _elems,_plot_nodes=False, _linewidth=.2):

    print('num of nodes:', len(_nodes), 'num of elements:', len(_elems))
    fig, ax = plt.subplots()
    
    if _plot_nodes:
        for _node in _nodes:
            x, y = _node()
            ax.plot(x, y, 'bo') 
            ax.text(x, y, f'{_node.id()}', fontsize=12, ha='right')
    
    for _elem in _elems:
        polygon = np.array([_nodes[i]() for i in _elem.get_nodes_id()])
        ax.plot(*zip(*polygon, polygon[0]), 'k-', linewidth=_linewidth)
    
    ax.set_aspect('equal')
    plt.xlabel('X')
    plt.ylabel('Y')
    plt.title('Mesh Plot')
    plt.show()