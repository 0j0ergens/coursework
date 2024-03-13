#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <criterion/criterion.h>
#include "hw7.h"
// tests: more for existence of operations than for correctness
// these tests leak memory freely
Test(hw7_student_new, stunew00)
{
student *stu = student_new(1,"a",2,"b","c");
cr_assert(stu);
}

Test(hw7_student_new, stunew01)
{
    char *cnet = "adsd";
    char *lname = "bz";
    char *fname = "cw";
    student *stu = student_new(14234232,cnet,22323,lname, fname);
    cr_assert(stu -> ucid == 14234232);
    cr_assert(stu -> cnet != cnet); // check fo strdup
    cr_assert(!strcmp(stu -> cnet, "adsd"));
    cr_assert(stu -> ssn == 22323);
    cr_assert(stu -> lname != lname); // check fo strdup
    cr_assert(!strcmp(stu -> lname, "bz"));
    cr_assert(stu -> fname != fname); // check fo strdup
    cr_assert(!strcmp(stu -> fname, "cw"));
}

Test(hw7_student_from_string, sfs00)
{
student *stu = student_from_string("4,q,5,t,y");
cr_assert(stu);
}

Test(hw7_student_from_string, sfs01)
{
    student *stu = student_from_string("4234234,qzj,51111,tw,ys");
    //printf("%d:%s:%d:%s:%s\n", stu -> ucid, stu -> cnet, stu ->ssn, stu -> lname, stu ->fname);
    cr_assert(stu -> ucid == 4234234);
    cr_assert(!strcmp(stu -> cnet, "qzj"));
    cr_assert(stu -> ssn == 51111);
    cr_assert(!strcmp(stu -> lname, "tw"));
    cr_assert(!strcmp(stu -> fname, "ys"));
}

Test(hw7_student_free, stufree00)
{
student *stu = student_new(1,"a",2,"b","c");
student_free(stu);
cr_assert(1);
}

// a stub hash function for ints
uint64_t zero(uint32_t n) {return 0;}
Test(hw7_ihi_new, ihinew00)
{
ihi *idx = ihi_new(100,&zero);
cr_assert(idx);
}

Test(hw7_ihi_insert_by_ucid, ihiinsid00)
{
student *stu = student_new(1,"a",2,"b","c");
ihi *idx = ihi_new(100,&zero);
ihi_insert_by_ucid(idx,stu);
cr_assert(1);
}

Test(hw7_ihi_insert_by_ucid, ihiinsid01)
{
    student *stu = student_new(1,"a",2,"b","c");
    cr_assert(stu -> ucid == 1);
    cr_assert(!strcmp(stu -> cnet, "a"));
    cr_assert(stu -> ssn == 2);
    cr_assert(!strcmp(stu -> lname, "b"));
    cr_assert(!strcmp(stu -> fname, "c"));

    student *stu2 = student_from_string("4234234,qzj,51111,tw,ys");
    cr_assert(stu2 -> ucid == 4234234);
    cr_assert(!strcmp(stu2 -> cnet, "qzj"));
    cr_assert(stu2 -> ssn == 51111);
    cr_assert(!strcmp(stu2 -> lname, "tw"));
    cr_assert(!strcmp(stu2 -> fname, "ys"));

    ihi *idx = ihi_new(100,&zero);
    ihi_insert_by_ucid(idx,stu);
    ihi_insert_by_ucid(idx, stu2);
    cr_assert(ihi_find_by_ucid(idx, stu ->ucid) == stu);
    cr_assert(ihi_find_by_ucid(idx, stu2 ->ucid) == stu2);
    cr_assert(!ihi_find_by_ucid(idx, 0));
}

Test(hw7_ihi_insert_by_ssn, ihiinsssn00)
{
student *stu = student_new(1,"a",2,"b","c");
ihi *idx = ihi_new(100,&zero);
ihi_insert_by_ucid(idx,stu);
cr_assert(1);
}

Test(hw7_ihi_find_by_ucid, ihifindid00)
{
student *stu = student_new(1,"a",2,"b","c");
ihi *idx = ihi_new(100,&zero);
ihi_insert_by_ucid(idx,stu);
cr_assert(ihi_find_by_ucid(idx,1));
}

Test(hw7_ihi_find_by_ssn, ihifindssn00)
{
student *stu = student_new(1,"a",2,"b","c");
ihi *idx = ihi_new(100,&zero);
ihi_insert_by_ssn(idx,stu);
cr_assert(ihi_find_by_ssn(idx,2));
cr_assert(!ihi_find_by_ssn(idx, 1)); 
}

uint64_t one(char *s) {return 1;}
Test(hw7_shi_new, shinew00)
{
    shi *idx = shi_new(100,&one);
    cr_assert(idx);
}

Test(hw7_shi_new, shinew01)
{
    shi *idx = shi_new(100,&one);
    cr_assert(idx -> n_buckets == 100);
    cr_assert(idx -> hash == &one);
    cr_assert(idx -> buckets != NULL);
}

