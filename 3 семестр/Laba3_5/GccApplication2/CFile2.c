#include <avr/io.h>
uint32_t x = 0;
int flag = 0;
int main(void){
	DDRB = 0x20;
	while(1){
		if (x==800000){
			if (flag == 0){
				PORTB = 0x20;
				flag =1;
			}
			else
			{
				PORTB = 0x00;
				flag = 0;
			}
			x=0;
		}
		x++;
	}
}