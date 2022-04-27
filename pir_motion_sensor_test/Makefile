APPLICATION = PIR_motion_sensor_test
BOARD ?= nucleo-f401re

RIOTBASE ?= $(CURDIR)/../../RIOT

DEVELHELP ?= 1
QUIET ?= 1

USEMODULE += pir
USEMODULE += xtimer
USEMODULE += periph_gpio

FEATURES_OPTIONAL += periph_rtc

include $(RIOTBASE)/Makefile.include