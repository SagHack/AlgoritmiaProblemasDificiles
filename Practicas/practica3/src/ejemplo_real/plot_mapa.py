import matplotlib.pyplot as plt

def read_nodes(input_file):
    with open(input_file, 'r') as f:
        lines = f.readlines()
        
    node_numbers = []
    x_coordinates = []
    y_coordinates = []

    for line in lines[1:]: 
        node, x, y, _ = line.strip().split()
        node_numbers.append(int(node))
        x_coordinates.append(float(x))
        y_coordinates.append(float(y))

    return node_numbers, x_coordinates, y_coordinates

def read_edges(edge_file):
    with open(edge_file, 'r') as f:
        lines = f.readlines()

 
    node_mapping = {}

    for line in lines[1:]:  
        # Información de las aristas
        new_node, original_node = map(int, line.strip().split())
        node_mapping[new_node] = original_node

    return node_mapping

def plot_nodes_and_edges(node_file, edge_file):
    node_numbers, x_coordinates, y_coordinates = read_nodes(node_file)
    node_mapping = read_edges(edge_file)

   
    plt.scatter(x_coordinates, y_coordinates, marker='o', label='Nodes', color='blue')

    
    for new_node, original_node in node_mapping.items():
        if new_node in node_numbers and original_node in node_numbers:
            x1, y1 = x_coordinates[node_numbers.index(new_node)], y_coordinates[node_numbers.index(new_node)]
            x2, y2 = x_coordinates[node_numbers.index(original_node)], y_coordinates[node_numbers.index(original_node)]
            plt.plot([x1, x2], [y1, y2], color='black', linestyle='--', linewidth=0.5)

    # Nodos que queremos que se muestren de otro color, los almacenes y donde vivo
    labeled_nodes = [5, 70, 202]
    for node in labeled_nodes:
        if node in node_numbers:
            i = node_numbers.index(node)
            plt.scatter(x_coordinates[i], y_coordinates[i], marker='o', label=f'Node {node}', color='red')
            plt.annotate(node, (x_coordinates[i], y_coordinates[i]), textcoords="offset points", ha='center', va='center', xytext=(0, 0), fontsize=8)

    plt.title('Node-Edge Map')
    plt.xlabel('X Coordinate')
    plt.ylabel('Y Coordinate')
    plt.grid(True)
    plt.show()

if __name__ == "__main__":
    node_file_path = "posicion_nodos.txt" 
    edge_file_path = "indice_nodos.txt"  

    plot_nodes_and_edges(node_file_path, edge_file_path)
