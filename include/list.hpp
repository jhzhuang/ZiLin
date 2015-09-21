#ifndef _ZILIN_LIST_HPP_
#define _ZILIN_LIST_HPP_

#include "list.h"

namespace ZiLin {

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
			return (Body_Type *)((char *)(list_head)+offset);
		}
	private:
		unsigned int offset;
	};

}

#endif
