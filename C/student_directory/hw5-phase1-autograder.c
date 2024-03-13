#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include "hw5.h"
// These tests only check that the given functions exist and don't
// crash on simple inputs. They do not check correctness.
// ^ Ignore this. The added tests check correctness. (No guarantees though)
// Also note that, as written, allocated memory is not freed in these
// tests. You should be aware of that in case you run this code under
// valgrind.
// ^ Don't ignore this.

Test(hw5, student_new00) { // test 1
  student *s = student_new(123,"samli23",567,"Li","Sam");
  cr_assert(1);
}

// check that all attributes are correct and strings are heap allocated
Test(hw5, student_new01) { //test 2
  char *lname = "bruh";
  char *fname = (char *) malloc(4);
  fname[0] = 'm';
  fname[1] = 'a';
  fname[2] = 'n';
  fname[3] = '\0';

  student *s = student_new(456, "manbruh99", 789, lname, fname);

  // test uint32_t attributes
  cr_assert(s -> ucid == 456);
  cr_assert(s -> ssn == 789);

  // test string attributes
  lname = "";
  free(fname);
  
  cr_assert(!strcmp(s -> cnet, "manbruh99"));
  cr_assert(!strcmp(s -> lname, "bruh"));
  cr_assert(!strcmp(s -> fname, "man"));
}

Test(hw5, student_free00) { // test 3
  student *s = student_new(123,"samli23",567,"Li","Sam");
  student_free(s);
  cr_assert(1);
}

Test(hw5, ui_singleton00) { // test 4
  student *s = student_new(123,"samli23",567,"Li","Sam");
  uint32_idx *ui = ui_singleton(123,s);
  cr_assert(1);
}

// check value accuracy
Test(hw5, ui_singleton01) { // test 5
  student *s = student_new(456, "cvelaryon", 789, "Velaryon", "Corlys");
  uint32_idx *ui = ui_singleton(456, s);

  cr_assert(ui -> key == 456);
  cr_assert(ui -> stu -> ucid == 456);
  cr_assert(ui -> stu -> ssn == 789);
  cr_assert(!strcmp(ui -> stu -> cnet, "cvelaryon"));
  cr_assert(ui -> stu == s);
  cr_assert(ui -> left == NULL);
  cr_assert(ui -> right == NULL);
}

// check that student isn't duplicated
Test(hw5, ui_singleton02) { // test 6
  student *s = student_new(456, "cvelaryon", 789, "Velaryon", "Corlys");
  uint32_idx *ui = ui_singleton(456, s);
  cr_assert(ui -> stu == s);
  cr_assert(&(ui -> stu) != &s);
}

Test(hw5, ui_insert00) { // test 7
  student *s = student_new(123,"samli23",567,"Li","Sam");
  uint32_idx *ui = ui_singleton(123, s);
  student *t = student_new(999,"edwu",888,"Wu","Ed");
  ui_insert(ui, 999, t);
  cr_assert(1);
}

// check that invalid keys don't insert
Test(hw5, ui_insert01) { // test 8
  student *s = student_new(111, "jpinkman", 111111, "Pinkman", "Jesse");
  uint32_idx *ui = ui_singleton(111111, s);
  student *t = student_new(222, "wwhite", 222222, "White", "Walter");
  ui_insert(ui, 202020, t);
  cr_assert(ui -> left == NULL && ui -> right == NULL);
}

// check that duplicates don't insert
Test(hw5, ui_insert03) { // test 10
  student *s = student_new(111, "jpinkman", 111111, "Pinkman", "Jesse");
  uint32_idx *ui = ui_singleton(111111, s);
  student *t = student_new(111, "jpinkman", 111111, "Pinkman", "Jesse");
  ui_insert(ui, 111111, s);
  ui_insert(ui, 111111, t);
  cr_assert(ui -> left == NULL && ui -> right == NULL);
}

