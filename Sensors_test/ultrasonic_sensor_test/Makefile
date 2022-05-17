# name of your application
APPLICATION = ultrasonic_test

# If no BOARD is found in the environment, use this default:
BOARD ?= nucleo-f401re

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../../../../RIOT

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
CFLAGS += -DDEVELHELP

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1

# Modules to include:
USEMODULE += shell
USEMODULE += shell_commands
USEMODULE += fmt
USEMODULE += ps
USEMODULE += srf04
USERMODULE += periph_gpio
USEMODULE += periph_gpio_irq
USEMODULE += xtimer
USEMODULE += netdev_default
USEMODULE += auto_init_gnrc_netif
USEMODULE += gnrc_ipv6_default
USEMODULE += emcute
USEMODULE += stdio_ethos
USEMODULE += gnrc_uhcpc

include $(RIOTBASE)/Makefile.include
