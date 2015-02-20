#include <common.h>

#define PORT 0x3f8   /* COM1 */

void init_serial();
uint8_t serial_received();
uint8_t read_serial();
uint8_t is_transmit_empty();
void write_serial(char);


// Useful functions
// I will first try to incorperate printf into s_write
// Then, try to develop a interacive shell after I completed the testing
void s_write(char*);
