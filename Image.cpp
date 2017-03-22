//*****************************************************************************
//
// Image.cpp : Defines the class operations on images
//
// Author - Parag Havaldar
// Code used by students as starter code to display and modify images
//
//*****************************************************************************

#include "Image.h"
#include <cmath>

// Constructor and Desctructors
MyImage::MyImage()
{
	Data = NULL;
	Width = -1;
	Height = -1;
	ImagePath[0] = 0;
}

MyImage::~MyImage()
{
	if (Data)
		delete Data;
}


// Copy constructor
MyImage::MyImage(MyImage *otherImage)
{
	Height = otherImage->Height;
	Width = otherImage->Width;
	Data = new char[Width*Height * 3];
	strcpy(otherImage->ImagePath, ImagePath);

	for (int i = 0; i<(Height*Width * 3); i++)
	{
		Data[i] = otherImage->Data[i];
	}
}



// = operator overload
MyImage & MyImage::operator= (const MyImage &otherImage)
{
	Height = otherImage.Height;
	Width = otherImage.Width;
	Data = new char[Width*Height * 3];
	strcpy((char *)otherImage.ImagePath, ImagePath);

	for (int i = 0; i<(Height*Width * 3); i++)
	{
		Data[i] = otherImage.Data[i];
	}

	return *this;

}

// MyImage::CreatImageCanv
// Function to create white image with two dots connected
bool MyImage::CreatImageCanv()
{
	// Allocate Data structure and copy
	Data = new char[Width*Height * 3];
	for (int i = 0; i < Height*Width; i++)
	{
		Data[3 * i] = 255;
		Data[3 * i + 1] = 255;
		Data[3 * i + 2] = 255;
	}

	// two coordinates to connect a line, x is for height, y is for row
	int x1 = 256, y1 = 256;
	int x2 = 512, y2 = 0;

	int start_x = x1, start_y = y1, end_x = x2, end_y = y2;
	int dx = x2 - x1;
	int dy = y2 - y1;
	double slope = 0;

	bool anchor_x;
	if (dx != 0) slope = dy / (double)dx;

	if (abs(slope) <= 1 && dx != 0) {
		anchor_x = true;
		if (dx < 0) {
			start_x = x2;
			start_y = y2;
			end_x = x1;
			end_y = y1;
		}
		slope = (end_y - start_y) / (double)(end_x - start_x);
	}
	else {
		anchor_x = false;
		if (dy < 0) {
			start_x = x2;
			start_y = y2;
			end_x = x1;
			end_y = y1;
		}
		if (dx == 0) { slope = 0; }
		else { slope = (end_x - start_x) / (double)(end_y - start_y); }
	}

	// set starting point to zero first
	Data[start_y*Width * 3 + start_x * 3] = 0;
	Data[start_y*Width * 3 + start_x * 3 + 1] = 0;
	Data[start_y*Width * 3 + start_x * 3 + 2] = 0;

	if (anchor_x) {
		double y = start_y + 0.5;
		for (int x = start_x + 1; x <= end_x; x++) {
			y = y + slope;
			int int_y = (int)floor(y);
			Data[int_y*Width * 3 + x * 3] = 0;
			Data[int_y*Width * 3 + x * 3 + 1] = 0;
			Data[int_y*Width * 3 + x * 3 + 2] = 0;
		}
	}
	else {
		double x = start_x + 0.5;
		for (int y = start_y + 1; y <= end_y; y++) {
			x = x + slope;
			int int_x = (int)floor(x);
			Data[y*Width * 3 + int_x * 3] = 0;
			Data[y*Width * 3 + int_x * 3 + 1] = 0;
			Data[y*Width * 3 + int_x * 3 + 2] = 0;
		}
	}
	return true;
}

//Scale Image

//create Box

