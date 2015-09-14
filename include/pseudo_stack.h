#ifndef _ZILIN_PSEUDO_STACK_H_
#define _ZILIN_PSEUDO_STACK_H_

#include "list.h"

namespace ZiLin {
        
        typedef char * PStack_Page;
        
        List_Head * Get_Page_List_Head(PStack_Page *page) {
                return (List_Head *)(page);
        }
        
        unsigned int Get_Page_Size(PStack_Page *page) {
                return *((int *)(page + sizeof(List_Head)));
        }
        
        unsigned int Get_Page_HWM(PStack_Page *page) {
                return *((int *)(page + sizeof(List_Head)) + 1);
        }
}

#endif
