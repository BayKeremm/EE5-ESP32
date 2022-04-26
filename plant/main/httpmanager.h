#ifndef HTTPMANAGER_H_
#define HTTPMANAGER_H_
void http_POST_measurement_request(char type[50],double value);
void http_GET_ideal_parameters();
void http_GET_day_parameter();
#endif