Test(hw7_shi_insert_by_cnet, shiinsc00)
{
student *stu = student_new(1,"a",2,"b","c");
shi *idx = shi_new(100,&one);
shi_insert_by_cnet(idx,stu);
cr_assert(1);
}

Test(hw7_shi_insert_by_cnet, shiinsc01)
{
    student *stu = student_new(1,"a",2,"b","c");
    cr_assert(stu -> ucid == 1);
    cr_assert(!strcmp(stu -> cnet, "a"));
    cr_assert(stu -> ssn == 2);
    cr_assert(!strcmp(stu -> lname, "b"));
    cr_assert(!strcmp(stu -> fname, "c"));

    student *stu2 = student_from_string("4234234,qzj,51111,tw,ys");
    cr_assert(stu2 -> ucid == 4234234);
    cr_assert(!strcmp(stu2 -> cnet, "qzj"));
    cr_assert(stu2 -> ssn == 51111);
    cr_assert(!strcmp(stu2 -> lname, "tw"));
    cr_assert(!strcmp(stu2 -> fname, "ys"));

    shi *idx = shi_new(100,&one);
    shi_insert_by_cnet(idx,stu);
    shi_insert_by_cnet(idx, stu2);
    cr_assert(shi_find_by_cnet(idx, stu ->cnet) == stu);
    cr_assert(shi_find_by_cnet(idx, stu2 ->cnet) == stu2);
    cr_assert(! shi_find_by_cnet(idx, "0"));
}

Test(hw7_shi_insert_by_cnet, shiinsc02)
{
    // test for linked list situation
    student *stu = student_new(1,"a",2,"b","c");

    student *stu2 = student_from_string("4234234,a,3,tw,ys");

    shi *idx = shi_new(100,&one);
    shi_insert_by_cnet(idx,stu);
    shi_insert_by_cnet(idx, stu2);
    cr_assert(shi_find_by_cnet(idx, stu ->cnet) == stu);
    cr_assert(shi_find_by_cnet(idx, stu2 ->cnet) -> next == NULL);
    cr_assert(! shi_find_by_cnet(idx, "0"));
}

Test(hw7_shi_insert_by_lname, shiinsl00)
{
    student *stu = student_new(1,"a",2,"b","c");
    shi *idx = shi_new(100,&one);
    shi_insert_by_lname(idx,stu);
    cr_assert(1);
}

Test(hw7_shi_insert_by_lname, shiinsl01)
{
    student *stu = student_new(1,"a",2,"b","c");
    cr_assert(stu -> ucid == 1);
    cr_assert(!strcmp(stu -> cnet, "a"));
    cr_assert(stu -> ssn == 2);
    cr_assert(!strcmp(stu -> lname, "b"));
    cr_assert(!strcmp(stu -> fname, "c"));

    student *stu2 = student_from_string("4234234,qzj,51111,tw,ys");
    cr_assert(stu2 -> ucid == 4234234);
    cr_assert(!strcmp(stu2 -> cnet, "qzj"));
    cr_assert(stu2 -> ssn == 51111);
    cr_assert(!strcmp(stu2 -> lname, "tw"));
    cr_assert(!strcmp(stu2 -> fname, "ys"));

    shi *idx = shi_new(100,&one);
    shi_insert_by_lname(idx,stu);
    shi_insert_by_lname(idx, stu2);
    cr_assert(shi_find_by_lname(idx, stu ->lname) == stu);
    cr_assert(shi_find_by_lname(idx, stu2 ->lname) == stu2);
    cr_assert(! shi_find_by_lname(idx, "0"));
}


Test(hw7_shi_insert_by_fname, shiinsf00)
{
    student *stu = student_new(1,"a",2,"b","c");
    shi *idx = shi_new(100,&one);
    shi_insert_by_fname(idx,stu);
    cr_assert(1);
}

Test(hw7_shi_insert_by_fname, shiinsf01)
{
    student *stu = student_new(1,"a",2,"b","c");
    cr_assert(stu -> ucid == 1);
    cr_assert(!strcmp(stu -> cnet, "a"));
    cr_assert(stu -> ssn == 2);
    cr_assert(!strcmp(stu -> lname, "b"));
    cr_assert(!strcmp(stu -> fname, "c"));

    student *stu2 = student_from_string("4234234,qzj,51111,tw,ys");
    cr_assert(stu2 -> ucid == 4234234);
    cr_assert(!strcmp(stu2 -> cnet, "qzj"));
    cr_assert(stu2 -> ssn == 51111);
    cr_assert(!strcmp(stu2 -> lname, "tw"));
    cr_assert(!strcmp(stu2 -> fname, "ys"));

    shi *idx = shi_new(100,&one);
    shi_insert_by_fname(idx,stu);
    shi_insert_by_fname(idx, stu2);
    cr_assert(shi_find_by_fname(idx, stu ->fname) == stu);
    cr_assert(shi_find_by_fname(idx, stu2 ->fname) == stu2);
    cr_assert(! shi_find_by_fname(idx, "0"));
}

