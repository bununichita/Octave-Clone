//# Copyright Bunu Nichita-Adrian 313CA 2022-2023
#include <stdio.h>
#include <stdlib.h>
#define MOD (10 * 10 * 10 * 10 + 7)

int alocare(int ****a, int **v_lin, int **v_col, int **sum, int m_prec)
{
	//Alocam un nou strat pentru matricea a, si vectorii aferenti
	int ***aux;
	aux = realloc(*a, (m_prec + 1) * sizeof(int **));
		if (!aux)
			return 1;
	*a = aux;
	int *aux_lin, *aux_col;
	aux_lin = realloc(*v_lin, (m_prec + 1) * sizeof(int));
		if (!aux_lin)
			return 1;
		aux_col = realloc(*v_col, (m_prec + 1) * sizeof(int));
		if (!aux_col)
			return 1;
	*v_lin = aux_lin;
	*v_col = aux_col;
	int *aux_sum;
		aux_sum = realloc(*sum, (m_prec + 1) * sizeof(int));
		if (!aux_sum)
			return 1;
	*sum = aux_sum;
	return 0;
}

int suma(int ***a, int *v_lin, int *v_col, int i_mat)
{
	//Calculam suma matricei cu indicele "i_mat"
	int i, j;
	long long sum = 0;
	for (i = 0; i < v_lin[i_mat]; i++)
		for (j = 0; j < v_col[i_mat]; j++)
			sum += a[i_mat][i][j];
	sum %= MOD;
	if (sum < 0)
		sum += MOD;
	return sum;
}

int citire(int ***a, int *v_lin, int *v_col, int *sum, int m_prec)
{
	//Actualizam vectorii de linii si coloane
	int lin, col;
	scanf("%d %d", &lin, &col);
	v_lin[m_prec] = lin;
	v_col[m_prec] = col;
	int **aux;
	aux = malloc(lin * sizeof(int *));
	if (!aux)
		return 1;
	for (int i = 0; i < lin; i++) {
		aux[i] = malloc(col * sizeof(int));
		if (!aux[i])
			return 1;
	}
	a[m_prec] = aux;
	//Citim valorile noului strat de matrice
	for (int i = 0; i < lin; i++)
		for (int j = 0; j < col; j++)
			scanf("%d", &a[m_prec][i][j]);
	//Pentru eficienta actualizam vectorul de suma la fiecare adaugare
	sum[m_prec] = suma(a, v_lin, v_col, m_prec);
	return 0;
}

int inmultire(int **a, int **b, int lin)
{
	//Functie ce inmulteste doua matrice patratice, de aceleasi dimensiuni
	//Matricea a suporta modificarile rezultatului
	int i, j, k, **produs;
	produs = calloc(lin, sizeof(int *));
	if (!produs)
		return 1;
	for (i = 0; i < lin; i++) {
		*(produs + i) = calloc(lin, sizeof(long long));
		if (!(*(produs + i)))
			return 1;
	}
	for (i = 0; i < lin; i++)
		for (j = 0; j < lin; j++)
			for (k = 0; k < lin; k++)
				produs[i][j] += a[i][k] * b[k][j];
	for (i = 0; i < lin; i++)
		for (j = 0; j < lin; j++) {
			produs[i][j] %= MOD;
			if (produs[i][j] < 0)
				produs[i][j] += MOD;
		}
	for (i = 0; i < lin; i++)
		for (j = 0; j < lin; j++)
			a[i][j] = produs[i][j];
	for (i = 0; i < lin; i++)
		free(produs[i]);
	free(produs);
	return 0;
}

void comanda_2(int *v_lin, int *v_col, int m_prec, int i_mat)
{
	//Afisam dimensiunile matricei cu indicele "i_mat"
	if (i_mat < m_prec && (i_mat > -1))
		printf("%d %d\n", v_lin[i_mat], v_col[i_mat]);
	else
		printf("No matrix with the given index\n");
}

void comanda_3(int ***a, int *v_lin, int *v_col, int m_prec, int i_mat)
{
	//Afisam matricea cu indicele "i_mat"
	int i, j;
	if (i_mat < m_prec && (i_mat > -1))
		for (i = 0; i < v_lin[i_mat]; i++) {
			for (j = 0; j < v_col[i_mat]; j++)
				printf("%d ", a[i_mat][i][j]);
			printf("\n");
		}
	else
		printf("No matrix with the given index\n");
}

