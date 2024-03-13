#ifndef _HW5_HEADER_
#define _HW5_HEADER_
// note: this "ifndef" idiom ensures the header file is only included once  
#include <stdint.h>
struct student_record {
uint32_t ucid;
char *cnet;
uint32_t ssn;
char *lname;
char *fname;
};
typedef struct student_record student;
struct uint32_unique_index {
uint32_t key;
struct student_record *stu;
struct uint32_unique_index *left;
struct uint32_unique_index *right;
};
// note: by convention, NULL represents the empty index
struct string_unique_index {
char *key;
struct student_record *stu;
struct string_unique_index *left;
struct string_unique_index *right;
};
// note: by convention, NULL represents the empty index
typedef struct string_unique_index string_idx;
typedef struct uint32_unique_index uint32_idx;
struct student_database {
uint32_t count;
uint32_idx *ucid_idx;
string_idx *cnet_idx;
uint32_idx *ssn_idx;
};
typedef struct student_database student_db;
// ------ student record operations
student *student_new(uint32_t ucid, char *cnet, uint32_t ssn, char *lname, char
*fname);
// allocate a fresh student record with the given information
// strdup the three strings and point to them from the record
void student_free(student *stu);
// free the student record and the strings pointed to by it
// ------ uint32 index operations
uint32_idx *ui_singleton(uint32_t key, student *stu);
// create a size-one index with given key and student record
// do not copy the student record, just point to it
// precondition: the key must match the corresponding field in the student record
// - if the precondition is not met, GIGO
void ui_insert(uint32_idx *ui, uint32_t key, student *stu);
// insert the given key/record into the index
// do not copy the student record, just point to it
// if the given index "ui" is NULL, GIGO
// if the given key does match the corresponding field in the record, GIGO
student *ui_find(uint32_idx *ui, uint32_t n);
// look for student record with key n in the index
// return NULL if not found, if found return pointer to it
// ------ string index operations
string_idx *si_singleton(char *key, student *stu);
// create a size-one index with given key and student record
// do not copy the student record, just point to it
// precondition: the key must match the corresponding field in the student record
// - if the precondition is not met, GIGO
void si_insert(string_idx *si, char *key, student *stu);
// insert the given key/record into the index
// strdup the key pointed to by the index node
// do not copy the student record, just point to it
// if the given index "si" is NULL, GIGO
// if the given key does match the corresponding field in the record, GIGO
student *si_find(string_idx *si, char *s);
// look for student record with key s in the index
// return NULL if not found, if found return pointer to it
// ------ database operations
student_db *db_new();
// create a new database with count 0 and three empty indexes (all NULL)
uint32_t db_num_entries(student_db *db);
// return the number of records in the database
void db_insert(student_db *db, student *stu);
// check that the given student record has a unique ucid, cnet, and ssn
// in the database
// if it is non-unique in any of these three fields, fprintf a message to stderr
// and return (don't crash)
// if it is unique in these three fields, update all three indexes and
// increment count
student *find_by_ucid(student_db *db, uint32_t ucid);
// look in the ucid index for the given student record
// return either a pointer to it, or NULL if not found
student *find_by_cnet(student_db *db, char *cnet);
// look in the cnet index for the given student record
// return either a pointer to it, or NULL if not found
student *find_by_ssn(student_db *db, uint32_t ssn);
// look in the ssn index for the given student record
// return either a pointer to it, or NULL if not found
void db_free(student_db *db);
// free the whole database, including all pointed-to items
#endif /* _HW5_HEADER_ */