Test(hw7_shi_insert_by_fname, shiinsf02)
{
    // test for linked list situation
    student *stu = student_new(1,"a",2,"b","c");

    student *stu2 = student_from_string("4234234,qzj,51111,tw,c");

    shi *idx = shi_new(100,&one);
    shi_insert_by_fname(idx,stu);
    shi_insert_by_fname(idx, stu2);
    cr_assert(shi_find_by_fname(idx, stu ->fname) == stu);
    cr_assert(shi_find_by_fname(idx, stu2->fname) == stu);
}

Test(hw7_db_new, dbnew00)
{
    student_db *db = db_new(100,&zero,&one);
    
    cr_assert(db -> ucid_idx -> n_buckets == 100);
    cr_assert(db -> ucid_idx -> hash == &zero);
    cr_assert(db -> ucid_idx -> buckets != NULL);

    cr_assert(db -> cnet_idx -> n_buckets == 100);
    cr_assert(db -> cnet_idx -> hash == &one);
    cr_assert(db -> cnet_idx -> buckets != NULL);

    cr_assert(db -> ssn_idx -> n_buckets == 100);
    cr_assert(db -> ssn_idx -> hash == &zero);
    cr_assert(db -> ssn_idx -> buckets != NULL);

    cr_assert(db -> lname_idx -> n_buckets == 100);
    cr_assert(db -> lname_idx -> hash == &one);
    cr_assert(db -> lname_idx -> buckets != NULL);

    cr_assert(db -> fname_idx -> n_buckets == 100);
    cr_assert(db -> fname_idx -> hash == &one);
    cr_assert(db -> fname_idx -> buckets != NULL);
}

Test(hw7_db_insert, dbins00)
{
    student *stu = student_new(1,"a",2,"b","c");
    student_db *db = db_new(100,&zero,&one);
    db_insert(db,stu);
    cr_assert(db);
}

Test(hw7_db_insert, dbins01){
    student *stu = student_new(1,"a",2,"b","c");
    cr_assert(stu -> ucid == 1);
    cr_assert(!strcmp(stu -> cnet, "a"));
    cr_assert(stu -> ssn == 2);
    cr_assert(!strcmp(stu -> lname, "b"));
    cr_assert(!strcmp(stu -> fname, "c"));

    student *stu2 = student_from_string("4234234,qzj,51111,tw,ys");
    cr_assert(stu2 -> ucid == 4234234);
    cr_assert(!strcmp(stu2 -> cnet, "qzj"));
    cr_assert(stu2 -> ssn == 51111);
    cr_assert(!strcmp(stu2 -> lname, "tw"));
    cr_assert(!strcmp(stu2 -> fname, "ys"));

    student_db *db = db_new(100,&zero,&one);
    db_insert(db,stu);
    db_insert(db,stu2);

    student *stu3 = find_by_ucid(db, stu ->ucid);
    //printf("a%d:%s:%d:%s:%s\n", stu3 -> ucid, stu3 -> cnet, stu3 ->ssn, stu3 -> lname, stu3 ->fname);
    cr_assert(find_by_ucid(db, stu ->ucid) == stu);
    cr_assert(find_by_ucid(db, stu2 ->ucid) == stu2);
    cr_assert(! find_by_ucid(db, 0));

    stu3 = find_by_cnet(db, stu ->cnet);
    //printf("b%d:%s:%d:%s:%s\n", stu3 -> ucid, stu3 -> cnet, stu3 ->ssn, stu3 -> lname, stu3 ->fname);
    cr_assert(find_by_cnet(db, stu ->cnet) == stu);
    cr_assert(find_by_cnet(db, stu2 ->cnet) == stu2);
    cr_assert(! find_by_cnet(db, "0"));

    stu3 = find_by_ssn(db, stu2 ->ssn);
    //printf("c%d:%s:%d:%s:%s\n", stu3 -> ucid, stu3 -> cnet, stu3 ->ssn, stu3 -> lname, stu3 ->fname);
    cr_assert(find_by_ssn(db, stu ->ssn) == stu);
    cr_assert(find_by_ssn(db, stu2 ->ssn) == stu2);
    cr_assert(! find_by_ssn(db, 0));

    stu3 = find_by_lname(db, stu -> lname);
    //printf("d%d:%s:%d:%s:%s\n", stu3 -> ucid, stu3 -> cnet, stu3 ->ssn, stu3 -> lname, stu3 ->fname);
    cr_assert(find_by_lname(db, stu ->lname) == stu);
    cr_assert(find_by_lname(db, stu2 ->lname) == stu2);
    cr_assert(! find_by_lname(db, "0"));

    stu3 = find_by_fname(db, stu2 ->fname);
    //printf("e%d:%s:%d:%s:%s\n", stu3 -> ucid, stu3 -> cnet, stu3 ->ssn, stu3 -> lname, stu3 ->fname);
    cr_assert(find_by_fname(db, stu ->fname) == stu);
    cr_assert(find_by_fname(db, stu2 ->fname) == stu2);
    cr_assert(! find_by_fname(db, "0"));
}

