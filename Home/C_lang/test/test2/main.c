# include <stdio.h>
//typedef void (*choose[])(int *, int *, int *, int *) = {no_hope, tong, tang, ket_thuc} ;
void tong(int *a, int *b, int *c, int *d)
{
	printf("tong la %d", *a+*b+*c+*d);
}

void tang(int *a, int *b, int *c, int *d)
{
    int tang[4];
	printf("tang dan");
}

void ket_thuc(int *a, int *b, int *c, int *d)
{
	printf("ket thuc");
}

void no_hope(int *a, int *b, int *c, int *d) 
{
    printf("khong co lua chon");
}

int main()
{
	void (*choose[])(int *, int *, int *, int *) = {no_hope, tong, tang, ket_thuc} ;
	int a[4];
	int b=4;
	int *n=&b;
	
//void (*choose[])(int *no_hope, int *tong, int *tang, int *ket_thuc) ;

	printf("nhap vao cac so :\n");
	for(int i=0; i<4; i++)
	{
		printf("a[%d] = ",i);
		scanf("%d",&a[i]);
	}
	
	int number;
	printf("sap xep tu lon toi nho nhan phim 1\n");
	printf("sap xep tu nho toi lon nhan phim 2\n");
	printf("ket thuc nhan phim 3\n");
	scanf("%d", &number);
	
	(*choose[number])(&a[0], &a[1], &a[2], &a[3]);
	
	
	return 0;
}