// check that valid ucid insertions work properly
Test(hw5, ui_insert04) { // test 11
  student *s = student_new(5, "jpinkman", 55, "Pinkman", "Jesse");
  uint32_idx *ui = ui_singleton(5, s);

  // create new students
  student *t = student_new(2, "wwhite", 22, "White", "Walter");
  student *u = student_new(3, "swhite", 33, "White", "Skyler");
  student *v = student_new(1, "sgoodman", 11, "Goodman", "Saul");
  student *w = student_new(9, "kwexler", 99, "Wexler", "Kim");
  student *x = student_new(7, "mehrmantraut", 77, "Ehrmantraut", "Mike");
  student *y = student_new(6, "lsalamanca", 66, "Salamanca", "Lalo");
  student *z = student_new(8, "nvarga", 88, "Varga", "Nacho");
  //student *a = student_new(1000, "aa", 10, "bb", "cc"); repeating ui_insert02

  // insert new students
  ui_insert(ui, 2, t);
  ui_insert(ui, 3, u);
  ui_insert(ui, 1, v);
  ui_insert(ui, 9, w);
  ui_insert(ui, 7, x);
  ui_insert(ui, 6, y);
  ui_insert(ui, 8, z);
  //ui_insert(ui, 10, a); repeating ui_insert02

  // test tree accuracy
  cr_assert(ui -> left -> stu -> ucid == 2);
  cr_assert(ui -> left -> left -> stu -> ucid == 1);
  cr_assert(ui -> left -> right -> stu -> ucid == 3);
  cr_assert(ui -> right -> stu -> ucid == 9);
  //cr_assert(ui -> right -> right == NULL); repeating ui_insert02
  cr_assert(ui -> right -> left -> stu -> ucid == 7);
  cr_assert(ui -> right -> left -> left -> stu -> ucid == 6);
  cr_assert(ui -> right -> left -> right -> stu -> ucid == 8);
}

Test(hw5, ui_find00) { // test 12
  uint32_idx *ui = NULL;
  student *s = ui_find(ui, 123);
  cr_assert(1);
}

// check that it returns NULL if student is not present (no children)
Test(hw5, ui_find01) { // test 13
  student *s = student_new(111, "jpinkman", 111111, "Pinkman", "Jesse");
  uint32_idx *ui = ui_singleton(111, s);
  cr_assert(ui_find(ui, 222) == NULL);
}

// check that it returns NULL if student is not present (children)
Test(hw5, ui_find02) { // test 14
  student *s = student_new(5, "jpinkman", 55, "Pinkman", "Jesse");
  uint32_idx *ui = ui_singleton(5, s);

  // create new students
  student *t = student_new(2, "wwhite", 22, "White", "Walter");
  student *u = student_new(3, "swhite", 33, "White", "Skyler");
  student *v = student_new(1, "sgoodman", 11, "Goodman", "Saul");
  student *w = student_new(9, "kwexler", 99, "Wexler", "Kim");
  student *x = student_new(7, "mehrmantraut", 77, "Ehrmantraut", "Mike");
  student *y = student_new(6, "lsalamanca", 66, "Salamanca", "Lalo");
  student *z = student_new(8, "nvarga", 88, "Varga", "Nacho");

  // insert new students
  ui_insert(ui, 2, t);
  ui_insert(ui, 3, u);
  ui_insert(ui, 1, v);
  ui_insert(ui, 9, w);
  ui_insert(ui, 7, x);
  ui_insert(ui, 6, y);
  ui_insert(ui, 8, z);

  cr_assert(ui_find(ui, 10) == NULL);
}

// check that it returns the proper student if present (no children)
Test(hw5, ui_find03) { // test 15
  student *s = student_new(111, "jpinkman", 111111, "Pinkman", "Jesse");
  uint32_idx *ui = ui_singleton(111, s);
  
  // test accuracy
  student *found = ui_find(ui, 111);
  cr_assert(found -> ssn == 111111);
  cr_assert(!strcmp(found -> cnet, "jpinkman"));
}