Test(hw7_db_insert, dbins02){
    // test for insertion of students with same ucid, cnet, ssn, lname, and fname
    student *stu = student_new(1,"a",2,"b","c");
    student *stu2 = student_new(1,"b",3,"z","z"); // same ucid, should not be inserted
    student *stu3 = student_new(2,"a",4,"y","y"); // same cnet, should not be inserted
    student *stu4 = student_new(3,"c",2,"x","x"); // same ssn, should not be inserted
    student *stu5 = student_new(4,"d",5,"b","d"); // same lname, should be inserted
    student *stu6 = student_new(5,"e",6,"j","c"); // same fname, should be inserted

    student_db *db = db_new(100,&zero,&one);
    db_insert(db,stu);
    db_insert(db,stu2); // error message shall be printed for this
    db_insert(db,stu3); // error message shall be printed for this
    db_insert(db,stu4); // error message shall be printed for this
    db_insert(db,stu5);
    db_insert(db,stu6);

    cr_assert(find_by_ucid(db, stu ->ucid) == stu);
    cr_assert(find_by_ucid(db, stu2 ->ucid) == stu);
    cr_assert(find_by_ucid(db, stu2 ->ucid) -> next == NULL); // found: set "next" to NULL
    cr_assert(!find_by_ucid(db, stu3 ->ucid));
    cr_assert(!find_by_ucid(db, stu4 ->ucid));
    cr_assert(find_by_ucid(db, stu5 ->ucid) == stu5);
    cr_assert(find_by_ucid(db, stu6 ->ucid) == stu6);
    cr_assert(! find_by_ucid(db, 0));

    cr_assert(find_by_cnet(db, stu ->cnet) == stu);
    cr_assert(!find_by_cnet(db, stu2 ->cnet));
    cr_assert(find_by_cnet(db, stu3 ->cnet) == stu);
    cr_assert(find_by_cnet(db, stu3 ->cnet) -> next == NULL); // found: set "next" to NULL
    cr_assert(!find_by_cnet(db, stu4 ->cnet));
    cr_assert(find_by_cnet(db, stu5 ->cnet) == stu5);
    cr_assert(find_by_cnet(db, stu6 ->cnet) == stu6);
    cr_assert(! find_by_cnet(db, "0"));

    cr_assert(find_by_ssn(db, stu ->ssn) == stu);
    cr_assert(!find_by_ssn(db, stu2 ->ssn));
    cr_assert(!find_by_ssn(db, stu3 ->ssn));
    cr_assert(find_by_ssn(db, stu4 ->ssn) == stu);
    cr_assert(find_by_ssn(db, stu4 ->ssn) -> next == NULL); // found: set "next" to NULL
    cr_assert(find_by_ssn(db, stu5 ->ssn) == stu5);
    cr_assert(find_by_ssn(db, stu6 ->ssn) == stu6);
    cr_assert(! find_by_ssn(db, 0));

    cr_assert(find_by_lname(db, stu ->lname) == stu);
    cr_assert(!find_by_lname(db, stu2 ->lname)); // these are not added into the hash (and not found) table due to redundency
    cr_assert(!find_by_lname(db, stu3 ->lname));
    cr_assert(!find_by_lname(db, stu4 ->lname));
    cr_assert(find_by_lname(db, stu5 ->lname) == stu);
    cr_assert(find_by_lname(db, stu6 ->lname) == stu6);
    cr_assert(! find_by_lname(db, "0"));

    cr_assert(find_by_fname(db, stu ->fname) == stu);
    cr_assert(!find_by_fname(db, stu2 ->fname)); // same here
    cr_assert(!find_by_fname(db, stu3 ->fname));
    cr_assert(!find_by_fname(db, stu4 ->fname));
    cr_assert(find_by_fname(db, stu5 ->fname) == stu5);
    cr_assert(find_by_fname(db, stu6 ->fname) == stu);
    cr_assert(! find_by_fname(db, "0"));

    /*
    // to test whether stu5 is stu -> next
    student *stu0 = find_by_lname(db, stu5 ->lname) -> next;
    printf("%p\n", stu0);
    printf("%d:%s:%d:%s:%s\n", stu0 -> ucid, stu0 -> cnet, stu0 ->ssn, stu0 -> lname, stu0 ->fname);
    printf("%p\n", stu0 -> next);

    // to test whether stu6 is stu -> next
    stu0 = find_by_fname(db, stu6 ->fname) -> next;
    printf("%d:%s:%d:%s:%s\n", stu0 -> ucid, stu0 -> cnet, stu0 ->ssn, stu0 -> lname, stu0 ->fname);
    printf("%p\n", stu0 -> next);
    */
}

Test(hw7_db_from_file, dbff00)
{
    student_db*(*f)(char*, uint64_t (*)(uint32_t), uint64_t (*)(char *)) = &db_from_file;
    cr_assert(f);
}

int same_stu(student *s1, student *s2){
    // test if two students are the same
    
   //printf("\n %s,%s \n", s1->fname, s2->fname);
    // printf("%d,%d,%d,%d,%d %s|%s\n",
    // s1 -> ucid == s2 -> ucid,
    // ! strcmp(s1 -> cnet, s2 -> cnet), 
    // s1 -> ssn == s2 -> ssn,
    // ! strcmp(s1 -> lname, s2 -> lname),
    // ! strcmp(s1 -> fname, s2 -> fname), s1->fname, s2->fname);
    

    return (s1 -> ucid == s2 -> ucid 
    && ! strcmp(s1 -> cnet, s2 -> cnet) 
    && s1 -> ssn == s2 -> ssn 
    && ! strcmp(s1 -> lname, s2 -> lname)
    && ! strcmp(s1 -> fname, s2 -> fname));
}


