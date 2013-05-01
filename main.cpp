#include "ch.hpp"
#include "hal.h"
#include "shell.h"
#include "chprintf.h"

using namespace chibios_rt;

/* ******************************************************************* */
/* arduino */

#define ARDUINOS 4

#include "arduino/arduino.h"
#include "arduino/arduino0.h"
#include "arduino/arduino1.h"
#include "arduino/arduino2.h"
#include "arduino/arduino3.h"

static WORKING_AREA(waArduino[ARDUINOS], 1024*1024);
unsigned int enableArduino[ARDUINOS];

static msg_t arduino0(void *arg) {
  (void) arg;
  chRegSetThreadName("arduino0");
  _arduino0::setup();
  enableArduino[0] = TRUE;
  while (TRUE) {
    if (enableArduino[0] == TRUE) {
      _arduino0::loop();
    } else {
      chThdSleepMilliseconds(100);
    }
  }
  return 0;
}

static msg_t arduino1(void *arg) {
  (void) arg;
  chRegSetThreadName("arduino1");
  _arduino1::setup();
  enableArduino[1] = TRUE;
  while (TRUE) {
    if (enableArduino[1] == TRUE) {
      _arduino1::loop();
    } else {
      chThdSleepMilliseconds(100);
    }
  }
  return 0;
}

static msg_t arduino2(void *arg) {
  (void) arg;
  chRegSetThreadName("arduino2");
  _arduino2::setup();
  enableArduino[2] = TRUE;
  while (TRUE) {
    if (enableArduino[2] == TRUE) {
      _arduino2::loop();
    } else {
      chThdSleepMilliseconds(100);
    }
  }
  return 0;
}
  
static msg_t arduino3(void *arg) {
  (void) arg;
  chRegSetThreadName("arduino3");
  _arduino3::setup();
  enableArduino[3] = TRUE;
  while (TRUE) {
    if (enableArduino[3] == TRUE) {
      _arduino3::loop();
    } else {
      chThdSleepMilliseconds(100);
    }
  }
  return 0;
}

/* ******************************************************************* */
/* test */

static WORKING_AREA(waTestThread, 8);
static msg_t testThread(void *p) {
  (void)p;
  chRegSetThreadName("test");
  palSetPadMode(ONBOARD_LED_PORT, ONBOARD_LED_PAD, PAL_MODE_OUTPUT);
  while (TRUE) {
    palClearPad(ONBOARD_LED_PORT, ONBOARD_LED_PAD);
    chThdSleepMilliseconds(100);
    palSetPad(ONBOARD_LED_PORT, ONBOARD_LED_PAD);
    chThdSleepMilliseconds(100);
  }
  return 0;
}

/* ******************************************************************* */
/* shell */

#define SHELL_WA_SIZE       THD_WA_SIZE(4096)

static void cmd_status(BaseSequentialStream *chp, int argc, char *argv[]) {
  unsigned int i;
  (void) argv;

  if (argc > 0) {
    chprintf(chp, "Usage: status\r\n");
    return;
  }

  for (i = 0; i < ARDUINOS; i++) {
    chprintf(chp, "arduino%u: ", i);
    if (enableArduino[i] == TRUE) {
      chprintf(chp, "enabled");
    } else {
      chprintf(chp, "disabled");
    }
    chprintf(chp, "\r\n");
  }
}

static void cmd_pause(BaseSequentialStream *chp, int argc, char *argv[]) {

  if (argc != 1) {
    chprintf(chp, "Usage: pause [arduino]\r\n");
    return;
  }

  if (*argv[0] == '0') {
    enableArduino[0] = FALSE;
  } else if (*argv[0] == '1') {
    enableArduino[1] = FALSE;
  } else if (*argv[0] == '2') {
    enableArduino[2] = FALSE;
  } else if (*argv[0] == '3') {
    enableArduino[3] = FALSE;
  } else {
    chprintf(chp, "invalid arduino\r\n");
  }
}

static void cmd_resume(BaseSequentialStream *chp, int argc, char *argv[]) {

  if (argc != 1) {
    chprintf(chp, "Usage: resume [arduino]\r\n");
    return;
  }

  if (*argv[0] == '0') {
    enableArduino[0] = TRUE;
  } else if (*argv[0] == '1') {
    enableArduino[1] = TRUE;
  } else if (*argv[0] == '2') {
    enableArduino[2] = TRUE;
  } else if (*argv[0] == '3') {
    enableArduino[3] = TRUE;
  } else {
    chprintf(chp, "invalid arduino\r\n");
  }
}