// check that it returns the proper student if present (children)
Test(hw5, ui_find04) { // test 16
  student *s = student_new(5, "jpinkman", 55, "Pinkman", "Jesse");
  uint32_idx *ui = ui_singleton(5, s);

  // create new students
  student *t = student_new(2, "wwhite", 22, "White", "Walter");
  student *u = student_new(3, "swhite", 33, "White", "Skyler");
  student *v = student_new(1, "sgoodman", 11, "Goodman", "Saul");
  student *w = student_new(9, "kwexler", 99, "Wexler", "Kim");
  student *x = student_new(7, "mehrmantraut", 77, "Ehrmantraut", "Mike");
  student *y = student_new(6, "lsalamanca", 66, "Salamanca", "Lalo");
  student *z = student_new(8, "nvarga", 88, "Varga", "Nacho");

  // insert new students
  ui_insert(ui, 2, t);
  ui_insert(ui, 3, u);
  ui_insert(ui, 1, v);
  ui_insert(ui, 9, w);
  ui_insert(ui, 7, x);
  ui_insert(ui, 6, y);
  ui_insert(ui, 8, z);

  // test accuracy
  student *found = ui_find(ui, 8);
  cr_assert(found -> ssn == 88);
  cr_assert(!strcmp(found -> cnet, "nvarga"));
}

Test(hw5, si_singleton00) { // test 17
  student *s = student_new(123,"samli23",567,"Li","Sam");
  string_idx *si = si_singleton("samli23",s);
  cr_assert(1);
}

// check value accuracy
Test(hw5, si_singleton01) { // test 18
  student *s = student_new(456, "sbaratheon", 789, "Baratheon", "Stannis");
  string_idx *si = si_singleton("sbaratheon", s);

  cr_assert(!strcmp(si -> key, "sbaratheon"));
  cr_assert(si -> stu -> ucid == 456);
  cr_assert(si -> stu -> ssn == 789);
  cr_assert(!strcmp(si -> stu -> cnet, "sbaratheon"));
  cr_assert(si -> stu == s);
  cr_assert(si -> left == NULL);
  cr_assert(si -> right == NULL);
}

// check that student isn't duplicated
Test(hw5, si_singleton02) { // test 19
  student *s = student_new(456, "sbaratheon", 789, "Baratheon", "Stannis");
  string_idx *si = si_singleton("sbaratheon", s);
  cr_assert(si -> stu == s);
  cr_assert(&(si -> stu) != &s);
}

Test(hw5, si_insert00) { // test 20
  student *s = student_new(123,"samli23",567,"Li","Sam");
  string_idx *si = si_singleton("samli23", s);
  student *t = student_new(999,"edwu",888,"Wu","Ed");
  si_insert(si, "edwu", t);
  cr_assert(1);
}

// check that valid ucid insertions work properly
Test(hw5, si_insert03) { // test 23
  student *s = student_new(5, "lwittgenstein", 55, "Wittgenstein", "Ludwig");
  string_idx *si = si_singleton("lwittgenstein", s);

  // create new students
  student *t = student_new(2, "brussell", 22, "Russell", "Bertrand");
  student *u = student_new(3, "gfrege", 33, "Frege", "Gottlob");
  student *v = student_new(1, "wvoquine", 11, "Quine", "Willard");
  student *w = student_new(9, "rcarnap", 99, "Carnap", "Rudolf");
  student *x = student_new(7, "ajayer", 77, "Ayer", "Alfred");
  student *y = student_new(6, "bwilliams", 66, "Williams", "Bernard");
  student *z = student_new(8, "dickrorty", 88, "Rorty", "Richard");

  // insert new students
  si_insert(si, "brussell", t);
  si_insert(si, "gfrege", u);
  si_insert(si, "wvoquine", v);
  si_insert(si, "rcarnap", w);
  si_insert(si, "ajayer", x);
  si_insert(si, "bwilliams", y);
  si_insert(si, "dickrorty", z);
  
  // test tree accuracy
  /* independent of how tree structure is determined, as long as it is
     consistent (i.e. given strings a and b where strcmp(a, b) > 0, it doesn't
     matter whether you put b to the right or left of a, as long as you do
     whatever it is that you choose consistently) */
  int case1_test1 = !strcmp(si -> right -> stu -> cnet, "wvoquine");
  int case1_test2 = !strcmp(si -> right -> key, "wvoquine");
  int case2_test1 = !strcmp(si -> left -> stu -> cnet, "wvoquine");
  int case2_test2 = !strcmp(si -> left -> key, "wvoquine");
  cr_assert((case1_test1 && case1_test2) || (case2_test1 && case2_test2));

  // alphabetical order
  if (case1_test1) {
    cr_assert(!strcmp(si -> right -> left -> stu -> cnet, "rcarnap"));
    cr_assert(!strcmp(si -> left -> stu -> cnet, "brussell"));
    cr_assert(!strcmp(si -> left -> left -> stu -> cnet, "ajayer"));
    cr_assert(!strcmp(si -> left -> right -> stu -> cnet, "gfrege"));
    cr_assert(!strcmp(si -> left -> right -> left -> stu -> cnet, "bwilliams"));
    cr_assert(!strcmp(si -> left -> right -> left -> right -> stu -> cnet, "dickrorty"));
  }

  // reverse alphabetical order
  else {
    cr_assert(!strcmp(si -> left -> right -> stu -> cnet, "rcarnap"));
    cr_assert(!strcmp(si -> right -> stu -> cnet, "brussell"));
    cr_assert(!strcmp(si -> right -> right -> stu -> cnet, "ajayer"));
    cr_assert(!strcmp(si -> right -> left -> stu -> cnet, "gfrege"));
    cr_assert(!strcmp(si -> right -> left -> right -> stu -> cnet, "bwilliams"));
    cr_assert(!strcmp(si -> right -> left -> right -> left -> stu -> cnet, "dickrorty"));
  }
}

