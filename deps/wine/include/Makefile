# include/Makefile.  Generated from Makefile.in by configure.      -*-Makefile-*-

prefix          = /usr/local
exec_prefix     = ${prefix}
bindir          = ${exec_prefix}/bin
libdir          = ${exec_prefix}/lib
datarootdir     = ${prefix}/share
datadir         = ${datarootdir}
infodir         = ${datarootdir}/info
mandir          = ${datarootdir}/man
fontdir         = $(datadir)/wine/fonts
includedir      = ${prefix}/include/wine
dlldir          = ${exec_prefix}/lib/wine
fakedlldir      = $(dlldir)/fakedlls
top_srcdir      = ..
top_builddir    = ..
srcdir          = .

SHELL           = /bin/sh
RM              = rm -f
MV              = mv
CC              = gcc -m32
CROSSCC         = false
CFLAGS          = -g -O2
CPPFLAGS        = 
EXTRACFLAGS     = -Wall -pipe -fno-strict-aliasing -Wdeclaration-after-statement -Wempty-body -Wstrict-prototypes -Wwrite-strings -gstabs+ -fno-omit-frame-pointer -Wpointer-arith
TARGETFLAGS     = -m32
LIBS            = 
BISON           = bison
FLEX            = flex
EXEEXT          = 
OBJEXT          = o
LIBEXT          = dylib
DLLEXT          = .so
FAKEEXT         = $(DLLEXT:.so=.fake)
TOOLSEXT        = 
IMPLIBEXT       = def
DLLTOOL         = 
DLLWRAP         = 
AR              = ar
ARFLAGS         = rc
RANLIB          = ranlib
LN_S            = ln -s
TOOLSDIR        = $(top_builddir)
LDFLAGS         = 
PRELINK         = 
LINT            = 
LINTFLAGS       = 
FONTFORGE       = false
RSVG            = false
CONVERT         = false
ICOTOOL         = false
MSGFMT          = false
CROSSTARGET     = 
LINGUAS         = 
ALL_MO_FILES    = $(LINGUAS:%=../po/%.mo)
PORCFLAGS       = 
CROSSAR         = $(CROSSTARGET)-ar
CROSSRANLIB     = $(CROSSTARGET)-ranlib
MKINSTALLDIRS   = $(top_srcdir)/tools/mkinstalldirs -m 755
WINAPI_CHECK    = $(top_srcdir)/tools/winapi/winapi_check
BUILDIMAGE      = $(top_srcdir)/tools/buildimage
C2MAN           = $(top_srcdir)/tools/c2man.pl
RUNTEST         = $(top_srcdir)/tools/runtest
MAKECTESTS      = $(TOOLSDIR)/tools/make_ctests$(TOOLSEXT)
MAKEXFTMPL      = $(TOOLSDIR)/tools/make_xftmpl$(TOOLSEXT)
MAKEDEP         = $(TOOLSDIR)/tools/makedep$(TOOLSEXT)
RELPATH         = $(TOOLSDIR)/tools/relpath$(TOOLSEXT)
SFNT2FNT        = $(TOOLSDIR)/tools/sfnt2fnt$(TOOLSEXT)
WIDL            = $(TOOLSDIR)/tools/widl/widl$(TOOLSEXT)
WINEBUILD       = $(TOOLSDIR)/tools/winebuild/winebuild$(TOOLSEXT)
WMC             = $(TOOLSDIR)/tools/wmc/wmc$(TOOLSEXT)
WRC             = $(TOOLSDIR)/tools/wrc/wrc$(TOOLSEXT)
LIBPORT         = $(top_builddir)/libs/port/libwine_port.a
LIBWPP          = $(top_builddir)/libs/wpp/libwpp.a
LIBWINE         = -L$(top_builddir)/libs/wine -lwine
WINEGCC         = $(TOOLSDIR)/tools/winegcc/winegcc $(TARGETFLAGS) -B$(TOOLSDIR)/tools/winebuild --sysroot=$(top_builddir) 
CROSSWINEGCC    = $(TOOLSDIR)/tools/winegcc/winegcc $(CROSSTARGET:%=-b %) -B$(TOOLSDIR)/tools/winebuild --sysroot=$(top_builddir) --lib-suffix=.cross.a
LDPATH          = 
LDRPATH_INSTALL = -Wl,-rpath,@loader_path/`$(RELPATH) $(bindir) $(libdir)`
LDRPATH_LOCAL   = -Wl,-rpath,@loader_path/$(top_builddir)/libs/wine
INSTALL         = /usr/bin/install -c $(INSTALL_FLAGS)
INSTALL_PROGRAM = ${INSTALL} $(INSTALL_PROGRAM_FLAGS)
INSTALL_SCRIPT  = ${INSTALL} $(INSTALL_SCRIPT_FLAGS)
INSTALL_DATA    = ${INSTALL} -m 644 $(INSTALL_DATA_FLAGS)
prog_manext     = 1
api_manext      = 3w
conf_manext     = 5


all:

# End of common header
PRIVATE_IDL_H_SRCS = \
	wine/winedxgi.idl

PUBLIC_IDL_H_SRCS = \
	activaut.idl \
	activdbg.idl \
	activscp.idl \
	amstream.idl \
	amvideo.idl \
	asptlb.idl \
	atliface.idl \
	audioclient.idl \
	audiopolicy.idl \
	austream.idl \
	bits.idl \
	bits1_5.idl \
	comcat.idl \
	commoncontrols.idl \
	control.idl \
	cor.idl \
	cordebug.idl \
	ctfutb.idl \
	ctxtcall.idl \
	d3d10.idl \
	d3d10_1.idl \
	d3d11.idl \
	d3dcommon.idl \
	ddstream.idl \
	devicetopology.idl \
	dimm.idl \
	dispex.idl \
	docobj.idl \
	docobjectservice.idl \
	downloadmgr.idl \
	dwrite.idl \
	dxgi.idl \
	endpointvolume.idl \
	exdisp.idl \
	fusion.idl \
	gameux.idl \
	hlink.idl \
	htiface.idl \
	htiframe.idl \
	httprequest.idl \
	iads.idl \
	icftypes.idl \
	iextag.idl \
	imnact.idl \
	imnxport.idl \
	indexsrv.idl \
	mediaobj.idl \
	metahost.idl \
	mimeinfo.idl \
	mimeole.idl \
	mlang.idl \
	mmc.idl \
	mmdeviceapi.idl \
	mmstream.idl \
	mscoree.idl \
	msctf.idl \
	msdadc.idl \
	msdasc.idl \
	mshtmhst.idl \
	mshtml.idl \
	msident.idl \
	msinkaut.idl \
	mstask.idl \
	msxml.idl \
	msxml2.idl \
	msxml6.idl \
	netcon.idl \
	netfw.idl \
	oaidl.idl \
	objectarray.idl \
	objidl.idl \
	objsafe.idl \
	ocidl.idl \
	ocmm.idl \
	oleacc.idl \
	oledb.idl \
	oleidl.idl \
	optary.idl \
	perhist.idl \
	propidl.idl \
	propsys.idl \
	pstore.idl \
	qedit.idl \
	richole.idl \
	sensevts.idl \
	servprov.idl \
	shdeprecated.idl \
	shldisp.idl \
	shobjidl.idl \
	shtypes.idl \
	strmif.idl \
	structuredquerycondition.idl \
	textstor.idl \
	tlogstg.idl \
	tom.idl \
	uiautomationclient.idl \
	uiautomationcore.idl \
	unknwn.idl \
	urlhist.idl \
	urlmon.idl \
	vmr9.idl \
	wbemcli.idl \
	wbemprov.idl \
	wia_lh.idl \
	wia_xp.idl \
	wincodec.idl \
	wincodecsdk.idl \
	wine/itss.idl \
	wine/svcctl.idl \
	winsxs.idl \
	wmiutils.idl \
	wmsbuffer.idl \
	wmsdkidl.idl \
	wpcapi.idl \
	wtypes.idl \
	wuapi.idl \
	xmllite.idl

IDL_TLB_SRCS = \
	stdole2.idl

XTEMPLATE_SRCS = \
	rmxftmpl.x

