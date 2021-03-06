#include "pseudo_stack.h"

namespace ZiLin {

	typedef struct _PStack_Page {
		List_Head list_head;
		unsigned int size;
		unsigned int hwm;
		char *page;
	} PStack_Page;

	typedef struct _PStack {
		List_Head list_head;
		List page_list;
		unsigned int stack_id;
	} PStack;

	static List PStack_List = { 0, 0 };

	static unsigned int PStack_Page_Size = 4 * 1024 * 1024;

	static unsigned int PStack_Page_Offset = (unsigned int)(&(((PStack_Page *)(0))->list_head));

	static unsigned int PStack_Offset = (unsigned int)(&(((PStack *)(0))->list_head));

	PStack *PStack_List_Search(unsigned int id);

	void PStack_Add_Page(PStack *pstack);

	void PStack_Free_Page(PStack *pstack);

	static inline PStack *PStack_Fetch(List_Head *list_head) {
		return (PStack *)((char *)list_head - PStack_Offset);
	}

	static inline PStack_Page *PStack_Page_Fetch(List_Head *list_head) {
		return (PStack_Page *)((char *)list_head - PStack_Page_Offset);
	}

	static inline char * PStack_Page_Allocate(PStack_Page *page, unsigned int obj_size) {
		unsigned int old_hwm = page->hwm;
		page->hwm = old_hwm + obj_size;
		return page->page + old_hwm;
	}

	void PStack_List_Initial(void) {
		List_Initial(&PStack_List);
	}

	unsigned int PStack_List_Add_PStack() {
		static unsigned int id = 0;
		PStack *pstack = new PStack;
		id = id + 1;
		List_Insert(&PStack_List, &(pstack->list_head));
		List_Initial(&(pstack->page_list));
		pstack->stack_id = id;
		return id;
	}

	void PStack_List_Delete_PStack(unsigned int id) {
		PStack *pstack = PStack_List_Search(id);
		if (0 != pstack)
		{
			PStack_Free_Page(pstack);
			List_Delete(&PStack_List, &(pstack->list_head));
			delete pstack;
		}
		else
		{
			return;
		}
	}

	PStack *PStack_List_Search(unsigned int id) {
		if (List_Is_Empty(&PStack_List)) {
			return 0;
		}
		else {
			PStack *pstack = PStack_Fetch(PStack_List.next);
			while (&(pstack->list_head) != &PStack_List && pstack->stack_id != id) {
				pstack = PStack_Fetch(pstack->list_head.next);
			}
			if (&(pstack->list_head) == &PStack_List) {
				return 0;
			}
			else {
				return pstack;
			}
		}
	}

	char *PStack_List_Allocate(unsigned int obj_size, unsigned int id) {
		PStack *pstack = PStack_List_Search(id);
		if (0 == pstack) {
			return 0;
		}
		else if (PStack_Page_Size < obj_size) {
			return 0;
		}
		else {
			PStack_Page *last_page = PStack_Page_Fetch(pstack->page_list.prev);
			if (last_page->hwm + obj_size < last_page->size) {
				PStack_Page_Allocate(last_page, obj_size);
			}
			else {
				PStack_Add_Page(pstack);
				last_page = PStack_Page_Fetch(pstack->page_list.prev);
				PStack_Page_Allocate(last_page, obj_size);
			}
		}
	}

	void PStack_Add_Page(PStack *pstack) {
		PStack_Page *page = new PStack_Page;
		List_Insert(&(pstack->page_list), &(page->list_head));
		page->size = PStack_Page_Size;
		page->hwm = 0;
		page->page = new char[PStack_Page_Size];
	}

	void PStack_Free_Page(PStack *pstack) {
		while (!List_Is_Empty(&(pstack->page_list))) {
			PStack_Page *last_page = PStack_Page_Fetch(pstack->page_list.prev);
			last_page->hwm = 0;
			delete[] last_page->page;
			List_Delete(&(pstack->page_list), &(last_page->list_head));
			delete last_page;
		}
	}

}