Test(hw7_db_from_file, dbff01)
{   
    student *stu = student_from_string("123,a,234,wer,azd");

    student *stu2 = student_from_string("1,b,2,nd,skz");

    student *stu3 = student_from_string("0,sdfsf,10086,as1,123");

    student *stu4 = student_from_string("153,z,1,wer,azd"); // test for insertion of students with same fname and lname

    student_db* db = db_from_file("test.csv", &zero, &one);

    //student *stu5 = find_by_ucid(db, stu ->ucid);
   // printf("\n%d:%s:%d:%s:%s\n", stu5 -> ucid, stu5 -> cnet, stu5 ->ssn, stu5 -> lname, stu5 ->fname);
    cr_assert(same_stu(find_by_ucid(db, stu ->ucid), stu));
    cr_assert(same_stu(find_by_ucid(db, stu2 ->ucid), stu2));
    cr_assert(same_stu(find_by_ucid(db, stu3 ->ucid), stu3));
    cr_assert(same_stu(find_by_ucid(db, stu4 ->ucid), stu4)); 
    cr_assert(! find_by_ucid(db, 1000));

    cr_assert(same_stu(find_by_cnet(db, stu ->cnet), stu));
    cr_assert(same_stu(find_by_cnet(db, stu2 ->cnet), stu2));
    cr_assert(same_stu(find_by_cnet(db, stu3 ->cnet), stu3));
    cr_assert(same_stu(find_by_cnet(db, stu4 ->cnet), stu4));
    cr_assert(! find_by_cnet(db, "1000"));

    cr_assert(same_stu(find_by_ssn(db, stu ->ssn), stu));
    cr_assert(same_stu(find_by_ssn(db, stu2 ->ssn), stu2));
    cr_assert(same_stu(find_by_ssn(db, stu3 ->ssn), stu3));
    cr_assert(same_stu(find_by_ssn(db, stu4 ->ssn), stu4));
    cr_assert(! find_by_ssn(db, 1000));

    cr_assert(same_stu(find_by_lname(db, stu ->lname), stu));
    cr_assert(same_stu(find_by_lname(db, stu2 ->lname), stu2));
    cr_assert(same_stu(find_by_lname(db, stu3 ->lname), stu3));

    // /*
    // student *stu5 = find_by_lname(db, stu4 ->lname) -> next;
    // printf("%p\n", stu5);
    // printf("%d:%s:%d:%s:%s\n", stu5 -> ucid, stu5 -> cnet, stu5 ->ssn, stu5 -> lname, stu5 ->fname);
    // */

    //cr_assert(same_stu(find_by_lname(db, stu4 ->lname) -> next, stu4)); // linked together
    cr_assert(! find_by_lname(db, "1000"));

    cr_assert(same_stu(find_by_fname(db, stu ->fname), stu));
    cr_assert(same_stu(find_by_fname(db, stu2 ->fname), stu2));
    cr_assert(same_stu(find_by_fname(db, stu3 ->fname), stu3));
    //cr_assert(same_stu(find_by_fname(db, stu4 ->fname) -> next, stu4)); // linked together
    cr_assert(! find_by_fname(db, "1000"));
}

