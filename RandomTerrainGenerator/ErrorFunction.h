#pragma once
#include <iostream>

#define FILE_OPEN_OPEN_ERROR 0x000001
#define FILE_SAVE_OPEN_ERROR 0x000002
#define FILE_ROAD_OPEN_ERROR 0x000003

void ShowError(int Code, const char *Message);
void ExplainError(int Code, const char *Message);