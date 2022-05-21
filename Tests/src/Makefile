# name of your application
APPLICATION = ultrasonic_test

# If no BOARD is found in the environment, use this default:
BOARD ?= nucleo-f401re
#BOARD ?= native

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

CFLAGS += -DCONFIG_GNRC_NETIF_IPV6_ADDRS_NUMOF=5
IPV6_PREFIX ?= 2000:2::/64
STATIC_ROUTES ?= 1
UPLINK ?= ethos
ETHOS_BAUDRATE ?= 115200
CFLAGS += -DETHOS_BAUDRATE=$(ETHOS_BAUDRATE)
TAP ?= tap0
host-tools:
	$(Q)env -u CC -u CFLAGS $(MAKE) -C $(RIOTTOOLS)
TERMDEPS += host-tools
TERMPROG ?= sudo sh $(RIOTTOOLS)/ethos/start_network.sh
TERMFLAGS ?= $(FLAGS_EXTRAS) $(PORT) $(TAP) $(IPV6_PREFIX) $(ETHOS_BAUDRATE)

FEATURES_REQUIRED = periph_gpio
FEATURES_REQUIRED = periph_adc


include $(RIOTBASE)/Makefile.include
