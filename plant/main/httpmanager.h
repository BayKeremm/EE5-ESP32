#ifndef HTTPMANAGER_H_
#define HTTPMANAGER_H_
#define REAL_TO_STRING(s) #s
#define TO_STRING(s) REAL_TO_STRING(s)
void http_POST_measurement_request(char type[50],int timestamp,double value);
void http_GET_ideal_parameters(char * deviceId);
void http_GET_day_parameter();
#endif
