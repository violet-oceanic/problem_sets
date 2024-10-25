#include "helpers.h"
#include "math.h"
#include <stdio.h>

int max_check(int n);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    printf("height[%i] x width[%i]\n", height, width);
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int avg = round((image[h][w].rgbtRed + image[h][w].rgbtGreen + image[h][w].rgbtBlue) / 3);
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
    printf("height[%i] x width[%i]\n", height, width);
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w <= width/2; w++)
        {
            int temp_Red = image[h][w].rgbtRed;
            image[h][w].rgbtRed = image[h][width - 1 - w].rgbtRed;
            image[h][width - 1 - w].rgbtRed = temp_Red;
            
            int temp_Green = image[h][w].rgbtGreen;
            image[h][w].rgbtGreen = image[h][width - 1 - w].rgbtGreen;
            image[h][width - 1 - w].rgbtGreen = temp_Green;
            
            int temp_Blue = image[h][w].rgbtBlue;
            image[h][w].rgbtBlue = image[h][width - 1 - w].rgbtBlue;
            image[h][width - 1 - w].rgbtBlue = temp_Blue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE blur_image[height][width];
    
    printf("height[%i] x width[%i]\n", height, width);


    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int total_rgbtRed = 0;
            int total_rgbtGreen = 0;
            int total_rgbtBlue = 0;
            int count = 0;
            for (int n = h-1; n <= h+1; n++)
            {
                for (int p = w-1; p <= w+1; p++)
                {
                    if ((n >= 0) && (n < height) && (p >= 0) && (p < width))
                    {
                        total_rgbtRed += image[n][p].rgbtRed;
                        total_rgbtGreen += image[n][p].rgbtGreen;
                        total_rgbtBlue += image[n][p].rgbtBlue;
                        count++;
                    }
                }
            }
            blur_image[h][w].rgbtRed = (int) round((total_rgbtRed / count));
            blur_image[h][w].rgbtGreen= (int) round((total_rgbtGreen / count));
            blur_image[h][w].rgbtBlue = (int) round((total_rgbtBlue / count));
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
    
    printf("height[%i] x width[%i]\n", height, width);


    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            //printf("H:%i by W:%i\n", h, w);
            int xtotal_rgbtRed = 0;
            int xtotal_rgbtGreen = 0;
            int xtotal_rgbtBlue = 0;
            int ytotal_rgbtRed = 0;
            int ytotal_rgbtGreen = 0;
            int ytotal_rgbtBlue = 0;

            for (int n = h-1; n <= h+1; n++)
            {
                for (int p = w-1; p <= w+1; p++)
                {
                    if (((n < 0) || (n >= height) || (p < 0) || (p >= width)))
                    {
                        //printf("h[%i] by w[%i] is outside border\n", n, p);
                    }
                    else
                    {
                        
                        //Gx
                        // middle left (-2)
                        if ((n == (h)) && (p == (w - 1)))
                        {
                            xtotal_rgbtRed += (image[n][p].rgbtRed * -2);
                            xtotal_rgbtGreen += (image[n][p].rgbtGreen * -2); 
                            xtotal_rgbtBlue += (image[n][p].rgbtBlue * -2);
                        }
                        // top left, bottom left (-1)
                        if (((n == (h - 1)) || (n == (h + 1))) && (p == (w - 1)))
                        {
                            xtotal_rgbtRed += (image[n][p].rgbtRed * -1);
                            xtotal_rgbtGreen += (image[n][p].rgbtGreen * -1); 
                            xtotal_rgbtBlue += (image[n][p].rgbtBlue * -1);
                        }
                        // top middle, middle, bottom middle (0)
                        if ((n == ((h - 1)) || (n == (h)) || (n == (h + 1))) && (p == (w)))
                        {
                            xtotal_rgbtRed += (image[n][p].rgbtRed * 0);
                            xtotal_rgbtGreen += (image[n][p].rgbtGreen * 0); 
                            xtotal_rgbtBlue += (image[n][p].rgbtBlue * 0); 
                        }
                        // top right, bottom right (1)
                        if ((n == ((h - 1)) || (n == (h + 1))) && (p == (w + 1)))
                        {
                            xtotal_rgbtRed += (image[n][p].rgbtRed * 1);
                            xtotal_rgbtGreen += (image[n][p].rgbtGreen * 1); 
                            xtotal_rgbtBlue += (image[n][p].rgbtBlue * 1); 
                        }
                        // middle right (2)
                        if ((n == (h)) && (p == (w + 1)))
                        {
                            xtotal_rgbtRed += (image[n][p].rgbtRed * 2);
                            xtotal_rgbtGreen += (image[n][p].rgbtGreen * 2); 
                            xtotal_rgbtBlue += (image[n][p].rgbtBlue * 2); 
                        }


                        //Gy
                        // top middle (-2)
                        if ((n == (h - 1)) && (p == (w)))
                        {
                            ytotal_rgbtRed += (image[n][p].rgbtRed * -2);
                            ytotal_rgbtGreen += (image[n][p].rgbtGreen * -2); 
                            ytotal_rgbtBlue += (image[n][p].rgbtBlue * -2); 
                        }
                        // top left, top right (-1)
                        if ((n == (h - 1)) && (p == ((w - 1)) || (p == (w + 1))))
                        {
                            ytotal_rgbtRed += (image[n][p].rgbtRed * -1);
                            ytotal_rgbtGreen += (image[n][p].rgbtGreen * -1); 
                            ytotal_rgbtBlue += (image[n][p].rgbtBlue * -1); 
                        }
                        // middle left, middle, middle right (0)
                        if ((n == (h)) && (p == ((w - 1)) || (p == (w)) || (p == (w + 1))))
                        {
                            ytotal_rgbtRed += (image[n][p].rgbtRed * 0);
                            ytotal_rgbtGreen += (image[n][p].rgbtGreen * 0); 
                            ytotal_rgbtBlue += (image[n][p].rgbtBlue * 0); 
                        }
                        // bottom left, bottom right (1)
                        if ((n == (h - 1)) && (p == ((w - 1)) || (p == (w + 1))))
                        {
                            ytotal_rgbtRed += (image[n][p].rgbtRed * 1);
                            ytotal_rgbtGreen += (image[n][p].rgbtGreen * 1); 
                            ytotal_rgbtBlue += (image[n][p].rgbtBlue * 1); 
                        }
                        // bottom middle (2)
                        if ((n == (h - 1)) && (p == (w)))
                        {
                            ytotal_rgbtRed += (image[n][p].rgbtRed * 2);
                            ytotal_rgbtGreen += (image[n][p].rgbtGreen * 2); 
                            ytotal_rgbtBlue += (image[n][p].rgbtBlue * 2); 
                        }
                    }
                }
            }
            edge_image[h][w].rgbtRed = (int) round(sqrt(((xtotal_rgbtRed * xtotal_rgbtRed) + (ytotal_rgbtRed * ytotal_rgbtRed))));
            edge_image[h][w].rgbtGreen = (int) round(sqrt(((xtotal_rgbtGreen * xtotal_rgbtGreen) + (ytotal_rgbtGreen * ytotal_rgbtGreen))));
            edge_image[h][w].rgbtBlue = (int) round(sqrt(((xtotal_rgbtBlue * xtotal_rgbtBlue) + (ytotal_rgbtBlue * ytotal_rgbtBlue))));
            //printf(" - xTotalRed: %i | yTotalRed: %i | combined: %i\n", xtotal_rgbtRed, ytotal_rgbtRed, edge_image[h][w].rgbtRed);
            //printf(" - xTotalGreen: %i | yTotalGreen: %i | combined: %i\n", xtotal_rgbtGreen, ytotal_rgbtGreen, edge_image[h][w].rgbtGreen);
            //printf(" - xTotalBlue: %i | yTotalBlue: %i | combined: %i\n", xtotal_rgbtBlue, ytotal_rgbtBlue, edge_image[h][w].rgbtBlue);
        }
    }

    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            image[x][y].rgbtRed = max_check(edge_image[x][y].rgbtRed);
            image[x][y].rgbtGreen = max_check(edge_image[x][y].rgbtGreen);
            image[x][y].rgbtBlue = max_check(edge_image[x][y].rgbtBlue);
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