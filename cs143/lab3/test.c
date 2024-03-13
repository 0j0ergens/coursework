#include <criterion/criterion.h>
#include "lab3.h"

// streq is provided as a helper for tests below
int streq(char *s, char *t)
{
// by policy, NULLs are not equal to anything, even other NULLs
if (s==NULL || t==NULL) {
return 0;
}
unsigned int slen = len(s);
unsigned int tlen = len(t);
if (slen!=tlen) {
return 0;
}
for (int i=0; i<slen; i++) {
if (s[i]!=t[i]) {
return 0;
}
}
return 1;
}
// len tests...
Test(lab3, len0)
{
cr_assert(len("")==0);
}
// repeat_char tests...
Test(lab3, repeat_char0)
{
cr_assert(streq(repeat_char('x',0),""));
}
// count_char tests...
Test(lab3, count_char0)
{
cr_assert(count_char('a',"")==0);
}
// locations_of tests...
Test(lab3, locations_of0)
{
unsigned int n = 0;
unsigned int *locs = locations_of('x', "", &n);
cr_assert(n==0);
cr_assert(locs==NULL);
free(locs);
}
