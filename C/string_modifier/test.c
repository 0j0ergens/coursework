#include <criterion/criterion.h>
#include "hw4.h"
// helper function(s) to assist in testing
int same_string_array(char **ss1, char **ss2, unsigned int len)
{
for (int i=0; i<len; i++)
if (strcmp(ss1[i],ss2[i]))
return 0;
return 1;
}
// tests
Test(hw4, splitAt_00)
{
unsigned int n = 0;
char **test = split_at('?', "/usr/bin/clang", &n);
char *arr[] = {"/usr/bin/clang"};
cr_assert(n==1 && same_string_array(test, arr, n));
}
Test(hw4, splitAt_01)
{
unsigned int n = 0;
char **test = split_at('/', "/usr/bin/clang", &n);
char *arr[] = {"","usr","bin","clang"};
cr_assert(n==4 && same_string_array(test, arr, n));
}
Test(hw4, splitAt_02)
{
unsigned int n = 0;
char **test = split_at('x', "AxBxCCCxD", &n);
char *arr[] = {"A","B","CCC","D"};
cr_assert(n==4 && same_string_array(test, arr, n));
}
Test(hw4, join_00)
{
char *ss[] = {"a"};
char *test = join('?',ss,1);
cr_assert(!strcmp(test,"a"));
}
Test(hw4, join_01)
{
char *ss[] = {"a","b","xyz"};
char *test = join('?',ss,3);
cr_assert(!strcmp(test,"a?b?xyz"));
}
Test(hw4, join)
{
  char *ss[] = {"a","b","xyz"};
  char *test = join('?',ss,3);
  cr_assert(!strcmp(test,"a?b?xyz"));
}

Test(hw4, sl_cons)
{
  slist *ss = sl_cons("abc",NULL);
  cr_assert(!strcmp(ss->s,"abc") && ss->next==NULL);
}

Test(hw4, sl_total_length)
{
  slist *ss = sl_cons("aa", sl_cons("bbb", NULL));
  cr_assert(sl_total_length(ss)==5);
}

Test(hw4, singletons)
{
slist *ss = singletons("abc");
cr_assert(!strcmp(ss->s,"a") && !strcmp(ss->next->s,"b"));
//&& !strcmp(ss->next->next->s,"c") && (ss->next->next->next==NULL));
}

Test(hw4, sl_contains)
{
  slist *ss = sl_cons("coffee", NULL);
  cr_assert(sl_contains("coffee",ss));
}


Test(hw4, sl_concat_all)
{
  slist *ss = sl_cons("to", sl_cons("get", sl_cons("her", NULL)));
  cr_assert(!strcmp(sl_concat_all(ss),"together"));
}

Test(hw4, sl_count)
{
  slist *ss = sl_cons("to", sl_cons("get", sl_cons("her", NULL)));
  cr_assert(sl_count('e',ss)==2 && sl_count('o',ss)==1 && sl_count('z',ss)==0);
}

Test(hw4, sl_reverse_in_place)
{
  slist *ss = sl_cons("abc",NULL);
  char *original_pointer = ss->s;
  sl_reverse_in_place(ss);
  cr_assert(!strcmp(ss->s,"cba") && ss->s==original_pointer);
}

Test(hw4, sl_reverse_new)
{
  slist *ss = sl_cons("abc",NULL);
  char *original_pointer = ss->s;
  ss = sl_reverse_new(ss);
  cr_assert(!strcmp(ss->s,"cba") && ss->s!=original_pointer);
}

Test(hw4, sl_from_array)
{
 char *arr[] = {"aaa","bbb"};
 slist *ss = sl_from_array(arr, 2);
 cr_assert(!strcmp(ss->s,"aaa") && !strcmp(ss->next->s,"bbb") && ss->next->next==NULL);
}
Test(hw4, sl_shallow_copy)
{
  slist *ss1 = sl_cons("A",sl_cons("B",sl_cons("C",NULL)));
  slist *ss2 = sl_shallow_copy(ss1);
  while (ss1!=NULL) {
    cr_assert(ss1!=ss2 && ss1->s==ss2->s);
    ss1 = ss1->next;
    ss2 = ss2->next;
  }
}

Test(hw4, sl_deep_copy)
{
  slist *ss1 = sl_cons("A",sl_cons("B",sl_cons("C",NULL)));
  slist *ss2 = sl_deep_copy(ss1);
  while (ss1!=NULL) {
    cr_assert(ss1!=ss2 && ss1->s!=ss2->s && !strcmp(ss1->s,ss2->s));
    ss1 = ss1->next;
    ss2 = ss2->next;
  }
}

Test(hw4, sl_free)
{
  slist *ss = sl_cons("A",sl_cons("B",sl_cons("C",NULL)));
  sl_free(ss);
  cr_assert(1);
}

Test(hw4, sl_shallow_free)
{
  slist *ss = sl_cons("A",sl_cons("B",sl_cons("C",NULL)));
  char *string1=ss->s, *string2=ss->next->s, *string3=ss->next->next->s;
  sl_shallow_free(ss);
  cr_assert(!strcmp(string1,"A") && !strcmp(string2,"B") && !strcmp(string3,"C"));
}







