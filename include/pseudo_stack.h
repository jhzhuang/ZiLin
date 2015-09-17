#ifndef _ZILIN_PSEUDO_STACK_H_
#define _ZILIN_PSEUDO_STACK_H_

#include "list.h"

namespace ZiLin {
        
        typedef unsigned int PStack_Id;
        
        void PStack_List_Initial(void);
        
        PStack_Id PStack_List_Add_PStack(void);
        
        void PStack_List_Delete_PStack(PStack_Id id);
        
        char *PStack_List_Allocate(PStack_Id id, unsigned int obj_size);
}

#endif
