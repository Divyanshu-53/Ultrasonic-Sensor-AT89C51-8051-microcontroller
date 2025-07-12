#include <REGX52.h> 
#include <stdio.h> 
 
#define dataport P2 
 
sbit trig = P3^5; 
sbit echo = P3^2; 
sbit rs = P3^1; 
sbit rw = P3^3; 
sbit e = P3^4; 
 
 
int cms; 
 
void delay(unsigned int msec) { 
    unsigned int i, j; 
    for(i = 0; i < msec; i++) 
        for(j = 0; j < 1275; j++); 
} 
 
void lcd_cmd(unsigned char item) { 
    dataport = item; 
    rs = 0; 
    rw = 0; 
    e = 1; 
    delay(1); 
    e = 0; 
} 
 
void lcd_data(unsigned char item) { 
    dataport = item; 
    rs = 1; 
    rw = 0; 
    e = 1; 
    delay(1); 
    e = 0; 
} 
 
void lcd_data_string(unsigned char *str) { 
    while(*str != '\0') { 
        lcd_data(*str); 
        str++; 
        delay(1); 
    } 
} 

 
 
 
void send_pulse(void) { 
    TH0 = 0x00; 
    TL0 = 0x00; 
    trig = 1; 
    delay(5); 
    trig = 0; 
} 
 
unsigned int get_range(void) {  
    long int timer_val;  

    send_pulse();  
    while (!echo);  // Wait for echo to go HIGH  
    TR0 = 1;        // Start timer  
    while (echo);   // Wait for echo to go LOW  
    TR0 = 0;        // Stop timer  

    timer_val = (TH0 << 8) + TL0;  // Read Timer Value  

    return (timer_val < 38000) ? (timer_val / 58) : -1;  // Use 58 instead of 53 for better accuracy  
}


void display_range(int range) {  
    char buffer[16];  

    lcd_cmd(0x80);  // Move cursor to first line  
    lcd_data_string("Output: ");  // Fixed text  

    lcd_cmd(0x88);  // Move cursor to number position (column 9)  
    lcd_data_string("    ");  // Clear old number (overwrite with spaces)  

    lcd_cmd(0x88);  // Move back to number position  
    if (range != -1) {  
        sprintf(buffer, "%3d", range);  // Format number with 3-digit alignment  
        lcd_data_string(buffer);  
        lcd_data_string("cm");  // Append "cm" directly after the number  
    } else {  
        lcd_cmd(0xC0);  // Move cursor to second line  
        lcd_data_string("Out of range!");  
    }  
}



void initialize_lcd() { 
    lcd_cmd(0x38); 
    delay(5); 
    lcd_cmd(0x0C); 
    delay(5); 
    lcd_cmd(0x01); 
    delay(5); 
    lcd_cmd(0x80); 
    delay(5);  
 
 
} 
 
 
void main() { 
    initialize_lcd(); 
    lcd_data_string("Start"); 
    delay(100); 
 
    TMOD = 0x09; 
    TR0 = 1; 
    TH0 = 0x00; 
    TL0 = 0x00; 
 
    while(1) { 
        int range = get_range(); 
        display_range(range); 
        delay(10); 
    } 
}