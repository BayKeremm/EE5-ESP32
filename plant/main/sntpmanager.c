#include "config.h"


static void initialize_sntp(void)
{
    ESP_LOGI(TAG, "Initializing SNTP");

}



int obtaintime(){
	int time;
    initialize_sntp();
	return time;
}
