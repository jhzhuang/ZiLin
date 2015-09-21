#ifndef _ZILIN_LIST_H_
#define _ZILIN_LIST_H_

namespace ZiLin {

	typedef struct _List_Head {
		struct _List_Head *prev;
		struct _List_Head *next;
	} List_Head;

	typedef List_Head List;

	inline void List_Initial(List *list) {
		list->prev = list;
		list->next = list;
	}

	inline bool List_Is_Empty(List *list) {
		if (list == list->prev && list == list->next)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	inline void List_Insert(List *list, List_Head *node) {
		List *last = list->prev;

		last->next = node;
		node->prev = last;
		node->next = list;
		list->prev = node;
	}

	inline void List_Delete(List *list, List_Head *node) {
		node->prev->next = node->next;
		node->next->prev = node->prev;
		node->prev = 0;
		node->next = 0;
	}

}

#endif
