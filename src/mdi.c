#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "mdi.h"

int BASE = 65536;

void reverse(unsigned int *a, unsigned int digits)
{
	int i, j;
	unsigned int b[digits];

	for(i=digits-1, j=0; i>=0; i--, j++)
		b[i] = a[j];
	for(i=0; i<digits; i++)
		a[i] = b[i];
}

void mdi_init(mdi_ptr_ptr x)
{
	(*x)->ss = false;		//'0'  if positive and '1' if negative. Initially, the number is taken positive.
	(*x)->digits = 0;		//number of digits
	
	(*x)->dp = (unsigned int*)malloc(sizeof(unsigned int));
	(*x)->dp[0] = 0;		//the multiprecision number
}

mdi_ptr read_mdi(mdi_ptr x)
{
	unsigned int i, len, val;
	char* s, c;
	mdi_ptr ten, tmp1, tmp2, tmp3;

	s = (char*)malloc(100*sizeof(char));
	scanf("%s", s);

	len = strlen(s);

	ten = (mdi_ptr)malloc(sizeof(mdi));
	mdi_init(&ten);
	mdi_set_int(&ten, 10);

	tmp1 = (mdi_ptr)malloc(sizeof(mdi));
	mdi_init(&tmp1);
	mdi_set_int(&tmp1, 0);

	tmp2 = (mdi_ptr)malloc(sizeof(mdi));
	mdi_init(&tmp2);

	tmp3 = (mdi_ptr)malloc(sizeof(mdi));
	mdi_init(&tmp3);
	
	if(s[0] == '-')
	{
		x->ss = true;
		i = 1;
	}
	else
		i = 0;

	for(i=0; i<len; i++)
	{
		mdi_mul(&tmp2, tmp1, ten);
		val = (int)s[i] - 48;
		c = s[i];
		tmp3->dp[0] = val;
		tmp3->digits = 1;
		if(tmp2->digits >= tmp1->digits)
			mdi_add(&tmp1, tmp2, tmp3);
		else
			mdi_add(&tmp1, tmp3, tmp2);
	}

	mdi_set(&x, tmp1);
}

int print_mdi(mdi_ptr x)
{
	BASE = 10000;
	int i, j, dig;
	unsigned long int val;
	mdi_ptr var1, var2, var3, mod, res;	

	mod = (mdi_ptr)malloc(sizeof(mdi));
	mdi_init(&mod);
	mdi_set_int(&mod, 65536);
	
	var1 = (mdi_ptr)malloc(sizeof(mdi));
	mdi_init(&var1);
	mdi_set_int(&var1, 0);	

	var2 = (mdi_ptr)malloc(sizeof(mdi));
	mdi_init(&var2);

	var3 = (mdi_ptr)malloc(sizeof(mdi));
	mdi_init(&var3);

	dig = x->digits;
	
	for(i=dig-1; i>=0; i--)
	{
		mdi_mul(&var2, var1, mod);
		val = x->dp[i];
		var3->dp[0] = val;
		var3->digits = 1;
		if(var2->digits >= var1->digits)
			mdi_add(&var1, var2, var3);
		else
			mdi_add(&var1, var3, var2);
	}

	dig = var1->digits;

	if(x->ss == true)
		printf("-");

	reverse(var1->dp, var1->digits);

	printf("%d", var1->dp[0]);
	for(i=1; i<dig; i++)
	{
		if(var1->dp[i] == 0)
		{
			printf("0000");
			continue;
		}
		if(var1->dp[i]>=1 && var1->dp[i]<=9)
			printf("000");
		if(var1->dp[i]>=10 && var1->dp[i]<=99)
			printf("00");
		if(var1->dp[i]>=100 && var1->dp[i] <= 999)
			printf("0"); 
		printf("%d", var1->dp[i]);
	}

	printf("\n");
	BASE = 65536;
}

void mdi_set(mdi_ptr_ptr dst, mdi_ptr src)
{
	int i;

	(*dst)->dp = (unsigned int*)malloc((src->digits)*sizeof(unsigned int));
	
	for(i=0; i<src->digits; i++)
		(*dst)->dp[i] = src->dp[i];

	(*dst)->digits = src->digits;
	(*dst)->ss = src->ss;
}

void mdi_set_int(mdi_ptr_ptr dst, long int src)
{
	int *temp, i;
	long int val;

	if(src%65536 != 0)
		(*dst)->dp = (unsigned int*)malloc(4*sizeof(unsigned int));

	if(src<0)
	{
		(*dst)->ss = true;
		val = (-1)*src;
	}
	else
		val = src;
	i = 0;

	if(val == 0)
	{
		(*dst)->dp[0] = 0;
		(*dst)->digits++;
	}
	while(val != 0)
	{
		(*dst)->dp[i] = val%BASE;
		val = val/BASE;
		(*dst)->digits++;
		i++;
	}
}

