#ifndef ENTRY_H
#define ENTRY_H

/**
 * @struct Entry
 * @brief Represents a database entry.
 */
typedef struct {
  int iId;           /**< Unique identifier for the entry. */
  char *cpName;      /**< Name of the entry. */
  char *cpUserName;  /**< Associated username. */
  char *cpPassword;  /**< Password associated with the entry. */
  int bIsDeleted;    /**< Deletion status flag. */
} stEntry;

#endif // !ENTRY_H