Test(hw5, si_find00) { // test 24
  string_idx *si = NULL;
  student *s = si_find(si, "samli23");
   cr_assert(1);
}

// check that it returns NULL if index is not present (no children)
Test(hw5, si_find01) { // test 25
  student *s = student_new(111, "lwittgenstein", 111111, "Wittgenstein", "Ludwig");
  string_idx *si = si_singleton("lwittgenstein", s);
  cr_assert(si_find(si, "brussell") == NULL);
}

// check that it returns NULL if index is not present (children)
Test(hw5, si_find02) { // test 26
  student *s = student_new(5, "lwittgenstein", 55, "Wittgenstein", "Ludwig");
  string_idx *si = si_singleton("lwittgenstein", s);

  // create new students
  student *t = student_new(2, "brussell", 22, "Russell", "Bertrand");
  student *u = student_new(3, "gfrege", 33, "Frege", "Gottlob");
  student *v = student_new(1, "wvoquine", 11, "Quine", "Willard");
  student *w = student_new(9, "rcarnap", 99, "Carnap", "Rudolf");
  student *x = student_new(7, "ajayer", 77, "Ayer", "Alfred");
  student *y = student_new(6, "bwilliams", 66, "Williams", "Bernard");
  student *z = student_new(8, "dickrorty", 88, "Rorty", "Richard");

  // insert new students
  si_insert(si, "brussell", t);
  si_insert(si, "gfrege", u);
  si_insert(si, "wvoquine", v);
  si_insert(si, "rcarnap", w);
  si_insert(si, "ajayer", x);
  si_insert(si, "bwilliams", y);
  si_insert(si, "dickrorty", z);

  cr_assert(si_find(si, "kmarx") == NULL);
}

// check that it returns the proper index if present (no children) 
Test(hw5, si_find03) { // test 27
  student *s = student_new(111, "lwittgenstein", 111111, "Wittgenstein", "Ludwig");
  string_idx *si = si_singleton("lwittgenstein", s);

  student *found = si_find(si, "lwittgenstein");
  cr_assert(found -> ucid == 111);
  cr_assert(!strcmp(found -> fname, "Ludwig"));
}

