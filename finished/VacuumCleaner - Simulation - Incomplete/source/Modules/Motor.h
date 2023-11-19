#ifndef __MOTOR_H__
#define __MOTOR_H__




#define MOTOR_ANGLE_140		140
#define MOTOR_ANGLE_90		90
#define MOTOR_ANGLE_10		10


/* prototypes */
void Motor_Init();

void Motor_SetAngle(int Angle);

void Motor_Update(void);

int Motor_CurrentValue(void);

#endif