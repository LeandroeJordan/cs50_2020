#include "helpers.h"
#include <math.h>
#include <stdio.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int iline = 0; iline < height; iline++)
    {
        for (int icol = 0; icol < width; icol++)
        {
            int average = round(((image[iline][icol].rgbtRed) + (image[iline][icol].rgbtGreen)
                                 + (image[iline][icol].rgbtBlue)) / 3.000);
            image[iline][icol].rgbtRed = average;
            image[iline][icol].rgbtGreen = average;
            image[iline][icol].rgbtBlue = average;
        }
    }



    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int iline = 0; iline < (height); iline++)
    {
        for (int icol = 0; icol < (width / 2); icol++)
        {
            //sorting the line
            RGBTRIPLE collortemp;
            collortemp.rgbtRed = image[iline][width - (icol + 1)].rgbtRed;
            image[iline][width - (icol + 1)].rgbtRed = image[iline][icol].rgbtRed;
            image[iline][icol].rgbtRed = collortemp.rgbtRed;

            collortemp.rgbtGreen = image[iline][width - (icol + 1)].rgbtGreen;
            image[iline][width - (icol + 1)].rgbtGreen = image[iline][icol].rgbtGreen;
            image[iline][icol].rgbtGreen = collortemp.rgbtGreen;

            collortemp.rgbtBlue = image[iline][width - (icol + 1)].rgbtBlue;
            image[iline][width - (icol + 1)].rgbtBlue = image[iline][icol].rgbtBlue;
            image[iline][icol].rgbtBlue = collortemp.rgbtBlue;
            if (width == 2)
            {
                break;
            }    

        }
    }

    return;
}
int maxline = 3, maxcol = 3;
RGBTRIPLE array_neibour[3][3];
int avgred = 0, avggrn = 0, avgblu = 0, rcounter = 0, gcounter = 0, bcounter = 0;
//func to create the neibor array
void neibour(int height, int width, int iline, int icol, RGBTRIPLE image[height][width])
{
    // RGBTRIPLE array_neibour[maline][maxcol];
    int i = 0, j = 0;
    for (int lmask = iline; i < maxline; lmask++)
    {
        j = 0;
        for (int cmask = icol; j < maxcol; cmask++)
        {
            if (lmask < 0 || lmask > (height - 1) || cmask < 0 || cmask > (width - 1))
            {
                array_neibour[i][j].rgbtRed = 0;
                array_neibour[i][j].rgbtGreen = 0;
                array_neibour[i][j].rgbtBlue = 0;
            }
            else
            {
                array_neibour[i][j].rgbtRed = image[lmask][cmask].rgbtRed;
                array_neibour[i][j].rgbtGreen = image[lmask][cmask].rgbtGreen;
                array_neibour[i][j].rgbtBlue = image[lmask][cmask].rgbtBlue;
                rcounter++; 
                gcounter++; 
                bcounter++;
            }
            j++;//Incrementa coluna no array neibour
        }
        i++; //Incrementa linha no array neibour
    }


}

//Function BLUR
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE image2[height][width];
    for (int iline = 0; iline < height; iline++)
    {
        for (int icol = 0; icol < width; icol++)
        {
            avgred = 0; 
            avggrn = 0; 
            avgblu = 0; 
            rcounter = 0; 
            gcounter = 0; 
            bcounter = 0; 
            //function for make neighborhood
            neibour(height, width, (iline - 1), (icol - 1), image);
            for (int l = 0; l < maxline; l++)
            {
                for (int c = 0; c < maxcol; c++)
                {
                    //to calculate the average
                    if (array_neibour[l][c].rgbtRed > 0)
                    {
                        avgred = avgred + array_neibour[l][c].rgbtRed;
                        
                    }

                    if (array_neibour[l][c].rgbtGreen > 0)
                    {
                        avggrn = avggrn + array_neibour[l][c].rgbtGreen;
                        
                    }
                    
                    if (array_neibour[l][c].rgbtBlue > 0)
                    {
                        avgblu = avgblu + array_neibour[l][c].rgbtBlue;
                        
                    }
                    
                }
            }
            //to calculate the average
            avgred = (int)round((float)avgred / (float)rcounter++);
            avggrn = (int)round((float)avggrn / (float)gcounter++);
            avgblu = (int)round((float)avgblu / (float)bcounter++);
            image2[iline][icol].rgbtRed = avgred;
            image2[iline][icol].rgbtGreen = avggrn;
            image2[iline][icol].rgbtBlue = avgblu;
            rcounter = 0;
            gcounter = 0;
            bcounter = 0; 

        }

    }