// check that it returns the proper index if present (children)
Test(hw5, si_find04) { // test 28
  student *s = student_new(5, "lwittgenstein", 55, "Wittgenstein", "Ludwig");
  string_idx *si = si_singleton("lwittgenstein", s);

  // create new students
  student *t = student_new(2, "brussell", 22, "Russell", "Bertrand");
  student *u = student_new(3, "gfrege", 33, "Frege", "Gottlob");
  student *v = student_new(1, "wvoquine", 11, "Quine", "Willard");
  student *w = student_new(9, "rcarnap", 99, "Carnap", "Rudolf");
  student *x = student_new(7, "ajayer", 77, "Ayer", "Alfred");
  student *y = student_new(6, "bwilliams", 66, "Williams", "Bernard");
  student *z = student_new(8, "dickrorty", 88, "Rorty", "Richard");

  // insert new students
  si_insert(si, "brussell", t);
  si_insert(si, "gfrege", u);
  si_insert(si, "wvoquine", v);
  si_insert(si, "rcarnap", w);
  si_insert(si, "ajayer", x);
  si_insert(si, "bwilliams", y);
  si_insert(si, "dickrorty", z);

  // test accuracy
  student *found = si_find(si, "ajayer");
  cr_assert(found -> ssn == 77);
  cr_assert(!strcmp(found -> lname, "Ayer"));
}

Test(hw5, db_new00) { // test 29
  student_db *db = db_new();
  cr_assert(1);
}

// test default database values
Test(hw5, db_new01) { // test 30
  student_db *db = db_new();
  cr_assert(db -> count == 0);
  cr_assert(db -> ucid_idx == NULL);
  cr_assert(db -> cnet_idx == NULL);
  cr_assert(db -> ssn_idx == NULL);
}

Test(hw5, db_num_entries00) { // test 31
  student_db *db = db_new();
  uint32_t n = db_num_entries(db);
  cr_assert(1);
}

Test(hw5, db_num_entries01) { // test 32; relies on db_insert
  // instantiations
  student_db *db = db_new();
  student *s = student_new(5, "lwittgenstein", 55, "Wittgenstein", "Ludwig");
  student *t = student_new(2, "brussell", 22, "Russell", "Bertrand");
  student *u = student_new(3, "gfrege", 33, "Frege", "Gottlob");
  student *v = student_new(1, "wvoquine", 11, "Quine", "Willard");
  student *w = student_new(9, "rcarnap", 99, "Carnap", "Rudolf");
  student *x = student_new(7, "ajayer", 77, "Ayer", "Alfred");
  student *y = student_new(6, "bwilliams", 66, "Williams", "Bernard");
  student *z = student_new(8, "dickrorty", 88, "Rorty", "Richard");

  // insertions
  db_insert(db, s);
  db_insert(db, t);
  db_insert(db, u);
  db_insert(db, v);
  db_insert(db, w);
  db_insert(db, x);
  db_insert(db, y);
  db_insert(db, z);

  // test
  cr_assert(db_num_entries(db) == 8);
}

Test(hw5, db_insert00) { // test 33
  student_db *db = db_new();
  student *s = student_new(123,"samli23",567,"Li","Sam");
  db_insert(db, s);
  cr_assert(1);
}

