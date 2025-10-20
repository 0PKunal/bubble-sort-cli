#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

typedef struct {
    double *data;
    size_t length;
} NumberArray;

static char *read_file_to_buffer(const char *path, size_t *out_size) {
    FILE *f = fopen(path, "rb");
    if (!f) return NULL;
    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return NULL; }
    long size = ftell(f);
    if (size < 0) { fclose(f); return NULL; }
    rewind(f);
    char *buf = (char *)malloc((size_t)size + 1);
    if (!buf) { fclose(f); return NULL; }
    size_t read = fread(buf, 1, (size_t)size, f);
    fclose(f);
    buf[read] = '\0';
    if (out_size) *out_size = read;
    return buf;
}

static int is_integral_double(double x) {
    double r = round(x);
    return fabs(x - r) < 1e-9;
}

static NumberArray parse_numbers_from_buffer(char *buf) {
    // Replace commas with spaces for unified tokenization
    for (char *p = buf; *p; ++p) {
        if (*p == ',') *p = ' ';
    }

    size_t cap = 128;
    size_t len = 0;
    double *arr = (double *)malloc(cap * sizeof(double));
    if (!arr) {
        NumberArray empty = { NULL, 0 };
        return empty;
    }

    const char *delims = " \t\r\n";
    char *tok = strtok(buf, delims);
    while (tok) {
        char *endptr = NULL;
        double v = strtod(tok, &endptr);
        if (endptr != tok) { // parsed something
            if (len == cap) {
                cap = cap < 1024 ? cap * 2 : cap + cap / 2;
                double *tmp = (double *)realloc(arr, cap * sizeof(double));
                if (!tmp) { free(arr); arr = NULL; len = 0; break; }
                arr = tmp;
            }
            arr[len++] = v;
        }
        tok = strtok(NULL, delims);
    }

    NumberArray result = { arr, len };
    return result;
}

static void bubble_sort(double *data, size_t n) {
    if (!data || n == 0) return;
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j + 1 < n - i; ++j) {
            if (data[j] > data[j + 1]) {
                double tmp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = tmp;
            }
        }
    }
}

static void print_array(const double *data, size_t n) {
    putchar('[');
    for (size_t i = 0; i < n; ++i) {
        // %g prints compactly (integers as 1, floats as 1.23)
        printf("%g", data[i]);
        if (i + 1 < n) printf(", ");
    }
    putchar(']');
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    const char *file_path = argv[1];
    size_t file_size = 0;
    char *buffer = read_file_to_buffer(file_path, &file_size);
    if (!buffer) {
        fprintf(stderr, "Error: Failed to read file '%s'\n", file_path);
        return 1;
    }

    NumberArray arr = parse_numbers_from_buffer(buffer);
    if (!arr.data || arr.length == 0) {
        free(buffer);
        fprintf(stderr, "Error: No numbers found in '%s'\n", file_path);
        return 1;
    }

    int first_is_int = is_integral_double(arr.data[0]);

    // Preserve original numbers for display
    double *original = (double *)malloc(arr.length * sizeof(double));
    if (!original) {
        free(arr.data);
        free(buffer);
        fprintf(stderr, "Error: Out of memory\n");
        return 1;
    }
    memcpy(original, arr.data, arr.length * sizeof(double));

    clock_t start = clock();
    bubble_sort(arr.data, arr.length);
    clock_t end = clock();
    double elapsed = (double)(end - start) / (double)CLOCKS_PER_SEC;

    // Output mirrors python script
    printf("\nOriginal data: ");
    print_array(original, arr.length);
    printf("\n");
    printf("\nSorted data: ");
    print_array(arr.data, arr.length);
    printf("\n\n");
    printf("Sorting took %.6f seconds\n", elapsed);
    printf("Sorting algorithm used: Bubble Sort\n");
    printf("Number of elements sorted: %zu\n", arr.length);
    printf("\nData source: %s\n", file_path);
    printf("Data type: %s\n", first_is_int ? "int" : "float");
    printf("Data format: Comma and space-separated values\n");
    printf("Data order before sorting: Unsorted\n");
    printf("Data order after sorting: Sorted\n");
    printf("Data size: %zu elements\n\n", arr.length);

    free(arr.data);
    free(original);
    free(buffer);
    return 0;
}
