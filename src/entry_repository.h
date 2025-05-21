#ifndef ENTRY_REPOSITORY_H
#define ENTRY_REPOSITORY_H

#include "linked_list.h"
#include "entry.h"
#include "database.h"

stEntry *fnGetEntry(stDecryptedDatabase *stDecryptedDb, int iId);

stEntry *fnSearchEntry(stDecryptedDatabase *stDecryptedDb, char *cpSearchName);

stLinkedListNode *fnGetEntryList(stDecryptedDatabase *stDecryptedDb);

int fnCreateEntry(stDecryptedDatabase *stDecryptedDb, stEntry *stNewEntry);

int fnDeleteEntry(stDecryptedDatabase *stDecryptedDb, int iId);

int fnDeleteEntryHard(stDecryptedDatabase *stDecryptedDb, int iId);

int fnChangeEntry(stDecryptedDatabase *stDecryptedDb, int iOldId, stEntry *stNewEntry);

int fnSetupTable(stDecryptedDatabase *stDecryptedDb);

#endif
