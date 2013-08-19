#include <stdio.h>
#include <stdlib.h>

#include "mdi.h"

int main()
{
	int j, k, flag, n;
	long int num, i;
	mdi_ptr input1, input2, res;

	input1 = (mdi_ptr)malloc(sizeof(mdi));
	mdi_init(&input1);	

	input2 = (mdi_ptr)malloc(sizeof(mdi));
	mdi_init(&input2);

	res = (mdi_ptr)malloc(sizeof(mdi));
	mdi_init(&res);

	printf("1. Compute Sum of n mdi data\n2. Compute n!\n3. Compute 2^n\nEnter the serial number. Enter '4' to switch to another computation. Enter '-1' to exit:\n");

	while(scanf("%d", &flag))
	{
		if(flag == 5)
			continue;
		else if(flag == 1)
		{
			printf("Enter the number of mdi data to be added:\n");
			scanf("%d", &n);
			mdi_set_int(&res, 0);
			printf("Enter the mdi numbers:\n");
			while(n--)
			{
				input1 = read_mdi(input1);
				mdi_set(&input2, res);

				if(input1->digits >= input2->digits)
					mdi_add(&res, input1, input2);
				else
					mdi_add(&res, input2, input1);
			}
			print_mdi(res);
		}
			
		else if(flag == 2)
		{
			printf("Enter the number for which factorial is to be calculated:\n");
			scanf("%d", &n);
			mdi_init(&res);
			mdi_set_int(&res, 1);
			for(i=1; i<=n; i++)
			{
				input1->dp[0] = i;
				input1->digits = 1;
				mdi_set(&input2, res);
				mdi_mul(&res, input2, input1);
			}
			print_mdi(res);
		}

		else if(flag == 3)
		{
			printf("Enter the power of 2:\n");
			scanf("%d", &n);
			mdi_init(&res);
			mdi_set_int(&res, 1);
			input1->dp[0] = 2;
			input1->digits = 1;
			for(i=1; i<=n; i++)
			{
				mdi_set(&input2, res);
				mdi_mul(&res, input2, input1);
			}
			print_mdi(res);
		}
		
		else
			break;
	}
	return 0;
}
