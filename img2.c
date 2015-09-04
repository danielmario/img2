#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <IL/il.h>

char input[512];
char output[512];
const char *ext;

void mkoutput(const char *input)
{
	int i, n = strlen(input);
	strncpy(output, input, sizeof(output));
	for (i = n; i > 0 && input[i] != '.'; i--);
	if (i == 0) i = n;
	snprintf(&output[i], sizeof(output)-i, ".%s", ext);
}

int convert(const char *input)
{
	if (!ilLoadImage(input)) {
		fprintf(stderr, "Cannot load file: %s\n", input);
		return 1;
	}
	mkoutput(input);
	if (!ilSaveImage(output)) {
		fprintf(stderr, "Cannot save file: %s\n", output);
		return 1;
	}
	return 0;
}

int main(int argc, const char *argv[])
{
	int error = 0;
	if (argc == 1) {
		fprintf(stderr,
				"Converts input images to other formats using ImageLibrary.\n"
				"Usage: %s <output-format> [input-files...]\n"
				"\tIf no input-files are given, read filenames from stdin.\n",
				argv[0]);
		return 1;
	}
	ext = argv[1];
	ilInit();
	if (argc > 2) {
		int i;
		for (i=2; i<argc; i++) {
			error |= convert(argv[i]);
		}
	} else {
		fgets(input, sizeof(input), stdin);
		error |= convert(input);
	}
	return error;
}
