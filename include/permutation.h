#ifndef _ZILIN_PERMUTATION_H_
#define _ZILIN_PERMUTATION_H_

typedef struct _Permutation {
	int n;
	int *permutaion;
} Permutation;

inline void Permute(int *dst, int *src, int n, Permutation pmt) {
	for (int i = 0; i < n; i++)
	{
		dst[i] = pmt.permutaion[src[i]];
	}
}

void Permutation_Cst(Permutation *pmt, int n);

#endif