#ifndef _DC_MOTOR_TYPES_H_
#define _DC_MOTOR_TYPES_H_

#include <avr/io.h>
#include <inttypes.h>

#ifndef NULL
#define NULL 0
#endif


#define MICROSTEPS 16                       // 8 ili 16

#define MOTOR12_64KHZ _BV(CS20)             // no prescalera
#define MOTOR12_8KHZ _BV(CS21)              // prescaler 8
#define MOTOR12_2KHZ _BV(CS21) | _BV(CS20)  // prescaler 32
#define MOTOR12_1KHZ _BV(CS22)              // prescaler 64

#define MOTOR34_64KHZ _BV(CS00)             // bez prescalera
#define MOTOR34_8KHZ _BV(CS01)              // prescaler 8
#define MOTOR34_1KHZ _BV(CS01) | _BV(CS00)  // prescaler 64

#define DC_MOTOR_PWM_RATE   MOTOR34_8KHZ    // PWM rate za DC motore
#define STEPPER1_PWM_RATE   MOTOR12_64KHZ   // PWM rate za stepper 1
#define STEPPER2_PWM_RATE	MOTOR34_64KHZ	// PWM rate za stepper 2




// Pozicije bitova na izlazu shift registra 74HCT595
#define MOTOR1_A 2
#define MOTOR1_B 3
#define MOTOR2_A 1
#define MOTOR2_B 4
#define MOTOR4_A 0
#define MOTOR4_B 6
#define MOTOR3_A 5
#define MOTOR3_B 7

#define MOTOR_1  1
#define MOTOR_2  2
#define MOTOR_3  3
#define MOTOR_4  4

// Konstante koje se šalju u pozive metoda DC motora
#define FORWARD 1
#define BACKWARD 2
#define BRAKE 3
#define RELEASE 4

// Konstante koje se šalju u pozive metoda stepper motora
#define SINGLE 1
#define DOUBLE 2
#define INTERLEAVE 3
#define MICROSTEP 4

#endif
