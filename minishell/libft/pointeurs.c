#include <stdio.h>

int main(void)
{
	int a;
	int *pa;
	int b;
	
	b = 54;
	a = 10;
	pa = &a;
	printf("Adresse pointe par pa = %p\n", pa);
	printf("Adresse de la variable a = %p\n", &a);
	printf("Valeur de la variable a = %d\n", a);
	printf("Valeur de la variable de a pointe par p = %d\n", *pa);
	*pa = 42;
	printf("Valeur modifie par l'utilisation du pointeur sur a = %d\n", a);
	*pa = b;
	printf("Adresse de p %p\n", pa);
	printf("Valeur de p %d\n", *pa);
	printf("Valeur de a %d\n", a);
	printf("-------------------------------------------\n");
	printf("ARITHMETIC OF POINTERS\n");
	printf("Adresse de ptr : %p\n", &pa);
	printf("Adresse de ptr + 1 : %p\n", (pa + 1));

	
	printf("-------------------------------------------\n");
	printf("POINTERS TO POINTERS\n");

	int x = 5;
	int *p = &x;
	*p = 6;
	int **q = &p;
	int ***r = &q;
	printf("%d valeur de *p \n", *p);
	printf("%p adresse de *q \n", *q);
	printf("%d valeur de **q \n", **q);
	printf("%p adresse de **r \n", **r);
	printf("%d valeur de ***r \n", ***r);
	***r = 10;
	printf("***r = 10 donc x = %d \n", x);
	**q = *p +2;
	printf("**q = *p + 2 donc x = %d \n", x);


	printf("-------------------------------------------\n");
	printf("POINTERS AND ARRAY\n");
	int tab[5] = {12, 5, 7, 8, 10};
	int i = 0;
	while (i < 5)
	{
		printf("%p = adresse de &tab[i]\n", &tab[i]);
		printf("%p = adresse de (tab + i)\n", (tab + i));
		printf("%d = valeur de tab[i]\n", tab[i]);
		printf("%d = valeur de *(tab + i)\n", *(tab + i));
		i++;
	}
	printf("si *p = tab ----> tab++ invalide mais p++ sera valide\n");
	int tab2[3] = {5, 7, 9};
	int *ptrtab2 = tab2;
	printf("%d\n", *ptrtab2);
	ptrtab2++;
	printf("%d = valeur de ptrtab2\n", *ptrtab2);
	printf("%d\n", *ptrtab2);
}

// #include <stdio.h>

// int sumofelement(int tab[], int size)
// {
// 	int i, sum = 0;
// 	for(i = 0; i < size; i++)
// 		sum += tab[i]; // tab[i] idem que *(tab + i)
// 	return sum;
// }

// int main()
// {
// 	int tab[] = {1,2,3,4,5};
// 	int size = sizeof(tab)/sizeof(tab[0]);
// 	int total = sumofelement(tab, size); // tab ou &tab[0]
// 	printf("SumOfElement = %d\n", total);
// 	printf("Main - Size of tab = %lu, size of tab[0] %lu\n", sizeof(tab), sizeof(tab[0]));
// }

// #include <stdio.h>
// #include <unistd.h>

// int ft_strlen(char c[])
// {
// 	int i = 0;
// 	while(*(c + i))
// 	{
// 		i++;
// 	}
// 	return i;

// }

// void	ft_printf(char *c) // idem char[]
// {
// 	int i = 0;
// 	while(*c) // c[i] idem --> *(c + i) --> *c
// 	{
// 		write(1, &c[i], 1);
// 		c++; // i++ ou c++ idem
// 	}
// }

// int main()
// {
// 	char c1[] = "JOHN";
// 	char *c2;
// 	c2 = c1;
// 	c2[0] = 'M';
// 	printf("%c\n", c2[0]);
// 	printf("%s\n", c1);
// 	printf("%d\n", ft_strlen(c1));
// 	ft_printf(c1);
// }

// #include <stdio.h>

