/* Calculator
 * Created date: 10 10 2019
 * Author: Mohamed Fayez
 */

#include "keypad.h"
#include "lcd.h"
#include "delay.h"

int main(){
	unsigned char key  ,f_number=0, f_screen=0   ,operation ,pre_operation;
	uint16 number=0;    float32 result ;
	LCD_init();
	DELAY_init();

	while(1){
		key=KeyPad_getPressedKey();

		if(key>=0 && key <=9){
			if(operation=='=' && f_screen){
				LCD_clearScreen();
				f_screen=0;
			}
			LCD_displayNumber(key);
			number=number*10 + key;
		}
		else  //not number
		{
			LCD_displayCharacter(key); /* display the pressed keypad switch */
			operation=key;

			if (f_number==0){
				f_number =1;
				result = number;
				pre_operation = operation;
			}

			else if (f_number){
				switch(pre_operation){   /////
				case '+':
					result=result+number;
					break;
				case '-':
					result=result-number;
					break;
				case '*':
					result=result*number;
					break;
				case '/':
					result=result/number;
					break;
				default:
					result=0;
				}
				if(operation=='='){
					f_number=0;
					f_screen=1;
					LCD_displayFloatNumber(result ,2);
				}
				else
					pre_operation = operation;    //!=
			}
			number= 0;
		}
		DELAY_ms(300);
	}
}
