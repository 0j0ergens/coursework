// hw4.h, CMSC 14300, Spring 2023
// data definitions
struct string_list {
char *s;
struct string_list *next;
};
typedef struct string_list slist;
// === practice with string arrays
char **split_at(char sep, char *string, unsigned int *len);
// consume a string, split the string at every "sep"
// the result is an array of strings, with len pointing to its length
// len is an "out parameter"
// ex: split_at(','."a,b,c",p) --> produces ["a","b","c"], *p is 3
// ex: split_at(','."a,b,",p) --> produces ["a","b,""], *p is 3
// ex: split_at(',',"a,b$c",p) --> produces ["a","b$c"], *p is 2
// ex: split_at('$',"a,b$c",p) --> produces ["a,b","c"], *p is 2
// ex: split_at('$',"a,b,c",p) --> produces ["a,b,c"], *p is 1
char *join(char j, char **strings, unsigned int len);
// consume an array of strings, join with j
// len is the length of the string array (trusted to be correct)
// produce a fresh heap-allocated string
// ex: join(':',["a","b","c"],3) --> "a:b:c"
// ex: join(':',["aa","bcd"],2) --> "aa:bcd"
// === practice with string lists
slist *sl_cons(char *s, slist *strings);
// cons operator for string lists
// allocate a new list node, duplicate the string s,
// point to the duplicated string from new list node
// ex: sl_cons("a", "b"->"c") --> "a"->"b"->"c"
unsigned int sl_total_length(slist *strings);
// compute the total length of all strings in the list
// ex: total_length("a"->"bcd"->"z") --> 5
slist *singletons(char *s);
// given a string, produce the list with a length-one string
// for each character
// ex: singletons("ABCD") -> "A"->"B"->"C"->"D" (new list)
int sl_contains(char *s, slist *strings);
// return true if s appears in the list, false otherwise
// ex: contains("a","b"->"a"->"t") --> true
// ex: contains("x","b"->"a"->"t") --> false
// ex: contains("Chicago","Denver"->"Atlanta") --> false
// ex: contains("Denver","Denver"->"Atlanta") --> true
char *sl_concat_all(slist *strings);
// produce a new string that is the concatenation of all strings in list
// the result must be a fresh heap-allocated string
// ex: concat_all("a"->"bc"->"xy"->"z") --> "abcxyz"
unsigned int sl_count(char c, slist *strings);
// count the occurrences of c in all strings in list
// ex: count('x',"abx"->"xxy"->"yyz") --> 3
// ex: count('a',"abx"->"xxy"->"yyz") --> 1
// ex: count('w',"abx"->"xxy"->"yyz") --> 0
void sl_reverse_in_place(slist *strings);
// reverse all strings in list without any new allocation
// ex: given "abc"->"xyz", list should be changed to be
// "cba"->zyx", no return value
// note: the order of the list is intact, just the strings are reversed
slist *sl_reverse_new(slist *strings);
// this is like reverse_in_place, but produces an entirely new list, with new
//strings
// ex: "hello"->"and"->"goodbye" --> "olleh"->"dna"->"eybdoog" (whole new list)
slist *sl_from_array(char **strings, unsigned int len);
// given an array of strings, produce a corresponding linked list
// all strings should be duplicated, so the resulting structure is all new
// ex: sl_from_array(["a","b","x"],3) --> "a"->"b"->"x"
slist *sl_shallow_copy(slist *strings);
// copy all list nodes, but point to the very same strings in original list
// the resulting structure should be new list nodes, but the same strings
slist *sl_deep_copy(slist *strings);
// copy all list nodes and all strings pointed to
// the resulting structure, nodes and strings, should be all new allocations
void sl_free(slist *strings);
// free the string list as well as all strings pointed to
// (this is a "deep free")
void sl_shallow_free(slist *strings);
// free the string list nodes but do not free the strings pointed to
// (this is a "shallow free")

