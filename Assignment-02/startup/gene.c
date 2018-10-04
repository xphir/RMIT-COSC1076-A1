/******************************************************************************
** Student name: 	...
** Student number: 	...
** Course: 			Advanced Programming Techniques - S2 2018
******************************************************************************/

#include "gene.h"

int *create_pcbmill_chrom(int numAlleles)
{
	int *result;
	int *alleles;
	int allele1;
	int allele2;

	int i;
	int j;

	alleles = malloc(numAlleles * sizeof(alleles));
	if (alleles != NULL)
	{
		for (i = 0; i < numAlleles; ++i)
		{
			alleles[i] = i;
		}
		for (j = 0; j < numAlleles; j = allele1 + 1)
		{
			allele1 = rand() % numAlleles;
			allele2 = rand() % numAlleles;
			gene_swap_alleles(alleles, allele1, allele2);
		}
		result = alleles;
	}
	else
	{
		fwrite("Unable to allocate chromosome memory", 1, 36, stderr);
		result = NULL;
	}
	return result;
}
int *create_minfn_chrom(int numAlleles)
{
	int *result;
	int *alleles;
	int i;

	alleles = malloc(numAlleles * sizeof(alleles));
	if (alleles)
	{
		for (i = 0; i < numAlleles; ++i)
		{
			alleles[i] = rand() % MINFN_MAX;
		}
		result = alleles;
	}
	else
	{
		fwrite("Unable to allocate chromosome memory", 1, 36, stderr);
		result = NULL;
	}
	return result;
}

Gene *mutate_pcbmill(Gene *g)
{
	Gene *result_gene;
	int randomInt1;
	int randomInt2;
	int value1;
	int value2;
	Gene *new_gene;

	new_gene = gene_copy(g);
	if (new_gene != NULL)
	{
		randomInt1 = rand() % new_gene->num_alleles;
		randomInt2 = rand() % new_gene->num_alleles;
		value1 = new_gene->chromosome[randomInt1];
		value2 = new_gene->chromosome[randomInt2];
		fprintf(stdout, "Index %d Index %d\n", randomInt1, randomInt2);
		new_gene->chromosome[randomInt1] = value2;
		new_gene->chromosome[randomInt2] = value1;
		result_gene = new_gene;
	}
	else
	{
		result_gene = NULL;
	}
	return result_gene;
}

Gene *mutate_minfn(Gene *g)
{
	Gene *result_gene;
	int randomInt;
	int randomIndex;
	Gene *new_gene;

	new_gene = gene_copy(g);
	if (new_gene != NULL)
	{

		randomInt = rand() % MINFN_MAX;
		randomIndex = rand() % new_gene->num_alleles;
		fprintf(stdout, "Index %d\n", randomIndex);
		new_gene->chromosome[randomIndex] = randomInt;
		result_gene = new_gene;
	}
	else
	{
		result_gene = NULL;
	}
	return result_gene;
}

Gene *crossover_pcbmill(Gene *g1, Gene *g2)
{
	Gene *result_gene;
	Gene *new_gene;
	int randomInt1;
	int randomInt2;
	int j;
	int i;

	new_gene = gene_copy(g1);
	if (new_gene != NULL)
	{
		/* TO FIX */
		randomInt1 = 2;
		randomInt2 = 4;

		for (i = 0; randomInt1 - randomInt2 >= i; i++)
		{
			new_gene->chromosome[i] = g1->chromosome[i];
		}

		for (j = 0; g2->num_alleles > j; j++)
		{
			if (!gene_chrom_contains(new_gene, randomInt1 - randomInt2, g2->chromosome[j]))
			{
				new_gene->chromosome[i++] = g2->chromosome[j];
			}
		}
	}

	fprintf(stdout, "Index %d Index %d\n", randomInt1, randomInt2);
	result_gene = new_gene;
	return result_gene;
}

Gene *crossover_minfn(Gene *g1, Gene *g2)
{
	Gene *result_gene;
	Gene *new_gene;
	int randomInt;
	int i;
	int numAlleles;
	new_gene = gene_copy(g1);
	if (new_gene != NULL)
	{
		numAlleles = new_gene->num_alleles;
		/* Select a random index */
		randomInt = rand() % numAlleles;
		fprintf(stdout, "Index %d\n", randomInt);
		/* Copy every chromosome less than and including randomInt from g1 */
		for (i = 0; i <= randomInt; i++)
		{
			new_gene->chromosome[i] = g1->chromosome[i];
		}
		/* Copy every chromosome greater than  */
		for (i = (randomInt - 1); i < numAlleles; i++)
		{
			new_gene->chromosome[i] = g2->chromosome[i];
		}
		/* Fill raw and fitness at 0  */
		new_gene->raw_score = 0;
		new_gene->fitness = 0;
		/* Set the result_gene  */
		result_gene = new_gene;
	}
	else
	{
		result_gene = NULL;
	}
	return result_gene;
}

