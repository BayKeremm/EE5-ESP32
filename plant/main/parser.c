#include "parser.h"
#include <stdio.h>
#include "cJSON.h"
// globals
extern double idealParams[3];
extern double dayWait[2];
extern double ownershipId;

void parseIdealParams(char * response){
    const cJSON * T = NULL;
    const cJSON * M=NULL;
    const cJSON * L=NULL;
    const cJSON * owner_id=NULL;
    cJSON *response_json = cJSON_Parse(response);

    if (response_json == NULL)
    {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
        {
        }
        goto end;
    }

    T = cJSON_GetObjectItem(response_json,"idealTemperature");
    M = cJSON_GetObjectItem(response_json,"idealMoisture");
    L = cJSON_GetObjectItem(response_json,"idealLight");
    owner_id = cJSON_GetObjectItem(response_json,"id");
    if (!cJSON_IsNumber(T) || !cJSON_IsNumber(M)||!cJSON_IsNumber(L)||!cJSON_IsNumber(owner_id))
    {
        goto end;
    }
    idealParams[0] = T->valuedouble;
    idealParams[1] = M->valuedouble;
    idealParams[2] = L->valuedouble;
    ownershipId = owner_id->valuedouble;
    goto end;


    end:
    cJSON_Delete(response_json);
}
void parseDayParams(char * response){
    const cJSON * day = NULL;
    const cJSON * wait=NULL;
    cJSON *response_json = cJSON_Parse(response);

    if (response_json == NULL)
    {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
        {
        }
        goto end;
    }

    day = cJSON_GetObjectItem(response_json,"day");
    wait = cJSON_GetObjectItem(response_json,"wait");
    if (!cJSON_IsNumber(day) || !cJSON_IsNumber(wait))
    {
        goto end;
    }
    dayWait[0] = day->valuedouble;
    dayWait[1] = wait->valuedouble;
    goto end;


    end:
    cJSON_Delete(response_json);
}
