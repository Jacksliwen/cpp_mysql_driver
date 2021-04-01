#-------------------------------------------------------------------------
#
# NAME
# Makefile
#
# COPYRIGHT China-Mobile(SZ) Company 2015.
#           All rights reserved.
#
#
# AUTHOR
#                Collins 
#
# $Revision$
#
# Change Log
#       Time            Author          Reason
#       2015/01/26      Collins         Create
#
#-----------------------------------------------------------------------------

include $(SDP_MAKE_ENV)

MAKEFILE = makefile
EXE = main

OBJLIST =main.o CMySqlOcciConn.o CMySqlOcciConnException.o CMySqlOcciOper.o CMySqlStatement.o CMySqlResultSet.o

release:
	@make -f $(MAKEFILE) OBJS="$(OBJLIST)" EXE="$(EXE)" LD_FLAGS= build CPPFLAGS="$(STD_CPPFLAGS) $(MYSQLCPP_INC_DIR)" LD_FLAGS="$(MYSQLCPP_LINK) "

debug:
	@make -f $(MAKEFILE) OBJS="$(OBJLIST)" EXE="$(EXE)" LD_FLAGS= build CPPFLAGS="$(STD_CPPFLAGS) $(MYSQLCPP_INC_DIR) -DDEBUG -g" LD_FLAGS="$(MYSQLCPP_LINK)"

clean :
	rm -f *.o	$(EXE)

                                 
