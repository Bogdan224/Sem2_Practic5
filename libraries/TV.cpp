#include "TV.h"
void Init(TV* tv, const char model[20], int displaySize, bool haveWIFI)
{
	strncpy(tv->_model, model, 20);
	tv->_displaySize = displaySize;
	tv->_haveWIFI = haveWIFI;
}
void PrintTV(TV* tv)
{
	printf("Model: %s\nDisplay size: %d\n", tv->_model, tv->_displaySize);
	if (tv->_haveWIFI) {
		printf("Have WIFI: Yes\n");
	}
	else {
		printf("Have WIFI: No\n");
	}
	printf("\n");
}