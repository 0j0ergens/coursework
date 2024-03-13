"""
CMSC 14200, Winter 2023
Homework #3

People Consulted:
   List anyone (other than the course staff) that you consulted about
   this assignment.

Online resources consulted:
   List the URLs of any online resources other than the course text and
   the official Python language documentation that you used to complete
   this assignment.
"""

import math
import graph
import minheap
from util import haversine


def build_path(gr, start, end):
    """
    Returns the path between the specified vertices in the graph

    Parameters:
        gr : Graph
        start : Vertex : the starting vertex
        end   : Vertex : the final destination

    Returns: list[str] : the shortest path identified between these vertices
    """
    lst = []
    n = end
    while n != start: 
        lst.append(n.predecessor.name)
        n = n.predecessor
    lst.reverse()
    lst.append(end.name)
    return lst


def a_star(gr, start, end):
    """
    Finds a shortest path between the specified vertices in the graph
    using A* Search

    Parameters:
        gr : Graph
        start : Vertex : the starting vertex
        end   : Vertex : the final destination

    Returns: tuple[float, list[str], set[Vertex]] or None : None if no path
        exists, otherwise, a tuple of shortest path distance, the vertices
        along the path, and the set of vertices visited during the computation
    """

    openset = minheap.MinHeap() 
    closedset = set() 
    start.h_cost = haversine(start.lat, start.long, end.lat, end.long)
    start.g_cost = 0 
    start.f_cost = start.g_cost + start.h_cost
    openset.insert(start.f_cost, start)
    
    while not openset.is_empty(): 
        curr = openset.remove_min()[1]
        closedset.add(curr)

        if curr == end: 
            path = build_path(gr, start, end)
            return(end.g_cost, path, closedset)

        for item, v in curr.edges_to.items():
            vert = v[0]
            dist = v[1]
          
            if vert not in closedset:
                hcst = haversine(vert.lat, vert.long, end.lat, end.long)
                gcst = curr.g_cost + dist
                fcst = hcst + gcst
             
                if fcst < vert.f_cost:
                    vert.predecessor = curr  
                    if vert.f_cost == math.inf: 
                        vert.f_cost = fcst
                        vert.g_cost = gcst
                        vert.h_cost = hcst
                        openset.insert(vert.f_cost, vert)
                    else:    
                        vert.f_cost = fcst
                        vert.g_cost = gcst
                        vert.h_cost = hcst
                        openset.change_priority(vert, vert.f_cost)  
                    vert.predecessor = curr

    
         
        

    

    

        
        

            




  
 
       

  



   
