#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#define MIN_CROSSING_DELAY 500
#define CROSSING_DELAY 1000
#define ARRIVE_DELAY 1500

xTaskHandle *batTaskHandles; // Create as a pointer since the number of bats are unknown at compile time
SemaphoreHandle_t semMutex;
SemaphoreHandle_t NorthMutex;
SemaphoreHandle_t SouthMutex;
SemaphoreHandle_t EastMutex;
SemaphoreHandle_t WestMutex;

int *batIds;

volatile int counter = 0;

void goSouth(int batId)
{
	const TickType_t waitingToArriveDelay = (rand() % ARRIVE_DELAY) / portTICK_PERIOD_MS; // Generate a random delay 
	const TickType_t crossingDelay = (rand() % CROSSING_DELAY + MIN_CROSSING_DELAY) / portTICK_PERIOD_MS; 
	
	vPrintf("BAT %d from North has started to run and is on its way to the crossing\n", batId);

	vTaskDelay(waitingToArriveDelay);   

	
	vPrintf("BAT %d from North arrives at crossing\n", batId);

	if (xSemaphoreTake(semMutex,10000)){
	vPrintf("BAT %d from North enters crossing\n", batId);

	vTaskDelay(crossingDelay);   

	vPrintf("BAT %d from North leaving crossing\n", batId);    
	xSemaphoreGive(semMutex);
	vTaskDelay(waitingToArriveDelay);
	}
}

void goNorth(int batId)
{
	const TickType_t waitingToArriveDelay = (rand() % ARRIVE_DELAY) / portTICK_PERIOD_MS; // Generate a random delay 
	const TickType_t crossingDelay = (rand() % CROSSING_DELAY + MIN_CROSSING_DELAY) / portTICK_PERIOD_MS;

	vPrintf("BAT %d from South has started to run and is on its way to the crossing\n", batId);

	vTaskDelay(waitingToArriveDelay);   

	vPrintf("BAT %d from South arrives at crossing\n", batId);

	if (xSemaphoreTake(semMutex,10000)){
	vPrintf("BAT %d from South enters crossing\n", batId);

	vTaskDelay(crossingDelay);   

	vPrintf("BAT %d from South leaving crossing\n", batId);    
	xSemaphoreGive(semMutex);
	vTaskDelay(waitingToArriveDelay);
	}
}

void goEast(int batId)
{
	const TickType_t waitingToArriveDelay = (rand() % ARRIVE_DELAY) / portTICK_PERIOD_MS; // Generate a random delay   
	const TickType_t crossingDelay = (rand() % CROSSING_DELAY + MIN_CROSSING_DELAY) / portTICK_PERIOD_MS; 
	
	vPrintf("BAT %d from West has started to run and is on its way to the crossing\n", batId);

	vTaskDelay(waitingToArriveDelay);   

	vPrintf("BAT %d from West arrives at crossing\n", batId);

	if (xSemaphoreTake(semMutex,10000)){
	vPrintf("BAT %d from West enters crossing\n", batId);

	vTaskDelay(crossingDelay);   

	vPrintf("BAT %d from West leaving crossing\n", batId);    
	xSemaphoreGive(semMutex);
	vTaskDelay(waitingToArriveDelay);
	}
}

void goWest(int batId)
{
	const TickType_t waitingToArriveDelay = (rand() % ARRIVE_DELAY) / portTICK_PERIOD_MS; // Generate a random delay 
	const TickType_t crossingDelay = (rand() % CROSSING_DELAY + MIN_CROSSING_DELAY) / portTICK_PERIOD_MS; 
	
	vPrintf("BAT %d from East has started to run and is on its way to the crossing\n", batId);

	vTaskDelay(waitingToArriveDelay);   

	vPrintf("BAT %d from East arrives at crossing\n", batId);
	
	if (xSemaphoreTake(semMutex,10000)){
	vPrintf("BAT %d from East enters crossing\n", batId);

	vTaskDelay(crossingDelay);   

	vPrintf("BAT %d from East leaving crossing\n", batId);    
	xSemaphoreGive(semMutex);
	vTaskDelay(waitingToArriveDelay);
	}
}

void batFromNorth(void *pvParameters)
{
	int batId = *(int *)pvParameters;
	int a = 0;
	while (1) // Repeat forever
	{
	if (xSemaphoreTake(NorthMutex,10) && a == 0){		
	goSouth(batId); 
        a = 1;
	xSemaphoreGive(NorthMutex);	
	}
	if (xSemaphoreTake(NorthMutex,10) && a == 1){	
	goNorth(batId);
 	a = 0;
	xSemaphoreGive(NorthMutex);
	}
	}
}

