# This class represent a graph

class Graph:
    # Initialize the class
    def __init__(self, graph_dict=None, directed=True):
        self.graph_dict = graph_dict or {}
        self.directed = directed
        if not directed:
            self.make_undirected()

    # Create an undirected graph by adding symmetric edges
    def make_undirected(self):
        for a in list(self.graph_dict.keys()):
            for (b, dist) in self.graph_dict[a].items():
                self.graph_dict.setdefault(b, {})[a] = dist

    # Add a link from A and B of given distance, and also add the inverse link if the graph is undirected
    def connect(self, A, B, distance=1):
        self.graph_dict.setdefault(A, {})[B] = distance
        if not self.directed:
            self.graph_dict.setdefault(B, {})[A] = distance

    # Get neighbors or a neighbor
    def get(self, a, b=None):
        links = self.graph_dict.setdefault(a, {})
        if b is None:
            return links
        else:
            return links.get(b)

    # Return a list of nodes in the graph
    def nodes(self):
        s1 = set([k for k in self.graph_dict.keys()])
        s2 = set([k2 for v in self.graph_dict.values() for k2, v2 in v.items()])
        nodes = s1.union(s2)
        return list(nodes)


# This class represent a node
class Node:

    # Initialize the class
    def __init__(self, name, parent):
        self.name = name
        self.parent = parent
        self.g = 0  # Distance to start node
        self.h = 0  # Distance to goal node
        self.f = 0  # Total cost

    # Compare nodes
    def __eq__(self, other):
        return self.name == other.name

    # Sort nodes
    def __lt__(self, other):
        return self.f < other.f

    # Print node
    def __repr__(self):
        return ('({0},{1})'.format(self.name, self.f))


# A* search

def A_Star(graph, heuristics, start, end):
    open=[]
    closed=[]
    start_node= Node(start,None)
    goal_node= Node(end,None)
    open.append(start_node)
    # Loop until the open list is empty
    while len(open)>0:
        open.sort()  # sorts on ascending (largest to smallest)
        current=open.pop(0)  # gives last element that is smallest valued node
        print("Current node is ", current.name, " .It has been added to closed list")
        closed.append(current)  # adds it to closed (already considered) list
    # Check if we have reached the goal, return the path (From Current Node to Start Node By Node.parent)
        if current == goal_node:
            print("Current node was goal node")
            path = []
            print("path is:")
            while current != start_node:
                path.append(current.name)
                current = current.parent
    # Return reversed path (Hint: Return list of path in this Fashion for Reverse return path[::-1])
            path.append(current.name)
            return path[::-1]
    # Get neighbours
        neighbors = graph.get(current.name)
    # Loop neighbors
        for key, value in neighbors.items():
        # Create a neighbor node
            neighbor=Node(key,current)
            print("current neighbour is ", neighbor.name)

        # Check if the neighbor is in the closed list
            if (neighbor in closed):
                print("neighbour was in closed list so checking next neighbour")
                continue
        # Calculate cost to goal
            neighbor.g = current.g + value
        # Check if neighbor is in open list and if it has a lower f value
            if (In_Open(open, neighbor) == True):
                print("neighbor does not exsist in open list or neighbours's new weight from this parent is less than last calculated weight from some other parent")
                pass
            # Everything is green, add neighbor to open list
            print("neighbour added to open list")
            neighbor.h = heuristics.get(neighbor.name)
            neighbor.f = neighbor.g + neighbor.h
            open.append(neighbor)
# Return None, no path is found

# Check if a neighbor should be added to open list
def In_Open(open, neighbor):
    for node in open:
        print("checking open list.Current node ", node.name)
        if (neighbor == node and neighbor.f >= node.f):
            return False
    return True

# The main entry point for this module
def main():
    # Create a graph
    graph = Graph()

    # Create graph connections (Actual distance)
    graph.connect('Arad', 'Zerind', 75)
    graph.connect('Arad', 'Sibiiu', 140)
    graph.connect('Arad', 'Timisoara', 116)
    # Add Remaining Links From Example Given in Sides (Romania Map)
    graph.connect('Fugaras', 'Bucharest', 211)
    graph.connect('Fugaras', 'Zerind', 66)
    graph.connect('Pitesti', 'Bucharest', 101)
    graph.connect('Giurgiu', 'Bucharest', 90)
    graph.connect('Zerind', 'Timisoara', 86)

    print(graph.get('Arad', 'Zerind'))

    # Make graph undirected, create symmetric connections
    graph.make_undirected()

    # Create heuristics (straight-line distance, air-travel distance) for Destination Bucharest
    heuristics = {}     #here all heuristic values are calculated according to Bucharest
    heuristics['Bucharest'] = 0
    heuristics['Arad'] = 316
    heuristics['Pitesti'] = 266
    heuristics['Giurgiu'] = 125
    heuristics['Zerind'] = 399
    heuristics['Fugaras'] = 324
    heuristics['Sibiiu'] = 387
    heuristics['Timisoara'] = 357


    # Print Graph Nodes
    print(graph.nodes())
    print('\n')

    # Run search algorithm
    path = A_Star(graph, heuristics, 'Arad', 'Bucharest')
    print('Paths')
    print(path)


# Tell python to run main method
if __name__ == "__main__": main()


import codecs


def main():
  with codecs.open('Amna_Ilyas.txt', 'r', encoding='utf-8',
                 errors='ignore') as fdata:
    print(fdata)

# Tell python to run main method
if __name__ == "__main__": main()