Test(hw7_db_from_file, dbff02){
    student_db* db = db_from_file("data.csv", &zero, &one);

    // some random rows are used to test for accuracy here
    student *stu = student_from_string("1450307,RAKMSC69CD,580052300,9QFA0R3VVN,3OVQXBMEFM"); // row 60
    student *stu2 = student_from_string("57286621,4AGX4LFBDN,228196311,WLW1XX6D8E,K2BB5PHDT1"); // row 97
    student *stu3 = student_from_string("77849198,IJJSQ06VV3,370841217,N1U5460DJ6,CX18PN4WGN"); // row 24
    student *stu4 = student_from_string("77996042,6S9Q4A2K81,857258500,SVL45X0K0R,LRMB6AFO1I"); // row 2, first row
    student *stu5 = student_from_string("91867313,G9DE0MDZQN,838379687,2WUBEK3I0I,LFIHNV73GL"); // row 33
    student *stu6 = student_from_string("99635196,R7I8YOLXRG,605226492,E5TEJS97G4,BRZ35VDK8H"); // row 101, last row

   //printf("\n%d:%s:%d:%s:%s\n", stuk->ucid, stuk->cnet, stuk->ssn, stuk->lname, stuk->fname);
    cr_assert(same_stu(find_by_ucid(db, stu ->ucid), stu));
    cr_assert(same_stu(find_by_ucid(db, stu2 ->ucid), stu2));
    cr_assert(same_stu(find_by_ucid(db, stu3 ->ucid), stu3));
    cr_assert(same_stu(find_by_ucid(db, stu4 ->ucid), stu4));
    cr_assert(same_stu(find_by_ucid(db, stu5 ->ucid), stu5));
    cr_assert(same_stu(find_by_ucid(db, stu6 ->ucid), stu6));
    cr_assert(! find_by_ucid(db, 1000));

    cr_assert(same_stu(find_by_cnet(db, stu ->cnet), stu));
    cr_assert(same_stu(find_by_cnet(db, stu2 ->cnet), stu2));
    cr_assert(same_stu(find_by_cnet(db, stu3 ->cnet), stu3));
    cr_assert(same_stu(find_by_cnet(db, stu4 ->cnet), stu4));
    cr_assert(same_stu(find_by_cnet(db, stu5 ->cnet), stu5));
    cr_assert(same_stu(find_by_cnet(db, stu6 ->cnet), stu6));
    cr_assert(! find_by_cnet(db, "1000"));

    cr_assert(same_stu(find_by_ssn(db, stu ->ssn), stu));
    cr_assert(same_stu(find_by_ssn(db, stu2 ->ssn), stu2));
    cr_assert(same_stu(find_by_ssn(db, stu3 ->ssn), stu3));
    cr_assert(same_stu(find_by_ssn(db, stu4 ->ssn), stu4));
    cr_assert(same_stu(find_by_ssn(db, stu5 ->ssn), stu5));
    cr_assert(same_stu(find_by_ssn(db, stu6 ->ssn), stu6));
    cr_assert(! find_by_ssn(db, 1000));

    cr_assert(same_stu(find_by_lname(db, stu ->lname), stu));
    cr_assert(same_stu(find_by_lname(db, stu2 ->lname), stu2));
    cr_assert(same_stu(find_by_lname(db, stu3 ->lname), stu3));
    cr_assert(same_stu(find_by_lname(db, stu4 ->lname), stu4));
    cr_assert(same_stu(find_by_lname(db, stu5 ->lname), stu5));
    cr_assert(same_stu(find_by_lname(db, stu6 ->lname), stu6));
    cr_assert(! find_by_lname(db, "1000"));

    cr_assert(same_stu(find_by_fname(db, stu ->fname), stu));
    cr_assert(same_stu(find_by_fname(db, stu2 ->fname), stu2));
    cr_assert(same_stu(find_by_fname(db, stu3 ->fname), stu3));
    cr_assert(same_stu(find_by_fname(db, stu4 ->fname), stu4));
    cr_assert(same_stu(find_by_fname(db, stu5 ->fname), stu5));
    cr_assert(same_stu(find_by_fname(db, stu6 ->fname), stu6));
    cr_assert(! find_by_fname(db, "1000"));
}

Test(hw7_find_by_ucid, dbfindid00)
{
    student *stu = student_new(1,"a",2,"b","c");
    student_db *db = db_new(100,&zero,&one);
    db_insert(db,stu);
    cr_assert(find_by_ucid(db,1));
}

Test(hw7_find_by_cnet, dbfindc00)
{
    student *stu = student_new(1,"a",2,"b","c");
    student_db *db = db_new(100,&zero,&one);
    db_insert(db,stu);
    cr_assert(find_by_cnet(db,"a"));
}

Test(hw7_find_by_ssn, dbfindssn00)
{
    student *stu = student_new(1,"a",2,"b","c");
    student_db *db = db_new(100,&zero,&one);
    db_insert(db,stu);
    cr_assert(find_by_ssn(db,2));
}

Test(hw7_find_by_fname, dbfindf00)
{
    student *stu = student_new(1,"a",2,"b","c");
    student_db *db = db_new(100,&zero,&one);
    db_insert(db,stu);
    cr_assert(find_by_fname(db,"c"));
}


// Test(hw7_cnets_asc, cnets00)
// {
//     student *stu = student_new(1,"a",2,"b","c");
//     student *stu2 = student_from_string("57286621,4AGX4LFBDN,228196311,WLW1XX6D8E,K2BB5PHDT1"); // row 97
//     student *stu3 = student_from_string("77849198,IJJSQ06VV3,370841217,N1U5460DJ6,CX18PN4WGN"); // row 24
//     student *stu4 = student_from_string("77996042,6S9Q4A2K81,857258500,SVL45X0K0R,LRMB6AFO1I"); // row 2, first row
//     student *stu5 = student_from_string("91867313,G9DE0MDZQN,838379687,2WUBEK3I0I,LFIHNV73GL"); // row 33
//     student *stu6 = student_from_string("99635196,R7I8YOLXRG,605226492,E5TEJS97G4,BRZ35VDK8H"); // row 101, last row
    
//     student_db *db = db_new(100,&zero,&one);
//     db_insert(db,stu);
//     db_insert(db, stu2);
//     db_insert(db, stu3);
//     db_insert(db, stu4);
//     db_insert(db, stu5);
//     db_insert(db, stu6);
//     cnets_asc(db);
//     cr_assert(cnets_asc(db));
// }