void mdi_add(mdi_ptr_ptr dst, mdi_ptr src1, mdi_ptr src2)
{
	unsigned int l, k, i, val, cy;
	unsigned int *temp;

	k = src1->digits;
	l = src2->digits;

	(*dst)->dp = (unsigned int*)malloc((k+1)*sizeof(unsigned int));

	cy = 0;
	for(i=0; i<l; i++)
	{
		val = src1->dp[i] + src2->dp[i] + cy;
		(*dst)->dp[i] = val % BASE;
		cy = val/BASE;
	}
	for(i=l; i<k; i++)
	{
		val = src1->dp[i] + cy;
		(*dst)->dp[i] = val % BASE;
		cy = val/BASE;
	}
	if(cy == 1)
	{
		(*dst)->digits = k+1;
		(*dst)->dp[k] = 1;
	}
	else
		(*dst)->digits = k;
}

void mdi_mul(mdi_ptr_ptr dst, mdi_ptr src1, mdi_ptr src2)
{
	int l, k, i, j;
	unsigned long int val, cy;
	
	k = src1->digits;
	l = src2->digits;

	(*dst)->dp = (unsigned int*)malloc((k+l)*sizeof(unsigned int));

	for(i=0; i<k+l; i++)
		(*dst)->dp[i] = 0;

	for(i=0; i<k; i++)
	{
		cy = 0;	
		for(j=0; j<l; j++)
		{
			val = src1->dp[i]*src2->dp[j] + (*dst)->dp[i+j] + cy;
			(*dst)->dp[i+j] = val % BASE;
			cy = val/BASE;
		}
		(*dst)->dp[i+l] = cy;
	}
	if((*dst)->dp[k+l-1] > 0)
		(*dst)->digits = k + l;
	else
		(*dst)->digits = k + l - 1;
}

void mdi_div(mdi_ptr_ptr dst1, mdi_ptr_ptr dst2, mdi_ptr src1, mdi_ptr src2)
{
	int i, j, k, l;
	unsigned long int t, cy;

	k = src1->digits;
	l = src2->digits;

	(*dst1)->dp = (unsigned int*)malloc((k+1)*sizeof(unsigned int));
	(*dst2)->dp = (unsigned int*)malloc((k+1)*sizeof(unsigned int));

	for(i=0; i<k; i++)
		(*dst2)->dp[i] = src1->dp[i];
	(*dst2)->dp[k] = 0;	

	for(i=k-l; i>=0; i--)
	{
		t = ((*dst2)->dp[i+l]*BASE + (*dst2)->dp[i+l-1])/src2->dp[l-1];
		
		if(t >= BASE)
			(*dst1)->dp[i] = BASE - 1;
		else
			(*dst1)->dp[i] = t;
		cy = 0;

		for(j=0; j<l; j++)
		{
			t = (*dst2)->dp[i+j] - (*dst1)->dp[i]*src2->dp[j] + cy;
			(*dst2)->dp[i+j] = t%BASE;
			cy = t/BASE;
		}

		(*dst2)->dp[i+l] += cy;
		
		while((*dst2)->dp[i+l] < 0)
		{
			cy = 0;

			for(j=0; j<l; j++)
			{
				t = (*dst2)->dp[i+j] + src2->dp[j] + cy;
				(*dst2)->dp[i+j] = t%BASE;
				cy = t/BASE;
			}
			(*dst2)->dp[i+l] += cy;
			(*dst1)->dp[i]--;
		}
	}
	(*dst1)->digits = k-l+1;
	(*dst2)->digits = 0;
	i=0;
	while((*dst2)->dp[i] != 0)
	{
		if(i>k)
			break;
		(*dst2)->digits++;
		i++;
	}
}

void mdi_quo(mdi_ptr dst, mdi_ptr src1, mdi_ptr src2)
{
	mdi_ptr remainder;
	remainder = (mdi_ptr)malloc(sizeof(mdi));

	mdi_div(&dst, &remainder, src1, src2);
}

void mdi_rem(mdi_ptr_ptr dst, mdi_ptr src1, mdi_ptr src2)
{
	mdi_ptr quo;
	quo = (mdi_ptr)malloc(sizeof(mdi));

	mdi_div(&quo, dst, src1, src2);
}

int mdi_cmp_zero(mdi_ptr arg1)
{
	int i, k, flag=1;
	k = arg1->digits;
	
	for(i=0; i<k; i++)
	{
		if(arg1->dp[i] != 0)
		{
			flag = 0;
			break;
		}
	}
	
	return flag;
}