double eval_pcbmill(InVTable *invt, Gene *gene)
{
	int *tableRow1;
	int *tableRow2;
	int numAlleles;
	int *chromosome;
	double resultEval;
	int i;

	resultEval = 0.0;
	chromosome = gene_get_chrom(gene);
	numAlleles = gene_get_num_alleles(gene);
	for (i = 0; numAlleles - 1 > i; ++i)
	{
		tableRow1 = invector_get_table_row(invt, chromosome[i]);
		tableRow2 = invector_get_table_row(invt, chromosome[i + 1]);
		resultEval = pcbmill_distance(tableRow1, tableRow2) + resultEval;
	}
	return resultEval;
}

double eval_minfn(InVTable *invt, Gene *gene)
{
	/* TO DO */
	return 0.0;
}

Gene *gene_create_rand_gene(int numAlleles, CreateFn create_chrom)
{
	int *chromosome;
	Gene *result_gene;
	Gene *new_gene = malloc(sizeof(*new_gene));

	chromosome = create_chrom(numAlleles);

	if (new_gene != NULL)
	{
		new_gene->chromosome = chromosome;
		new_gene->num_alleles = numAlleles;
		new_gene->raw_score = 0;
		new_gene->fitness = 0;
		result_gene = new_gene;
	}
	else
	{
		fwrite("Unable to allocate memory in gene_create_rand_gene\n", 1, 51, stderr);
		result_gene = NULL;
	}
	return result_gene;
}

void gene_calc_fitness(Gene *gene, EvalFn evaluate_fn, InVTable *invTab)
{
	/* TO DO */
	return;
}

void gene_normalise_fitness(Gene *gene, double total_fitness)
{
	/* TO DO */
}

void gene_free(Gene *gene)
{
	free(gene->chromosome);
	free(gene);
}

double gene_get_fitness(Gene *gene)
{
	/* TO DO */
	return 0.0;
}

void gene_print(Gene *gene)
{
	int i;

	fwrite("chrom:", 1, 6, stdout);
	for (i = 0; gene->num_alleles > i; ++i)
	{
		fprintf(stdout, "%2d", gene->chromosome[i]);
		if (gene->num_alleles - 1 != i)
		{
			fputc(',', stdout);
		}
	}
	fprintf(stdout, " fit:%6.3f raw:%7.3f\n", gene->fitness, gene->raw_score);
	return;
}

double pcbmill_distance(int *tableRow1, int *tableRow2)
{
	int calcY;
	int calcX;
	double result;

	calcY = tableRow2 - tableRow1;
	calcX = *(tableRow2 + 4) - *(tableRow1 + 4);
	result = sqrt((calcX * calcX) + (calcY * calcY));
	return result;
}

Gene *gene_copy(Gene *g)
{
	/* TODO */
	int *chromosome;
	Gene *new_gene = malloc(sizeof(*g));

	if (new_gene != NULL)
	{
		chromosome = malloc(g->num_alleles * sizeof(int));
		if (chromosome != NULL)
		{
			new_gene->chromosome = chromosome;
			new_gene->num_alleles = g->num_alleles;
			new_gene->fitness = new_gene->raw_score = 0;
			/* Copy Values */
			memcpy(new_gene->chromosome, g->chromosome, g->num_alleles * sizeof(int));
		}
	}
	else
	{
		fwrite("Unable to allocate memory in gene_copy\n", 1, 39, stderr);
	}
	
	return new_gene;
}

int *gene_get_chrom(Gene *g)
{
	return g->chromosome;
}

int gene_get_num_alleles(Gene *g)
{
	return g->num_alleles;
}

void gene_swap_alleles(int *alleles, int allele1, int allele2)
{
	int alleleValue1;
	int alleleValue2;

	alleleValue1 = alleles[allele1];
	alleleValue2 = alleles[allele2];

	alleles[allele1] = alleleValue2;
	alleles[allele2] = alleleValue1;

	return;
}

Boolean gene_chrom_contains(Gene *g, int index, int value)
{
	int i;

	for (i = 0; i <= index; ++i)
	{
		if (g->chromosome[i] == value)
		{
			return TRUE;
		}
	}
	return FALSE;
}