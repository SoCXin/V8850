#define SAMPLETIMES		5			//12

void qprintf(const char* str, ...);
void qsprintf(unsigned char* ostr, const char* str, ...);
unsigned short crc16r(unsigned char *ptr, unsigned char length);
unsigned char bccCheck(unsigned char *dat, unsigned char length);

void SysTick_Init(unsigned char SYSCLK);
void delay_ms(unsigned short ms);
void delay_us(unsigned short us);

unsigned int filter(unsigned int *value_buf);

//void delay_us(unsigned long delayTime);
//void delay_ms(unsigned long delayTime);
