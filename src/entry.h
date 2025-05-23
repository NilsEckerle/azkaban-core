#ifndef ENTRY_H
#define ENTRY_H

/**
 * @struct t_entry
 * @brief Represents a database entry.
 */
typedef struct {
  int i_id;           /**< Unique identifier for the entry. */
  char *cp_name;      /**< Name of the entry. */
  char *cp_user_name;  /**< Associated username. */
  char *cp_password;  /**< Password associated with the entry. */
  int b_is_deleted;    /**< Deletion status flag. */
} t_entry;

#endif // !ENTRY_H
