#ifndef _REPORTS_H
#define _REPORTS_H

#ifndef TEMP_OK
#define TEMP_OK 44
#endif

#ifndef TEMP_ALERT
#define TEMP_ALERT 45
#endif

#ifndef TEMP_DANGER
#define TEMP_DANGER 46
#endif

#ifndef HUM_OK
#define HUM_OK 54
#endif

#ifndef HUM_ALERT
#define HUM_ALERT 55
#endif

#ifndef HUM_DANGER
#define HUM_DANGER 56
#endif

void REPORTE_general(int temp_in, int temp_out, int hum_in, int hum_out);

#endif