bool MyImage::CreateLines(int x1, int y1, int x2, int y2)
{
	// Allocate Data structure and copy

	int start_x = x1, start_y = y1, end_x = x2, end_y = y2;
	int dx = x2 - x1;
	int dy = y2 - y1;
	double slope = 0;

	bool anchor_x;
	if (dx != 0) slope = dy / (double)dx;

	if (abs(slope) <= 1 && dx != 0) {
		anchor_x = true;
		if (dx < 0) {
			start_x = x2;
			start_y = y2;
			end_x = x1;
			end_y = y1;
		}
		slope = (end_y - start_y) / (double)(end_x - start_x);
	}
	else {
		anchor_x = false;
		if (dy < 0) {
			start_x = x2;
			start_y = y2;
			end_x = x1;
			end_y = y1;
		}
		if (dx == 0) { slope = 0; }
		else { slope = (end_x - start_x) / (double)(end_y - start_y); }
	}

	// set starting point to zero first
	Data[start_y*Width * 3 + start_x * 3] = 0;
	Data[start_y*Width * 3 + start_x * 3 + 1] = 0;
	Data[start_y*Width * 3 + start_x * 3 + 2] = 0;

	if (anchor_x) {
		double y = start_y + 0.5;
		for (int x = start_x + 1; x <= end_x; x++) {
			y = y + slope;
			int int_y = (int)floor(y);
			Data[int_y*Width * 3 + x * 3] = 0;
			Data[int_y*Width * 3 + x * 3 + 1] = 0;
			Data[int_y*Width * 3 + x * 3 + 2] = 0;
		}
	}
	else {
		double x = start_x + 0.5;
		for (int y = start_y + 1; y <= end_y; y++) {
			x = x + slope;
			int int_x = (int)floor(x);
			Data[y*Width * 3 + int_x * 3] = 0;
			Data[y*Width * 3 + int_x * 3 + 1] = 0;
			Data[y*Width * 3 + int_x * 3 + 2] = 0;
		}
	}
	return true;
}

//RotateLines
void MyImage::rotate_point(float cx, float cy, float angle, int *newx, int *newy)
{
	int rot_degree = 360;
	float s = sin(angle);
	float c = cos(angle);
	float xnew, ynew;
	// translate point back to origin:
	if (rot_degree == 360)
	{
		*newx -= cx;
		*newy -= cy;
		// rotate point
		xnew = *newx * c - *newy * s;
		ynew = *newx * s + *newy * c;
		*newx = xnew + cx;
		*newy = ynew + cy;
	}
}

//Intersection
void MyImage::intersection(int x1, int y1, int *x2, int *y2, int x3, int y3, int x4, int y4, float angle)
{
	float m1, m2, c1, c2;
	float dx1, dx2, dy1, dy2;
	float int_x, int_y;
	float angle_sum = 360;

	if (angle > 0 && angle <= 90 && angle_sum == 360)
	{
		x3 = 511; y3 = 0; x4 = 511, y4 = 511;
	}
	else if (angle > 90 && angle <= 180 && angle_sum == 360)
	{
		x3 = 511; y3 = 511; x4 = 0; y4 = 511;
	}
	else if (angle > 180 && angle <= 270 && angle_sum == 360)
	{
		x3 = 0; y3 = 511; x4 = 0; y4 = 0;
	}
	else 
	{
		if (angle_sum == 360) {
			x3 = 0; y3 = 0; x4 = 511; y4 = 0;
		}
	}


	dx1 = *x2 - x1;
	dy1 = *y2 - y1;
	dx2 = x4 - x3;
	dy2 = y4 - y3;

	if (dx1 == 0)
	{
		dx1 = 1;
	}
	if (dx2 == 0)
	{
		dx2 = 1;
	}

	m1 = dy1 / dx1;
	m2 = dy2 / dx2;

	c1 = y1 - m1 * x1;
	c2 = y3 - m2 * x3;

	if ((m1 - m2) == 0)
	{
	}
	else
	{
		int_x = (c2 - c1) / (m1 - m2);
		int_y = m1 * int_x + c1;
	}
	*x2 = int_x;
	*y2 = int_y;


}

//scale - data
void MyImage::CreatImageScale(int width, int height)
{
	// Allocate Data structure and copy
	Data = new char[width*height * 4];

	for (int i = 0; i < height*width; i++)
	{
		Data[3 * i] = 255;
		Data[3 * i + 1] = 255;
		Data[3 * i + 2] = 255;
	}

}

//find average
char MyImage:: get_average(char *Data, int index, float scale) {
	float average = 0;
	int res, i, j;
	for (i = 0; i < scale; i++) {
		for (j = 0; j < scale; j++) {
			average += Data[(3 * 512 * i) + ((3 * j) + index)];
		}
	}
	average = average / (scale * scale);
	res = (int)average;
	return res;
}