SRCDIR_INCLUDES = \
	$(IDL_TLB_SRCS) \
	$(PUBLIC_IDL_H_SRCS) \
	$(XTEMPLATE_SRCS) \
	accctrl.h \
	access.idl \
	aclapi.h \
	aclui.h \
	adshlp.h \
	advpub.h \
	af_irda.h \
	amaudio.h \
	appcompatapi.h \
	appmgmt.h \
	asynot.idl \
	asysta.idl \
	atlbase.h \
	atlwin.h \
	audevcod.h \
	audiosessiontypes.h \
	aviriff.h \
	avrt.h \
	axcore.idl \
	axextend.idl \
	basetsd.h \
	basetyps.h \
	bcrypt.h \
	binres.idl \
	bitsmsg.h \
	cderr.h \
	cfgmgr32.h \
	cguid.h \
	cierror.h \
	clusapi.h \
	cmdbas.idl \
	cmdtxt.idl \
	commctrl.h \
	commctrl.rh \
	commdlg.h \
	compobj.h \
	corerror.h \
	corhdr.h \
	cpl.h \
	crtrow.idl \
	cryptdlg.h \
	cryptuiapi.h \
	custcntl.h \
	cvconst.h \
	d3d.h \
	d3d10_1shader.h \
	d3d10effect.h \
	d3d10misc.h \
	d3d10shader.h \
	d3d11shader.h \
	d3d8.h \
	d3d8caps.h \
	d3d8types.h \
	d3d9.h \
	d3d9caps.h \
	d3d9types.h \
	d3dcaps.h \
	d3dcompiler.h \
	d3dhal.h \
	d3drm.h \
	d3drmdef.h \
	d3drmobj.h \
	d3drmwin.h \
	d3dtypes.h \
	d3dvec.inl \
	d3dx9.h \
	d3dx9anim.h \
	d3dx9core.h \
	d3dx9effect.h \
	d3dx9math.h \
	d3dx9math.inl \
	d3dx9mesh.h \
	d3dx9shader.h \
	d3dx9shape.h \
	d3dx9tex.h \
	d3dx9xof.h \
	dbccmd.idl \
	dbcses.idl \
	dbdsad.idl \
	dbghelp.h \
	dbinit.idl \
	dbprop.idl \
	dbs.idl \
	dbt.h \
	dciddi.h \
	dciman.h \
	dcommon.h \
	dde.h \
	dde.rh \
	ddeml.h \
	ddk/compstui.h \
	ddk/hidsdi.h \
	ddk/imm.h \
	ddk/mountmgr.h \
	ddk/ntddcdvd.h \
	ddk/ntddk.h \
	ddk/ntddser.h \
	ddk/ntddtape.h \
	ddk/usb.h \
	ddk/usb100.h \
	ddk/usb200.h \
	ddk/usbdlib.h \
	ddk/wdm.h \
	ddk/winddiui.h \
	ddk/winsplp.h \
	ddraw.h \
	ddrawgdi.h \
	ddrawi.h \
	devenum.idl \
	devguid.h \
	devpkey.h \
	devpropdef.h \
	digitalv.h \
	dinput.h \
	dinputd.h \
	dispdib.h \
	dlgs.h \
	dls1.h \
	dls2.h \
	dmdls.h \
	dmerror.h \
	dmksctrl.h \
	dmo.h \
	dmoreg.h \
	dmort.h \
	dmplugin.h \
	dmusbuff.h \
	dmusicc.h \
	dmusicf.h \
	dmusici.h \
	dmusics.h \
	dpaddr.h \
	dplay.h \
	dplay8.h \
	dplobby.h \
	dplobby8.h \
	dpnathlp.h \
	dsconf.h \
	dsgetdc.h \
	dshow.h \
	dsound.h \
	dsrole.h \
	dvdmedia.h \
	dwmapi.h \
	dxdiag.h \
	dxerr8.h \
	dxerr9.h \
	dxfile.h \
	dxgiformat.h \
	dxgitype.h \
	dyngraph.idl \
	errorrep.h \
	errors.h \
	evcode.h \
	evntprov.h \
	evntrace.h \
	excpt.h \
	exdispid.h \
	fci.h \
	fdi.h \
	fltdefs.h \
	gdiplus.h \
	gdipluscolor.h \
	gdipluscolormatrix.h \
	gdiplusenums.h \
	gdiplusflat.h \
	gdiplusgpstubs.h \
	gdiplusimaging.h \
	gdiplusinit.h \
	gdiplusmem.h \
	gdiplusmetaheader.h \
	gdipluspixelformats.h \
	gdiplustypes.h \
	guiddef.h \
	hlguids.h \
	htmlhelp.h \
	http.h \
	httprequestid.h \
	i_cryptasn1tls.h \
	icm.h \
	icmpapi.h \
	idispids.h \
	ifdef.h \
	ifmib.h \
	imagehlp.h \
	imm.h \
	in6addr.h \
	inaddr.h \
	initguid.h \
	intshcut.h \
	ipexport.h \
	iphlpapi.h \
	ipifcons.h \
	ipmib.h \
	iprtrmib.h \
	iptypes.h \
	isguids.h \
	knownfolders.h \
	ks.h \
	ksguid.h \
	ksmedia.h \
	lm.h \
	lmaccess.h \
	lmapibuf.h \
	lmat.h \
	lmbrowsr.h \
	lmcons.h \
	lmerr.h \
	lmjoin.h \
	lmmsg.h \
	lmserver.h \
	lmshare.h \
	lmstats.h \
	lmuse.h \
	lmuseflg.h \
	lmwksta.h \
	loadperf.h \
	lzexpand.h \
	mapi.h \
	mapicode.h \
	mapidefs.h \
	mapiform.h \
	mapiguid.h \
	mapitags.h \
	mapiutil.h \
	mapival.h \
	mapix.h \
	mciavi.h \
	mcx.h \
	mediaerr.h \
	midles.h \
	minmax.h \
	mmddk.h \
	mmreg.h \
	mmsystem.h \
	mprapi.h \
	mprerror.h \
	msacm.h \
	msacmdlg.h \
	msacmdrv.h \
	mscat.h \
	msdaguid.h \
	mshtmcid.h \
	mshtmdid.h \
	msi.h \
	msidefs.h \
	msiquery.h \
	mssip.h \
	mstcpip.h \
	msvcrt/assert.h \
	msvcrt/conio.h \
	msvcrt/crtdbg.h \
	msvcrt/crtdefs.h \
	msvcrt/ctype.h \
	msvcrt/direct.h \
	msvcrt/dirent.h \
	msvcrt/dos.h \
	msvcrt/eh.h \
	msvcrt/errno.h \
	msvcrt/fcntl.h \
	msvcrt/float.h \
	msvcrt/io.h \
	msvcrt/limits.h \
	msvcrt/locale.h \
	msvcrt/malloc.h \
	msvcrt/math.h \
	msvcrt/mbctype.h \
	msvcrt/mbstring.h \
	msvcrt/memory.h \
	msvcrt/process.h \
	msvcrt/search.h \
	msvcrt/setjmp.h \
	msvcrt/share.h \
	msvcrt/signal.h \
	msvcrt/stddef.h \
	msvcrt/stdio.h \
	msvcrt/stdlib.h \
	msvcrt/string.h \
	msvcrt/sys/locking.h \
	msvcrt/sys/stat.h \
	msvcrt/sys/timeb.h \
	msvcrt/sys/types.h \
	msvcrt/sys/unistd.h \
	msvcrt/sys/utime.h \
	msvcrt/time.h \
	msvcrt/unistd.h \
	msvcrt/wchar.h \
	msvcrt/wctype.h \
	mswsock.h \
	msxml2did.h \
	msxml6did.h \
	msxmldid.h \
	nb30.h \
	ndrtypes.h \
	nldef.h \
	npapi.h \
	nspapi.h \
	ntddcdrm.h \
	ntddndis.h \
	ntddscsi.h \
	ntddstor.h \
	ntdsapi.h \
	ntquery.h \
	ntsecapi.h \
	ntsecpkg.h \
	ntstatus.h \
	objbase.h \
	objsel.h \
	odbcinst.h \
	ole2.h \
	ole2ver.h \
	oleauto.h \
	olectl.h \
	oledberr.h \
	oledlg.h \
	opnrst.idl \
	patchapi.h \
	pdh.h \
	pdhmsg.h \
	pktdef.h \
	poppack.h \
	powrprof.h \
	profinfo.h \
	propkey.h \
	propkeydef.h \
	propvarutil.h \
	prsht.h \
	psapi.h \
	pshpack1.h \
	pshpack2.h \
	pshpack4.h \
	pshpack8.h \
	ras.h \
	rasdlg.h \
	raserror.h \
	reason.h \
	regstr.h \
	restartmanager.h \
	richedit.h \
	rmxfguid.h \
	row.idl \
	rowchg.idl \
	rpc.h \
	rpcasync.h \
	rpcdce.h \
	rpcdcep.h \
	rpcndr.h \
	rpcnterr.h \
	rpcproxy.h \
	rpcsal.h \
	rstbas.idl \
	rstinf.idl \
	rstloc.idl \
	rtutils.h \
	scarderr.h \
	schannel.h \
	schemadef.h \
	schnlsp.h \
	sddl.h \
	secext.h \
	security.h \
	sensapi.h \
	sesprp.idl \
	setupapi.h \
	sfc.h \
	shdispid.h \
	shellapi.h \
	shlguid.h \
	shlobj.h \
	shlwapi.h \
	sipbase.h \
	slerror.h \
	slpublic.h \
	snmp.h \
	softpub.h \
	sql.h \
	sqlext.h \
	sqltypes.h \
	srrestoreptapi.h \
	sspi.h \
	sti.h \
	storage.h \
	strsafe.h \
	svrapi.h \
	t2embapi.h \
	tapi.h \
	tchar.h \
	tcpmib.h \
	textserv.h \
	tlhelp32.h \
	tmschema.h \
	traffic.h \
	twain.h \
	udpmib.h \
	uiautomation.h \
	uiautomationcoreapi.h \
	userenv.h \
	usp10.h \
	uuids.h \
	uxtheme.h \
	vdmdbg.h \
	ver.h \
	verrsrc.h \
	vfw.h \
	vfwmsgs.h \
	vmrender.idl \
	vsstyle.h \
	vssym32.h \
	werapi.h \
	wfext.h \
	wia.h \
	winbase.h \
	wincon.h \
	wincred.h \
	wincrypt.h \
	windef.h \
	windns.h \
	windows.h \
	windowsx.h \
	wine/debug.h \
	wine/exception.h \
	wine/library.h \
	wine/unicode.h \
	winerror.h \
	winevt.h \
	wingdi.h \
	winhttp.h \
	wininet.h \
	winineti.h \
	winioctl.h \
	winldap.h \
	winnetwk.h \
	winnls.h \
	winnls32.h \
	winnt.h \
	winnt.rh \
	winperf.h \
	winreg.h \
	winresrc.h \
	winsafer.h \
	winscard.h \
	winsmcrd.h \
	winsock.h \
	winsock2.h \
	winspool.h \
	winsvc.h \
	wintab.h \
	wintabx.h \
	winternl.h \
	wintrust.h \
	winuser.h \
	winuser.rh \
	winver.h \
	wmistr.h \
	wnaspi32.h \
	wownt32.h \
	ws2def.h \
	ws2ipdef.h \
	ws2spi.h \
	ws2tcpip.h \
	wshisotp.h \
	wsipx.h \
	wsnwlink.h \
	wtsapi32.h \
	xcmc.h \
	xinput.h \
	xmldom.h \
	xmldom.idl \
	xmldomdid.h \
	xmldso.idl \
	xmldsodid.h \
	zmouse.h

