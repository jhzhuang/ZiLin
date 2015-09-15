#ifndef _ZILIN_PSEUDO_STACK_H_
#define _ZILIN_PSEUDO_STACK_H_

#include "list.h"

namespace ZiLin {
        
        typedef struct _PStack_Page {
        	List_Head list_head;
        	unsigned int size;
        	unsigned int hwm;
        	char *page;
        } PStack_Page;
        
        PStack_Page * PStack_Page_Initial(void);
        
        void PStack_Page_Delete(PStack_Page *page);
        
        inline List_Head * PStack_Page_List_Head(PStack_Page *page) {
                return &(page->list_head);
        }
        
        inline unsigned int PStack_Page_Size(PStack_Page *page) {
                return page->size;
        }
        
        inline unsigned int PStack_Page_HWM(PStack_Page *page) {
                return page->hwm;
        }
        
        inline char * PStack_Page_Allocate(PStack_Page *page, unsigned int obj_size) {
        	unsigned int old_hwm = page->hwm;
        	page->hwm = old_hwm + obj_size;
        	return page->page + old_hwm;
        }
}

#endif
