#ifndef LISTS_H
#define LISTS_H

/** \brief interface of linked list */
typedef struct cont_list
{ struct cont_list* next;
  struct cont_list* prev;
  unsigned int      payload_id;
} cont_list_t;

/** \brief   initialize linked list root node structure
 *  \arg     list       pointer to a root node of list
 *  \arg     payload_id identifier of payloaded data type
 *                      \note this field is not necessary for linkde list
 *                            mechanisms theirselves but useful for a user
 *                            TODO: maybe deprecate?
 *  \return  pointer to a root node of list */
void* cont_list_init(void* list, unsigned int payload_id);

/** \brief   exclude element from linked list
 *  \details just redefine next and prev pointers
 *           \note TODO: add validation check
 *  \arg     list pointer to item be detached
 *                \note TODO: rename to "item"
 *  \return  pointer to detached item*/ 
void* cont_list_detach(void* list);

/** \brief   find first (root) item in list
 *  \details search by chain in previous
 *           \note TODO; add circle detecton
 *  \arg     list pointer to any item in list
 *                \note TODO: rename to "item"
 *  \return  pointer to first (root) item */
void* cont_list_first(void* list);

/** \brief   find last item in list
 *  \details search by chain in nexts
 *           \note TODO: add circle detection
 *  \arg     list pointer to any item in list
 *                \note TODO: rename to "item"
 *  \return  pointer to last item */
void* cont_list_last(void* list);

/** \brief   insert item in list before selected
 *  \details manipulates prev and next pointers
 *           \note TODO: make arguments validation
 *  \arg     list any item in list
 *                \note TODO: rename to "dest"
 *  \arg     item item to be inserted in list
 *  \return  pointer to inserted item */
void* cont_list_insert_before(void* list, void* item);

/** \brief   insert item in list after selected
 *  \details manipulates prev and next pointers
 *           \note TODO: make arguments validation
 *  \arg     list any item in list
 *                \note TODO: rename to "dest"
 *  \arg     item item to be inserted in list
 *  \return  pointer to inserted item */
void* cont_list_insert_after(void* list, void* item);

/** \brief   insert item in last position in linked list
 *  \details search last item and insert after it
 *  \arg     list any item of target list
 *  \arg     item item to be appended
 *  \return  pointer to appended item*/
void* cont_list_append(void* list, void* item);

/** \brief   insert item in first (root) position of linked list
 *  \details search first item and insert before it
 *  \arg     list any item of target list
 *  \arg     item item to be prepended
 *  \return  pointer to prepended item */
void* cont_list_prepend(void* list, void* item);

#endif//LISTS_H
