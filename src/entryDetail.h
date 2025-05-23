#ifndef ENTRYDETAIL_H
#define ENTRYDETAIL_H

#include <stdio.h>

/**
 * @struct t_entry_detail_content
 * @brief Represents content that can either be text or binary data.
 * 
 * This structure allows storing either plain text or binary data (blob),
 * with an associated content type and size.
 */
typedef struct {
  char *cp_type; /**< The type of the content (e.g., "text" or "blob"). */
  union {
    char *cp_text; /**< Pointer to text content. */
    void *vp_blob;  /**< Pointer to binary data. */
  } uni_data; /**< Union for storing text or binary data. */
  size_t sz_size; /**< Size of the content in bytes. */
} t_entry_detail_content;

/**
 * @struct EntryDetail
 * @brief Represents detailed information associated with an entry.
 * 
 * Each entry detail contains metadata such as ID, a reference to its parent
 * entry, content, and deletion status.
 */
typedef struct {
  int i_id;             /**< Unique identifier for the entry detail. */
  int i_entry_id;       /**< Foreign key referencing the associated entry. */
  t_entry_detail_content *t_content;  /**< Pointer to the content of the entry detail. */
  int b_is_deleted;      /**< Deletion status flag (0: active, 1: deleted). */
} st_entry_detail;

#endif // !ENTRYDETAIL_H