EXTRASUBDIRS = \
	ddk \
	msvcrt \
	msvcrt/sys \
	wine

INSTALLDIRS = \
	$(DESTDIR)$(includedir)/windows/ddk \
	$(DESTDIR)$(includedir)/windows \
	$(DESTDIR)$(includedir)/msvcrt/sys \
	$(DESTDIR)$(includedir)/msvcrt \
	$(DESTDIR)$(includedir)

IDL_H_SRCS = $(PUBLIC_IDL_H_SRCS) $(PRIVATE_IDL_H_SRCS)

# Global rules shared by all makefiles     -*-Makefile-*-
#
# Each individual makefile may define the following variables:
# C_SRCS       : C sources for the module
# OBJC_SRCS    : Objective-C sources for the module
# RC_SRCS      : resource source files
# EXTRA_SRCS   : extra source files for make depend
# EXTRA_OBJS   : extra object files
# IMPORTS      : dlls to import
# DELAYIMPORTS : dlls to import in delayed mode
# EXTRASUBDIRS : subdirectories that do not contain a Makefile
# MODCFLAGS    : extra CFLAGS for this module

# First some useful definitions

LDSHARED     = $(CC) -dynamiclib
INCLUDES     = -I$(srcdir) -I. -I$(top_srcdir)/include -I$(top_builddir)/include $(EXTRAINCL)
ALLCFLAGS    = $(INCLUDES) $(DEFS) $(DLLFLAGS) $(EXTRACFLAGS) $(CPPFLAGS) $(CFLAGS) $(MODCFLAGS)
ALLLINTFLAGS = $(INCLUDES) $(DEFS) $(LINTFLAGS)
IDLFLAGS     = $(INCLUDES) $(DEFS) $(EXTRAIDLFLAGS)
RCFLAGS      = --nostdinc $(PORCFLAGS) $(TARGETFLAGS) $(INCLUDES) $(DEFS) $(EXTRARCFLAGS)

IDL_GEN_C_SRCS  = $(IDL_C_SRCS:.idl=_c.c) $(IDL_I_SRCS:.idl=_i.c) \
                  $(IDL_P_SRCS:.idl=_p.c) $(IDL_S_SRCS:.idl=_s.c)
IDL_GEN_HEADERS = $(IDL_H_SRCS:.idl=.h) $(IDL_C_SRCS:.idl=.h) $(IDL_I_SRCS:.idl=.h) \
                  $(IDL_P_SRCS:.idl=.h) $(IDL_S_SRCS:.idl=.h)

CLEAN_FILES   = *.o *.a *.so *.mo *.ln *.res *.fake *.$(LIBEXT) \\\#*\\\# *~ *% .\\\#* *.bak *.orig *.rej *.flc core
CLEAN_TARGETS = $(IDL_GEN_C_SRCS) $(IDL_GEN_HEADERS) $(IDL_TLB_SRCS:.idl=.tlb) $(IDL_P_SRCS:%=dlldata.c) \
                $(BISON_SRCS:.y=.tab.c) $(BISON_SRCS:.y=.tab.h) $(LEX_SRCS:.l=.yy.c) \
                $(PO_SRCS:%=rsrc.pot) $(MC_SRCS:%=msg.pot) $(XTEMPLATE_SRCS:.x=.h)

OBJS = $(C_SRCS:.c=.o) $(BISON_SRCS:.y=.tab.o) $(LEX_SRCS:.l=.yy.o) $(IDL_GEN_C_SRCS:.c=.o) $(OBJC_SRCS:.m=.o) \
       $(IDL_R_SRCS:.idl=_r.res) $(IDL_TLB_RES) $(RC_SRCS:.rc=.res) $(MC_SRCS:.mc=.res) $(EXTRA_OBJS)

CROSSOBJS = $(OBJS:.o=.cross.o)
LINTS  = $(C_SRCS:.c=.ln)

filter: dummy
	@$(top_srcdir)/tools/winapi/make_filter --make $(MAKE) all

.PHONY: all filter

# Implicit rules

.SUFFIXES: .mc .rc .res .idl .tlb .h .y .l .tab.c .tab.h .yy.c .ok .man.in .man _c.c _i.c _p.c _s.c _r.res _t.res .cross.o .po .mo # .sfd .ttf .svg .ico .bmp

.c.o:
	$(CC) -c $(ALLCFLAGS) -o $@ $<

.m.o:
	$(CC) -c $(ALLCFLAGS) -o $@ $<

.c.cross.o:
	$(CROSSCC) -c $(INCLUDES) $(DEFS) -DWINE_CROSSTEST $(CPPFLAGS) $(CFLAGS) -o $@ $<

.y.tab.c:
	$(BISON) $(BISONFLAGS) -p $*_ -o $@ $<

.y.tab.h:
	$(BISON) $(BISONFLAGS) -p $*_ -o $*.tab.c -d $<

.l.yy.c:
	$(FLEX) $(LEXFLAGS) -o$@ $<

.mc.res:
	$(LDPATH) $(WMC) -U -O res -P $(top_srcdir)/po -o $@ $<

.rc.res:
	$(LDPATH) $(WRC) $(RCFLAGS) -o $@ $<

