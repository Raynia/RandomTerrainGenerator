#include "ErrorFunction.h"

void ShowError(int Code, const char *Message) {
	std::cout << "Error Code : " << Code<<"  ";
	ExplainError(Code, Message);
}

void ExplainError(int Code, const char *Message) {
	switch (Code) {
	case 0x000001:
		std::cout << "\"" << Message << "\" File Open Fail!\n";
		break;
	case 0x000002:
		std::cout << "\"" << Message << "\" File Save Fail!\n";
		break;
	case 0x000003:
		std::cout << "\"" << Message << "\" File Load Fail!\n";
		break;
	case 0x000004:
		std::cout << "\"Terrain Does Not Exist!\"\n";
	}
}