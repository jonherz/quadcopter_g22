#include "your_code.h"
#include "stabilizer.h"
#include "estimator_complementary.h"
#include "sensfusion6.h"
#include "position_estimator.h"
#include "sensors.h"

#define ATTITUDE_UPDATE_RATE RATE_250_HZ
#define ATTITUDE_UPDATE_DT 1.0/ATTITUDE_UPDATE_RATE

#define POS_UPDATE_RATE RATE_100_HZ
#define POS_UPDATE_DT 1.0/POS_UPDATE_RATE

void sensorupdate(float gx, float gy, float gz, float ax, float ay, float az, float dt);

static float gravX, gravY, gravZ; // Unit vector in the estimated gravity direction

// The acc in Z for static position (g)
// Set on first update, assuming we are in a static position since the sensors were just calibrates.
// This value will be better the more level the copter is at calibration time
static float baseZacc = 1.0;

static bool isInit;

static bool isCalibrated = false;

void comp_filter(state_t *state, sensorData_t *sensorData, const uint32_t tick)
{
    int gamma = 0.95;
    int     h = 0.01;
    float fx, fy, fz, ax, ay, az, theta, phi;

    xSemaphoreTake(semMutex,1000);
    sensorsAcquire(sensorData, tick); // Read sensors at full rate (1000Hz)

    ax = (*sensorData).acc.ax;
    ay = (*sensorData).acc.ay;
    az = (*sensorData).acc.az;

    if(!((ax == 0.0f) && (ay == 0.0f) && (az == 0.0f)))
    {
        fx = ax*invSqrt(ax * ax + ay * ay + az * az);
        fy = ax*invSqrt(ax * ax + ay * ay + az * az);
        fz = az*invSqrt(ax * ax + ay * ay + az * az);

        theta = (180/pi)*atan2(-fx,sqrt(fy^2 + fz^2));
        phi = (180/pi)*atan2(fy,fz);
        (*state).attitude.roll = (1-gamma)*theta + gamma*((*state).attitude.roll + h*(*sensorData).gyro.y);
        (*state).attitude.pitch = (1-gamma)*phi + gamma*((*state).attitude.pitch + h*(*sensorData).gyro.x);
    }
    xSemaphoreGive(semMutex);
}