void batFromSouth(void *pvParameters)
{
	int batId = *(int *)pvParameters;
	int b = 0;
	while (1)
	{
	if (xSemaphoreTake(SouthMutex,10) && b==0){
	goNorth(batId); 
	b = 1; 
	xSemaphoreGive(SouthMutex);	
 	}

	if (xSemaphoreTake(SouthMutex,10) && b==1){
	goSouth(batId);
	b = 0;	
	xSemaphoreGive(SouthMutex);
	}
	}
}

void batFromEast(void *pvParameters)
{
	int batId = *(int *)pvParameters;
	int c=0;
	while (1)
	{
	if (xSemaphoreTake(EastMutex,10) && c==0){
	goWest(batId); 
	c = 1;
        xSemaphoreGive(EastMutex);
        }
	if (xSemaphoreTake(EastMutex,10) && c==1){
	goEast(batId);
	c =0;
	xSemaphoreGive(EastMutex);
	}
	}
}

void batFromWest(void *pvParameters)
{	
	int batId = *(int *)pvParameters;
	int d = 0;
	while (1)
	{
	if (xSemaphoreTake(WestMutex,10) && d==0){
        goEast(batId);
	d = 1; 
        xSemaphoreGive(WestMutex);
        }
        
        if (xSemaphoreTake(WestMutex,10) && d==1){
        goWest(batId);
	d = 0;
	xSemaphoreGive(WestMutex);
        }
	}
}


int main(int argc, char **argv)
{
	int batId;
	int numberOfBats;
	semMutex = xSemaphoreCreateMutex();
	NorthMutex = xSemaphoreCreateMutex();
	SouthMutex = xSemaphoreCreateMutex();
	EastMutex = xSemaphoreCreateMutex();
	WestMutex = xSemaphoreCreateMutex();
	if (argc < 2)
	{
		vPrintf("Argument missing, specify sequence of arrivals. Example: ./batman nsewwewn\n");
		exit(-1);
	}
	
	char *commands = argv[1];
	numberOfBats = strlen(argv[1]);

	batTaskHandles = malloc(sizeof(xTaskHandle) * numberOfBats); // Allocate memory for the task handles
	batIds = malloc(sizeof(int) * numberOfBats); // Allocate memory for the task ids
	
	for (batId = 0; batId < numberOfBats; batId++)
	{
		batIds[batId] = batId;
		char currentBatDirection = (argv[1])[batId];
		char batTaskIdentity[50];
		
		if (currentBatDirection == 'n')
		{
			sprintf(batTaskIdentity, "Bat %d from North", batId);
			xTaskCreate(batFromNorth, batTaskIdentity, configMINIMAL_STACK_SIZE, (void *)&batIds[batId], 1, batTaskHandles[batId]);  
			vPrintf("Created task \"Bat %d from North\"\n", batId); 	
		}
		else if (currentBatDirection == 's')
		{
			sprintf(batTaskIdentity, "Bat %d from South", batId);
			xTaskCreate(batFromSouth, batTaskIdentity, configMINIMAL_STACK_SIZE, (void *)&batIds[batId], 1, batTaskHandles[batId]);  
			vPrintf("Created task \"Bat %d from South\"\n", batId);   	
		}
		else if (currentBatDirection == 'e')
		{
			sprintf(batTaskIdentity, "Bat %d from East", batId);
			xTaskCreate(batFromEast, batTaskIdentity, configMINIMAL_STACK_SIZE, (void *)&batIds[batId], 1, batTaskHandles[batId]);  
			vPrintf("Created task \"Bat %d from East\"\n", batId);    	
		}  
		else if (currentBatDirection == 'w')
		{
			sprintf(batTaskIdentity, "Bat %d from West", batId);
			xTaskCreate(batFromWest, batTaskIdentity, configMINIMAL_STACK_SIZE, (void *)&batIds[batId], 1, batTaskHandles[batId]);  
			vPrintf("Created task \"Bat %d from West\"\n", batId);    	
		}    	
		else
		{
			vPrintf("Unknown direction: %c\n", currentBatDirection);
			exit(-1);   	
		} 	

	}
	
	vTaskStartScheduler();
	while (1)
	{
		// Do nothing
	};

	free(batTaskHandles); // Return memory for the task handles
	return 0;
}

