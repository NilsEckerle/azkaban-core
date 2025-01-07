#ifndef ENTRY_H
#define ENTRY_H

#include <stdio.h>
#include <stdlib.h>

/**
 * @struct Entry
 * @brief Represents a database entry.
 */
typedef struct {
  int id;           /**< Unique identifier for the entry. */
  char *name;       /**< Name of the entry. */
  char *user_name;  /**< Associated username. */
  char *password;   /**< Password associated with the entry. */
  int is_deleted;   /**< Deletion status flag. */
} Entry;

/**
 * @struct EntryNode
 * @brief Linked list node for Entry structures.
 */
typedef struct EntryNode {
  Entry data;             /**< Entry data. */
  struct EntryNode *next; /**< Pointer to the next node. */
} EntryNode;

/**
 * @brief Initializes an entry list.
 * @return Pointer to the head of the list.
 */
EntryNode *entry_list_init(void);

/**
 * @brief Prepends an entry to the list.
 * @param head Pointer to the head of the list.
 * @param entry Entry data to prepend.
 */
void entry_list_prepend_item(EntryNode **head, Entry entry);

/**
 * @brief Iterates over the entry list and applies a callback function.
 * @param head Pointer to the head of the list.
 * @param callback Callback function to apply.
 * @param parameter_first_given_to_callback Additional parameter for the callback.
 *
 * @example
 * ```c
 * #include <stdio.h>
 * 
 * void *print_entry(void *parameter, Entry entry) {
 *     printf("Entry ID: %d, Name: %s, User: %s, Password: %s\n",
 *            entry.id, entry.name, entry.user_name, entry.password);
 *     return parameter;
 * }
 * 
 * int main() {
 *     EntryNode *head = entry_list_init();
 *     Entry entry1 = {1, "Email", "user1", "pass1", 0};
 *     Entry entry2 = {2, "Website", "user2", "pass2", 0};
 *     
 *     entry_list_prepend_item(&head, entry1);
 *     entry_list_prepend_item(&head, entry2);
 *     
 *     entry_list_itterate_function(head, print_entry, NULL);
 *     
 *     return 0;
 * }
 * ```
 */
void entry_list_itterate_function(EntryNode *head,
                                  void *callback(void *parameter, Entry entry),
                                  void *parameter_first_given_to_callback);

/**
 * @brief Gets the length of the entry list.
 * @param head Pointer to the head of the list.
 * @return Length of the list.
 */
int entry_list_get_length(EntryNode *head);

/**
 * @struct IContent
 * @brief Represents content that can either be text or binary data.
 * 
 * This structure allows storing either plain text or binary data (blob),
 * with an associated content type and size.
 */
typedef struct {
  char *type; /**< The type of the content (e.g., "text" or "blob"). */
  union {
    char *text; /**< Pointer to text content. */
    void *blob; /**< Pointer to binary data. */
  } data; /**< Union for storing text or binary data. */
  size_t size; /**< Size of the content in bytes. */
} IContent;

/**
 * @struct EntryDetail
 * @brief Represents detailed information associated with an entry.
 * 
 * Each entry detail contains metadata such as ID, a reference to its parent
 * entry, content, and deletion status.
 */
typedef struct {
  int id;           /**< Unique identifier for the entry detail. */
  int f_entry_id;   /**< Foreign key referencing the associated entry. */
  IContent *content; /**< Pointer to the content of the entry detail. */
  int is_deleted;   /**< Deletion status flag (0: active, 1: deleted). */
} EntryDetail;

/**
 * @struct EntryDetailNode
 * @brief Node structure for linked lists of EntryDetail.
 * 
 * This structure allows creating linked lists of entry details for 
 * efficient traversal and manipulation.
 */
typedef struct EntryDetailNode {
  EntryDetail data;             /**< Entry detail data. */
  struct EntryDetailNode *next; /**< Pointer to the next node. */
} EntryDetailNode;

/**
 * @brief Initializes a new entry detail list.
 * 
 * @return Pointer to the head of the new entry detail list.
 */
EntryDetailNode *entryDetail_list_init(void);

/**
 * @brief Prepends a new entry detail to the list.
 * 
 * @param head Pointer to the head of the list.
 * @param entry_detail Entry detail data to prepend.
 */
void entryDetail_list_prepend_item(EntryDetailNode **head,
                                   EntryDetail entry_detail);

/**
 * @brief Iterates over the entry detail list and applies a callback function.
 * 
 * @param head Pointer to the head of the list.
 * @param callback Callback function to apply to each entry detail.
 * @param parameter_first_given_to_callback Additional parameter passed to the callback.
 */
void entryDetail_list_itterate_function(
    EntryDetailNode *head,
    void *callback(void *parameter, EntryDetail entry_detail),
    void *parameter_first_given_to_callback);

/**
 * @brief Retrieves the length of the entry detail list.
 * 
 * @param head Pointer to the head of the list.
 * @return Length of the list.
 */
int entryDetail_list_get_length(EntryDetailNode *head);

/**
 * @struct FolderNode
 * @brief Represents a folder in the database.
 * 
 * Each folder contains a name and a pointer to the next folder node in the list.
 */
typedef struct FolderNode {
  char *folder_name; /**< Name of the folder. */
  struct FolderNode *next; /**< Pointer to the next folder node. */
} FolderNode;

/**
 * @brief Initializes a new folder list.
 * 
 * @return Pointer to the head of the new folder list.
 */
FolderNode *folder_list_init(void);

/**
 * @brief Prepends a new folder to the list.
 * 
 * @param head Pointer to the head of the folder list.
 * @param folder_name Name of the folder to prepend.
 */
void folder_list_prepent(FolderNode **head, char *folder_name);

/**
 * @brief Iterates over the folder list and applies a callback function.
 * 
 * @param head Pointer to the head of the folder list.
 * @param callback Callback function to apply to each folder.
 * @param parameter_first_given_to_callback Additional parameter passed to the callback.
 */
void folder_list_itterate_function(FolderNode *head,
                                   void *callback(void *parameter,
                                                  char *folder_name),
                                   void *parameter_first_given_to_callback);

/**
 * @brief Retrieves the length of the folder list.
 * 
 * @param head Pointer to the head of the folder list.
 * @return Length of the folder list.
 */
int folder_list_get_length(FolderNode *head);

#endif
