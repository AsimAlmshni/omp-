#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <cmath>
#include <string>
#include <fstream>
#ifdef _OPENMP
# include <omp.h>
#endif
using namespace std;
# ifdef _OPENMP
	
	
# endif
int thread_count =4;

string  mask,inputname,outputname;
int main(int argc, char* argv[]) {

    if (argc < 5) {
        printf("You must pass 4 parameters inputfilename,mask , outputfilename, and thread count\n");
        return 0;
    }
	

	   string s1(argv[1]);
	    string s2(argv[2]);
	    string s3(argv[3]);
	    stringstream er1(s1);
	    er1 >> inputname;
	    stringstream er2(s2);
	    er2 >> mask;
	    stringstream er3(s3);
	    er3 >> outputname; 
            thread_count = strtol(argv[4], NULL, 10);
		
	 
	
	int row , colm,pix,sum;
	 ifstream myfile (inputname.c_str());
  	if (myfile.is_open())
 	 {	
		ifstream myfile2 (mask.c_str());
		if (myfile2.is_open())
		{
	  	   	myfile>>row; 
	  	  	myfile>>colm; 
			int **image;
			int **image2;
			int mask[3][3];
		//create image matrex
			image=new  int* [row];
			image2=new  int* [row-3];
			for (int i =0; i<row;i++)
			{
				image[i]=new int [colm];
				
			}
			for (int i =0; i<row-3;i++)
			{
				
				image2[i]=new int [colm-3];
			}
		//get value from oimage.txt
			for(int i=0;i<row;i++)
			{
				for(int j=0;j<colm;j++)
				{	
					myfile>>pix;
					image[i][j]=pix;
				}
			}
		//crete mask or kernel matrex
			for(int i=0;i<3;i++)
			{
				for(int j=0;j<3;j++)
				{
					myfile2>>pix;
					mask[i][j]=pix;
					
				}
			}
			//open the output file
			
			 	
					//apply mask on matrex
				#pragma omp parallel for num_threads(thread_count) reduction(+ : sum)
					for(int i=0;i<row-3;i++)
					{
						
						for(int j=0;j<colm-3;j++)
						{	sum = 0;
							
							for(int z=0;z<3;z++)
							{
								
								for(int k=0;k<3;k++)
								{	
									
									sum+=image[i+z][j+k]*mask[z][k];
																	
								}
							}
						
							image2[i][j]=sum;
					
						}
						
					}
				
				ofstream myfile3;
				myfile3.open (outputname.c_str());
				if(myfile3.is_open())
				{
					for(int i=0;i<row-3;i++)
					{
						for(int j=0;j<colm-3;j++)
						{	
							myfile3<<image2[i][j]<<" ";
						}
						myfile3<<"\n";
					}
				}
				 myfile3.close();
			for (int i =0; i<row;i++)
			{
				delete [] image[i];
			}
			for (int i =0; i<row-3;i++)
			{
				delete [] image2[i];
			}
			delete []image;
			delete []image2;
		}
		myfile2.close();
  	  }
	
  	
	  myfile.close();
	  
	return 0;
}
