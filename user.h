/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/

/* TODO Application specific user parameters used in user.c may go here */

#define MULTIPLEX_LEDS 10 // 10 is normal
#define FADE_RESOLUTION 8 // 8 levels of fading
#define NEXT_FRAME 200 // (normally 200 for 1/16)

/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/

/* TODO User level functions prototypes (i.e. InitApp) go here */

void InitApp(void);         /* I/O and Peripheral Initialization */

void write_leds();

void update_fade();

void get_next_frame();