// test insertion accuracy
Test(hw5, db_insert02) { // test 35
  // instantiations
  student_db *db = db_new();
  student *s = student_new(5, "lwittgenstein", 55, "Wittgenstein", "Ludwig");
  student *t = student_new(2, "brussell", 22, "Russell", "Bertrand");
  student *u = student_new(3, "gfrege", 33, "Frege", "Gottlob");
  student *v = student_new(1, "wvoquine", 11, "Quine", "Willard");
  student *w = student_new(9, "rcarnap", 99, "Carnap", "Rudolf");
  student *x = student_new(7, "ajayer", 77, "Ayer", "Alfred");
  student *y = student_new(6, "bwilliams", 66, "Williams", "Bernard");
  student *z = student_new(8, "dickrorty", 88, "Rorty", "Richard");

  // insertions
  db_insert(db, s);
  db_insert(db, t);
  db_insert(db, u);
  db_insert(db, v);
  db_insert(db, w);
  db_insert(db, x);
  db_insert(db, y);
  db_insert(db, z);

  // tests
  cr_assert(db -> ucid_idx -> stu == s);
  cr_assert(db -> cnet_idx -> stu == s);
  cr_assert(db -> ssn_idx -> stu == s);
  cr_assert(db -> count == 8);
//   cr_assert(db -> ucid_idx -> left -> key == 2);
//   cr_assert(db -> ssn_idx -> right -> key == 99);
//   cr_assert(db -> ucid_idx -> left -> stu == t);
//   int case1_test1 = !strcmp(db -> cnet_idx -> right -> key, "wvoquine");
//   int case1_test2 = db -> cnet_idx -> right -> stu == v;
//   int case2_test1 = !strcmp(db -> cnet_idx -> left -> key, "wvoquine");
//   int case2_test2 = db -> cnet_idx -> left -> stu == v;
//   cr_assert(case1_test1 || case2_test1);
//   cr_assert((case1_test1 && case1_test2) || (case2_test1 && case2_test2));

//   if (case1_test1) {
//     cr_assert(!strcmp(db -> cnet_idx -> left -> right -> left -> right -> key, "dickrorty"));
//     cr_assert(db -> cnet_idx -> left -> right -> left -> right -> stu == z);
//   }
//   else {
//     cr_assert(!strcmp(db -> cnet_idx -> right -> left -> right -> left -> key, "dickrorty"));
//     cr_assert(db -> cnet_idx -> right -> left -> right -> left -> stu == z);
//   }
}

// test repeat insertion 2 (children)
Test(hw5, db_insert03) { // test 36
  // instantiations
  student_db *db = db_new();
  student *s = student_new(5, "lwittgenstein", 55, "Wittgenstein", "Ludwig");
  student *t = student_new(2, "brussell", 22, "Russell", "Bertrand");
  student *u = student_new(3, "gfrege", 33, "Frege", "Gottlob");
  student *v = student_new(1, "wvoquine", 11, "Quine", "Willard");
  student *w = student_new(9, "rcarnap", 99, "Carnap", "Rudolf");
  student *x = student_new(7, "ajayer", 77, "Ayer", "Alfred");
  student *y = student_new(6, "bwilliams", 66, "Williams", "Bernard");
  student *z = student_new(8, "dickrorty", 88, "Rorty", "Richard");

  // insertions
  fprintf(stderr, "Begin db_insert03 insertions, should print 5 messages\n");
  db_insert(db, s);
  db_insert(db, t);
  db_insert(db, u);
  db_insert(db, v);
  db_insert(db, u); // repeat; should print to stderr
  db_insert(db, w);
  db_insert(db, x);
  db_insert(db, y);
  db_insert(db, v); // repeat...
  db_insert(db, z);
  db_insert(db, w); // repeat
  db_insert(db, y); // repeat
  db_insert(db, z); // repeat
  fprintf(stderr, "End db_insert03 insertions\n\n");

  // test
  cr_assert(db -> count == 8);
}

Test(hw5, find_by_ucid00) { // test 37
  student *s = find_by_ucid(db_new(), 0);
  cr_assert(1);
}

// index not present, no children
Test(hw5, find_by_ucid01) { // test 38
  student_db *db = db_new();
  student *s = student_new(5, "lwittgenstein", 55, "Wittgenstein", "Ludwig");
  db_insert(db, s);
  cr_assert(find_by_ucid(db, 6) == NULL);
}

// index present, no children
Test(hw5, find_by_ucid02) { // test 39
  student_db *db = db_new();
  student *s = student_new(5, "lwittgenstein", 55, "Wittgenstein", "Ludwig");
  db_insert(db, s);
  cr_assert(find_by_ucid(db, 5) == s);
}

// index not present, children
Test(hw5, find_by_ucid03) { // test 40
// instantiations
  student_db *db = db_new();
  student *s = student_new(5, "lwittgenstein", 55, "Wittgenstein", "Ludwig");
  student *t = student_new(2, "brussell", 22, "Russell", "Bertrand");
  student *u = student_new(3, "gfrege", 33, "Frege", "Gottlob");
  student *v = student_new(1, "wvoquine", 11, "Quine", "Willard");
  student *w = student_new(9, "rcarnap", 99, "Carnap", "Rudolf");
  student *x = student_new(7, "ajayer", 77, "Ayer", "Alfred");
  student *y = student_new(6, "bwilliams", 66, "Williams", "Bernard");
  student *z = student_new(8, "dickrorty", 88, "Rorty", "Richard");

  // insertions
  db_insert(db, s);
  db_insert(db, t);
  db_insert(db, u);
  db_insert(db, v);
  db_insert(db, w);
  db_insert(db, x);
  db_insert(db, y);
  db_insert(db, z);

  // test
  cr_assert(find_by_ucid(db, 10) == NULL);
}

