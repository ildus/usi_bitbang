#ifndef bitbang_h
#define bitbang_h

enum PINFUNC
{
	PIN_SCK,
	PIN_MISO,
	PIN_MOSI,
	N_PINS
};

typedef struct ioctrl_t {
	enum PINFUNC pinno[3];
  	int  (*open)           (struct ioctrl_t *ctrl, char *port);
	void (*close)          (struct ioctrl_t *ctrl);
 	int  (*setpin)         (struct ioctrl_t *ctrl, int pinfunc, int value);
	int  (*getpin)         (struct ioctrl_t *ctrl, int pinfunc);
	int  (*cmd)            (struct ioctrl_t *ctrl, const unsigned char *cmd,
                      		unsigned char *res);
	int  (*highpulsepin)   (struct ioctrl_t *ctrl, int pinfunc);
} IOCtrl;

int bitbang_cmd(IOCtrl *ctrl, const unsigned char *cmd, unsigned char *res);

#endif
