#include "Platform.h"
void LoadVectorFromFile(CP_Vector* _vec, FILE* _inFile)
{
	char str[BUFFERSIZE] = { '\0' };
	fgets(str, BUFFERSIZE, _inFile);
	sscanf_s(str, "%f %f", &_vec->x, &_vec->y);
}

void LoadIntegerFromFile(int* _value, FILE* _inFile)
{
	char str[BUFFERSIZE] = { '\0' };
	fgets(str, BUFFERSIZE, _inFile);
	sscanf_s(str, "%d",_value);
}

void LoadFloatFromFile(float* _value, FILE* _inFile)
{
	char str[BUFFERSIZE] = { '\0' };
	fgets(str, BUFFERSIZE, _inFile);
	sscanf_s(str, "%f",_value);
}

void LoadColorFromFile(CP_Color* _col, FILE* _inFile)
{
	char str[BUFFERSIZE] = { '\0' };
	fgets(str, BUFFERSIZE, _inFile);

	int color[4] = { 0 };

	sscanf_s(str, "%d %d %d %d", &color[0], &color[1],
		&color[2], &color[3]);

	for (int i = 0; i < 4; i++)
		_col->rgba[i] = (char)color[i];
}

void Platform_Load(FILE* _inFile, char* str)
{

	_inFile=fopen(str, "r");

	if (_inFile == NULL)
	{
		printf("Error! Platform File is not exists : (function)Map_Load");
		return;
	}

	//MAP_LOAD	
	//1. ÇÃ·§Æû °¹¼ö ºÒ·¯¿À±â
	int i_value = 0;
	LoadIntegerFromFile(&i_value, _inFile);
	//2. ÇÃ·§Æû Position
	CP_Vector CP_Pos;
	LoadVectorFromFile(&CP_Pos, _inFile);
	
	//3. ÇÃ·§Æû »çÀÌÁî
	float f_value;
	LoadFloatFromFile(&f_value, _inFile);
	LoadFloatFromFile(&f_value, _inFile);
	//4. gap »çÀÌÁî
	CP_Vector CP_Gap;
	LoadVectorFromFile(&CP_Gap, _inFile);		

	//5. ÇÃ·§Æû Å¸ÀÔ <- º¸·ùÁß 
	int type;
	LoadIntegerFromFile(&type, _inFile);
}