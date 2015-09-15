#include "pseudo_stack.h"

namespace ZiLin {
	
	static int PStack_Page_Size = 4 * 1024 * 1024;
	
	static List PStack_List = {0, 0};
	
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
        
        static unsigned int PStack_Page_Offset = (unsigned int)(&(((PStack_Page *)(0))->list_head));
	
	void PStack_Add_Page(PStack *stack) {
		PStack_Page *page = new PStack_Page;
		List_Insert(stack->page_list, page->list_head);
		page->size = PStack_Page_Size;
		page->hwm = 0;
		page->page = new char[PStack_Page_Size];
	}
	
	void PStack_Free_Page(PStack *stack) {
		while (!List_Is_Empty(stack->page_list)) {
			PStack_Page *last_page = (PStack_Page *)((char *)(stack->page_list->prev) - PStack_Page_Offset);
			last_page->hwm = 0;
			delete [] last_page->page;
			List_Delete(stack->page_list, &(last_page->list_head));
			delete last_page;
		}
	}
	
	static inline char * PStack_Page_Allocate(PStack_Page *page, unsigned int obj_size) {
        	unsigned int old_hwm = page->hwm;
        	page->hwm = old_hwm + obj_size;
        	return page->page + old_hwm;
        }
        
        
}
