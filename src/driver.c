#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "ht.h"

#define MAX_LINE 1024

uint64_t hash(const char *name, size_t length) 
{
	uint64_t hash_val = 0;
	for (size_t i = 0; i < length; i++) {
		hash_val += name[i];
		hash_val = (hash_val * name[i]);
	}
	return hash_val;
}

void generate_random_word(char *buffer, size_t length)
{
	for (size_t i = 0; i < length - 1; i++) {
		buffer[i] = 'a' + (rand() % 26);
	}
	buffer[length - 1] = 0;
}

// if you want to do your own thing, otherwise pass NULL to ht_create
void my_cleanup(void *p) 
{
	printf("destroying %p\n", p);
	free(p);
}

int main(int argc, char **argv)
{
	if (argc != 3) {
		printf("Usage: %s <wordlist filename> <num guesses>", argv[0]);
		return EXIT_FAILURE;
	}

	char *filename = argv[1];
	char *end_ptr = 0;
	errno = 0;

	long num_guesses = strtol(argv[2], &end_ptr, 10);

	// check for conversion errors
	if (errno != 0 || *end_ptr != '\0') {
		fprintf(stderr, "Invalid number: %s\n", argv[2]);
		return 1;
	}
	// ensure num within valid range
	if (num_guesses < 0 || num_guesses > UINT32_MAX) {
		fprintf(stderr, "Number of guesses out of range\n");
		return 1;
	}

	uint32_t num_guesses_safe = (uint32_t) num_guesses;

	const int table_size = (1<<20);
	ht_t *table = ht_create(table_size, hash, NULL);

	FILE *fp = fopen(filename, "r");
	char buffer[MAX_LINE];
	uint32_t num_words = 0;

	while (!feof(fp) && fgets(buffer, MAX_LINE, fp) != NULL) {
		buffer[strcspn(buffer, "\n\r")] = 0;
		char *new_entry = malloc(strlen(buffer) + 1);
		strcpy(new_entry, buffer);
		ht_insert(table, new_entry, new_entry);
		num_words++;
	}

	fclose(fp);
	printf("Loaded %d words into table\n", num_words);

	// make guesses
	uint32_t good_guesses = 0;
	const int short_guess = 2;
	const int long_guess = 15;
	for (uint32_t i = 0; i < num_guesses; i++) {
		generate_random_word(buffer, short_guess + 
					(rand() % (long_guess - short_guess)));
		if (ht_search(table, buffer)) {
			good_guesses++;
		}
	}
	printf("%u out of %u in the table\n", good_guesses, num_guesses_safe);

	ht_printf(table);

	ht_destroy(table);
}