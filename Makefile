#_________________ compiler specifics _______________________
bcc_inc_dir = $(MAKEDIR)\..\include
bcc_lib_dir = $(MAKEDIR)\..\lib
bcc = $(MAKEDIR)\bcc32.exe
link = $(MAKEDIR)\ilink32.exe

!ifdef DEBUG
COPT=-v /Yd
LOPT=-v
!else
COPT=/Ox /TP
LOPT= /q /aa /w
!endif

cc_opt = -c $(COPT) -I"$(bcc_inc_dir)" -L"$(bcc_lib_dir)"  -I".\inc" -L".\lib" -n".\obj"
link_opt = -C -c $(LOPT) -L"$(bcc_lib_dir)" -L"$(bcc_lib_dir)\PSDK" -L".\lib"  -L".\obj" -I".\obj" 

#__________________ project specifics________________________
exe = GraffitiWin.exe

#_______________________ targets ____________________________
.autodepend
.suffixes: .exe .obj .asm .c .res .rc .cpp

clean:
	rm -f -r .\obj\*.*
	
compile:
	echo ================================== COMPILE ====================================================
	$(bcc) $(cc_opt) .\src\*.cpp

link: compile
	echo ================================== LINKING ====================================================
	$(link) $(link_opt) \
	c0w32.obj \
	GraffitiWin.obj \
	,\
	.\obj\$(exe),\
	,\
	cw32mt.lib \
	import32.lib \
	oleaut32.lib \
	ws2_32.lib \
	,, 

all: clean link
