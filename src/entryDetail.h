#ifndef ENTRYDETAIL_H
#define ENTRYDETAIL_H

#include <stdio.h>

/**
 * @struct IContent
 * @brief Represents content that can either be text or binary data.
 * 
 * This structure allows storing either plain text or binary data (blob),
 * with an associated content type and size.
 */
typedef struct {
  char *szType; /**< The type of the content (e.g., "text" or "blob"). */
  union {
    char *szText; /**< Pointer to text content. */
    void *pBlob;  /**< Pointer to binary data. */
  } uData; /**< Union for storing text or binary data. */
  size_t cbSize; /**< Size of the content in bytes. */
} stIContent;

/**
 * @struct EntryDetail
 * @brief Represents detailed information associated with an entry.
 * 
 * Each entry detail contains metadata such as ID, a reference to its parent
 * entry, content, and deletion status.
 */
typedef struct {
  int nId;             /**< Unique identifier for the entry detail. */
  int nFEntryId;       /**< Foreign key referencing the associated entry. */
  stIContent *pContent;  /**< Pointer to the content of the entry detail. */
  int bIsDeleted;      /**< Deletion status flag (0: active, 1: deleted). */
} stEntryDetail;

#endif // !ENTRYDETAIL_H