//update image from ima2
    for (int l = 0; l < (height); l++)
    {
        for (int c = 0; c < (width); c++)
        {
            image[l][c].rgbtRed = image2[l][c].rgbtRed;
            image[l][c].rgbtGreen = image2[l][c].rgbtGreen;
            image[l][c].rgbtBlue = image2[l][c].rgbtBlue;

        }
    }
 
    return;
}


// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image2[height][width];
    //create the masck
    int array_mask_gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int array_mask_gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    
    

    //calculate sobel 
    int resred_gx = 0, resgrn_gx = 0, resblu_gx = 0;
    int resred_gy = 0, resgrn_gy = 0, resblu_gy = 0;
    int resred = 0, resgrn = 0, resblu = 0;
    for (int iline = 0; iline < height; iline++)
    {
        for (int icol = 0; icol < width; icol++)
        {
            //function for make neighborhood
            neibour(height, width, (iline - 1), (icol - 1), image);
            for (int l = 0; l < maxline; l++)
            {
                for (int c = 0; c < maxcol; c++)
                {
                    //Calculate the value of color by mask_gx
                    resred_gx = resred_gx + (array_neibour[l][c].rgbtRed * array_mask_gx[l][c]);
                    resgrn_gx = resgrn_gx + (array_neibour[l][c].rgbtGreen * array_mask_gx[l][c]);
                    resblu_gx = resblu_gx + (array_neibour[l][c].rgbtBlue * array_mask_gx[l][c]);
                   
                    //Calculate the value of color by mask_gy
                    resred_gy = resred_gy + (array_neibour[l][c].rgbtRed * array_mask_gy[l][c]);
                    resgrn_gy = resgrn_gy + (array_neibour[l][c].rgbtGreen * array_mask_gy[l][c]) ;
                    resblu_gy = resblu_gy + (array_neibour[l][c].rgbtBlue * array_mask_gy[l][c]);


                }
            }
            //to calculate the new color value
            resred = (int)round(sqrt(pow(resred_gx, 2) + pow(resred_gy, 2)));
            resgrn = (int)round(sqrt(pow(resgrn_gx, 2) + pow(resgrn_gy, 2))); 
            resblu = (int)round(sqrt(pow(resblu_gx, 2) + pow(resblu_gy, 2)));
            
            //adjust value > 255
            if (resred > 255)
            {
                resred = 255;
            }
            if (resgrn > 255)
            {
                resgrn = 255;
            }
            if (resblu > 255)
            {
                resblu = 255;
            }
            //create a new image
            image2[iline][icol].rgbtRed = resred;
            image2[iline][icol].rgbtGreen = resgrn;
            image2[iline][icol].rgbtBlue = resblu;
            resred_gx = 0, resgrn_gx = 0, resblu_gx = 0;
            resred_gy = 0, resgrn_gy = 0, resblu_gy = 0;
            resred = 0, resgrn = 0, resblu = 0;

        }

    }

//update image from ima2
    for (int l = 0; l < (height); l++)
    {
        for (int c = 0; c < (width); c++)
        {
            image[l][c].rgbtRed = image2[l][c].rgbtRed;
            image[l][c].rgbtGreen = image2[l][c].rgbtGreen;
            image[l][c].rgbtBlue = image2[l][c].rgbtBlue;

        }
    }
 
    return;
}
