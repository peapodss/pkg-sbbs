# Makefile.gnu

#########################################################################
# Makefile for Synchronet Blackjack										#
# For use with GNU make and GNU C Compiler								#
# @format.tab-size 4, @format.use-tabs true								#
#																		#
# Linux: make -f Makefile.gnu											#
# Win32: make -f Makefile.gnu os=win32									#
# FreeBSD: make -f Makefile.gnu os=freebsd								#
#########################################################################

# $Id: GNUmakefile,v 1.3 2006/01/11 02:19:16 deuce Exp $

XSDK		=	../sdk
SRC_ROOT	?=	../../src
include $(SRC_ROOT)/build/Common.gmake

vpath %.c $(XSDK)

CFLAGS	+=	-I$(XSDK) -DUSE_XPDEV $(XPDEV-MT_CFLAGS)

ifeq ($(os),sunos)
 LDFLAGS	+=	-lnsl -lrt
endif

$(TBD): $(OBJS)
   ifndef bcc
	@echo Linking $@
   endif
	$(QUIET)$(CC) $(MT_LDFLAGS) $(XPDEV-MT_LDFLAGS) $(LDFLAGS) $^ -o $@ $(XPDEV-MT_LIBS)

$(MAPMAKER): mapmaker.o
   ifndef bcc
	@echo Linking $@
   endif
	$(QUIET)$(CC) $(MT_LDFLAGS) $(XPDEV-MT_LDFLAGS) $(LDFLAGS) $^ -o $@ $(XPDEV-MT_LIBS)

$(REROLL): reroll.o
   ifndef bcc
	@echo Linking $@
   endif
	$(QUIET)$(CC) $(MT_LDFLAGS) $(XPDEV-MT_LDFLAGS) $(LDFLAGS) $^ -o $@ $(XPDEV-MT_LIBS)