.idl.h:
	$(WIDL) $(IDLFLAGS) -h -o $@ $<

.idl_c.c:
	$(WIDL) $(IDLFLAGS) -c -o $@ $<

.idl_i.c:
	$(WIDL) $(IDLFLAGS) -u -o $@ $<

.idl_p.c:
	$(WIDL) $(IDLFLAGS) -p -o $@ $<

.idl_r.res:
	$(WIDL) $(IDLFLAGS) -r -o $@ $<

.idl_s.c:
	$(WIDL) $(IDLFLAGS) -s -o $@ $<

.idl.tlb:
	$(WIDL) $(TARGETFLAGS) $(IDLFLAGS) -t -o $@ $<

.idl_t.res:
	$(WIDL) $(TARGETFLAGS) $(IDLFLAGS) -t -o $@ $<

.c.ln:
	$(LINT) -c $(ALLLINTFLAGS) $< || ( $(RM) $@ && exit 1 )

.c.ok:
	$(RUNTEST) $(RUNTESTFLAGS) $< && touch $@

.sfd.ttf:
	$(FONTFORGE) -script $(top_srcdir)/fonts/genttf.ff $< $@

.man.in.man:
	LC_ALL=C sed -e 's,@bindir\@,$(bindir),g' -e 's,@dlldir\@,$(dlldir),g' -e 's,@PACKAGE_STRING\@,Wine 1.5.23,g' $< >$@ || ($(RM) $@ && false)

.svg.ico:
	CONVERT="$(CONVERT)" ICOTOOL="$(ICOTOOL)" RSVG="$(RSVG)" $(BUILDIMAGE) $< $@

.svg.bmp:
	CONVERT="$(CONVERT)" ICOTOOL="$(ICOTOOL)" RSVG="$(RSVG)" $(BUILDIMAGE) $< $@

.po.mo:
	$(MSGFMT) -o $@ $<

# Rules for IDL files

dlldata.c: $(WIDL) Makefile.in
	$(WIDL) $(IDLFLAGS) --dlldata-only -o $@ $(IDL_P_SRCS)

# Rule for linting

$(MODULE).ln : $(LINTS)
	if test "$(LINTS)" ; \
	then \
		$(LINT) $(ALLLINTFLAGS) -o$(MODULE) $(LINTS) ; \
	        $(MV) llib-l$(MODULE).ln $(MODULE).ln ; \
	else \
		$(LINT) $(ALLLINTFLAGS) -C$(MODULE) /dev/null ; \
	fi

lint:: $(MODULE).ln

# Rules for Windows API checking

winapi_check:: dummy
	$(WINAPI_CHECK) $(WINAPI_CHECK_FLAGS) $(WINAPI_CHECK_EXTRA_FLAGS) .

.PHONY: winapi_check

# Rules for dependencies

DEPEND_SRCS = $(C_SRCS) $(OBJC_SRCS) $(RC_SRCS) $(MC_SRCS) \
              $(IDL_H_SRCS) $(IDL_C_SRCS) $(IDL_I_SRCS) $(IDL_P_SRCS) $(IDL_S_SRCS) \
              $(IDL_GEN_C_SRCS) $(IDL_R_SRCS:.idl=_r.res) $(IDL_TLB_SRCS) $(IDL_TLB_SRCS:.idl=.tlb) \
              $(BISON_SRCS) $(LEX_SRCS) $(EXTRA_SRCS)

depend: dummy
	$(MAKEDEP) $(MAKEDEPFLAGS) -C$(srcdir) -S$(top_srcdir) -T$(top_builddir) $(EXTRAINCL) $(DEPEND_SRCS)

.PHONY: depend

# Rules for man pages

MANPAGES = $(MANPAGE) $(EXTRA_MANPAGES)

all: $(MANPAGES)

install-man-pages:: $(MANPAGE) $(DESTDIR)$(mandir)/man$(prog_manext)
	$(INSTALL_DATA) $(MANPAGE) $(DESTDIR)$(mandir)/man$(prog_manext)/$(MANPAGE:.man=).$(prog_manext)

uninstall-man-pages::
	$(RM) $(DESTDIR)$(mandir)/man$(prog_manext)/$(MANPAGE:.man=).$(prog_manext)

install::  $(MANPAGE:%=install-man-pages)
uninstall::  $(MANPAGE:%=uninstall-man-pages)

# Rules for cleaning

$(EXTRASUBDIRS:%=%/__clean__): dummy
	-cd `dirname $@` && $(RM) $(CLEAN_FILES)

clean:: $(EXTRASUBDIRS:%=%/__clean__)
	$(RM) $(CLEAN_FILES) $(CLEAN_TARGETS) $(PROGRAMS) $(MANPAGES)

.PHONY: clean $(EXTRASUBDIRS:%=%/__clean__)

# Rules for installing

$(INSTALLDIRS):
	$(MKINSTALLDIRS) $@

install install-lib install-dev uninstall::

.PHONY: install install-lib install-dev uninstall

# Rules for resources

rsrc.pot: $(WRC)
	$(LDPATH) $(WRC) $(RCFLAGS) -O pot -o $@ $(PO_SRCS)

msg.pot: $(WMC)
	$(LDPATH) $(WMC) -O pot -o $@ $(MC_SRCS)

$(MC_SRCS:.mc=.res): $(WMC) $(ALL_MO_FILES)
$(RC_SRCS:.rc=.res): $(WRC)
$(PO_SRCS:.rc=.res): $(ALL_MO_FILES)

# Misc. rules

$(IDL_GEN_HEADERS) $(IDL_GEN_C_SRCS) $(IDL_TLB_SRCS:.idl=.tlb) $(IDL_TLB_RES) $(IDL_R_SRCS:.idl=_r.res): $(WIDL)

dummy:

.PHONY: dummy

# End of global rules

OBJDIR_INCLUDES = $(PUBLIC_IDL_H_SRCS:.idl=.h) $(XTEMPLATE_SRCS:.x=.h)

all: $(IDL_H_SRCS:.idl=.h) $(IDL_TLB_SRCS:.idl=.tlb) $(XTEMPLATE_SRCS:.x=.h)

rmxftmpl.h: rmxftmpl.x $(MAKEXFTMPL)
	$(MAKEXFTMPL) -i D3DRM_XTEMPLATES -s D3DRM_XTEMPLATE_BYTES -o $@ $(srcdir)/rmxftmpl.x

