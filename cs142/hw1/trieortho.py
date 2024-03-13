"""
CMSC 14200: trie-based spell-checker and tab-completer Distribution

Adam Shaw
Winter 2023

Olivia Joergens
"""
from listortho import ListOrthographer

<<<<<<< HEAD
#py.test -vx -k insert test_hw1_trie.py
=======
#py.test -vx -k num_words test_hw1_trie.py
>>>>>>> 2ae83d47b072c33ba6215ca2c2d8b3a9985727d9
class Trie:
    """
    Class for representing tries
    """

    def __init__(self, root):
        '''
        Constructor

        Parameters:
         root : str (a character, but Python does not have a "char" type)

        Initialize root to given char, empty dict of children, final to False.
        '''
        self.root = root
        self.children = {}
        self.final = False
        self.fcount = 0 
        self.compcount = 0 
       
    def insert(self, word):
        '''
        Insert the word into the trie.

        Parameters:
	     word : str

        Returns: (does not return a value)
        '''
<<<<<<< HEAD
        children = self.children
        children[self.root] = {}
        current = children[self.root]
        print(current)
    
        
        for letter in word[1:]: 
            if letter not in current:
                current[letter] = {}
                current = current[letter]
            #updating to value associated with current letter 
        print(children)
           

        
            
     
                

#, i in enumerate(word)#
        
        """
        if the letter isn't in that node, then you add it. 
        you do not need to modify the word itself. 
        each letter is checked against keys each time. 
        if it is not already there, add the letter at the key. then start over. 


        
        """
            




        # current = self.root 
        # children = self.children

        # for letter in word: 
        #     print(letter)
        #     if letter not in current: 
        #         children[letter] = {}
        #         print(current)
        #     current = current.children[letter]
        # self.final = True 

        # print(current)
            
    

=======
        #py.test -vx -k insert test_hw1_trie.py

        
        current_node = self
        for c in word: 
            if(current_node.children.get(c)==None):
                next_node = Trie(c)
            else:
                next_node = current_node.children[c]
            current_node.children[c] = next_node
            current_node = next_node
        if not next_node.final:
            self.fcount+=1
            next_node.final = True
       
        
>>>>>>> 2ae83d47b072c33ba6215ca2c2d8b3a9985727d9
    def contains(self, word):
        '''
        Check presence of given word in the trie.

        Parameters:
         word : str

        Returns: boolean
        ''' 
       
        current_node = self
        for c in word:
            if(current_node.children.get(c)==None):
                return False
            current_node = current_node.children[c]
        return True

    def all_wordRecurse(self, node, word, word_list):
        if(node.final):
            word_list.append(word)
        for child in node.children:
            self.all_wordRecurse(node.children[child],word+child,word_list)     
        return word_list

    def all_words(self):
        '''
        Return all the words in the trie. Returned list not guaranteed
        in any particular order.

        Parameters:
         none

        Returns: list[str]
        '''
        return self.all_wordRecurse(self,'',[])

    def num_words(self):
        '''
        Return the number of words in the trie.

        Parameters:
          none

        Returns: int
        '''
        return self.fcount


    #py.test -vx -k completions test_hw1_trie.py
  
    def completions(self, prefix):
        '''
        Return all completions given prefix. The returned list is not
        guaranteed to be in any particular order.

        Parameters:
          prefix : str

        Returns: list[str]
        '''
        
        words = self._compl(prefix, "")
        return words

    def _compl(self, prefix, acc):
        '''
        Private method. Return all completions given prefix. The
        variable acc stores the string seen thus far in traversal of
        the trie. The returned list is not guaranteed to be in any
        particular order.

        Parameters:
          prefix : str
          acc : str

        Returns: list[str]
        '''
        current = self
        for char in prefix:
            if(current.children.get(char)==None):
                return []
            else:
                current = current.children[char]
        return self.all_wordRecurse(current, prefix, [])

    def num_completions(self, prefix):
        '''
        Return the number of completions of the given prefix.

        Parameters:
          prefix : str

        Returns: int
        '''
        return len()
        
class TrieOrthographer:
    """
    Class for a trie-based orthographer
    """

    def __init__(self):
        '''
        Constructor

        Parameters:
          none

        Initialize dictionary of empty tries, one per letter.
        '''
        self.tries = {}
        for char in 'abcdefghijklmnopqrstuvwxyz':
            self.tries[char] = Trie(char)

    def insert(self, word):
        '''
        Insert the word into the orthographer if it consists only of lowercase
        letters.

        Parameters:
          word : str

        Returns: (does not return a value)
        '''
        char = word[0]
        if word.islower() and word.isalpha():  
            current_node = self.tries[char]
            current_node.insert(word)
        
    def insert_from_file(self, filename):
        '''
        Read the named file, insert words (one per line in file).

        Parameters:
          filename : str

        Returns: (does not return a value)
        '''
        with open (filename) as f: 
            file = f.read()
            word = file.split()
            for n in word:
                self.insert(n)

    def contains(self, word):
        '''
        Check presence of given word in the orthographer.

        Parameters:
          word : str

        Returns: boolean
        '''
        char = word[0]
        return Trie.contains(self.tries[char], word)

    def completions(self, prefix):
        '''
        Return all completions given prefix. The returned list is not
        guaranteed to be in any particular order.

        Parameters:
          prefix : str

        Returns: list[str]
        '''
        char = prefix[0]
        return Trie.completions(self.tries[char], prefix)

    def num_completions(self, prefix):
        '''
        Return the number of completions given prefix.

        Parameters:
          prefix : str

        Returns: int
        '''
        raise NotImplementedError("todo: TrieOrthographer.num_completions")


    def all_words(self):
        '''
        Return all the words in the orthographer. Returned list not
        guaranteed in any particular order.

        Parameters:
          none

        Returns: list[str]
        '''
    
        lst = []
        for char in self.tries:
            if Trie.all_words(self.tries[char]) != []:  
                for word in Trie.all_words(self.tries[char]): 
                    lst.append(word)
        return(lst)
            

    def num_words(self):
        '''
        Return the number of words in the orthographer.

        Parameters:
          none

        Returns: int
        '''
        raise NotImplementedError("todo: TrieOrthographer.num_words")

