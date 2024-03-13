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


class MinHeap:
    @staticmethod
    def parent_index(i):
        """
        Finds the parent index of a node

        Parameters: 
            i | int: index of current node 
        Returns: 
            int: index of parent node 
        """
        if i == 0:
            return None
        return (i - 1) // 2

    @staticmethod
    def left_child_index(i):
        """
        Finds the left child index of a node

        Parameters: 
            i | int: index of current node 
        Returns: 
            int: index of left child  
        """
        return 2 * i + 1

    @staticmethod
    def right_child_index(i):
        """
        Finds the right child index of a node

        Parameters: 
            i: int: index of current node 
        Returns: 
            int: index of right child  
        """
        return 2 * i + 2

    def __init__(self, max_capacity=999):
        self.data = [None] * max_capacity
        self.next = 0
        self.index_of_item = {} 
        """
        Constructor 
        Parameters: 
            max_capacity: int: maximum number of nodes in minheap 
        """

    def size(self):
        """
        Finds size of heap

        Returns: int: Size of heap
        """
        return self.next

    def height(self):
        return math.floor(math.log(self.next, 2)) + 1

    def is_empty(self):
        """
        Finds whether heap is empty

        Return: boolean: True if heap is empty. False if not. 
        """
        return self.next == 0

    def reset(self):
        self.next = 0

    def min(self):
        """
        Returns the minimum value of a heap

        Returns: tuple: tuple of minimum priority and corresponding item 
        """
        if self.is_empty():
            return None
        return self.data[0]

    def _swap(self, p, q):
        """
        Swaps nodes in minheap 

        Parameters:
            p: int: index of current node
            q: int: index of parent of current node
        
        Returns: nothing
        """
        assert p < self.next and q < self.next
        tmp = self.data[p]
        idx = self.index_of_item[tmp[1]]
        p_idx = self.index_of_item[self.data[q][1]]
        self.data[p] = self.data[q]
        self.index_of_item[tmp[1]] = p_idx
        self.index_of_item[self.data[q][1]] = idx
        self.data[q] = tmp

    def _sift_up(self, pos):
        """
        Moves a node up until it is in the correct placement within heap

        Parameters:
            pos: int: index of current node 

        Returns: nothing
        """
        self.index_of_item[self.data[pos][1]] = pos
        if pos == 0:
            return
        pi = MinHeap.parent_index(pos)
        if self.data[pos][0] < self.data[pi][0]:
            self._swap(pos, pi)
            self._sift_up(pi)

    def _sift_down(self, pos):
        """
        Sifts node down through heap

        Parameters:
            pos: int: index of current node
        
        Returns: nothing
        """
        curr = self.data[pos]
        li = MinHeap.left_child_index(pos)
        ri = MinHeap.right_child_index(pos)
        self.index_of_item[curr[1]] = pos

        if li >= self.next:
            return
        if li < self.next and ri >= self.next:
            lc = self.data[li]
            m = min(curr, lc)
            if lc == m: 
                self._swap(pos, li)
                self._sift_down(li)
        else:
            (lc, rc) = (self.data[li], self.data[ri])
            m = min([curr, lc, rc])
            if rc == m:
                self._swap(pos, ri)
                self._sift_down(ri)
            elif lc == m:
                self._swap(pos, li)
                self._sift_down(li)

    def remove_min(self):
        """
        Removes the minimum value of  the heap 

        Returns: 
            min_item: tuple: tuple of minimum priority and corresponding item
        """

        min_item = self.data[0]
        self.index_of_item.pop(min_item[1])

        if self.is_empty():
            return None
        if self.next > 0:
            self.data[0] = self.data[self.next - 1]
            self.next -= 1
            self._sift_down(0)
        if self.is_empty(): 
            self.index_of_item = {}
    
        return min_item

    def insert(self, priority, item):
        """
        Inserts an item into the heap based on its priority

        Parameters:
            priority: int: priority
            item: str or Vertex: node's key (can be string or Vertex object 
            depending on task)
        """
        self.data[self.next] = (priority, item)
        self.next += 1
        self._sift_up(self.next -   1)

    def _verify(self, pos):
        """
        Checks if nodes are in the correct order in heap 
        (not larger than children)

        Parameters:
            pos: int: node's index
        
        Returns:
            boolean
        """

        if pos >= self.next:
            return True
        curr = self.data[pos]
        li = MinHeap.left_child_index(pos)
        ri = MinHeap.right_child_index(pos)
        if ri < self.next:
            return (
                curr <= self.data[ri]
                and curr <= self.data[li]
                and self._verify(ri)
                and self._verify(li)
            )
        if li < self.next:
            return curr <= self.data[li] and self._verify(li)
        return True

    def verify(self):

        return self._verify(0)

    def show(self):
        """
        Creates string representation of heap

        Returns: nothing
        """
        if self.is_empty():
            print("[empty]")
            return
        linebreak = 1
        row_count = 0
        for i in range(self.next):
            print(self.data[i], end=" ")
            row_count += 1
            if row_count == linebreak or i == self.next - 1:
                print()
                linebreak *= 2
                row_count = 0
    
    def change_priority(self, item, new_priority):
        """
        Changes the priority of an item in the heap and modifies item's 
        position in heap based on new_priority if needed. 

        Parameters:
            item: str or Vertex: node's key (can be string or Vertex object 
            depending on task)
            new_priority: int: new priority 
        
        Returns: nothing
        """
        if item not in self.index_of_item:
            raise ValueError("item does not exist")
        idx = self.index_of_item[item]
        prior = self.data[idx][0]
        self.data[idx] = (new_priority, item)
        if new_priority > prior: 
            self._sift_down(idx)
        else: 
            self._sift_up(idx)

