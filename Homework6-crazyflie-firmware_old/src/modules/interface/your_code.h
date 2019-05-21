#ifndef YOUR_CODE_H_
#define YOUR_CODE_H_

#include <stdbool.h>
#include <stdint.h>
#include <math.h>
#include "FreeRTOS.h"
#include "task.h"

#include "system.h"
#include "log.h"
#include "param.h"

#include "sensors.h"
#include "commander.h"
#include "motors.h"

void yourCodeInit(void);
void comp_filter(state_t *state, sensorData_t *sensorData, const uint32_t tick);


#endif /* YOUR_CODE_H_ */
