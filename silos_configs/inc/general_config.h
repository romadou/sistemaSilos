#ifndef _GENERAL_CONFIG_H
#define _GENERAL_CONFIG_H

#ifndef TEMP_MAX
#define TEMP_MAX 8000
#endif

#ifndef TEMP_MIN
#define TEMP_MIN -400
#endif

#ifndef HUM_MAX
#define HUM_MAX 1000
#endif

#ifndef HUM_MIN
#define HUM_MIN 0
#endif

#ifndef TEMP_SET_OK
#define TEMP_SET_OK 0
#endif

#ifndef TEMP_SET_OK
#define TEMP_SET_OK 0
#endif

#ifndef TEMP_TOO_LOW
#define TEMP_TOO_LOW 1
#endif

#ifndef TEMP_TOO_HIGH
#define TEMP_TOO_HIGH 2
#endif

#ifndef HUM_SET_OK
#define HUM_SET_OK 0
#endif

#ifndef HUM_TOO_LOW
#define HUM_TOO_LOW 1
#endif

#ifndef HUM_TOO_HIGH
#define HUM_TOO_HIGH 2
#endif

void CONFIG_init(void);
int CONFIG_get_desired_temp(void);
int CONFIG_set_desired_temp(int desired_temp);
int CONFIG_check_temp(int temp_in, int temp_out);
int CONFIG_get_desired_hum(void);
int CONFIG_set_desired_hum(int desired_hum);

#endif