// index present, children
Test(hw5, find_by_ucid04) { // test 41
  // instantiations
  student_db *db = db_new();
  student *s = student_new(5, "lwittgenstein", 55, "Wittgenstein", "Ludwig");
  student *t = student_new(2, "brussell", 22, "Russell", "Bertrand");
  student *u = student_new(3, "gfrege", 33, "Frege", "Gottlob");
  student *v = student_new(1, "wvoquine", 11, "Quine", "Willard");
  student *w = student_new(9, "rcarnap", 99, "Carnap", "Rudolf");
  student *x = student_new(7, "ajayer", 77, "Ayer", "Alfred");
  student *y = student_new(6, "bwilliams", 66, "Williams", "Bernard");
  student *z = student_new(8, "dickrorty", 88, "Rorty", "Richard");

  // insertions
  db_insert(db, s);
  db_insert(db, t);
  db_insert(db, u);
  db_insert(db, v);
  db_insert(db, w);
  db_insert(db, x);
  db_insert(db, y);
  db_insert(db, z);

  // tests
  cr_assert(find_by_ucid(db, 9) == w);
  cr_assert(find_by_ucid(db, 6) == y);
  cr_assert(find_by_ucid(db, 3) == u);
}

Test(hw5, find_by_cnet00) { // test 42
  student *s = find_by_cnet(db_new(), "x");
  cr_assert(1);
}

// index not present, no children
Test(hw5, find_by_cnet01) { // test 43
  student_db *db = db_new();
  student *s = student_new(5, "lwittgenstein", 55, "Wittgenstein", "Ludwig");
  db_insert(db, s);
  cr_assert(find_by_cnet(db, "pfstrawson") == NULL);
}

// index present, no children
Test(hw5, find_by_cnet02) { // test 44
  student_db *db = db_new();
  student *s = student_new(5, "lwittgenstein", 55, "Wittgenstein", "Ludwig");
  db_insert(db, s);
  cr_assert(find_by_cnet(db, "lwittgenstein") == s);
}

// index not present, children
Test(hw5, find_by_cnet03) { // test 45
  // instantiations
  student_db *db = db_new();
  student *s = student_new(5, "lwittgenstein", 55, "Wittgenstein", "Ludwig");
  student *t = student_new(2, "brussell", 22, "Russell", "Bertrand");
  student *u = student_new(3, "gfrege", 33, "Frege", "Gottlob");
  student *v = student_new(1, "wvoquine", 11, "Quine", "Willard");
  student *w = student_new(9, "rcarnap", 99, "Carnap", "Rudolf");
  student *x = student_new(7, "ajayer", 77, "Ayer", "Alfred");
  student *y = student_new(6, "bwilliams", 66, "Williams", "Bernard");
  student *z = student_new(8, "dickrorty", 88, "Rorty", "Richard");

  // insertions
  db_insert(db, s);
  db_insert(db, t);
  db_insert(db, u);
  db_insert(db, v);
  db_insert(db, w);
  db_insert(db, x);
  db_insert(db, y);
  db_insert(db, z);

  // test
  cr_assert(find_by_cnet(db, "skripke") == NULL);
}

