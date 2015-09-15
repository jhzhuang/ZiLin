#include "pseudo_stack.h"

namespace ZiLin {
	
	static int PStack_Page_Size = 4 * 1024 * 1024;
	
	static List PStack_Page_List = {0, 0};
	
	PStack_Page * PStack_Page_Initial(void) {
		PStack_Page *page = new PStack_Page;
		page->list_head = {0, 0};
		page->size = PStack_Page_Size;
		page->hwm = 0;
		page->page = new char[PStack_Page_Size];
	}
	
	void PStack_Page_Delete(PStack_Page *page) {
		page->hwm = 0;
		delete [] page->page;
		delete page;
	}
	
}
