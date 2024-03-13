import math
import heapq
from util import haversine

class Vertex:
    """
    Class for representing a vertex in a weighted, directed graph
    with geographic locations and supporting the attributes needed for A* Search
    """

    def __init__(self, name, lat, long):
        """
        Constructor

        Parameters:
            name : str : airport code for the vertex
            lat  : float : latitude of the airport
            long : float : longitude of the airport
        """
        self.name = name
        self.lat = lat
        self.long = long
        self.edges_to = {}
        self.f_cost = math.inf
        self.g_cost = math.inf
        self.h_cost = None
        self.predecessor = None
    
    
    def add_edge_to(self, dest):
        """
        Adds edge from and to this vertex and another

        Parameters:
            dest : Vertex : vertex to which to add an edge
            
        Returns: nothing
        """
        distance = haversine(self.lat, self.long, dest.lat, dest.long)
        self.edges_to[dest.name] = (dest, distance)
        
    def __str__(self):
        """
        Produce a string representation of a Vertex with the name, f-, g-, and
        h-costs, and list of neighbors and their distances

        Parameters: none beyond self
            
        Returns: str
        """
        rv = f"Vertex {self.name}: (f={self.f_cost}, g={self.g_cost}, " + \
             f"h={self.h_cost})"
        neighbors = ", ".join(sorted([f"({v.name}, {dist})" for v, dist in
            self.edges_to.values()]))
        return rv + " edges: " + neighbors
            
            
class Graph:
    """
    Class for representing an entire weighted, directed graph
    """

    def __init__(self, filename=None, nclosest=None):
        """
        Constructor

        Parameters:
            filename : None or str : a CSV file with airports and locations
            nclosest : float : make edges with this many closest airports
        """
        self.vertices = {}
        print("VERTICES", self.vertices)
        
        if filename:
            with open(filename) as f:
                for line in f:
                    iata, _, lat, long = line.strip().split(",")
                    v = Vertex(iata, float(lat), float(long))
                    self.add_vertex(v)
                    
            if nclosest:
                for v in self.vertices:
                    ovs = [v2 for v2 in self.vertices.keys() if v != v2]
                    h = []
                    v = self.get_vertex(v)
                    for ov in ovs:
                        ov = self.get_vertex(ov)
                        h.append((haversine(v.lat, v.long, ov.lat, ov.long), ov))
                    heapq.heapify(h)
                    for _, ov in heapq.nsmallest(nclosest, h):
                        v.add_edge_to(ov)
                        ov.add_edge_to(v)

    
    def add_vertex(self, vertex):
        """
        Adds vertex to graph

        Parameters:
            vertex : Vertex : vertex to be added
            
        Returns: nothing
        """
        self.vertices[vertex.name] = vertex
        
    def get_vertex(self, name):
        """
        Looks up vertex in graph

        Parameters:
            name : str : name of sought vertex
            
        Returns: Vertex or None (if not found)
        """
        return self.vertices.get(name)
