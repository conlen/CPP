#include <fcntl.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>

#include <sys/mman.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>



#define BS	4096

int propcmp(void const *a, void const *b)
{
	char const *aa = *(char const **)a;
	char const *bb = *(char const **)b;
	return(strcmp(aa, bb));
}

// computeNamesScores //
int64_t computeNamesScores(void)
{
	int				fd, rc;
	char			*f, *d, *cur, **list, blockLen = 0;
	struct 			stat	buf;
	uint64_t		count = 0, i, j, *scores, x = 0;



	if((fd = open("names.txt", O_RDONLY)) == -1) goto error0;
	if((rc = fstat(fd, &buf)) ==-1) goto error1;
	if((f = (char *)mmap(NULL, buf.st_size, PROT_READ, MAP_FILE | MAP_PRIVATE, fd, 0)) == MAP_FAILED) goto error1;
	if((d = malloc(sizeof(char)*buf.st_size)) == NULL) goto error2;
	memcpy(d, f, buf.st_size);
	munmap(f, buf.st_size);
	close(fd);
	count=0;
	cur = strtok(d, ",\"");
	blockLen = 1;
	if((list = malloc(sizeof(char *)*BS)) == NULL) goto error0;
	do { 
		if(count >= blockLen * BS) list = realloc(list, sizeof(char *)*(BS * ++blockLen));
		list[count++] = cur;
	} while((cur = strtok(NULL, ",\"")) != NULL);
	if((scores = calloc(count, sizeof(uint64_t))) == NULL) goto error3;
	qsort(list, count, sizeof(char *), propcmp);
	for(i=0; i<count; i++) { 
		for(j=0; j<strlen(list[i]); j++) {
			scores[i] += list[i][j] - 'A' + 1;
		}	
		scores[i] *= (i+1);
		x += scores[i];
	}
	free(scores);
	free(list);
	return(x);

error3:
	free(list);
	goto error0;
error2:
	munmap(f, buf.st_size);
error1:
	close(fd);
error0:
	perror("computeNamesScores");
	return(-1);
}
// end computeNamesScores //

int main(int argc, char *argv[])
{
	uint64_t	x;
	int 		rc;
	struct rusage	ru;
	double			startTime, endTime;

	if((rc = getrusage(RUSAGE_SELF, &ru)) != 0) { perror("getrusage 1");}
	startTime = ru.ru_utime.tv_sec + ru.ru_stime.tv_sec + ((long double)(ru.ru_utime.tv_usec + ru.ru_stime.tv_sec)) / 1000000;
	x = computeNamesScores();
	if((rc = getrusage(RUSAGE_SELF, &ru)) != 0) { perror("getrusage 1");}
	endTime = ru.ru_utime.tv_sec + ru.ru_stime.tv_sec + ((long double)(ru.ru_utime.tv_usec + ru.ru_stime.tv_sec)) / 1000000;
	printf("Computed %lld in %f\n", x, endTime - startTime);
	exit(0);
}
