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

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    printf("height[%i] x width[%i]\n", height, width);
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int sepiaRed = round(((float) image[h][w].rgbtRed * 0.393) + ((float) image[h][w].rgbtGreen * 0.769) + ((float) image[h][w].rgbtBlue * 0.189));
            int sepiaGreen = round(((float) image[h][w].rgbtRed * 0.349) + ((float) image[h][w].rgbtGreen * 0.686) + ((float) image[h][w].rgbtBlue * 0.168));
            int sepiaBlue = round(((float) image[h][w].rgbtRed * 0.272) + ((float) image[h][w].rgbtGreen * 0.534) + ((float) image[h][w].rgbtBlue * 0.131));
            image[h][w].rgbtRed = max_check(sepiaRed);
            image[h][w].rgbtGreen = max_check(sepiaGreen);
            image[h][w].rgbtBlue = max_check(sepiaBlue);
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


int max_check(int n)
{
    int max = n;
    if (max > 255)
    {
        max = 255;
    }
	return max;
}