#ifndef _HW7_HEADER_
#define _HW7_HEADER_
// note: this "ifndef" idiom ensures the header file is only included
// once per project
#include <stdint.h>
// ====== data definitions
struct student_record {
uint32_t ucid;
char *cnet;
uint32_t ssn;
char *lname;
char *fname;
struct student_record *next;
};
// note: the next pointer allows student records to
// be connected together into a linked list
typedef struct student_record student;
struct student_entry {
uint64_t hash_code;
student *stu;
struct student_entry *next;
};
// note: the next pointer allows student entries to
// be connected together into a linked list
typedef struct student_entry entry;
struct uint32_hash_index {
uint64_t(*hash)(uint32_t n);
uint32_t n_buckets;
struct student_entry **buckets;
};
struct string_hash_index {
uint64_t(*hash)(char *s);
uint32_t n_buckets;
struct student_entry **buckets;
};
typedef struct string_hash_index shi;
typedef struct uint32_hash_index ihi;
struct student_database {
uint32_t count;
ihi *ucid_idx;
shi *cnet_idx;
ihi *ssn_idx;
shi *lname_idx;
shi *fname_idx;
};
typedef struct student_database student_db;
// ====== operations
// ------ student records operations
student *student_new(uint32_t ucid, char *cnet, uint32_t ssn, char *lname, char
*fname);
// allocate a fresh student record with the given information
// strdup the three strings and point to them from the record
// initialize "next" pointer to NULL
student *student_from_string(char *csv_row);
// csv_row is a string with comma separation like this:
// "12345,jlee99,999888,Lee,Janet"
// order must be ucid, cnet, ssn, lname, fname
// if the given string is malformed, GIGO
void student_free(student *stu);
// free the student record and the strings pointed to by it
// ------ uint32 hash index operations
ihi *ihi_new(uint32_t n_buckets, uint64_t(*h)(uint32_t n));
// build a new empty integer hash index
void ihi_insert_by_ucid(ihi *idx, student *stu);
// insert student into hash index using ucid
void ihi_insert_by_ssn(ihi *idx, student *stu);
// insert student into hash index using ssn
student *ihi_find_by_ucid(ihi *idx, uint32_t n);
// find student in hash index using ucid
// if student is found, set the "next" field to NULL
// return NULL if student is not found
student *ihi_find_by_ssn(ihi *idx, uint32_t n);
// find student in hash index using ssn
// if student is found, set the "next" field to NULL
// return NULL if student is not found
// ------ string hash index operations
shi *shi_new(uint32_t n_buckets, uint64_t(*h)(char *s));
// build a new empty string hash index
void shi_insert_by_cnet(shi *idx, student *stu);
// insert student into hash index using cnet
void shi_insert_by_lname(shi *idx, student *stu);
// insert student into hash index using last name
void shi_insert_by_fname(shi *idx, student *stu);
// insert student into hash index using first name
student *shi_find_by_cnet(shi *idx, char *s);
// find student in hash index using cnet
// if student is found, set the "next" field to NULL
// return NULL if student is not found
student *shi_find_by_lname(shi *idx, char *s);
// find student in hash index using last name
// return NULL (the empty list) if no students are found
// if students are found, use "next" to link them into a list
// the list can be in any order
student *shi_find_by_fname(shi *idx, char *s);
// find student in hash index using first name
// return NULL (the empty list) if no students are found
// if students are found, use "next" to link them into a list
// the list can be in any order
// ------ database operations
student_db *db_new(uint32_t n_buckets, uint64_t(*int_hash)(uint32_t n),
uint64_t(*string_hash)(char *));
// create a new database with count 0 and five empty hash indexes
// use the same number of buckets in every index
void db_insert(student_db *db, student *stu);
// check that the given student record has a unique ucid, cnet, and ssn
// in the database
// if it is non-unique in any of these three fields, fprintf a message to stderr
// and return with no insertion (don't crash)
// if student is unique in these three fields, insert into all five indexes and
// increment count
student_db *db_from_file(char *filename, \
uint64_t(*int_hash)(uint32_t n), uint64_t(*string_hash)(char *));
// consume a CSV file with one student per row (see student_from_string)
// build database from all students in file
student *find_by_ucid(student_db *db, uint32_t ucid);
// look in the ucid index for the given student record
// return either a pointer to it, or NULL if not found
student *find_by_cnet(student_db *db, char *cnet);
// look in the cnet index for the given student record
// return either a pointer to it, or NULL if not found
student *find_by_ssn(student_db *db, uint32_t ssn);
// look in the ssn index for the given student record
// return either a pointer to it, or NULL if not found
student *find_by_lname(student_db *db, char *lname);
// return a list of students with given last name
// in no particular order (NULL for no students)
student *find_by_fname(student_db *db, char *fname);
// return a list of students with given first name
// in no particular order (NULL for no students)
char **cnets_asc(student_db *db);
// return an array of all the cnets in strcmp-ascending order
student_db *db_resize(student_db *db, uint32_t n_buckets);
// create a new database with new number of buckets
void db_free(student_db *db);
// free the whole database, including all pointed-to items
#endif /* _HW7_HEADER_ */
