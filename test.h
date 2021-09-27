#ifndef TEST_H
#define TEST_H

#include "header.h"

int createdeleterecord(Record* record, List* plist);
int testinsert(List* plist, Record* record);
int deleteRecord_test(List* plist, Record* data);
int testshuffle(List* plist, Record* record1, Record* record2, Record* record3);
int createdeleterecord_Soundgarden(Record* record, List* plist);
int createdeleterecord_Beck(Record* record, List* plist);

#endif