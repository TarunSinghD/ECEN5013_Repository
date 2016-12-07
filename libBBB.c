#include "libBBB.h"

int16_t setUsrLedValue(int8_t* led, int16_t value)
{
	FILE *usr;
	int8_t buf[20];
	int8_t buf2[50] = "/sys/class/leds/beaglebone:green:";

	//build file path to usr led brightness
	sprintf(buf,"%s",led);
	strcat(buf2,strcat(buf,"/brightness"));

	usr = fopen(buf2, "w");
	if(usr == NULL) printf("USR Led failed to open\n");
	fseek(usr,0,SEEK_SET);
	fprintf(usr,"%d",value);
	fflush(usr);
	fclose(usr);

	return 0;
}

int16_t initPin(int16_t pinnum)
{
	FILE *io;

	io = fopen("/sys/class/gpio/export", "w");
	if(io == NULL) printf("Pin failed to initialize\n");
	fseek(io,0,SEEK_SET);
	fprintf(io,"%d",pinnum);
	fflush(io);
	fclose(io);

	return 0;
}

int16_t setPinDirection(int16_t pinnum, int8_t* dir)
{
	FILE *pdir;
	int8_t buf[10];
	int8_t buf2[50] = "/sys/class/gpio/gpio";

	//build file path to the direction file
	sprintf(buf,"%i",pinnum);
	strcat(buf2,strcat(buf,"/direction"));

	pdir = fopen(buf2, "w");
	if(pdir == NULL) printf("Direction failed to open\n");
	fseek(pdir,0,SEEK_SET);
	fprintf(pdir,"%s",dir);
	fflush(pdir);
	fclose(pdir);

	return 0;
}

int16_t setPinValue(int16_t pinnum, int16_t value)
{
	FILE *val;
	int8_t buf[5];
	int8_t buf2[50] = "/sys/class/gpio/gpio";

	//build path to value file
	sprintf(buf,"%i",pinnum);
	strcat(buf2,strcat(buf,"/value"));

	val = fopen(buf2, "w");
	if(val == NULL) printf("Value failed to open\n");
	fseek(val,0,SEEK_SET);
	fprintf(val,"%d",value);
	fflush(val);
	fclose(val);

	return 0;
}

int16_t getPinValue(int16_t pinnum)
{
	FILE *val;
	int16_t value;
	int8_t buf[5];
	int8_t buf2[50] = "/sys/class/gpio/gpio";

	//build file path to value file
	sprintf(buf,"%i",pinnum);
	strcat(buf2,strcat(buf,"/value"));

	val = fopen(buf2, "r");
	if(val == NULL) printf("Input value failed to open\n");
	fseek(val,0,SEEK_SET);
	fscanf(val,"%d",&value);
	fclose(val);

	return value;
}

int16_t initPWM(int16_t mgrnum, int8_t* pin)
{
	FILE *pwm;
	int8_t buf[5];
	int8_t buf2[50] = "/sys/devices/bone_capemgr.";
	int8_t buf3[20] = "bone_pwm_";

	//build file paths
	sprintf(buf,"%i",mgrnum);
	strcat(buf2,strcat(buf,"/slots"));

	strcat(buf3,pin);

	pwm = fopen(buf2, "w");
	if(pwm == NULL) printf("PWM failed to initialize\n");
	fseek(pwm,0,SEEK_SET);
	fprintf(pwm,"am33xx_pwm");
	fflush(pwm);
	fprintf(pwm,"%s",buf3);
	fflush(pwm);
	fclose(pwm);

	return 0;
}

int16_t setPWMPeriod(int16_t helpnum, int8_t* pin, int16_t period)
{
	FILE *pwm;
	int8_t buf[5];
	int8_t buf2[60] = "/sys/devices/ocp.2/pwm_test_";

	//build file path
	sprintf(buf,"%i",helpnum);
	printf("%s\n",pin);
	strcat(buf2,pin);
	strcat(buf2,".");
	strcat(buf2,strcat(buf,"/period"));
	
	printf("%s\n",buf2);
	pwm = fopen(buf2, "w");
	if(pwm == NULL) printf("PWM Period failed to open\n");
	fseek(pwm,0,SEEK_SET);
	fprintf(pwm,"%d",period);
	fflush(pwm);
	fclose(pwm);

	return 0;
}