void MyImage::ScaleImage(const MyImage &inImage, float scale, int anti_alias)
{
	int outindex = 0;
	Data = new char[((511 / (float)scale) + 1) * ((511 / (float)scale) + 1) * 3];
	strcpy((char *)inImage.ImagePath, ImagePath);
	int width = inImage.Height;
	int height = inImage.Height;
	int scale_val = 0;
	if (anti_alias == 0) {
		for (int i = 0; i < width; i += scale) {
			for (int j = 0; j < width; j += scale) {
				if (scale_val == 0)
				{
					bool data_flag = true;
					if (data_flag)
					{
						Data[3 * outindex] = inImage.Data[(3 * 512 * i) + ((3 * j) + 0)];
						Data[3 * outindex + 1] = inImage.Data[(3 * 512 * i) + ((3 * j) + 1)];
						Data[3 * outindex + 2] = inImage.Data[(3 * 512 * i) + ((3 * j) + 2)];
						outindex++;
					}
					else {
						data_flag = false;
					}
				}
			}
		}
		CreateLines(0, 511.0/scale, 511.0/scale, 511.0/scale);
		CreateLines(511.0/scale, 0, 511.0/scale, 511.0/scale);
	}
	else {
		for (int i = 0; i < width; i += scale) {
			for (int j = 0; j < height; j += scale) {
				if (scale_val == 0)
				{
					bool data_flag = true;
					if (data_flag)
					{
						Data[3 * outindex] = get_average(inImage.Data, ((3 * 512 * i) + (3 * j)), scale);
						Data[3 * outindex + 1] = get_average(inImage.Data, ((3 * 512 * i) + ((3 * j) + 1)), scale);
						Data[3 * outindex + 2] = get_average(inImage.Data, ((3 * 512 * i) + ((3 * j) + 2)), scale);
						outindex++;
					}
					else
					{
						data_flag = false;
					}
				}
			}
		}
	}
}


// MyImage::ReadImage
// Function to read the image given a path
bool MyImage::ReadImage()
{

	// Verify ImagePath
	if (ImagePath[0] == 0 || Width < 0 || Height < 0)
	{
		fprintf(stderr, "Image or Image properties not defined");
		fprintf(stderr, "Usage is `Image.exe Imagefile w h`");
		return false;
	}

	// Create a valid output file pointer
	FILE *IN_FILE;
	IN_FILE = fopen(ImagePath, "rb");
	if (IN_FILE == NULL)
	{
		fprintf(stderr, "Error Opening File for Reading");
		return false;
	}

	// Create and populate RGB buffers
	int i;
	char *Rbuf = new char[Height*Width];
	char *Gbuf = new char[Height*Width];
	char *Bbuf = new char[Height*Width];

	for (i = 0; i < Width*Height; i++)
	{
		Rbuf[i] = fgetc(IN_FILE);
	}
	for (i = 0; i < Width*Height; i++)
	{
		Gbuf[i] = fgetc(IN_FILE);
	}
	for (i = 0; i < Width*Height; i++)
	{
		Bbuf[i] = fgetc(IN_FILE);
	}

	// Allocate Data structure and copy
	Data = new char[Width*Height * 3];
	for (i = 0; i < Height*Width; i++)
	{
		Data[3 * i] = Bbuf[i];
		Data[3 * i + 1] = Gbuf[i];
		Data[3 * i + 2] = Rbuf[i];
	}

	// Clean up and return
	delete Rbuf;
	delete Gbuf;
	delete Bbuf;
	fclose(IN_FILE);

	return true;

}



// MyImage functions defined here
bool MyImage::WriteImage()
{
	// Verify ImagePath
	// Verify ImagePath
	if (ImagePath[0] == 0 || Width < 0 || Height < 0)
	{
		fprintf(stderr, "Image or Image properties not defined");
		return false;
	}

	// Create a valid output file pointer
	FILE *OUT_FILE;
	OUT_FILE = fopen(ImagePath, "wb");
	if (OUT_FILE == NULL)
	{
		fprintf(stderr, "Error Opening File for Writing");
		return false;
	}

	// Create and populate RGB buffers
	int i;
	char *Rbuf = new char[Height*Width];
	char *Gbuf = new char[Height*Width];
	char *Bbuf = new char[Height*Width];

	for (i = 0; i < Height*Width; i++)
	{
		Bbuf[i] = Data[3 * i];
		Gbuf[i] = Data[3 * i + 1];
		Rbuf[i] = Data[3 * i + 2];
	}


	// Write data to file
	for (i = 0; i < Width*Height; i++)
	{
		fputc(Rbuf[i], OUT_FILE);
	}
	for (i = 0; i < Width*Height; i++)
	{
		fputc(Gbuf[i], OUT_FILE);
	}
	for (i = 0; i < Width*Height; i++)
	{
		fputc(Bbuf[i], OUT_FILE);
	}

	// Clean up and return
	delete Rbuf;
	delete Gbuf;
	delete Bbuf;
	fclose(OUT_FILE);

	return true;

}




// Here is where you would place your code to modify an image
// eg Filtering, Transformation, Cropping, etc.
bool MyImage::Modify()
{

	// TO DO by student

	// sample operation
	for (int i = 0; i<Width*Height; i++)
	{
		Data[3 * i] = 0;
		Data[3 * i + 1] = 0;
	}

	return false;
}