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

	bool List_Is_Empty(List *list) {
		if (list == list->prev && list == list->next)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void List_Insert(List *list, List_Head *node) {
		List *last = list->prev;

		last->next = node;
		node->prev = last;
		node->next = list;
		list->prev = node;
	}

	void List_Delete(List *list, List_Head *node) {
		node->prev->next = node->next;
		node->next->prev = node->prev;
		node->prev = 0;
		node->next = 0;
	}

	template<typename List_Body>
	class List_Node {
	public:
		typedef List_Body Body_Type;
	public:
		List_Head head;
		List_Body body;
	};

	template<typename Node_Type>
	class List_Fetch {
	public:
		typedef typename Node_Type::Body_Type Body_Type;
	public:
		List_Fetch(void) {
			offset = (unsigned int)(&(((Node_Type *)(0))->body)) - (unsigned int)(&(((Node_Type *)(0))->head));
		}

		Body_Type *Fetch(List_Head *list_head) {
			return (Body_Type *)((char *)(list_head) + offset);
		}
	private:
		unsigned int offset;
	};
}

#endif