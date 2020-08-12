#include "includes.h"
#include <stdio.h>
#include "system.h"
#include "images.h"
#include "ascii_gray.h"
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>
double start_time, end_time;

double read_timer();

#define dSPAN 15
#define cropSIZE  2*dSPAN + 1
unsigned char matrix_temp[100][100];
int matrix_temp2[27][27];
int dimX,dimY;
int current_image=0;


void producematrix(int x,int y,unsigned char *t)
{
	int i,j;
	for(j=0;j<y;j++)
		for(i=0;i<x;i++)
		    {matrix_temp[i][j]=*t;t++;}
}

//1.grayF
unsigned char grayFout[64*64];
unsigned char *grayF(unsigned char *src)
{int i;
src=image_sequence[current_image];//get the position of the new picture

 for (i=0;i<dimX*dimY;i++)
	        {

		    src+=3;
	        grayFout[i]=(src[0]*3125+src[1]*5625+src[2]*1250)/10000;

	        }

return grayFout;
}

//2.calcCoordF
unsigned char *calcCoordFout;//coords->[cropX,cropY]
unsigned char *calcCoordF(unsigned char *previous)//input:previous->[prevX,prevY],img
{

unsigned char prevX,prevY;
prevX=previous[0];
prevY=previous[1];
 if(prevX <= dSPAN)              calcCoordFout[0]=0;
 else if(prevX > dimX-dSPAN)     calcCoordFout[0]=dimX-cropSIZE-1;
 else                            calcCoordFout[0]=prevX-dSPAN-1;

 if(prevY <= dSPAN)              calcCoordFout[1]=0;
 else if(prevY > dimY-dSPAN)     calcCoordFout[1]=dimY-cropSIZE-1;
 else                            calcCoordFout[1]=prevY-dSPAN-1;
return calcCoordFout;
}


//3.cropF
unsigned char cropFout[cropSIZE*cropSIZE];
unsigned char *cropF(unsigned char *coords, unsigned char *grayed)
{
	producematrix(dimX,dimY,grayed);
	unsigned char cX,cY;
	unsigned char i,j;
int k;
k=0;

cX=coords[0];
cY=coords[1];
for(j=cY;j<cY+cropSIZE;j++)
for(i=cX;i<cX+cropSIZE;i++)
		{cropFout[k]=matrix_temp[i][j];k++;}
return cropFout;
}

//4.xcorr2F
short int xcorr2Fout[27*27];
short int *xcorr2F(unsigned char *cropFout)
{int n,i,j;

 producematrix(cropSIZE,cropSIZE,cropFout);
n=0;
for(j=0;j<27;j++)
for(i=0;i<27;i++)
 {

xcorr2Fout[n]=(int)(matrix_temp[i+2][j])+(int)(matrix_temp[i+1][j+1])+(int)(matrix_temp[i][j+2])+(int)(matrix_temp[i+1][j+3])
	                  +(int)(matrix_temp[i+2][j+4])+(int)(matrix_temp[i+3][j+1])+(int)(matrix_temp[i+4][j+2])+(int)(matrix_temp[i+3][j+3]);
 n++;}

return  xcorr2Fout;
}


//5.getOffsetF

unsigned char getOffsetFout[2];
short int max=0;
unsigned char *getOffsetF(short int *sum)
{int i,j,k,l;
	for(j=0;j<27;j++)
	 for(i=0;i<27;i++)
	  {matrix_temp2[i][j]=*sum;sum++;}
	for(l=0;l<27;l++)
	for(k=0;k<27;k++)
	if(max<matrix_temp2[k][l])
		{max=matrix_temp2[k][l];getOffsetFout[0]=k;getOffsetFout[1]=l;}
return getOffsetFout;
}

//6. objectPos
unsigned char objectPosout[2];
unsigned char *objectPos(unsigned char *coords,unsigned char *offset)
{
	objectPosout[0]=coords[0]+offset[0]+2;
	objectPosout[1]=coords[1]+offset[1]+2;


return objectPosout;
}


int main (void)
{
	dimX = *image_sequence[current_image];
	dimY = *(image_sequence[current_image]+1);

//test
unsigned char *offset;
unsigned char *cropFout2;
unsigned char previous[2]={15,15};//first time
unsigned char *coords;
unsigned char *grayed;
unsigned char *detect;
unsigned char *src;

for(current_image=0;current_image<4;current_image++)
{
    start_time = read_timer();
src=image_sequence[current_image];
grayed=grayF(src);

//printf("\ngrayF done");

coords=calcCoordF(previous);
printf("\ncoords=[%d,%d]",coords[0],coords[1]);
//printf("\ncalcCoordF done");


cropFout2=cropF(coords,grayed);
//printf("\ncropF done");

short int *sum;
sum=xcorr2F(cropFout2);
//printf("\nxcorr2F done");


offset=getOffsetF(sum);
printf("\noffset=[%d,%d] max=%d",offset[0],offset[1],max);
//printf("\ngetOffsetF done");
max=0;//reset max
detect=objectPos(coords,offset);
printf("\ncoordinate=[%d,%d]",detect[0],detect[1]);
//printf("\nobjectPos done");

previous[0]=detect[0];
previous[1]=detect[1];//delay

    
    end_time = read_timer();
    printf("The execution time is %g sec\n", end_time - start_time);
//printf("\n--------------------input in ascii------------------\n");
/*print grayed ppm in ascii*/
//printAscii(grayFout,dimX,dimY);
//printf("\n--------------------output in ascii------------------\n");
/*print output ppm in ascii*/
/*printAsciiHidden(grayFout, dimX, dimY,detect[0],detect[1],
		      5, grayFout[(detect[1])*dimX+detect[0]]);
//                             the position in a list*/
}

return 0;

}
double read_timer() {
    static bool initialized = false;
    static struct timeval start;
    struct timeval end;
    if( !initialized )
    {
        gettimeofday( &start, NULL );
        initialized = true;
    }
    gettimeofday( &end, NULL );
    return (end.tv_sec - start.tv_sec) + 1.0e-6 * (end.tv_usec - start.tv_usec);
}