static void print_log(BaseSequentialStream *chp, msg_t ptr) {
  struct _serialMsg *serialMsg = (_serialMsg *) ptr;
  chprintf(chp, "%u: %s\r\n", serialMsg->timestamp, (char *) serialMsg->msg);
  chHeapFree((void *) ptr);
}

static void cmd_log(BaseSequentialStream *chp, int argc, char *argv[]) {
  msg_t ptr, result;

  if (argc != 1) {
    chprintf(chp, "Usage: log [arduino]\r\n");
    return;
  }

  if (*argv[0] == '0') {
    while (TRUE) {
      result = chMBFetch(&_arduino0::mboxSerial, &ptr, TIME_IMMEDIATE);
      if (result == RDY_OK) {
        print_log(chp, ptr);
      } else {
        break;
      }
    }
  } else if (*argv[0] == '1') {
    while (TRUE) {
      result = chMBFetch(&_arduino1::mboxSerial, &ptr, TIME_IMMEDIATE);
      if (result == RDY_OK) {
        print_log(chp, ptr);
      } else {
        break;
      }
    }
  } else if (*argv[0] == '2') {
    while (TRUE) {
      result = chMBFetch(&_arduino2::mboxSerial, &ptr, TIME_IMMEDIATE);
      if (result == RDY_OK) {
        print_log(chp, ptr);
      } else {
        break;
      }
    }
  } else if (*argv[0] == '3') {
    while (TRUE) {
      result = chMBFetch(&_arduino3::mboxSerial, &ptr, TIME_IMMEDIATE);
      if (result == RDY_OK) {
        print_log(chp, ptr);
      } else {
        break;
      }
    }
  } else {
    chprintf(chp, "invalid arduino\r\n");
  }
}

static void cmd_mem(BaseSequentialStream *chp, int argc, char *argv[]) {
  size_t n, size;

  UNUSED(argv);
  if (argc > 0) {
    chprintf(chp, "Usage: mem\r\n");
    return;
  }
  n = chHeapStatus(NULL, &size);
  chprintf(chp, "core free memory : %u bytes\r\n", chCoreStatus());
  chprintf(chp, "heap fragments   : %u\r\n", n);
  chprintf(chp, "heap free total  : %u bytes\r\n", size);
}

static void cmd_threads(BaseSequentialStream *chp, int argc, char *argv[]) {
  static const char *states[] = {THD_STATE_NAMES};
  Thread *tp;

  UNUSED(argv);
  if (argc > 0) {
    chprintf(chp, "Usage: threads\r\n");
    return;
  }
  chprintf(chp, "    addr    stack prio refs     state time    name\r\n");
  tp = chRegFirstThread();
  do {
    chprintf(chp, "%.8lx %.8lx %4lu %4lu %9s %-8lu %s\r\n",
            (uint32_t)tp, (uint32_t)tp->p_ctx.r13,
            (uint32_t)tp->p_prio, (uint32_t)(tp->p_refs - 1),
			 states[tp->p_state], (uint32_t)tp->p_time, tp->p_name);
    tp = chRegNextThread(tp);
  } while (tp != NULL);
}

static void cmd_reboot(BaseSequentialStream *chp, int argc, char *argv[]) {
  UNUSED(argv);
  if (argc > 0) {
    chprintf(chp, "Usage: reboot\r\n");
    return;
  }
  watchdog_start(1);
}

static const ShellCommand commands[] = {
  { "status", cmd_status },
  { "resume", cmd_resume },
  { "pause", cmd_pause },
  { "log", cmd_log },
  { "mem", cmd_mem },
  { "threads", cmd_threads },
  { "reboot", cmd_reboot },
  { NULL, NULL }
};

static const ShellConfig shell_config = {
  (BaseSequentialStream *)&SD1,
  commands
};

/* ******************************************************************* */
/* main */

int main(void) {
  halInit();
  System::Init();

  chThdCreateStatic(waTestThread, sizeof(waTestThread), NORMALPRIO, testThread, NULL);

  sdStart(&SD1, NULL);
  chprintf((BaseSequentialStream *)&SD1, "\r\nArdusat-RPi started");

  shellInit();
  shellCreate(&shell_config, SHELL_WA_SIZE, NORMALPRIO);
  
  chThdCreateStatic(waArduino[0], sizeof(waArduino[0]), NORMALPRIO, arduino0, NULL);
  chThdCreateStatic(waArduino[1], sizeof(waArduino[1]), NORMALPRIO, arduino1, NULL);
  chThdCreateStatic(waArduino[2], sizeof(waArduino[2]), NORMALPRIO, arduino2, NULL);
  chThdCreateStatic(waArduino[3], sizeof(waArduino[3]), NORMALPRIO, arduino3, NULL);

  chThdWait(chThdSelf());
  return 0;
}