Test(hw7_cnets_asc, cnets01){
    student *stu = student_from_string("123,a,234,wer,azd");
    student *stu2 = student_from_string("1,b,2,nd,skz");
    student *stu3 = student_from_string("0,sdfsf,10086,as1,123");
    student *stu4 = student_from_string("132,adc,11,assfd,qwsf");
    student *stu5 = student_from_string("99,zcsdfzc,1,sfw34sd,3422342");
    student *stu6 = student_from_string("14723,gezij,-10000,.2e0diz,1343dsw");
    student_db *db = db_new(100,&zero,&one);
    db_insert(db,stu);
    db_insert(db,stu2);
    db_insert(db,stu3);
    db_insert(db,stu4);
    db_insert(db,stu5);
    db_insert(db,stu6);

    char **rtr_val = cnets_asc(db);
    cr_assert(! strcmp(rtr_val[0], "a") 
    && ! strcmp(rtr_val[1], "adc") 
    && ! strcmp(rtr_val[2], "b")
    && ! strcmp(rtr_val[3], "gezij")
    && ! strcmp(rtr_val[4], "sdfsf")
    && ! strcmp(rtr_val[5], "zcsdfzc"));
}

Test(hw7_db_resize, resize00)
{
    student_db *db1 = db_new(100,&zero,&one);
    student_db *db2 = db_resize(db1,101);
    cr_assert(db2);
}


