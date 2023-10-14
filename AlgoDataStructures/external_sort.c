#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *x1, const void *x2)
{
	return strcmp(*(char**)x1, *(char**)x2);
}

int merge(unsigned long long chunk_size) {
	FILE* input_1 = fopen("input.txt", "r+");
	FILE* input_2 = fopen("input.txt", "r+");
	FILE* output = fopen("output.txt", "w+");
	FILE* byte = fopen("byte.txt", "r+");
	FILE* new_byte = fopen("byte_new.txt", "w+");


	unsigned long long byte_size = 0;
	unsigned long long new_byte_size = 0;
	char str_1[10000];
	char str_2[10000];
	int flag = 0;
	while(1) {
		if (flag == 0) {
			if (fscanf(byte, "%lld", &byte_size) == -1) {
				fclose(input_1);
				fclose(input_2);
				fclose(output);
				fclose(byte);
				fclose(new_byte);
				return -1;
			}
			fseek(input_2, byte_size, SEEK_CUR);
			fscanf(input_1, "%s", str_1);
			if (fscanf(input_2, "%s", str_2) == -1) {
				fclose(input_1);
				fclose(input_2);
				fclose(output);
				fclose(byte);
				fclose(new_byte);
				return -1;
			}
		} else {
			new_byte_size += byte_size;
			if (fscanf(byte, "%lld", &byte_size) == -1) {
				fclose(input_1);
				fclose(input_2);
				fclose(output);
				fclose(byte);
				fclose(new_byte);
				rename("output.txt", "input.txt");
				rename("byte_new.txt", "byte.txt");
				return 1;
			}
			new_byte_size += byte_size;
			fprintf(new_byte, "%lld\n", new_byte_size);
			new_byte_size = 0;
			fseek(input_1, byte_size, SEEK_CUR);
			if (fscanf(byte, "%lld", &byte_size) == - 1) {
				while (fscanf(input_1, "%s", str_1) != -1) {
					fprintf(output, "%s\n", str_1);
				}
				fclose(input_1);
				fclose(input_2);
				fclose(output);
				fclose(byte);
				fclose(new_byte);
				rename("output.txt", "input.txt");
				rename("byte_new.txt", "byte.txt");
				return 1;
			}
			fseek(input_2, byte_size, SEEK_CUR);
			if (fscanf(input_1, "%s", str_1) == -1 || fscanf(input_2, "%s", str_2) == -1) {
				fprintf(output, "%s\n", str_1);
				while (fscanf(input_1, "%s", str_1) != -1) {
					fprintf(output, "%s\n", str_1);
				}
				fclose(input_1);
				fclose(input_2);
				fclose(output);
				fclose(byte);
				fclose(new_byte);
				rename("output.txt", "input.txt");
				rename("byte_new.txt", "byte.txt");
				return 1;
			}
		}



		unsigned long long size_1 = 0;
		unsigned long long size_2 = 0;
		int tmp_flag = 0;
		while (1) {
			if (size_1 != chunk_size && size_2 != chunk_size && tmp_flag == 0) {
				if (strcmp(str_1, str_2) <= 0) {
					fprintf(output, "%s\n", str_1);
					size_1++;
					if (size_1 != chunk_size)
						fscanf(input_1, "%s", str_1);
				} else {
					fprintf(output, "%s\n", str_2);
					size_2++;
					if (size_2 != chunk_size)
						if (fscanf(input_2, "%s", str_2) == -1) {
							tmp_flag = -1;
						}
				}
			} else if ((size_1 == chunk_size && size_2 == chunk_size) || (size_1 == chunk_size && tmp_flag == -1)) {
				break;
			} else if (size_1 == chunk_size && tmp_flag != -1) {
				fprintf(output, "%s\n", str_2);
				size_2++;
				if (size_2 != chunk_size)
					if (fscanf(input_2, "%s", str_2) == -1) {
						tmp_flag = -1;
					}
			} else if (size_2 == chunk_size || tmp_flag == -1) {
				fprintf(output, "%s\n", str_1);
				size_1++;
				if (size_1 != chunk_size)
					fscanf(input_1, "%s", str_1);
			}
		}
		flag = 1;
	}
	fclose(input_1);
	fclose(input_2);
	fclose(output);
	fclose(byte);
	fclose(new_byte);
	rename("output.txt", "input.txt");
	rename("byte_new.txt", "byte.txt");
	return 1;
}


void external_sort()
{
	FILE* input = fopen("input.txt", "r+");
	FILE* output = fopen("output.txt", "w+");
	FILE* chunks_size = fopen("byte.txt", "w+");
	size_t max_size = 25;
	size_t arr_size = 0;
	unsigned long long byte_count = 0;
	char** chunk = calloc(max_size, sizeof(char*));
	for (int i = 0; i < max_size; i++)
		chunk[i] = calloc(10000, sizeof(char));
	while (fscanf(input, "%10000s", chunk[arr_size]) != EOF)
	{
		byte_count += strlen(chunk[arr_size]) + 1;
		arr_size++;
		if (arr_size == max_size)
		{
			fprintf(chunks_size, "%lld\n", byte_count);
			byte_count = 0;
			arr_size = 0;
			qsort(chunk, max_size, sizeof(char*), compare);
			for (int i = 0; i < max_size; i++)
				fprintf(output, "%s\n", chunk[i]);
		}
	}
	if (arr_size > 0)
	{
		fprintf(chunks_size, "%lld\n", byte_count);
		qsort(chunk, arr_size, sizeof(char*), compare);
		for (int i = 0; i < arr_size; i++)
			fprintf(output, "%s\n", chunk[i]);
	}
	for (int i = 0; i < max_size; i++)
		free(chunk[i]);
	free(chunk);

	fclose(input);
	fclose(output);
	fclose(chunks_size);
	rename("output.txt", "input.txt");
	while (merge(max_size) != -1)
		max_size *= 2;
	rename("input.txt", "output.txt");
	remove("byte.txt");
	remove("byte_new.txt");
}

int main()
{
	external_sort();
	return 0;
}
