#ifndef bitbang_h
#define bitbang_h

enum SPI_PINS
{
	SCK,
	MISO,
	MOSI
} SPI_PINS;

typedef struct ioctrl_t {
	SPI_PINS pinno[3];
  	int  (*open)           (struct ioctrl_t *ctrl, char *port);
	void (*close)          (struct ioctrl_t *ctrl);
 	int  (*setpin)         (struct ioctrl_t *ctrl, int pinfunc, int value);
	int  (*getpin)         (struct ioctrl_t *ctrl, int pinfunc);
	int  (*cmd)            (struct ioctrl_t *ctrl, const unsigned char *cmd,
                      		unsigned char *res);
  	int  (*initialize)     (struct programmer_t * pgm, AVRPART * p);
} IOCtrl;

int bitbang_cmd(IOCtrl *ctrl, const unsigned char *cmd, unsigned char *res);

#endif