int16_t setPWMDuty(int16_t helpnum, int8_t* pin, int16_t duty)
{
	FILE *pwm;
	int8_t buf[5];
	int8_t buf2[50] = "/sys/devices/ocp.2/pwm_test_";

	//build file path
	sprintf(buf,"%i",helpnum);
	strcat(buf2,pin);
	strcat(buf2,".");
	strcat(buf2,strcat(buf,"/duty"));

	pwm = fopen(buf2, "w");
	if(pwm == NULL) printf("PWM Duty failed to open\n");
	fseek(pwm,0,SEEK_SET);
	fprintf(pwm,"%d",duty);
	fflush(pwm);
	fclose(pwm);

	return 0;
}

int16_t setPWMOnOff(int16_t helpnum, int8_t* pin, int16_t run)
{
	FILE *pwm;
	int8_t buf[5];
	int8_t buf2[50] = "/sys/devices/ocp.2/pwm_test_";

	//build file path
	sprintf(buf,"%i",helpnum);
	strcat(buf2,pin);
	strcat(buf2,".");
	strcat(buf2,strcat(buf,"/run"));

	pwm = fopen(buf2, "w");
	if(pwm == NULL) printf("PWM Run failed to open\n");
	fseek(pwm,0,SEEK_SET);
	fprintf(pwm,"%d",run);
	fflush(pwm);
	fclose(pwm);

	return 0;
}

int16_t initUART(int16_t mgrnum, int8_t* uartnum)
{
	//This function loads the overlay
	FILE *uart;
	int8_t buf[5];
	int8_t buf2[50] = "/sys/devices/bone_capemgr.";

	sprintf(buf,"%i",mgrnum);
	strcat(buf2,strcat(buf,"/slots"));

	uart = fopen(buf2, "w");
	if(uart == NULL) printf("UART overlay failed to load\n");
	fseek(uart,0,SEEK_SET);
	fprintf(uart,uartnum);
	fflush(uart);
	fclose(uart);

	return 0;
}

int16_t configUART(UART u, int16_t property, int8_t* value)
{

	return 0;
}

int16_t txUART(int16_t uart, unsigned int8_t data)
{

	return 0;
}

unsigned int8_t rxUART(int16_t uart)
{

	return 0;
}

int16_t strUART(int16_t uart, int8_t* buf)
{

	return 0;
}

int16_t initADC(int16_t mgrnum)
{
	FILE *ain;
	int8_t buf[5];
	int8_t buf2[50] = "/sys/devices/bone_capemgr.";

	//build path to setup ain
	sprintf(buf,"%i",mgrnum);
	strcat(buf2,strcat(buf,"/slots"));

	ain = fopen(buf2, "w");
	if(ain == NULL) printf("Analog failed load\n");
	fseek(ain,0,SEEK_SET);
	fprintf(ain,"cape-bone-iio");
	fflush(ain);
	fclose(ain);

	return 0;
}

int16_t readADC(int16_t helpnum, int8_t* ach)
{
	FILE *aval;
	int16_t value;
	int8_t buf[5];
	int8_t buf2[50] = "/sys/devices/ocp.2/helper.";

	//build file path to read adc
	sprintf(buf,"%i",helpnum);
	strcat(buf2,strcat(buf,ach));
	
	aval = fopen(buf2, "r");
	if(aval == NULL) printf("Analog failed to open\n");
	fseek(aval,0,SEEK_SET);
	fscanf(aval,"%d",&value);
	fflush(aval);
	fclose(aval);

	return value;
}

void pauseSec(int16_t sec)
{
	time_t now,later;

	now = time(NULL);
	later = time(NULL);

	while((later - now) < (double)sec)
		later = time(NULL);
}

int16_t pauseNanoSec(long nano)
{
	struct timespec tmr1,tmr2;

	//assume you are not trying to pause more than 1s
	tmr1.tv_sec = 0;
	tmr1.tv_nsec = nano;

	if(nanosleep(&tmr1, &tmr2) < 0)
	{
		printf("Nano second pause failed\n");
		return -1;
	}
	return 0;
}
