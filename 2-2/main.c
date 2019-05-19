#include <stdio.h>
#include <stdint.h>

int main()
{
	int32_t ascii = 0;
	int32_t unicode = 0;
	int32_t ch = 0;
	while ((ch = getchar()) != EOF) {
		if ((ch & (1 << 7)) == 0) {
                	ascii += 1;
		}
		else {
			int32_t next = 0;
			int32_t count_okt = 0;
            		if ((ch >> 3) == 30) {
                		count_okt = 4;
            		}
            		if ((ch >> 4) == 14) {
               			 count_okt = 3;
            		}
            		if ((ch >> 5) == 6) {
                		count_okt = 2;
            		}
           	 	if (count_okt > 4 || count_okt < 2) {
				printf("%i %i", ascii, unicode);
				return 1;
			}
			for (int j = 1; j < count_okt; ++j) {
				if ((next = getchar()) == EOF || !((next >> 6) == 2)) {
					printf("%i %i", ascii, unicode);
					return 1;
				}
			}
			unicode += 1;
		}
	}
	printf("%i %i", ascii, unicode);
	return 0;
}
