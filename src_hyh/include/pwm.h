#ifndef MILLET_PWM_H
#define MILLET_PWM_H

extern void timer1_init();
extern void do_timer1(void);
extern void stop_timer1(void);

#define PWM_BASE 0x139D0000

#define TCFG0  (*(volatile unsigned int *)(PWM_BASE + 0x0000)) 
#define TCFG1  (*(volatile unsigned int *)(PWM_BASE + 0x0004)) 
#define TCON   (*(volatile unsigned int *)(PWM_BASE + 0x0008)) 
#define TCNTB0 (*(volatile unsigned int *)(PWM_BASE + 0x000C))
#define TCMPB0 (*(volatile unsigned int *)(PWM_BASE + 0x0010))
#define TCNTO0 (*(volatile unsigned int *)(PWM_BASE + 0x0014))
#define TCNTB1 (*(volatile unsigned int *)(PWM_BASE + 0x0018))
#define TCMPB1 (*(volatile unsigned int *)(PWM_BASE + 0x001C))
#define TCNTO1 (*(volatile unsigned int *)(PWM_BASE + 0x0020))
#define TCNTB2 (*(volatile unsigned int *)(PWM_BASE + 0x0024))
#define TCMPB2 (*(volatile unsigned int *)(PWM_BASE + 0x0028))
#define TCNTO2 (*(volatile unsigned int *)(PWM_BASE + 0x002C))
#define TCNTB3 (*(volatile unsigned int *)(PWM_BASE + 0x0030))
#define TCMPB3 (*(volatile unsigned int *)(PWM_BASE + 0x0034))
#define TCNTO3 (*(volatile unsigned int *)(PWM_BASE + 0x0038))
#define TCNTB4 (*(volatile unsigned int *)(PWM_BASE + 0x003C))
#define TCNTO4 (*(volatile unsigned int *)(PWM_BASE + 0x0040))
#define TINT_CSTAT (*(volatile unsigned int *)(PWM_BASE + 0x0044))


#endif
