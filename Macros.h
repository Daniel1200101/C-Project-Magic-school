#pragma once

#define HALFOF(x)  (x)/2
#define AVG5(n1,n2,n3,n4,n5)  ((n1)+(n2)+(n3)+(n4)+(n5))/5.0F
#define MAX(x, y)	(x) > (y) ? (x) : (y)
#define MIN(x, y)	(x) < (y) ? (x) : (y)
#define SQUARE(x)	(x)*(x)
#define MULT(x,y)	(x)*(y)
#define SUM(x, y)	(x)+(y)

#define PRINT(s)	printf(#s"\n");

#define CHECK_RETURN_NULL(ptr) {if(!ptr) return NULL;}
#define CHECK_COLSE_RETURN_NULL(ptr,fp) {if(!ptr){fclose(fp); return NULL;}}

