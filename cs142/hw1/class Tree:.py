class Tree:
    
    def __init__(self, k, v=None):        
        self.key = k
        self.value = v 
        
        self.children = []
        
    def add_child(self, other_tree):
        if not isinstance(other_tree, Tree):
            raise ValueError("Parameter to add_child must be a Tree object")
        
        self.children.append(other_tree)

    def num_children(self):
        return len(self.children)
    
    def height(self):
        if self.num_children() == 0:
            return 1
        else:
            st_heights = [st.height() for st in self.children]
            return 1 + max(st_heights)


t = Tree("R")
t1 = Tree("1")
t2 = Tree("2")
t.add_child(t2)
t.add_child(t1)
t11 = Tree("1.1")
t12 = Tree("1.2")
t13 = Tree("1.3")
t1.add_child(t11)
t1.add_child(t12)
t1.add_child(t13)
t121 = Tree("1.2.1")
t122 = Tree("1.2.2")
t12.add_child(t121)
t12.add_child(t122)

