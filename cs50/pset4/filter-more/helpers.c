#include "helpers.h"
#include "math.h"
#include <stdio.h>

int max_check(int n);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //printf("height[%i] x width[%i]\n", height, width);
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            double avg = round(((float) image[h][w].rgbtRed + (float) image[h][w].rgbtGreen + (float) image[h][w].rgbtBlue) / 3);
            image[h][w].rgbtRed = (int) avg;
            image[h][w].rgbtGreen = (int) avg;
            image[h][w].rgbtBlue = (int) avg;
            //printf("[%i][%i]:%i|", h, w, avg);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //printf("height[%i] x width[%i]\n", height, width);
    int updated_width;
    if (width % 2 == 0)
    {
        updated_width = width/2;
    }
    else
    {
        updated_width = (width - 1)/2;
    }

    for (int h = 0; h < height; h++)
    {

        for (int w = 0; w < updated_width; w++)
        {
            int temp_Red = image[h][w].rgbtRed;
            image[h][w].rgbtRed = image[h][width - (w + 1)].rgbtRed;
            image[h][width - (w + 1)].rgbtRed = temp_Red;

            int temp_Green = image[h][w].rgbtGreen;
            image[h][w].rgbtGreen = image[h][width - (w + 1)].rgbtGreen;
            image[h][width - (w + 1)].rgbtGreen = temp_Green;

            int temp_Blue = image[h][w].rgbtBlue;
            image[h][w].rgbtBlue = image[h][width - (w + 1)].rgbtBlue;
            image[h][width - (w + 1)].rgbtBlue = temp_Blue;
        }
    }
    return;
}


// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE blur_image[height][width];
    
    //printf("height[%i] x width[%i]\n", height, width);


    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            double total_rgbtRed = 0;
            double total_rgbtGreen = 0;
            double total_rgbtBlue = 0;
            double count = 0;
            for (int n = -1; n < 2; n++)
            {
                for (int p = -1; p < 2; p++)
                {
                    if ((h + n) < 0 || (h + n) >= height)
                    {
                        continue;
                    }
                    if ((w + p) < 0 || (w + p) >= width)
                    {
                        continue;
                    }
                    total_rgbtRed += image[h + n][w + p].rgbtRed;
                    total_rgbtGreen += image[h + n][w + p].rgbtGreen;
                    total_rgbtBlue += image[h + n][w + p].rgbtBlue;
                    count++;

                }
            }
            blur_image[h][w].rgbtRed = round((total_rgbtRed / count));
            blur_image[h][w].rgbtGreen= round((total_rgbtGreen / count));
            blur_image[h][w].rgbtBlue = round((total_rgbtBlue / count));
        }
    }

    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            image[x][y].rgbtRed = blur_image[x][y].rgbtRed;
            image[x][y].rgbtGreen = blur_image[x][y].rgbtGreen;
            image[x][y].rgbtBlue = blur_image[x][y].rgbtBlue;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE edge_image[height][width];
    
    //printf("height[%i] x width[%i]\n", height, width);

    int gx[] = {-1,0,1,-2,0,2,-1,0,1};
    int gy[] = {-1,-2,-1,0,0,0,1,2,1};

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            //printf("H:%i by W:%i\n", h, w);
            double xtotal_rgbtRed = 0;
            double xtotal_rgbtGreen = 0;
            double xtotal_rgbtBlue = 0;
            double ytotal_rgbtRed = 0;
            double ytotal_rgbtGreen = 0;
            double ytotal_rgbtBlue = 0;
            int count = 0;
            for (int n = -1; n < 2; n++)
            {
                for (int p = -1; p < 2; p++)
                {
                    if ((h + n) < 0 || (h + n) >= height)
                    {
                        count++;
                        continue;
                    }
                    if ((w + p) < 0 || (w + p) >= width)
                    {
                        count++;
                        continue;
                    }
                    //Gx
                    xtotal_rgbtRed += (image[h + n][w + p].rgbtRed * (gx[count]));
                    xtotal_rgbtGreen += (image[h + n][w + p].rgbtGreen * (gx[count])); 
                    xtotal_rgbtBlue += (image[h + n][w + p].rgbtBlue * (gx[count]));
                    //Gy
                    ytotal_rgbtRed += (image[h + n][w + p].rgbtRed * (gy[count]));
                    ytotal_rgbtGreen += (image[h + n][w + p].rgbtGreen * (gy[count])); 
                    ytotal_rgbtBlue += (image[h + n][w + p].rgbtBlue * (gy[count]));
                    count++;
                }
            }
            edge_image[h][w].rgbtRed = max_check(round(sqrt(pow(xtotal_rgbtRed, 2) + pow(ytotal_rgbtRed, 2))));
            edge_image[h][w].rgbtGreen = max_check(round(sqrt(pow(xtotal_rgbtGreen, 2) + pow(ytotal_rgbtGreen, 2))));
            edge_image[h][w].rgbtBlue = max_check(round(sqrt(pow(xtotal_rgbtBlue, 2) + pow(ytotal_rgbtBlue, 2))));
            //printf(" - xTotalRed: %lf | yTotalRed: %lf | combined: %i\n", xtotal_rgbtRed, ytotal_rgbtRed, edge_image[h][w].rgbtRed);
            //printf(" - xTotalGreen: %lf | yTotalGreen: %lf | combined: %i\n", xtotal_rgbtGreen, ytotal_rgbtGreen, edge_image[h][w].rgbtGreen);
            //printf(" - xTotalBlue: %lf | yTotalBlue: %lf | combined: %i\n", xtotal_rgbtBlue, ytotal_rgbtBlue, edge_image[h][w].rgbtBlue);
        }
    }

    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            image[x][y].rgbtRed = edge_image[x][y].rgbtRed;
            image[x][y].rgbtGreen = edge_image[x][y].rgbtGreen;
            image[x][y].rgbtBlue = edge_image[x][y].rgbtBlue;
        }
    }
    return;
}



int max_check(int n)
{
    int max = n;
    if (max > 255)
    {
        max = 255;
    }
	return max;
}