int comanda_4(int ****a, int *v_lin, int *v_col, int i_mat, int m_prec)
{
	int *aux1, *aux2, *r_lin, *r_col, nr_lin, nr_col;
	int **aux_mat, i, j;
	scanf("%d", &nr_lin);
	aux1 = calloc(nr_lin, sizeof(int));
	if (aux1)
		r_lin = aux1;
	else
		return 1;
	for (i = 0; i < nr_lin; i++)
		scanf("%d", &r_lin[i]);
	scanf("%d", &nr_col);
	aux2 = calloc(nr_col, sizeof(int));
	if (aux2)
		r_col = aux2;
	else
		return 1;
	for (i = 0; i < nr_col; i++)
		scanf("%d", &r_col[i]);
	if (i_mat < m_prec && (i_mat > -1)) {
		aux_mat = calloc(nr_lin, sizeof(int *));
		if (aux_mat)
			for (i = 0; i < nr_lin; i++)
				*(aux_mat + i) = calloc(nr_col, sizeof(int));
		else
			return 1;
		//Redimensionam matricea
		for (i = 0; i < nr_lin; i++)
			for (j = 0; j < nr_col; j++)
				aux_mat[i][j] = (*a)[i_mat][r_lin[i]][r_col[j]];
		for (i = 0; i < v_lin[i_mat]; i++)
			free((*a)[i_mat][i]);
		free((*a)[i_mat]);
		*(*a + i_mat) = aux_mat;
		//Actualizam vectorii de linii si coloane
		v_lin[i_mat] = nr_lin;
		v_col[i_mat] = nr_col;
	} else {
		printf("No matrix with the given index\n");
		free(r_lin);
		free(r_col);
		return 2;
	}
	free(r_lin);
	free(r_col);
	return 0;
}

int comanda_5(int ****a, int **v_lin, int **v_col, int **sum, int m_prec)
{
	int i_mat1, i_mat2;
	scanf("%d %d", &i_mat1, &i_mat2);
	if (i_mat1 < m_prec && i_mat2 < m_prec && (i_mat1 > -1) && (i_mat2 > -1)) {
		//Verificam posibilitatea inmultirii matricelor d. p. d. v. matematic
		if ((*v_col)[i_mat1] != (*v_lin)[i_mat2]) {
			printf("Cannot perform matrix multiplication\n");
			return 0;
		}
		//Alocam spatiu pentru noua matrice
		if (alocare(a, v_lin, v_col, sum, m_prec))
			return 1;
		int i, j, k;
		//aux1 = prima matrice, aux2 = a doua matrice
		int **aux1, **aux2, **produs;
		aux1 = (*a)[i_mat1];
		aux2 = (*a)[i_mat2];
		produs = calloc((*v_lin)[i_mat1], sizeof(int *));
		if (produs)
			for (i = 0; i < (*v_lin)[i_mat1]; i++) {
				*(produs + i) = calloc((*v_col)[i_mat2], sizeof(int));
				if (!(*(produs + i)))
					return 1;
			}
		else
			return 1;
		//Completam matricea produs
		for (i = 0; i < (*v_lin)[i_mat1]; i++)
			for (j = 0; j < (*v_col)[i_mat2]; j++)
				for (k = 0; k < (*v_col)[i_mat1]; k++) {
					produs[i][j] += aux1[i][k] * aux2[k][j];
					produs[i][j] %= MOD;
					if (k == (*v_col)[i_mat1] - 1 && produs[i][j] < 0)
						produs[i][j] += MOD;
				}
		//Pointam la matricea produs
		(*a)[m_prec] = produs;
		//Actualizam vectorii de linii si coloane si suma pt noua matrice
		(*v_lin)[m_prec] = (*v_lin)[i_mat1];
		(*v_col)[m_prec] = (*v_col)[i_mat2];
		(*sum)[m_prec] = suma(*a, *v_lin, *v_col, m_prec);
		return 2;
	}
	printf("No matrix with the given index\n");
	return 0;
}

int comanda_6(int ***a, int *v_lin, int *v_col, int *sum, int m_prec)
{
	//Folosim un algoritm de sortare pt vectorul de sume si odata cu
	//sumele schimbam si matricele intre ele impreuna cu vectorii de
	//linii si coloane
	int i, j, swap1;
	for (i = 0; i < m_prec - 1; i++)
		for (j = 0; j < m_prec - i - 1; j++)
			if (sum[j] > sum[j + 1]) {
				swap1 = sum[j];
				sum[j] = sum[j + 1];
				sum[j + 1] = swap1;
				int **swap2 = a[j];
				a[j] = a[j + 1];
				a[j + 1] = swap2;
				swap1 = v_lin[j];
				v_lin[j] = v_lin[j + 1];
				v_lin[j + 1] = swap1;
				swap1 = v_col[j];
				v_col[j] = v_col[j + 1];
				v_col[j + 1] = swap1;
			}
	return 0;
}

