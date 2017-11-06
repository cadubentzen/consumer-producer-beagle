#ifndef LCD_H
#define LCD_H

#define LCD_BUF_SIZE 100

static char lcd_buf[LCD_BUF_SIZE];
static int lcd_len;

int lcd_open(const char* devpath);
void lcd_message(int lcd_fd, const char* fmt, ...);
void lcd_clear_screen(int lcd_fd);
void lcd_go_home(int lcd_fd);
void lcd_clear_and_home(int lcd_fd);

#endif
