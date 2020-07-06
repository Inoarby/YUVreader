#include "stdafx.h"
#include "YUVreader.h"


YUV_FILE* YUVopen(const char* file_name, int width, int height, const char* format){

	YUV_FILE* yuv_file = (YUV_FILE*) malloc(sizeof(YUV_FILE));
	if (yuv_file == NULL) return 0;

	yuv_file->frame_count	= 0;
	yuv_file->width			= width;
	yuv_file->height		= height;
	yuv_file->FILE_NAME		= (char*)malloc(sizeof(char) * 528);
	yuv_file->FORMAT		= (char*)malloc(sizeof(char) * 16);
	strcpy(yuv_file->FILE_NAME, file_name);
	strcpy(yuv_file->FORMAT, format);

	yuv_file->fp			= fopen(file_name, "rb"); // Consider checking fp validity here.

	return(yuv_file);
}

int YUVclose(YUV_FILE* yuv_file){

	int i = fclose(yuv_file->fp);
	free(yuv_file);

	if (i == EOF) return(-1);
	return(0);

}


int YUVread_frame(uint8_t* y_comp, uint8_t* u_comp, uint8_t* v_comp, YUV_FILE* yuv_file){

	int luma_res, chroma_res;
	size_t pixel_depth;

	if (!strcmp(yuv_file->FORMAT, "i420")){
		luma_res = yuv_file->width * yuv_file->height;
		chroma_res = (int)(luma_res / 4); // What if resolution does not devide 4?
		pixel_depth = sizeof(uint8_t);
	}

	size_t noy = fread(y_comp, pixel_depth, luma_res, yuv_file->fp);
	size_t nou = fread(u_comp, pixel_depth, chroma_res, yuv_file->fp);
	size_t nov = fread(v_comp, pixel_depth, chroma_res, yuv_file->fp);

	// Consider checking read validity here.
	//if () return();
	yuv_file->frame_count += 1;

	return 0;
}


int YUVwrite_frame(const uint8_t* y_comp, const uint8_t* u_comp, const uint8_t* v_comp, 
				   const YUV_FILE* yuv_file, FILE* fp){

	int luma_res, chroma_res;
	size_t pixel_depth;

	if (!strcmp(yuv_file->FORMAT, "i420")){

		luma_res = yuv_file->width * yuv_file->height;
		chroma_res = (int)(luma_res / 4);
		pixel_depth = sizeof(uint8_t);
	}

	size_t noy = fwrite(y_comp, pixel_depth, luma_res, fp);
	size_t nou = fwrite(u_comp, pixel_depth, chroma_res, fp);
	size_t nov = fwrite(v_comp, pixel_depth, chroma_res, fp);

	return(0);
}


int YUVseek_frame(int frame_count, YUV_FILE* yuv_file);
int YUVtell_frame(YUV_FILE* yuv_file);