// int main(void)
// {
// 	int b[2][3];
// 	int (*p)[3] = b;
// 	b[0][0] = 2;
// 	b[0][1] = 3;
// 	b[0][2] = 6;
// 	b[1][0] = 4;
// 	b[1][1] = 5;
// 	b[1][2] = 9;
// 	printf("-----------------TABLEAUX MULTI DIMENSIONEL -----------------\n");
// 	printf("Tableau b[2][3]\n");
// 	printf("Lets go to b[0][0]\n\n");
// 	printf("Adresse de b ou &b = %p\n", b);
// 	printf("Adresse de b[0] ou &b[0] = %p\n", b[0]);
// 	printf("Adresse de &b[0][0] = %p\n", &b[0][0]);
// 	printf("Valeur de **b = %d\n", **b);
// 	printf("Valeur de *b[0] = %d\n", *b[0]);
// 	printf("Valeur de b[0][0] = %d\n", b[0][0]);
// 	printf("----------------------------------------------------------------\n");
// 	printf("Lets go to b[0][1]\n\n");
// 	printf("Adresse de (*b + 1) = %p\n", (*b + 1));
// 	printf("Adresse de b[0] + 1 = %p\n", b[0] + 1);
// 	printf("Adresse de &b[0][1] = %p\n", &b[0][1]);
// 	printf("Valeur de *(*b + 1) = %d\n", *(*b + 1));
// 	printf("Valeur de *b[0] + 1 = %d\n", *b[0] + 1);
// 	printf("Valeur de b[0][1] = %d\n", b[0][1]);
// 	printf("----------------------------------------------------------------\n");
// 	printf("Lets go to b[1][0]\n\n");
// 	printf("Adresse de b + 1 = %p\n", b + 1);
// 	printf("Adresse de &b[1] = %p\n", &b[1]);
// 	printf("Adresse de &b[1][0] = %p\n", &b[1][0]);
// 	printf("Valeur de **(b + 1) = %d\n", **(b + 1));
// 	printf("Valeur de *b[1] = %d\n", *b[1]);
// 	printf("Valeur de b[1][0] = %d\n\n", b[1][0]);
// 	printf("b[i][j] == *(b[i] + j) == *(*(b + i) + j)\n\n");

// 	printf("-----------------TABLEAUX 3 DIMENSION -----------------\n\n");
// 	printf("Tableau c[3][2][2]\n");
// 	int c[3][2][2] = {{{2,5},{7,9}},{{3,4},{6,1}},{{0,8},{11, 13}}};
// 	printf("Adresse de c = %p\n", c);
// 	printf("Adresse de *c = %p\n", *c);
// 	printf("Adresse de c[0] = %p\n", c[0]);
// 	printf("Adresse de &c[0][0] = %p\n", &c[0][0]);
// 	printf("Adresse de &c[0][0][0] = %p\n", &c[0][0][0]);


// }

// #include <stdio.h>

// void	func(int *a) //argument : 1-D tableau d'entier
// 			(int (*b)[3])	ou (int b[][3])	// argument : 2-D
// 			(int c[][2][2]) ou (int (*c)[2][2])
// {

// }

// int main() 
// {
// 	int c[3][2][2] = {{{2,5},{7,9}},{{3,4},{6,1}},{{0,8},{11, 13}}}; // c returns int(*)[2][2]
// 	int b[2][3] = {{2,4,6},{5,7,8}}; // b returns int (*)[3]
// 	int a[2] = {1,2};
// 	func(a) // a return int*
// }

// #include <stdlib.h>
// #include <stdio.h>

// int main()
// {
// 	int *p;

// 	p = (int*)malloc(50 * sizeof(int));
// 	printf("%p\n", p);
// 	*p = 2; // same as p[0]
// 	*(p + 1) = 5; // same as p[1]
// 	printf("%d\n", *p);
// 	printf("%d\n", *(p + 1));
// }

// #include <stdlib.h>
// #include <stdio.h>

// int main()
// {
// 	int n;
// 	int i;

// 	i = 0;
// 	printf("Enter a size of array\n"); 
// 	scanf("%d", &n);
// 	int *p;

// 	p = (int*)malloc(n * sizeof(int)); // dynamic allocated array

// 	while(i < n)
// 	{
// 		p[i] = i+1;
// 		printf("%d, ", p[i]);
// 		i++;
// 	}

// }