int comanda_7(int ****a, int *v_lin, int *v_col, int i_mat, int m_prec)
{
	//Transpunem matricea "i_mat" si o memoram in acelasi loc
	int aux1;
	int **aux_mat, i, j;
	if (i_mat < m_prec && (i_mat > -1)) {
		aux_mat = calloc(v_col[i_mat], sizeof(int *));
		if (aux_mat)
			for (i = 0; i < v_col[i_mat]; i++)
				*(aux_mat + i) = calloc(v_lin[i_mat], sizeof(int));
		else
			return 1;
		for (i = 0; i < v_col[i_mat]; i++)
			for (j = 0; j < v_lin[i_mat]; j++)
				aux_mat[i][j] = (*a)[i_mat][j][i];
		for (i = 0; i < v_lin[i_mat]; i++)
			free((*a)[i_mat][i]);
		free((*a)[i_mat]);
		*(*a + i_mat) = aux_mat;
		aux1 = v_lin[i_mat];
		v_lin[i_mat] = v_col[i_mat];
		v_col[i_mat] = aux1;
	} else {
		printf("No matrix with the given index\n");
	}
	return 0;
}

int comanda_8(int ****a, int *v_lin, int *v_col, int m_prec, int *sum)
{
	//Ridicare la putere in timp logaritmic
	int i_mat, putere;
	scanf("%d %d", &i_mat, &putere);
	if (i_mat >= m_prec || i_mat < 0) {
		printf("No matrix with the given index\n");
		return 0;
	}
	if (putere < 0) {
		printf("Power should be positive\n");
		return 0;
	}
	if (v_lin[i_mat] != v_col[i_mat]) {
		printf("Cannot perform matrix multiplication\n");
		return 0;
	}
	//aux = matricea pe care o ridicam la putere
	//produs = rezultatul ridicarii la putere
	int **produs, **aux, i, j;
	//Alocare aux
	aux = calloc(v_lin[i_mat], sizeof(int *));
	if (!aux)
		return 1;
	for (i = 0; i < v_lin[i_mat]; i++) {
		*(aux + i) = calloc(v_lin[i_mat], sizeof(int));
		if (!(*(aux + i)))
			return 1;
	}
	//Alocare produs
	produs = calloc(v_lin[i_mat], sizeof(int *));
	if (!produs)
		return 1;
	for (i = 0; i < v_lin[i_mat]; i++) {
		*(produs + i) = calloc(v_lin[i_mat], sizeof(int));
		if (!(*(produs + i)))
			return 1;
	}
	//Produs este initial o matrice de tip I
	for (i = 0; i < v_lin[i_mat]; i++)
		produs[i][i] = 1;
	//Completam matricea aux
	for (i = 0; i < v_lin[i_mat]; i++)
		for (j = 0; j < v_lin[i_mat]; j++)
			aux[i][j] = (*a)[i_mat][i][j];
	//Algoritm logaritmic
	while (putere) {
		if (putere % 2 == 1)
			//Inmultirea se stocheaza in produs
			inmultire(produs, aux, v_lin[i_mat]);
		//Inmultirea se stocheaza in aux
		inmultire(aux, aux, v_lin[i_mat]);
		putere /= 2;
	}
	//Eliberam aux
	for (i = 0; i < v_lin[i_mat]; i++) {
		free(aux[i]);
		free((*a)[i_mat][i]);
	}
	free(aux);
	//Introducem modificarile in matricea tridimensionala "a"
	free((*a)[i_mat]);
	*(*a + i_mat) = produs;
	//Actualizam vectorul de sume
	sum[i_mat] = suma(*a, v_lin, v_col, i_mat);
	return 0;
}

