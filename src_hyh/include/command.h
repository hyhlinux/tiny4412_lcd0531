#ifndef  __COMMAND_H__
#define  __COMMAND_H__


#define DEF_ATTRIBUTE  __attribute__ ((unused, section(".shell_cmd_")))
#define CMD_T(name, func, help) \
	cmd_t cmd_##name DEF_ATTRIBUTE = { \
		#name,	\
		func, 	\
		help   \
		}


typedef struct{
	char *name;
	void (*cmd_func)(void);
	char *help;
}cmd_t;

extern cmd_t  start_shell_cmd_add;
extern cmd_t  end_shell_cmd_add;
extern void   find_cmd_exec(char *buf);
extern void   find_state_exec(void);
extern void   enter_app(void);

extern void sh_cmd1(void);
extern void sh_cmd2(void);//teris
extern void sh_cmd3(void);//alpha
extern void sh_cmd4(void);//pic20
extern void sh_cmd5(void);//rotator
extern void sh_cmd6(void);

#define CMD_X 0
#define CMD_Y 0

#endif 