// index present, children
Test(hw5, find_by_cnet04) { // test 46
  // instantiations
  student_db *db = db_new();
  student *s = student_new(5, "lwittgenstein", 55, "Wittgenstein", "Ludwig");
  student *t = student_new(2, "brussell", 22, "Russell", "Bertrand");
  student *u = student_new(3, "gfrege", 33, "Frege", "Gottlob");
  student *v = student_new(1, "wvoquine", 11, "Quine", "Willard");
  student *w = student_new(9, "rcarnap", 99, "Carnap", "Rudolf");
  student *x = student_new(7, "ajayer", 77, "Ayer", "Alfred");
  student *y = student_new(6, "bwilliams", 66, "Williams", "Bernard");
  student *z = student_new(8, "dickrorty", 88, "Rorty", "Richard");

  // insertions
  db_insert(db, s);
  db_insert(db, t);
  db_insert(db, u);
  db_insert(db, v);
  db_insert(db, w);
  db_insert(db, x);
  db_insert(db, y);
  db_insert(db, z);

  // tests
  cr_assert(find_by_cnet(db, "rcarnap") == w);
  cr_assert(find_by_cnet(db, "bwilliams") == y);
  cr_assert(find_by_cnet(db, "gfrege") == u);
}

Test(hw5, find_by_ssn00) { // test 47
  student *s = find_by_ssn(db_new(), 0);
  cr_assert(1);
}

// index not present, no children
Test(hw5, find_by_ssn01) { // test 48
  student_db *db = db_new();
  student *s = student_new(5, "lwittgenstein", 55, "Wittgenstein", "Ludwig");
  db_insert(db, s);
  cr_assert(find_by_ssn(db, 66) == NULL);
}

// index present, no children
Test(hw5, find_by_ssn02) { // test 49
  student_db *db = db_new();
  student *s = student_new(5, "lwittgenstein", 55, "Wittgenstein", "Ludwig");
  db_insert(db, s);
  cr_assert(find_by_ssn(db, 55) == s);
}

// index not present, children
Test(hw5, find_by_ssn03) { // test 50
  // instantiations
  student_db *db = db_new();
  student *s = student_new(5, "lwittgenstein", 55, "Wittgenstein", "Ludwig");
  student *t = student_new(2, "brussell", 22, "Russell", "Bertrand");
  student *u = student_new(3, "gfrege", 33, "Frege", "Gottlob");
  student *v = student_new(1, "wvoquine", 11, "Quine", "Willard");
  student *w = student_new(9, "rcarnap", 99, "Carnap", "Rudolf");
  student *x = student_new(7, "ajayer", 77, "Ayer", "Alfred");
  student *y = student_new(6, "bwilliams", 66, "Williams", "Bernard");
  student *z = student_new(8, "dickrorty", 88, "Rorty", "Richard");

  // insertions
  db_insert(db, s);
  db_insert(db, t);
  db_insert(db, u);
  db_insert(db, v);
  db_insert(db, w);
  db_insert(db, x);
  db_insert(db, y);
  db_insert(db, z);

  // test
  cr_assert(find_by_ssn(db, 10) == NULL);
}

// index present, children
Test(hw5, find_by_ssn04) { // test 51
  // instantiations
  student_db *db = db_new();
  student *s = student_new(5, "lwittgenstein", 55, "Wittgenstein", "Ludwig");
  student *t = student_new(2, "brussell", 22, "Russell", "Bertrand");
  student *u = student_new(3, "gfrege", 33, "Frege", "Gottlob");
  student *v = student_new(1, "wvoquine", 11, "Quine", "Willard");
  student *w = student_new(9, "rcarnap", 99, "Carnap", "Rudolf");
  student *x = student_new(7, "ajayer", 77, "Ayer", "Alfred");
  student *y = student_new(6, "bwilliams", 66, "Williams", "Bernard");
  student *z = student_new(8, "dickrorty", 88, "Rorty", "Richard");

  // insertions
  db_insert(db, s);
  db_insert(db, t);
  db_insert(db, u);
  db_insert(db, v);
  db_insert(db, w);
  db_insert(db, x);
  db_insert(db, y);
  db_insert(db, z);

  // tests
  cr_assert(find_by_ssn(db, 99) == w);
  cr_assert(find_by_ssn(db, 66) == y);
  cr_assert(find_by_ssn(db, 33) == u);
}

Test(hw5, db_free00) { // test 52
  student_db *db = db_new();
  db_free(db);
  cr_assert(1);
}
