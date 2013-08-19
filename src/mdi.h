#ifndef _MDI_H
#define _MDI_H

#define true 1
#define false 0

typedef struct
{
	unsigned int *dp;
	int ss;
	unsigned int digits;
}mdi;

typedef mdi* mdi_ptr;
typedef mdi** mdi_ptr_ptr;

/**************************************Function Prototypes***********************************************/

void mdi_init(mdi_ptr_ptr x); 					// Initialises the data-type.

mdi_ptr read_mdi(mdi_ptr x); 					// Reads a sequence of ASCII code of digits

int print_mdi(mdi_ptr x); 					// Prints a sequence of ASCII code of digits
	
void mdi_set(mdi_ptr_ptr dst, mdi_ptr src);			// dst<--src

void mdi_set_int(mdi_ptr_ptr dst, long int src); 		// dst <-- src

void mdi_add(mdi_ptr_ptr dst, mdi_ptr src1, mdi_ptr src2); 	// dst <-- src1 + src2

void mdi_mul(mdi_ptr_ptr dst, mdi_ptr src1, mdi_ptr src2); 	// dst <-- src1 * src2

void mdi_div(mdi_ptr_ptr dst1, mdi_ptr_ptr dst2, mdi_ptr src1, mdi_ptr src2);

void mdi_quo(mdi_ptr dst, mdi_ptr src1, mdi_ptr src2); 		// dst <-- src1 / src2

void mdi_rem(mdi_ptr_ptr dst, mdi_ptr src1, mdi_ptr src2); 		// dst <-- src1 % src2

int mdi_cmp_zero(mdi_ptr arg1);					// returns 1 if arg1 = 0
								// returns 0 if arg1 != 0


#endif