Test(hw7_db_resize, resize01)
{
    student *stu = student_from_string("123,a,234,wer,azd");
    student *stu2 = student_from_string("1,b,2,nd,skz");
    student *stu3 = student_from_string("0,sdfsf,10086,as1,123");
    student *stu4 = student_from_string("132,adc,11,assfd,qwsf");
    student *stu5 = student_from_string("99,zcsdfzc,1,sfw34sd,3422342");
    student *stu6 = student_from_string("14723,gezij,-10000,.2e0diz,1343dsw");
    student_db *db = db_new(10086,&zero,&one);
    db_insert(db,stu);
    db_insert(db,stu2);
    db_insert(db,stu3);
    db_insert(db,stu4);
    db_insert(db,stu5);
    db_insert(db,stu6);

    student_db *db2 = db_resize(db,29372914);

    // test size is changed
    cr_assert(db2 -> ucid_idx -> n_buckets == 29372914);
    cr_assert(db2 -> cnet_idx -> n_buckets == 29372914);
    cr_assert(db2 -> ssn_idx -> n_buckets == 29372914);
    cr_assert(db2 -> lname_idx -> n_buckets == 29372914);
    cr_assert(db2 -> fname_idx -> n_buckets == 29372914);
//--------------------------------------------------------------
    // test hash function is not changed
    cr_assert(db2 -> ucid_idx -> hash == db -> ucid_idx -> hash);
    cr_assert(db2 -> cnet_idx -> hash == db -> cnet_idx -> hash);
    cr_assert(db2 -> ssn_idx -> hash == db -> ssn_idx -> hash);
    cr_assert(db2 -> lname_idx -> hash == db -> lname_idx -> hash);
    cr_assert(db2 -> fname_idx -> hash == db -> fname_idx -> hash);
//--------------------------------------------------------------
    // test the original db is not changed (or freed)
    cr_assert(same_stu(find_by_ucid(db, stu ->ucid), stu));
    cr_assert(same_stu(find_by_ucid(db, stu2 ->ucid), stu2));
    cr_assert(same_stu(find_by_ucid(db, stu3 ->ucid), stu3));
    cr_assert(same_stu(find_by_ucid(db, stu4 ->ucid), stu4));
    cr_assert(same_stu(find_by_ucid(db, stu5 ->ucid), stu5));
    cr_assert(same_stu(find_by_ucid(db, stu6 ->ucid), stu6));
    cr_assert(! find_by_ucid(db, 1000));

    cr_assert(same_stu(find_by_cnet(db, stu ->cnet), stu));
    cr_assert(same_stu(find_by_cnet(db, stu2 ->cnet), stu2));
    cr_assert(same_stu(find_by_cnet(db, stu3 ->cnet), stu3));
    cr_assert(same_stu(find_by_cnet(db, stu4 ->cnet), stu4));
    cr_assert(same_stu(find_by_cnet(db, stu5 ->cnet), stu5));
    cr_assert(same_stu(find_by_cnet(db, stu6 ->cnet), stu6));
    cr_assert(! find_by_cnet(db, "1000"));

    cr_assert(same_stu(find_by_ssn(db, stu ->ssn), stu));
    cr_assert(same_stu(find_by_ssn(db, stu2 ->ssn), stu2));
    cr_assert(same_stu(find_by_ssn(db, stu3 ->ssn), stu3));
    cr_assert(same_stu(find_by_ssn(db, stu4 ->ssn), stu4));
    cr_assert(same_stu(find_by_ssn(db, stu5 ->ssn), stu5));
    cr_assert(same_stu(find_by_ssn(db, stu6 ->ssn), stu6));
    cr_assert(! find_by_ssn(db, 1000));

    cr_assert(same_stu(find_by_lname(db, stu ->lname), stu));
    cr_assert(same_stu(find_by_lname(db, stu2 ->lname), stu2));
    cr_assert(same_stu(find_by_lname(db, stu3 ->lname), stu3));
    cr_assert(same_stu(find_by_lname(db, stu4 ->lname), stu4));
    cr_assert(same_stu(find_by_lname(db, stu5 ->lname), stu5));
    cr_assert(same_stu(find_by_lname(db, stu6 ->lname), stu6));
    cr_assert(! find_by_lname(db, "1000"));

    cr_assert(same_stu(find_by_fname(db, stu ->fname), stu));
    cr_assert(same_stu(find_by_fname(db, stu2 ->fname), stu2));
    cr_assert(same_stu(find_by_fname(db, stu3 ->fname), stu3));
    cr_assert(same_stu(find_by_fname(db, stu4 ->fname), stu4));
    cr_assert(same_stu(find_by_fname(db, stu5 ->fname), stu5));
    cr_assert(same_stu(find_by_fname(db, stu6 ->fname), stu6));
    cr_assert(! find_by_fname(db, "1000"));
// ----------------------------------------------------------------
    // test the new db copies students successfully (just pointer, not new student)
    cr_assert(same_stu(find_by_ucid(db2, stu ->ucid), stu));
    cr_assert(same_stu(find_by_ucid(db2, stu2 ->ucid), stu2));
    cr_assert(same_stu(find_by_ucid(db2, stu3 ->ucid), stu3));
    cr_assert(same_stu(find_by_ucid(db2, stu4 ->ucid), stu4));
    cr_assert(same_stu(find_by_ucid(db2, stu5 ->ucid), stu5));
    cr_assert(same_stu(find_by_ucid(db2, stu6 ->ucid), stu6));
    cr_assert(! find_by_ucid(db2, 1000));

    cr_assert(same_stu(find_by_cnet(db2, stu ->cnet), stu));
    cr_assert(same_stu(find_by_cnet(db2, stu2 ->cnet), stu2));
    cr_assert(same_stu(find_by_cnet(db2, stu3 ->cnet), stu3));
    cr_assert(same_stu(find_by_cnet(db2, stu4 ->cnet), stu4));
    cr_assert(same_stu(find_by_cnet(db2, stu5 ->cnet), stu5));
    cr_assert(same_stu(find_by_cnet(db2, stu6 ->cnet), stu6));
    cr_assert(! find_by_cnet(db2, "1000"));

    cr_assert(same_stu(find_by_ssn(db2, stu ->ssn), stu));
    cr_assert(same_stu(find_by_ssn(db2, stu2 ->ssn), stu2));
    cr_assert(same_stu(find_by_ssn(db2, stu3 ->ssn), stu3));
    cr_assert(same_stu(find_by_ssn(db2, stu4 ->ssn), stu4));
    cr_assert(same_stu(find_by_ssn(db2, stu5 ->ssn), stu5));
    cr_assert(same_stu(find_by_ssn(db2, stu6 ->ssn), stu6));
    cr_assert(! find_by_ssn(db2, 1000));

    cr_assert(same_stu(find_by_lname(db2, stu ->lname), stu));
    cr_assert(same_stu(find_by_lname(db2, stu2 ->lname), stu2));
    cr_assert(same_stu(find_by_lname(db2, stu3 ->lname), stu3));
    cr_assert(same_stu(find_by_lname(db2, stu4 ->lname), stu4));
    cr_assert(same_stu(find_by_lname(db2, stu5 ->lname), stu5));
    cr_assert(same_stu(find_by_lname(db2, stu6 ->lname), stu6));
    cr_assert(! find_by_lname(db2, "1000"));

    cr_assert(same_stu(find_by_fname(db2, stu ->fname), stu));
    cr_assert(same_stu(find_by_fname(db2, stu2 ->fname), stu2));
    cr_assert(same_stu(find_by_fname(db2, stu3 ->fname), stu3));
    cr_assert(same_stu(find_by_fname(db2, stu4 ->fname), stu4));
    cr_assert(same_stu(find_by_fname(db2, stu5 ->fname), stu5));
    cr_assert(same_stu(find_by_fname(db2, stu6 ->fname), stu6));
    cr_assert(! find_by_fname(db2, "1000"));
//--------------------------------------------------------------
    // test the original and new db stores the same pointers
    cr_assert(find_by_ucid(db, stu ->ucid) == find_by_ucid(db2, stu ->ucid));
    cr_assert(find_by_cnet(db, stu ->cnet) == find_by_cnet(db2, stu ->cnet));
    cr_assert(find_by_ssn(db, stu ->ssn) == find_by_ssn(db2, stu ->ssn));
    cr_assert(find_by_lname(db, stu ->lname) == find_by_lname(db2, stu ->lname));
    cr_assert(find_by_fname(db, stu ->fname) == find_by_fname(db2, stu ->fname));
}

Test(hw7_db_free, dbfree00)
{
    student_db *db = db_new(100,&zero,&one);
    db_free(db);
    cr_assert(1);
}

// a simple student_free test: for instructions see below: db_free test
/*
int main(){
    student *stu = student_from_string("123,a,234,wer,azd");
    student_free(stu);
}
*/
