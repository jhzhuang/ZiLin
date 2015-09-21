#include "pseudo_stack.h"

namespace ZiLin_Test {

	using namespace ZiLin;

	typedef struct _S1 {
		int size;
		int *arr;
	} S1;

	void Test() {
		PStack_List_Initial();
		PStack_Id id = PStack_List_Add_PStack();
		S1 *s1 = (S1 *)PStack_List_Allocate(sizeof(S1), id);
		s1->size = 4;
		s1->arr = (int *)PStack_List_Allocate(s1->size * sizeof(int), id);
		for (int i = 0; i < s1->size; i++)
		{
			s1->arr[i] = i;
		}
		PStack_List_Delete_PStack(id);
	}
}

int main(int argc, char **argv) {
	ZiLin_Test::Test();
	return 0;
}