int comanda_9(int ****a, int **v_lin, int **v_col, int m_prec, int **sum)
{
	//Eliberam memoria aferenta matricei cu indicele "i_mat"
	int i_mat, i;
	scanf("%d", &i_mat);
	if (i_mat < m_prec && (i_mat > -1)) {
		for (i = 0; i < (*v_lin)[i_mat]; i++)
			free((*a)[i_mat][i]);
		free((*a)[i_mat]);
		//Mutam toate matricele cu o pozitie in stanga
		for (i = i_mat; i < m_prec - 1; i++)
			(*a)[i] = (*a)[i + 1];
		//MUtam toate elementele vectorilor cu o pozitie in stanga
		for (i = i_mat; i < m_prec - 1; i++)
			(*v_lin)[i] = (*v_lin)[i + 1];
		for (i = i_mat; i < m_prec - 1; i++)
			(*v_col)[i] = (*v_col)[i + 1];
		for (i = i_mat; i < m_prec - 1; i++)
			(*sum)[i] = (*sum)[i + 1];
		//Eliminam ultimul element din fiecare vector
		(*a) = realloc((*a), (m_prec - 1) * sizeof(int *));
		(*v_lin) = realloc((*v_lin), (m_prec - 1) * sizeof(int));
		(*v_col) = realloc((*v_col), (m_prec - 1) * sizeof(int));
		(*sum) = realloc((*sum), (m_prec - 1) * sizeof(int));
		return 0;
	}
	printf("No matrix with the given index\n");
	return 1;
}

void dealocare(int ***a, int *v_lin, int *v_col, int *sum, int m_prec)
{
	//Dealocam memoria pentru vectorii din antet
	for (int i = 0; i < m_prec; i++) {
		for (int j = 0; j < v_lin[i]; j++)
			free(a[i][j]);
		free(a[i]);
	}
	free(a);
	free(v_lin);
	free(v_col);
	free(sum);
}

int main(void)
{
	//Cream a, un tablou tridimensional, si vectorii ce retin
	//numarul de linii si coloane si suma fiecarei matrice
	//bidimensionala
	//La fiecare alocare esuata programul returneaza 1
	int ***a, m_prec = 0, *v_lin, *v_col, *sum;
	a = NULL;
	v_lin = NULL;
	v_col = NULL;
	sum = NULL;
	char caracter;
	while (1) {
		scanf("%c", &caracter);
		while (caracter == ' ' || caracter == '\n' || caracter == '\t')
			scanf("%c", &caracter);
		if (caracter == 'L') {
			if (alocare(&a, &v_lin, &v_col, &sum, m_prec))
				return 1;
			if (citire(a, v_lin, v_col, sum, m_prec))
				return 1;
			m_prec++;
		} else if (caracter == 'D') {
			int i_mat;
			scanf("%d", &i_mat);
			comanda_2(v_lin, v_col, m_prec, i_mat);
		} else if (caracter == 'P') {
			int i_mat;
			scanf("%d", &i_mat);
			comanda_3(a, v_lin, v_col, m_prec, i_mat);
		} else if (caracter == 'C') {
			int i_mat;
			scanf("%d", &i_mat);
			int rezultat = comanda_4(&a, v_lin, v_col, i_mat, m_prec);
			if (rezultat == 1)
				return 1;
			else if (rezultat == 0)
				sum[i_mat] = suma(a, v_lin, v_col, i_mat);
		} else if (caracter == 'M') {
			int c_5;
			c_5 = comanda_5(&a, &v_lin, &v_col, &sum, m_prec);
			if (c_5 == 1)
				return 1;
			else if (c_5 == 2)
				m_prec++;
			//Numarul matricelor se mareste doar daca functia returneaza 2
			//Functia returneaza 2 doar daca se poate executa inmultirea
		} else if (caracter == 'O') {
			if (comanda_6(a, v_lin, v_col, sum, m_prec))
				return 1;
		} else if (caracter == 'T') {
			int i_mat;
			scanf("%d", &i_mat);
			if (comanda_7(&a, v_lin, v_col, i_mat, m_prec))
				return 1;
		} else if (caracter == 'R') {
			if (comanda_8(&a, v_lin, v_col, m_prec, sum))
				return 1;
		} else if (caracter == 'F') {
			if (!(comanda_9(&a, &v_lin, &v_col, m_prec, &sum)))
				m_prec--;
		} else if (caracter == 'Q') {
			if (a)
				dealocare(a, v_lin, v_col, sum, m_prec);
			return 0;
		} else if (caracter == 'S') {
			int c_5;
			c_5 = comanda_5(&a, &v_lin, &v_col, &sum, m_prec);
			if (c_5 == 1)
				return 1;
			else if (c_5 == 2)
				m_prec++;
		} else {
			printf("Unrecognized command\n");
		}
	}
	return 0;
}
