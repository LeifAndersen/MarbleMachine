#ifndef __LIST_H
#define __LIST_H

typedef struct
{
	int item_count;
	int current_max_size;
	char growable;

	void **items;
	char **names;	
} obj_list;

void list_make(obj_list *listo, int size, char growable);
int list_add_item(obj_list *listo, void *item, char *name);
char* list_print_items(obj_list *listo);
void* list_get_name(obj_list *listo, char *name);
void* list_get_index(obj_list *listo, int indx);
void* list_get_item(obj_list *listo, void *item_to_find);
int list_find(obj_list *listo, char *name_to_find);
void list_delete_index(obj_list *listo, int indx);
void list_delete_name(obj_list *listo, char *name);
void list_delete_item(obj_list *listo, void *item);
void list_delete_all(obj_list *listo);
void list_print_list(obj_list *listo);
void list_free(obj_list *listo);

void test_list();
#endif
