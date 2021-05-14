#include <stddef.h>
#include "lists.h"

void* cont_list_init(void* list, unsigned int payload_id)
{ cont_list_t* l = (cont_list_t*)list;

  l->next = NULL; l->prev = NULL; l->payload_id = payload_id;

  return l; }

void* cont_list_detach(void* list)
{ cont_list_t* l = (cont_list_t*)list;
  
  if (l->prev) { l->prev->next = l->next; }
  if (l->next) { l->next->prev = l->prev; }

  return l; }

void* cont_list_first(void* list)
{ cont_list_t* l = (cont_list_t*)list;

  while (l->prev != NULL) { l = l->prev; }

  return l; }

void* cont_list_last(void* list)
{ cont_list_t* l = (cont_list_t*)list;

  while (l->next != NULL) { l = l->next; }

  return l; }

void* cont_list_insert_before(void* list, void* item)
{ cont_list_t* prev = ((cont_list_t*)list)->prev;
  cont_list_t* next = (cont_list_t*)list;
  cont_list_t* i    = (cont_list_t*)item;

  i->prev = prev; i->next = next;
  if (prev) { prev->next = i; }
  if (next) { next->prev = i; }

  return i; }

void* cont_list_insert_after(void* list, void* item)
{ cont_list_t* prev = (cont_list_t*)list;
  cont_list_t* next = ((cont_list_t*)list)->next;
  cont_list_t* i    = (cont_list_t*)item;

  i->prev = prev; i->next = next;
  if (prev) { prev->next = i; }
  if (next) { next->prev = i; }

  return i; }

void* cont_list_append(void* list, void* item)
{ return cont_list_insert_after(cont_list_last(list), item); }

void* cont_list_prepend(void* list, void* item)
{ return cont_list_insert_before(cont_list_first(list), item); } 