install install-dev:: $(OBJDIR_INCLUDES) $(INSTALLDIRS)
	for f in $(SRCDIR_INCLUDES); do case $$f in \
	  wine/*)   $(INSTALL_DATA) $(srcdir)/$$f $(DESTDIR)$(includedir)/`expr $$f : 'wine/\(.*\)'` ;; \
	  msvcrt/*) $(INSTALL_DATA) $(srcdir)/$$f $(DESTDIR)$(includedir)/$$f ;; \
	  *)        $(INSTALL_DATA) $(srcdir)/$$f $(DESTDIR)$(includedir)/windows/$$f ;; \
	esac; done
	for f in $(OBJDIR_INCLUDES); do case $$f in \
	  wine/*)   $(INSTALL_DATA) $$f $(DESTDIR)$(includedir)/`expr $$f : 'wine/\(.*\)'` ;; \
	  msvcrt/*) $(INSTALL_DATA) $$f $(DESTDIR)$(includedir)/$$f ;; \
	  *)        $(INSTALL_DATA) $$f $(DESTDIR)$(includedir)/windows/$$f ;; \
	esac; done

# Don't just do a rm -rf on $(includedir) -- don't want to wipe out
# anything extra the user may have put there.
uninstall::
	for f in $(SRCDIR_INCLUDES) $(OBJDIR_INCLUDES); do case $$f in \
	  wine/*)   $(RM) $(DESTDIR)$(includedir)/`expr $$f : 'wine/\(.*\)'` ;; \
	  msvcrt/*) $(RM) $(DESTDIR)$(includedir)/$$f ;; \
	  *)        $(RM) $(DESTDIR)$(includedir)/windows/$$f ;; \
	esac; done
	-rmdir $(INSTALLDIRS)

### Dependencies
activaut.h: activaut.idl ocidl.idl oleidl.idl objidl.idl unknwn.idl \
 wtypes.idl basetsd.h guiddef.h oaidl.idl servprov.idl urlmon.idl \
 msxml.idl msxmldid.h msxml2did.h idispids.h xmldom.idl xmldomdid.h \
 xmldso.idl xmldsodid.h
activdbg.h: activdbg.idl ocidl.idl oleidl.idl objidl.idl unknwn.idl \
 wtypes.idl basetsd.h guiddef.h oaidl.idl servprov.idl urlmon.idl \
 msxml.idl msxmldid.h msxml2did.h idispids.h xmldom.idl xmldomdid.h \
 xmldso.idl xmldsodid.h activscp.idl
activscp.h: activscp.idl ocidl.idl oleidl.idl objidl.idl unknwn.idl \
 wtypes.idl basetsd.h guiddef.h oaidl.idl servprov.idl urlmon.idl \
 msxml.idl msxmldid.h msxml2did.h idispids.h xmldom.idl xmldomdid.h \
 xmldso.idl xmldsodid.h
amstream.h: amstream.idl unknwn.idl wtypes.idl basetsd.h guiddef.h \
 mmstream.idl strmif.idl objidl.idl devenum.idl oaidl.idl axcore.idl \
 axextend.idl dyngraph.idl vmrender.idl
amvideo.h: amvideo.idl objidl.idl unknwn.idl wtypes.idl basetsd.h \
 guiddef.h
asptlb.h: asptlb.idl unknwn.idl wtypes.idl basetsd.h guiddef.h \
 objidl.idl oaidl.idl
atliface.h: atliface.idl ocidl.idl oleidl.idl objidl.idl unknwn.idl \
 wtypes.idl basetsd.h guiddef.h oaidl.idl servprov.idl urlmon.idl \
 msxml.idl msxmldid.h msxml2did.h idispids.h xmldom.idl xmldomdid.h \
 xmldso.idl xmldsodid.h
audioclient.h: audioclient.idl wtypes.idl basetsd.h guiddef.h \
 unknwn.idl audiosessiontypes.h
audiopolicy.h: audiopolicy.idl oaidl.idl objidl.idl unknwn.idl \
 wtypes.idl basetsd.h guiddef.h ocidl.idl oleidl.idl servprov.idl \
 urlmon.idl msxml.idl msxmldid.h msxml2did.h idispids.h xmldom.idl \
 xmldomdid.h xmldso.idl xmldsodid.h propidl.idl audiosessiontypes.h \
 audioclient.idl
austream.h: austream.idl unknwn.idl wtypes.idl basetsd.h guiddef.h \
 mmstream.idl
bits.h: bits.idl unknwn.idl wtypes.idl basetsd.h guiddef.h
bits1_5.h: bits1_5.idl bits.idl unknwn.idl wtypes.idl basetsd.h \
 guiddef.h
comcat.h: comcat.idl unknwn.idl wtypes.idl basetsd.h guiddef.h
commoncontrols.h: commoncontrols.idl oaidl.idl objidl.idl unknwn.idl \
 wtypes.idl basetsd.h guiddef.h ocidl.idl oleidl.idl servprov.idl \
 urlmon.idl msxml.idl msxmldid.h msxml2did.h idispids.h xmldom.idl \
 xmldomdid.h xmldso.idl xmldsodid.h
control.h: control.idl oaidl.idl objidl.idl unknwn.idl wtypes.idl \
 basetsd.h guiddef.h
cor.h: cor.idl propidl.idl objidl.idl unknwn.idl wtypes.idl basetsd.h \
 guiddef.h oaidl.idl
cordebug.h: cordebug.idl unknwn.idl wtypes.idl basetsd.h guiddef.h \
 objidl.idl
ctfutb.h: ctfutb.idl oaidl.idl objidl.idl unknwn.idl wtypes.idl \
 basetsd.h guiddef.h
ctxtcall.h: ctxtcall.idl wtypes.idl basetsd.h guiddef.h objidl.idl \
 unknwn.idl
d3d10.h: d3d10.idl oaidl.idl objidl.idl unknwn.idl wtypes.idl \
 basetsd.h guiddef.h ocidl.idl oleidl.idl servprov.idl urlmon.idl \
 msxml.idl msxmldid.h msxml2did.h idispids.h xmldom.idl xmldomdid.h \
 xmldso.idl xmldsodid.h dxgi.idl dxgitype.h dxgiformat.h d3dcommon.idl
d3d10_1.h: d3d10_1.idl oaidl.idl objidl.idl unknwn.idl wtypes.idl \
 basetsd.h guiddef.h ocidl.idl oleidl.idl servprov.idl urlmon.idl \
 msxml.idl msxmldid.h msxml2did.h idispids.h xmldom.idl xmldomdid.h \
 xmldso.idl xmldsodid.h d3d10.idl dxgi.idl dxgitype.h dxgiformat.h \
 d3dcommon.idl
d3d11.h: d3d11.idl oaidl.idl objidl.idl unknwn.idl wtypes.idl \
 basetsd.h guiddef.h ocidl.idl oleidl.idl servprov.idl urlmon.idl \
 msxml.idl msxmldid.h msxml2did.h idispids.h xmldom.idl xmldomdid.h \
 xmldso.idl xmldsodid.h dxgi.idl dxgitype.h dxgiformat.h d3dcommon.idl
d3dcommon.h: d3dcommon.idl oaidl.idl objidl.idl unknwn.idl wtypes.idl \
 basetsd.h guiddef.h ocidl.idl oleidl.idl servprov.idl urlmon.idl \
 msxml.idl msxmldid.h msxml2did.h idispids.h xmldom.idl xmldomdid.h \
 xmldso.idl xmldsodid.h
ddstream.h: ddstream.idl unknwn.idl wtypes.idl basetsd.h guiddef.h \
 mmstream.idl
devicetopology.h: devicetopology.idl oaidl.idl objidl.idl unknwn.idl \
 wtypes.idl basetsd.h guiddef.h ocidl.idl oleidl.idl servprov.idl \
 urlmon.idl msxml.idl msxmldid.h msxml2did.h idispids.h xmldom.idl \
 xmldomdid.h xmldso.idl xmldsodid.h propidl.idl
dimm.h: dimm.idl unknwn.idl wtypes.idl basetsd.h guiddef.h
dispex.h: dispex.idl ocidl.idl oleidl.idl objidl.idl unknwn.idl \
 wtypes.idl basetsd.h guiddef.h oaidl.idl servprov.idl urlmon.idl \
 msxml.idl msxmldid.h msxml2did.h idispids.h xmldom.idl xmldomdid.h \
 xmldso.idl xmldsodid.h
docobj.h: docobj.idl ocidl.idl oleidl.idl objidl.idl unknwn.idl \
 wtypes.idl basetsd.h guiddef.h oaidl.idl servprov.idl urlmon.idl \
 msxml.idl msxmldid.h msxml2did.h idispids.h xmldom.idl xmldomdid.h \
 xmldso.idl xmldsodid.h
docobjectservice.h: docobjectservice.idl objidl.idl unknwn.idl \
 wtypes.idl basetsd.h guiddef.h mshtml.idl mshtmdid.h mshtmcid.h \
 olectl.h ocidl.h rpc.h windows.h winresrc.h winuser.rh commctrl.rh \
 dde.rh winnt.rh dlgs.h winver.h verrsrc.h excpt.h windef.h winnt.h \
 pshpack2.h poppack.h pshpack8.h pshpack4.h winbase.h winerror.h \
 wingdi.h winuser.h winnls.h wincon.h winreg.h reason.h winnetwk.h \
 cderr.h dde.h ddeml.h lzexpand.h mmsystem.h pshpack1.h nb30.h \
 shellapi.h winperf.h winsock.h inaddr.h wincrypt.h bcrypt.h \
 winscard.h wtypes.h rpcndr.h rpcsal.h winioctl.h winsmcrd.h \
 scarderr.h winspool.h ole2.h objbase.h unknwn.h objidl.h cguid.h \
 urlmon.h oleidl.h servprov.h msxml.h oaidl.h propidl.h oleauto.h \
 commdlg.h prsht.h winsvc.h mcx.h imm.h rpcdce.h rpcdcep.h rpcnterr.h \
 rpcasync.h ocidl.idl oleidl.idl oaidl.idl servprov.idl urlmon.idl \
 msxml.idl msxmldid.h msxml2did.h idispids.h xmldom.idl xmldomdid.h \
 xmldso.idl xmldsodid.h dimm.idl shtypes.idl dispex.idl
downloadmgr.h: downloadmgr.idl unknwn.idl wtypes.idl basetsd.h \
 guiddef.h ocidl.idl oleidl.idl objidl.idl oaidl.idl servprov.idl \
 urlmon.idl msxml.idl msxmldid.h msxml2did.h idispids.h xmldom.idl \
 xmldomdid.h xmldso.idl xmldsodid.h
dwrite.h: dwrite.idl unknwn.idl wtypes.idl basetsd.h guiddef.h \
 dcommon.h
dxgi.h: dxgi.idl oaidl.idl objidl.idl unknwn.idl wtypes.idl basetsd.h \
 guiddef.h ocidl.idl oleidl.idl servprov.idl urlmon.idl msxml.idl \
 msxmldid.h msxml2did.h idispids.h xmldom.idl xmldomdid.h xmldso.idl \
 xmldsodid.h dxgitype.h dxgiformat.h
endpointvolume.h: endpointvolume.idl unknwn.idl wtypes.idl basetsd.h \
 guiddef.h devicetopology.idl oaidl.idl objidl.idl ocidl.idl \
 oleidl.idl servprov.idl urlmon.idl msxml.idl msxmldid.h msxml2did.h \
 idispids.h xmldom.idl xmldomdid.h xmldso.idl xmldsodid.h propidl.idl
exdisp.h: exdisp.idl ocidl.idl oleidl.idl objidl.idl unknwn.idl \
 wtypes.idl basetsd.h guiddef.h oaidl.idl servprov.idl urlmon.idl \
 msxml.idl msxmldid.h msxml2did.h idispids.h xmldom.idl xmldomdid.h \
 xmldso.idl xmldsodid.h docobj.idl olectl.h ocidl.h rpc.h windows.h \
 winresrc.h winuser.rh commctrl.rh dde.rh winnt.rh dlgs.h winver.h \
 verrsrc.h excpt.h windef.h winnt.h pshpack2.h poppack.h pshpack8.h \
 pshpack4.h winbase.h winerror.h wingdi.h winuser.h winnls.h wincon.h \
 winreg.h reason.h winnetwk.h cderr.h dde.h ddeml.h lzexpand.h \
 mmsystem.h pshpack1.h nb30.h shellapi.h winperf.h winsock.h inaddr.h \
 wincrypt.h bcrypt.h winscard.h wtypes.h rpcndr.h rpcsal.h winioctl.h \
 winsmcrd.h scarderr.h winspool.h ole2.h objbase.h unknwn.h objidl.h \
 cguid.h urlmon.h oleidl.h servprov.h msxml.h oaidl.h propidl.h \
 oleauto.h commdlg.h prsht.h winsvc.h mcx.h imm.h rpcdce.h rpcdcep.h \
 rpcnterr.h rpcasync.h exdispid.h
fusion.h: fusion.idl objidl.idl unknwn.idl wtypes.idl basetsd.h \
 guiddef.h
gameux.h: gameux.idl oaidl.idl objidl.idl unknwn.idl wtypes.idl \
 basetsd.h guiddef.h ocidl.idl oleidl.idl servprov.idl urlmon.idl \
 msxml.idl msxmldid.h msxml2did.h idispids.h xmldom.idl xmldomdid.h \
 xmldso.idl xmldsodid.h shobjidl.idl docobj.idl shtypes.idl comcat.idl \
 propidl.idl propsys.idl structuredquerycondition.idl objectarray.idl
hlink.h: hlink.idl urlmon.idl objidl.idl unknwn.idl wtypes.idl \
 basetsd.h guiddef.h oleidl.idl servprov.idl msxml.idl msxmldid.h \
 msxml2did.h idispids.h oaidl.idl xmldom.idl xmldomdid.h xmldso.idl \
 xmldsodid.h
htiface.h: htiface.idl objidl.idl unknwn.idl wtypes.idl basetsd.h \
 guiddef.h oleidl.idl urlmon.idl servprov.idl msxml.idl msxmldid.h \
 msxml2did.h idispids.h oaidl.idl xmldom.idl xmldomdid.h xmldso.idl \
 xmldsodid.h
htiframe.h: htiframe.idl objidl.idl unknwn.idl wtypes.idl basetsd.h \
 guiddef.h oleidl.idl
httprequest.h: httprequest.idl httprequestid.h oaidl.idl objidl.idl \
 unknwn.idl wtypes.idl basetsd.h guiddef.h
iads.h: iads.idl oaidl.idl objidl.idl unknwn.idl wtypes.idl basetsd.h \
 guiddef.h
icftypes.h: icftypes.idl wtypes.idl basetsd.h guiddef.h
iextag.h: iextag.idl oaidl.idl objidl.idl unknwn.idl wtypes.idl \
 basetsd.h guiddef.h ocidl.idl oleidl.idl servprov.idl urlmon.idl \
 msxml.idl msxmldid.h msxml2did.h idispids.h xmldom.idl xmldomdid.h \
 xmldso.idl xmldsodid.h
imnact.h: imnact.idl objidl.idl unknwn.idl wtypes.idl basetsd.h \
 guiddef.h
imnxport.h: imnxport.idl imnact.idl objidl.idl unknwn.idl wtypes.idl \
 basetsd.h guiddef.h
indexsrv.h: indexsrv.idl oaidl.idl objidl.idl unknwn.idl wtypes.idl \
 basetsd.h guiddef.h
mediaobj.h: mediaobj.idl unknwn.idl wtypes.idl basetsd.h guiddef.h \
 objidl.idl
metahost.h: metahost.idl unknwn.idl wtypes.idl basetsd.h guiddef.h \
 oaidl.idl objidl.idl ocidl.idl oleidl.idl servprov.idl urlmon.idl \
 msxml.idl msxmldid.h msxml2did.h idispids.h xmldom.idl xmldomdid.h \
 xmldso.idl xmldsodid.h mscoree.idl
mimeinfo.h: mimeinfo.idl objidl.idl unknwn.idl wtypes.idl basetsd.h \
 guiddef.h
mimeole.h: mimeole.idl ocidl.idl oleidl.idl objidl.idl unknwn.idl \
 wtypes.idl basetsd.h guiddef.h oaidl.idl servprov.idl urlmon.idl \
 msxml.idl msxmldid.h msxml2did.h idispids.h xmldom.idl xmldomdid.h \
 xmldso.idl xmldsodid.h propidl.idl
mlang.h: mlang.idl unknwn.idl wtypes.idl basetsd.h guiddef.h
mmc.h: mmc.idl basetsd.h oaidl.idl objidl.idl unknwn.idl wtypes.idl \
 guiddef.h
mmdeviceapi.h: mmdeviceapi.idl unknwn.idl wtypes.idl basetsd.h \
 guiddef.h propsys.idl objidl.idl oleidl.idl ocidl.idl oaidl.idl \
 servprov.idl urlmon.idl msxml.idl msxmldid.h msxml2did.h idispids.h \
 xmldom.idl xmldomdid.h xmldso.idl xmldsodid.h shtypes.idl \
 structuredquerycondition.idl propidl.idl
mmstream.h: mmstream.idl unknwn.idl wtypes.idl basetsd.h guiddef.h
mscoree.h: mscoree.idl unknwn.idl wtypes.idl basetsd.h guiddef.h
msctf.h: msctf.idl oaidl.idl objidl.idl unknwn.idl wtypes.idl \
 basetsd.h guiddef.h comcat.idl textstor.idl ctfutb.idl
msdadc.h: msdadc.idl oaidl.idl objidl.idl unknwn.idl wtypes.idl \
 basetsd.h guiddef.h ocidl.idl oleidl.idl servprov.idl urlmon.idl \
 msxml.idl msxmldid.h msxml2did.h idispids.h xmldom.idl xmldomdid.h \
 xmldso.idl xmldsodid.h oledb.idl propidl.idl dbs.idl access.idl \
 rstbas.idl rstinf.idl rstloc.idl cmdbas.idl cmdtxt.idl dbccmd.idl \
 dbcses.idl dbprop.idl dbinit.idl dbdsad.idl asynot.idl asysta.idl \
 sesprp.idl opnrst.idl row.idl rowchg.idl binres.idl crtrow.idl
msdasc.h: msdasc.idl oaidl.idl objidl.idl unknwn.idl wtypes.idl \
 basetsd.h guiddef.h ocidl.idl oleidl.idl servprov.idl urlmon.idl \
 msxml.idl msxmldid.h msxml2did.h idispids.h xmldom.idl xmldomdid.h \
 xmldso.idl xmldsodid.h oledb.idl propidl.idl dbs.idl access.idl \
 rstbas.idl rstinf.idl rstloc.idl cmdbas.idl cmdtxt.idl dbccmd.idl \
 dbcses.idl dbprop.idl dbinit.idl dbdsad.idl asynot.idl asysta.idl \
 sesprp.idl opnrst.idl row.idl rowchg.idl binres.idl crtrow.idl
mshtmhst.h: mshtmhst.idl ocidl.idl oleidl.idl objidl.idl unknwn.idl \
 wtypes.idl basetsd.h guiddef.h oaidl.idl servprov.idl urlmon.idl \
 msxml.idl msxmldid.h msxml2did.h idispids.h xmldom.idl xmldomdid.h \
 xmldso.idl xmldsodid.h docobj.idl
mshtml.h: mshtml.idl mshtmdid.h mshtmcid.h olectl.h ocidl.h rpc.h \
 windows.h winresrc.h winuser.rh commctrl.rh dde.rh winnt.rh dlgs.h \
 winver.h verrsrc.h excpt.h windef.h winnt.h basetsd.h guiddef.h \
 pshpack2.h poppack.h pshpack8.h pshpack4.h winbase.h winerror.h \
 wingdi.h winuser.h winnls.h wincon.h winreg.h reason.h winnetwk.h \
 cderr.h dde.h ddeml.h lzexpand.h mmsystem.h pshpack1.h nb30.h \
 shellapi.h winperf.h winsock.h inaddr.h wincrypt.h bcrypt.h \
 winscard.h wtypes.h rpcndr.h rpcsal.h winioctl.h winsmcrd.h \
 scarderr.h winspool.h ole2.h objbase.h unknwn.h objidl.h cguid.h \
 urlmon.h oleidl.h servprov.h msxml.h oaidl.h propidl.h oleauto.h \
 commdlg.h prsht.h winsvc.h mcx.h imm.h rpcdce.h rpcdcep.h rpcnterr.h \
 rpcasync.h ocidl.idl oleidl.idl objidl.idl unknwn.idl wtypes.idl \
 oaidl.idl servprov.idl urlmon.idl msxml.idl msxmldid.h msxml2did.h \
 idispids.h xmldom.idl xmldomdid.h xmldso.idl xmldsodid.h dimm.idl \
 shtypes.idl dispex.idl
msident.h: msident.idl unknwn.idl wtypes.idl basetsd.h guiddef.h \
 ocidl.idl oleidl.idl objidl.idl oaidl.idl servprov.idl urlmon.idl \
 msxml.idl msxmldid.h msxml2did.h idispids.h xmldom.idl xmldomdid.h \
 xmldso.idl xmldsodid.h
msinkaut.h: msinkaut.idl oaidl.idl objidl.idl unknwn.idl wtypes.idl \
 basetsd.h guiddef.h ocidl.idl oleidl.idl servprov.idl urlmon.idl \
 msxml.idl msxmldid.h msxml2did.h idispids.h xmldom.idl xmldomdid.h \
 xmldso.idl xmldsodid.h
mstask.h: mstask.idl oaidl.idl objidl.idl unknwn.idl wtypes.idl \
 basetsd.h guiddef.h oleidl.idl
msxml.h: msxml.idl msxmldid.h msxml2did.h idispids.h unknwn.idl \
 wtypes.idl basetsd.h guiddef.h objidl.idl oaidl.idl xmldom.idl \
 xmldomdid.h xmldso.idl xmldsodid.h
msxml2.h: msxml2.idl msxml2did.h idispids.h unknwn.idl wtypes.idl \
 basetsd.h guiddef.h objidl.idl oaidl.idl
msxml6.h: msxml6.idl msxml6did.h msxml2did.h idispids.h unknwn.idl \
 wtypes.idl basetsd.h guiddef.h objidl.idl oaidl.idl
netcon.h: netcon.idl oaidl.idl objidl.idl unknwn.idl wtypes.idl \
 basetsd.h guiddef.h
netfw.h: netfw.idl icftypes.idl wtypes.idl basetsd.h guiddef.h \
 oaidl.idl objidl.idl unknwn.idl
oaidl.h: oaidl.idl objidl.idl unknwn.idl wtypes.idl basetsd.h \
 guiddef.h
objectarray.h: objectarray.idl oaidl.idl objidl.idl unknwn.idl \
 wtypes.idl basetsd.h guiddef.h ocidl.idl oleidl.idl servprov.idl \
 urlmon.idl msxml.idl msxmldid.h msxml2did.h idispids.h xmldom.idl \
 xmldomdid.h xmldso.idl xmldsodid.h
objidl.h: objidl.idl unknwn.idl wtypes.idl basetsd.h guiddef.h
objsafe.h: objsafe.idl unknwn.idl wtypes.idl basetsd.h guiddef.h
ocidl.h: ocidl.idl oleidl.idl objidl.idl unknwn.idl wtypes.idl \
 basetsd.h guiddef.h oaidl.idl servprov.idl urlmon.idl msxml.idl \
 msxmldid.h msxml2did.h idispids.h xmldom.idl xmldomdid.h xmldso.idl \
 xmldsodid.h
ocmm.h: ocmm.idl oaidl.idl objidl.idl unknwn.idl wtypes.idl basetsd.h \
 guiddef.h oleidl.idl
oleacc.h: oleacc.idl oaidl.idl objidl.idl unknwn.idl wtypes.idl \
 basetsd.h guiddef.h
oledb.h: oledb.idl wtypes.idl basetsd.h guiddef.h oaidl.idl objidl.idl \
 unknwn.idl ocidl.idl oleidl.idl servprov.idl urlmon.idl msxml.idl \
 msxmldid.h msxml2did.h idispids.h xmldom.idl xmldomdid.h xmldso.idl \
 xmldsodid.h propidl.idl dbs.idl access.idl rstbas.idl rstinf.idl \
 rstloc.idl cmdbas.idl cmdtxt.idl dbccmd.idl dbcses.idl dbprop.idl \
 dbinit.idl dbdsad.idl asynot.idl asysta.idl sesprp.idl opnrst.idl \
 row.idl rowchg.idl binres.idl crtrow.idl
oleidl.h: oleidl.idl objidl.idl unknwn.idl wtypes.idl basetsd.h \
 guiddef.h
optary.h: optary.idl objidl.idl unknwn.idl wtypes.idl basetsd.h \
 guiddef.h oleidl.idl
perhist.h: perhist.idl objidl.idl unknwn.idl wtypes.idl basetsd.h \
 guiddef.h oleidl.idl
propidl.h: propidl.idl objidl.idl unknwn.idl wtypes.idl basetsd.h \
 guiddef.h oaidl.idl
propsys.h: propsys.idl objidl.idl unknwn.idl wtypes.idl basetsd.h \
 guiddef.h oleidl.idl ocidl.idl oaidl.idl servprov.idl urlmon.idl \
 msxml.idl msxmldid.h msxml2did.h idispids.h xmldom.idl xmldomdid.h \
 xmldso.idl xmldsodid.h shtypes.idl structuredquerycondition.idl \
 propidl.idl
pstore.h: pstore.idl wtypes.idl basetsd.h guiddef.h oaidl.idl \
 objidl.idl unknwn.idl
qedit.h: qedit.idl oaidl.idl objidl.idl unknwn.idl wtypes.idl \
 basetsd.h guiddef.h ocidl.idl oleidl.idl servprov.idl urlmon.idl \
 msxml.idl msxmldid.h msxml2did.h idispids.h xmldom.idl xmldomdid.h \
 xmldso.idl xmldsodid.h amstream.idl mmstream.idl strmif.idl \
 devenum.idl axcore.idl axextend.idl dyngraph.idl vmrender.idl
richole.h: richole.idl oleidl.idl objidl.idl unknwn.idl wtypes.idl \
 basetsd.h guiddef.h
sensevts.h: sensevts.idl wtypes.idl basetsd.h guiddef.h oaidl.idl \
 objidl.idl unknwn.idl
servprov.h: servprov.idl objidl.idl unknwn.idl wtypes.idl basetsd.h \
 guiddef.h
shdeprecated.h: shdeprecated.idl objidl.idl unknwn.idl wtypes.idl \
 basetsd.h guiddef.h ocidl.idl oleidl.idl oaidl.idl servprov.idl \
 urlmon.idl msxml.idl msxmldid.h msxml2did.h idispids.h xmldom.idl \
 xmldomdid.h xmldso.idl xmldsodid.h shtypes.idl shobjidl.idl \
 docobj.idl comcat.idl propidl.idl propsys.idl \
 structuredquerycondition.idl objectarray.idl hlink.idl exdisp.idl \
 olectl.h ocidl.h rpc.h windows.h winresrc.h winuser.rh commctrl.rh \
 dde.rh winnt.rh dlgs.h winver.h verrsrc.h excpt.h windef.h winnt.h \
 pshpack2.h poppack.h pshpack8.h pshpack4.h winbase.h winerror.h \
 wingdi.h winuser.h winnls.h wincon.h winreg.h reason.h winnetwk.h \
 cderr.h dde.h ddeml.h lzexpand.h mmsystem.h pshpack1.h nb30.h \
 shellapi.h winperf.h winsock.h inaddr.h wincrypt.h bcrypt.h \
 winscard.h wtypes.h rpcndr.h rpcsal.h winioctl.h winsmcrd.h \
 scarderr.h winspool.h ole2.h objbase.h unknwn.h objidl.h cguid.h \
 urlmon.h oleidl.h servprov.h msxml.h oaidl.h propidl.h oleauto.h \
 commdlg.h prsht.h winsvc.h mcx.h imm.h rpcdce.h rpcdcep.h rpcnterr.h \
 rpcasync.h exdispid.h
shldisp.h: shldisp.idl ocidl.idl oleidl.idl objidl.idl unknwn.idl \
 wtypes.idl basetsd.h guiddef.h oaidl.idl servprov.idl urlmon.idl \
 msxml.idl msxmldid.h msxml2did.h idispids.h xmldom.idl xmldomdid.h \
 xmldso.idl xmldsodid.h shdispid.h
shobjidl.h: shobjidl.idl objidl.idl unknwn.idl wtypes.idl basetsd.h \
 guiddef.h oleidl.idl oaidl.idl docobj.idl ocidl.idl servprov.idl \
 urlmon.idl msxml.idl msxmldid.h msxml2did.h idispids.h xmldom.idl \
 xmldomdid.h xmldso.idl xmldsodid.h shtypes.idl comcat.idl propidl.idl \
 propsys.idl structuredquerycondition.idl objectarray.idl
shtypes.h: shtypes.idl wtypes.idl basetsd.h guiddef.h
strmif.h: strmif.idl unknwn.idl wtypes.idl basetsd.h guiddef.h \
 objidl.idl devenum.idl oaidl.idl axcore.idl axextend.idl dyngraph.idl \
 vmrender.idl
structuredquerycondition.h: structuredquerycondition.idl oaidl.idl \
 objidl.idl unknwn.idl wtypes.idl basetsd.h guiddef.h ocidl.idl \
 oleidl.idl servprov.idl urlmon.idl msxml.idl msxmldid.h msxml2did.h \
 idispids.h xmldom.idl xmldomdid.h xmldso.idl xmldsodid.h propidl.idl
textstor.h: textstor.idl oaidl.idl objidl.idl unknwn.idl wtypes.idl \
 basetsd.h guiddef.h
tlogstg.h: tlogstg.idl objidl.idl unknwn.idl wtypes.idl basetsd.h \
 guiddef.h oleidl.idl shtypes.idl
tom.h: tom.idl oaidl.idl objidl.idl unknwn.idl wtypes.idl basetsd.h \
 guiddef.h ocidl.idl oleidl.idl servprov.idl urlmon.idl msxml.idl \
 msxmldid.h msxml2did.h idispids.h xmldom.idl xmldomdid.h xmldso.idl \
 xmldsodid.h
uiautomationclient.h: uiautomationclient.idl uiautomationcore.idl \
 oaidl.idl objidl.idl unknwn.idl wtypes.idl basetsd.h guiddef.h \
 oleacc.idl
uiautomationcore.h: uiautomationcore.idl oaidl.idl objidl.idl \
 unknwn.idl wtypes.idl basetsd.h guiddef.h oleacc.idl
unknwn.h: unknwn.idl wtypes.idl basetsd.h guiddef.h
urlhist.h: urlhist.idl objidl.idl unknwn.idl wtypes.idl basetsd.h \
 guiddef.h oleidl.idl oaidl.idl docobj.idl ocidl.idl servprov.idl \
 urlmon.idl msxml.idl msxmldid.h msxml2did.h idispids.h xmldom.idl \
 xmldomdid.h xmldso.idl xmldsodid.h
urlmon.h: urlmon.idl objidl.idl unknwn.idl wtypes.idl basetsd.h \
 guiddef.h oleidl.idl servprov.idl msxml.idl msxmldid.h msxml2did.h \
 idispids.h oaidl.idl xmldom.idl xmldomdid.h xmldso.idl xmldsodid.h
vmr9.h: vmr9.idl unknwn.idl wtypes.idl basetsd.h guiddef.h
wbemcli.h: wbemcli.idl oaidl.idl objidl.idl unknwn.idl wtypes.idl \
 basetsd.h guiddef.h
wbemprov.h: wbemprov.idl
wia_lh.h: wia_lh.idl unknwn.idl wtypes.idl basetsd.h guiddef.h \
 oaidl.idl objidl.idl propidl.idl
wia_xp.h: wia_xp.idl unknwn.idl wtypes.idl basetsd.h guiddef.h \
 oaidl.idl objidl.idl propidl.idl
wincodec.h: wincodec.idl wtypes.idl basetsd.h guiddef.h propidl.idl \
 objidl.idl unknwn.idl oaidl.idl ocidl.idl oleidl.idl servprov.idl \
 urlmon.idl msxml.idl msxmldid.h msxml2did.h idispids.h xmldom.idl \
 xmldomdid.h xmldso.idl xmldsodid.h
wincodecsdk.h: wincodecsdk.idl wtypes.idl basetsd.h guiddef.h \
 wincodec.idl propidl.idl objidl.idl unknwn.idl oaidl.idl ocidl.idl \
 oleidl.idl servprov.idl urlmon.idl msxml.idl msxmldid.h msxml2did.h \
 idispids.h xmldom.idl xmldomdid.h xmldso.idl xmldsodid.h
wine/itss.h: wine/itss.idl oaidl.idl objidl.idl unknwn.idl wtypes.idl \
 basetsd.h guiddef.h
wine/svcctl.h: wine/svcctl.idl wtypes.idl basetsd.h guiddef.h
winsxs.h: winsxs.idl objidl.idl unknwn.idl wtypes.idl basetsd.h \
 guiddef.h oleidl.idl
wmiutils.h: wmiutils.idl oaidl.idl objidl.idl unknwn.idl wtypes.idl \
 basetsd.h guiddef.h
wmsbuffer.h: wmsbuffer.idl objidl.idl unknwn.idl wtypes.idl basetsd.h \
 guiddef.h
wmsdkidl.h: wmsdkidl.idl oaidl.idl objidl.idl unknwn.idl wtypes.idl \
 basetsd.h guiddef.h wmsbuffer.idl
wpcapi.h: wpcapi.idl oaidl.idl objidl.idl unknwn.idl wtypes.idl \
 basetsd.h guiddef.h ocidl.idl oleidl.idl servprov.idl urlmon.idl \
 msxml.idl msxmldid.h msxml2did.h idispids.h xmldom.idl xmldomdid.h \
 xmldso.idl xmldsodid.h
wtypes.h: wtypes.idl basetsd.h guiddef.h
wuapi.h: wuapi.idl oaidl.idl objidl.idl unknwn.idl wtypes.idl \
 basetsd.h guiddef.h
xmllite.h: xmllite.idl unknwn.idl wtypes.idl basetsd.h guiddef.h \
 objidl.idl oaidl.idl
wine/winedxgi.h: wine/winedxgi.idl dxgi.idl oaidl.idl objidl.idl \
 unknwn.idl wtypes.idl basetsd.h guiddef.h ocidl.idl oleidl.idl \
 servprov.idl urlmon.idl msxml.idl msxmldid.h msxml2did.h idispids.h \
 xmldom.idl xmldomdid.h xmldso.idl xmldsodid.h dxgitype.h dxgiformat.h
stdole2.tlb stdole2_t.res: stdole2.idl
