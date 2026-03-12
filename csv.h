#include <stdbool.h>

bool isCsvFile(const char* filename);
int parseCSVContent(char* received_csv, char* filename, char** data);