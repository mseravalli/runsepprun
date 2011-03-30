#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int alternativeMain()
{
	char c;
	int count = 0;
	int countSeq = -1;
	int status = 1;
	char tmp[3];
	char tmp2[4];	
	FILE *input = fopen("./img.html", "rb");
	FILE *output = fopen("./img.parsed", "wb");

	char *init = "int img[X*Y*3] = {";
	char *endinit = "};";

	fwrite(init, sizeof(char), 18 , output);
	
	status = fread(&c, sizeof(char), 1, input);
	
	while(status > 0)
	{
		if(c == 35)
		{
			countSeq = 0;
			status = fread(&c, sizeof(char), 1, input);
	                count++;
		}
		
		if(countSeq >= 0 && countSeq <= 2)
		{
			tmp[0] = c;
			status = fread(&c, sizeof(char), 1, input);
                        //count++;
			tmp[1] = c;
			tmp[2] = 0;

			int nResult;
			sscanf(tmp, "%x", &nResult);
			int read = sprintf(tmp2, "%d", nResult);
//			printf(" :%s", tmp2);
			fwrite(tmp2, sizeof(char), read, output);
			fwrite(", ", sizeof(char), 2, output);	
		
			countSeq++;
		}
		else
			countSeq = -1;
		
		if(count > 8)
		{
			fwrite("\n", sizeof(char), 1, output);		
			count = 0;
		}

		status = fread(&c, sizeof(char), 1, input);
		//count++;
	}

	fwrite(endinit, sizeof(char), 2, output);

	fclose(input);
	fclose(output);
	return 0;
}
