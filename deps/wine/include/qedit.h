/*** Autogenerated by WIDL 1.5.23 from qedit.idl - Do not edit ***/

#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include <rpc.h>
#include <rpcndr.h>

#ifndef COM_NO_WINDOWS_H
#include <windows.h>
#include <ole2.h>
#endif

#ifndef __qedit_h__
#define __qedit_h__

/* Forward declarations */

#ifndef __ISampleGrabberCB_FWD_DEFINED__
#define __ISampleGrabberCB_FWD_DEFINED__
typedef interface ISampleGrabberCB ISampleGrabberCB;
#endif

#ifndef __ISampleGrabber_FWD_DEFINED__
#define __ISampleGrabber_FWD_DEFINED__
typedef interface ISampleGrabber ISampleGrabber;
#endif

#ifndef __IMediaDet_FWD_DEFINED__
#define __IMediaDet_FWD_DEFINED__
typedef interface IMediaDet IMediaDet;
#endif

#ifndef __MediaDet_FWD_DEFINED__
#define __MediaDet_FWD_DEFINED__
#ifdef __cplusplus
typedef class MediaDet MediaDet;
#else
typedef struct MediaDet MediaDet;
#endif /* defined __cplusplus */
#endif /* defined __MediaDet_FWD_DEFINED__ */

/* Headers for imported files */

#include <oaidl.h>
#include <ocidl.h>
#include <amstream.h>
#include <msxml.h>

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
 * ISampleGrabberCB interface
 */
#ifndef __ISampleGrabberCB_INTERFACE_DEFINED__
#define __ISampleGrabberCB_INTERFACE_DEFINED__

DEFINE_GUID(IID_ISampleGrabberCB, 0x0579154a, 0x2b53, 0x4994, 0xb0,0xd0, 0xe7,0x73,0x14,0x8e,0xff,0x85);
#if defined(__cplusplus) && !defined(CINTERFACE)
MIDL_INTERFACE("0579154a-2b53-4994-b0d0-e773148eff85")
ISampleGrabberCB : public IUnknown
{
    virtual HRESULT STDMETHODCALLTYPE SampleCB(
        double SampleTime,
        IMediaSample *pSample) = 0;

    virtual HRESULT STDMETHODCALLTYPE BufferCB(
        double SampleTime,
        BYTE *pBuffer,
        LONG BufferLen) = 0;

};
#ifdef __CRT_UUID_DECL
__CRT_UUID_DECL(ISampleGrabberCB, 0x0579154a, 0x2b53, 0x4994, 0xb0,0xd0, 0xe7,0x73,0x14,0x8e,0xff,0x85)
#endif
#else
typedef struct ISampleGrabberCBVtbl {
    BEGIN_INTERFACE

    /*** IUnknown methods ***/
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        ISampleGrabberCB* This,
        REFIID riid,
        void **ppvObject);

    ULONG (STDMETHODCALLTYPE *AddRef)(
        ISampleGrabberCB* This);

    ULONG (STDMETHODCALLTYPE *Release)(
        ISampleGrabberCB* This);

    /*** ISampleGrabberCB methods ***/
    HRESULT (STDMETHODCALLTYPE *SampleCB)(
        ISampleGrabberCB* This,
        double SampleTime,
        IMediaSample *pSample);

    HRESULT (STDMETHODCALLTYPE *BufferCB)(
        ISampleGrabberCB* This,
        double SampleTime,
        BYTE *pBuffer,
        LONG BufferLen);

    END_INTERFACE
} ISampleGrabberCBVtbl;
interface ISampleGrabberCB {
    CONST_VTBL ISampleGrabberCBVtbl* lpVtbl;
};

#ifdef COBJMACROS
#ifndef WIDL_C_INLINE_WRAPPERS
/*** IUnknown methods ***/
#define ISampleGrabberCB_QueryInterface(This,riid,ppvObject) (This)->lpVtbl->QueryInterface(This,riid,ppvObject)
#define ISampleGrabberCB_AddRef(This) (This)->lpVtbl->AddRef(This)
#define ISampleGrabberCB_Release(This) (This)->lpVtbl->Release(This)
/*** ISampleGrabberCB methods ***/
#define ISampleGrabberCB_SampleCB(This,SampleTime,pSample) (This)->lpVtbl->SampleCB(This,SampleTime,pSample)
#define ISampleGrabberCB_BufferCB(This,SampleTime,pBuffer,BufferLen) (This)->lpVtbl->BufferCB(This,SampleTime,pBuffer,BufferLen)
#else
/*** IUnknown methods ***/
static FORCEINLINE HRESULT ISampleGrabberCB_QueryInterface(ISampleGrabberCB* This,REFIID riid,void **ppvObject) {
    return This->lpVtbl->QueryInterface(This,riid,ppvObject);
}
static FORCEINLINE ULONG ISampleGrabberCB_AddRef(ISampleGrabberCB* This) {
    return This->lpVtbl->AddRef(This);
}
static FORCEINLINE ULONG ISampleGrabberCB_Release(ISampleGrabberCB* This) {
    return This->lpVtbl->Release(This);
}
/*** ISampleGrabberCB methods ***/
static FORCEINLINE HRESULT ISampleGrabberCB_SampleCB(ISampleGrabberCB* This,double SampleTime,IMediaSample *pSample) {
    return This->lpVtbl->SampleCB(This,SampleTime,pSample);
}
static FORCEINLINE HRESULT ISampleGrabberCB_BufferCB(ISampleGrabberCB* This,double SampleTime,BYTE *pBuffer,LONG BufferLen) {
    return This->lpVtbl->BufferCB(This,SampleTime,pBuffer,BufferLen);
}
#endif
#endif

#endif

HRESULT STDMETHODCALLTYPE ISampleGrabberCB_SampleCB_Proxy(
    ISampleGrabberCB* This,
    double SampleTime,
    IMediaSample *pSample);
void __RPC_STUB ISampleGrabberCB_SampleCB_Stub(
    IRpcStubBuffer* This,
    IRpcChannelBuffer* pRpcChannelBuffer,
    PRPC_MESSAGE pRpcMessage,
    DWORD* pdwStubPhase);
HRESULT STDMETHODCALLTYPE ISampleGrabberCB_BufferCB_Proxy(
    ISampleGrabberCB* This,
    double SampleTime,
    BYTE *pBuffer,
    LONG BufferLen);
void __RPC_STUB ISampleGrabberCB_BufferCB_Stub(
    IRpcStubBuffer* This,
    IRpcChannelBuffer* pRpcChannelBuffer,
    PRPC_MESSAGE pRpcMessage,
    DWORD* pdwStubPhase);

#endif  /* __ISampleGrabberCB_INTERFACE_DEFINED__ */

/*****************************************************************************
 * ISampleGrabber interface
 */
#ifndef __ISampleGrabber_INTERFACE_DEFINED__
#define __ISampleGrabber_INTERFACE_DEFINED__

DEFINE_GUID(IID_ISampleGrabber, 0x6b652fff, 0x11fe, 0x4fce, 0x92,0xad, 0x02,0x66,0xb5,0xd7,0xc7,0x8f);
#if defined(__cplusplus) && !defined(CINTERFACE)
MIDL_INTERFACE("6b652fff-11fe-4fce-92ad-0266b5d7c78f")
ISampleGrabber : public IUnknown
{
    virtual HRESULT STDMETHODCALLTYPE SetOneShot(
        BOOL OneShot) = 0;

    virtual HRESULT STDMETHODCALLTYPE SetMediaType(
        const AM_MEDIA_TYPE *pType) = 0;

    virtual HRESULT STDMETHODCALLTYPE GetConnectedMediaType(
        AM_MEDIA_TYPE *pType) = 0;

    virtual HRESULT STDMETHODCALLTYPE SetBufferSamples(
        BOOL BufferThem) = 0;

    virtual HRESULT STDMETHODCALLTYPE GetCurrentBuffer(
        LONG *pBufferSize,
        LONG *pBuffer) = 0;

    virtual HRESULT STDMETHODCALLTYPE GetCurrentSample(
        IMediaSample **ppSample) = 0;

    virtual HRESULT STDMETHODCALLTYPE SetCallback(
        ISampleGrabberCB *pCallback,
        LONG WhichMethodToCallback) = 0;

};
#ifdef __CRT_UUID_DECL
__CRT_UUID_DECL(ISampleGrabber, 0x6b652fff, 0x11fe, 0x4fce, 0x92,0xad, 0x02,0x66,0xb5,0xd7,0xc7,0x8f)
#endif
#else
typedef struct ISampleGrabberVtbl {
    BEGIN_INTERFACE

    /*** IUnknown methods ***/
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        ISampleGrabber* This,
        REFIID riid,
        void **ppvObject);

    ULONG (STDMETHODCALLTYPE *AddRef)(
        ISampleGrabber* This);

    ULONG (STDMETHODCALLTYPE *Release)(
        ISampleGrabber* This);

    /*** ISampleGrabber methods ***/
    HRESULT (STDMETHODCALLTYPE *SetOneShot)(
        ISampleGrabber* This,
        BOOL OneShot);

    HRESULT (STDMETHODCALLTYPE *SetMediaType)(
        ISampleGrabber* This,
        const AM_MEDIA_TYPE *pType);

    HRESULT (STDMETHODCALLTYPE *GetConnectedMediaType)(
        ISampleGrabber* This,
        AM_MEDIA_TYPE *pType);

    HRESULT (STDMETHODCALLTYPE *SetBufferSamples)(
        ISampleGrabber* This,
        BOOL BufferThem);

    HRESULT (STDMETHODCALLTYPE *GetCurrentBuffer)(
        ISampleGrabber* This,
        LONG *pBufferSize,
        LONG *pBuffer);

    HRESULT (STDMETHODCALLTYPE *GetCurrentSample)(
        ISampleGrabber* This,
        IMediaSample **ppSample);

    HRESULT (STDMETHODCALLTYPE *SetCallback)(
        ISampleGrabber* This,
        ISampleGrabberCB *pCallback,
        LONG WhichMethodToCallback);

    END_INTERFACE
} ISampleGrabberVtbl;
interface ISampleGrabber {
    CONST_VTBL ISampleGrabberVtbl* lpVtbl;
};

#ifdef COBJMACROS
#ifndef WIDL_C_INLINE_WRAPPERS
/*** IUnknown methods ***/
#define ISampleGrabber_QueryInterface(This,riid,ppvObject) (This)->lpVtbl->QueryInterface(This,riid,ppvObject)
#define ISampleGrabber_AddRef(This) (This)->lpVtbl->AddRef(This)
#define ISampleGrabber_Release(This) (This)->lpVtbl->Release(This)
/*** ISampleGrabber methods ***/
#define ISampleGrabber_SetOneShot(This,OneShot) (This)->lpVtbl->SetOneShot(This,OneShot)
#define ISampleGrabber_SetMediaType(This,pType) (This)->lpVtbl->SetMediaType(This,pType)
#define ISampleGrabber_GetConnectedMediaType(This,pType) (This)->lpVtbl->GetConnectedMediaType(This,pType)
#define ISampleGrabber_SetBufferSamples(This,BufferThem) (This)->lpVtbl->SetBufferSamples(This,BufferThem)
#define ISampleGrabber_GetCurrentBuffer(This,pBufferSize,pBuffer) (This)->lpVtbl->GetCurrentBuffer(This,pBufferSize,pBuffer)
#define ISampleGrabber_GetCurrentSample(This,ppSample) (This)->lpVtbl->GetCurrentSample(This,ppSample)
#define ISampleGrabber_SetCallback(This,pCallback,WhichMethodToCallback) (This)->lpVtbl->SetCallback(This,pCallback,WhichMethodToCallback)
#else
/*** IUnknown methods ***/
static FORCEINLINE HRESULT ISampleGrabber_QueryInterface(ISampleGrabber* This,REFIID riid,void **ppvObject) {
    return This->lpVtbl->QueryInterface(This,riid,ppvObject);
}
static FORCEINLINE ULONG ISampleGrabber_AddRef(ISampleGrabber* This) {
    return This->lpVtbl->AddRef(This);
}
static FORCEINLINE ULONG ISampleGrabber_Release(ISampleGrabber* This) {
    return This->lpVtbl->Release(This);
}
/*** ISampleGrabber methods ***/
static FORCEINLINE HRESULT ISampleGrabber_SetOneShot(ISampleGrabber* This,BOOL OneShot) {
    return This->lpVtbl->SetOneShot(This,OneShot);
}
static FORCEINLINE HRESULT ISampleGrabber_SetMediaType(ISampleGrabber* This,const AM_MEDIA_TYPE *pType) {
    return This->lpVtbl->SetMediaType(This,pType);
}
static FORCEINLINE HRESULT ISampleGrabber_GetConnectedMediaType(ISampleGrabber* This,AM_MEDIA_TYPE *pType) {
    return This->lpVtbl->GetConnectedMediaType(This,pType);
}
static FORCEINLINE HRESULT ISampleGrabber_SetBufferSamples(ISampleGrabber* This,BOOL BufferThem) {
    return This->lpVtbl->SetBufferSamples(This,BufferThem);
}
static FORCEINLINE HRESULT ISampleGrabber_GetCurrentBuffer(ISampleGrabber* This,LONG *pBufferSize,LONG *pBuffer) {
    return This->lpVtbl->GetCurrentBuffer(This,pBufferSize,pBuffer);
}
static FORCEINLINE HRESULT ISampleGrabber_GetCurrentSample(ISampleGrabber* This,IMediaSample **ppSample) {
    return This->lpVtbl->GetCurrentSample(This,ppSample);
}
static FORCEINLINE HRESULT ISampleGrabber_SetCallback(ISampleGrabber* This,ISampleGrabberCB *pCallback,LONG WhichMethodToCallback) {
    return This->lpVtbl->SetCallback(This,pCallback,WhichMethodToCallback);
}
#endif
#endif

#endif

HRESULT STDMETHODCALLTYPE ISampleGrabber_SetOneShot_Proxy(
    ISampleGrabber* This,
    BOOL OneShot);
void __RPC_STUB ISampleGrabber_SetOneShot_Stub(
    IRpcStubBuffer* This,
    IRpcChannelBuffer* pRpcChannelBuffer,
    PRPC_MESSAGE pRpcMessage,
    DWORD* pdwStubPhase);
HRESULT STDMETHODCALLTYPE ISampleGrabber_SetMediaType_Proxy(
    ISampleGrabber* This,
    const AM_MEDIA_TYPE *pType);
void __RPC_STUB ISampleGrabber_SetMediaType_Stub(
    IRpcStubBuffer* This,
    IRpcChannelBuffer* pRpcChannelBuffer,
    PRPC_MESSAGE pRpcMessage,
    DWORD* pdwStubPhase);
HRESULT STDMETHODCALLTYPE ISampleGrabber_GetConnectedMediaType_Proxy(
    ISampleGrabber* This,
    AM_MEDIA_TYPE *pType);
void __RPC_STUB ISampleGrabber_GetConnectedMediaType_Stub(
    IRpcStubBuffer* This,
    IRpcChannelBuffer* pRpcChannelBuffer,
    PRPC_MESSAGE pRpcMessage,
    DWORD* pdwStubPhase);
HRESULT STDMETHODCALLTYPE ISampleGrabber_SetBufferSamples_Proxy(
    ISampleGrabber* This,
    BOOL BufferThem);
void __RPC_STUB ISampleGrabber_SetBufferSamples_Stub(
    IRpcStubBuffer* This,
    IRpcChannelBuffer* pRpcChannelBuffer,
    PRPC_MESSAGE pRpcMessage,
    DWORD* pdwStubPhase);
HRESULT STDMETHODCALLTYPE ISampleGrabber_GetCurrentBuffer_Proxy(
    ISampleGrabber* This,
    LONG *pBufferSize,
    LONG *pBuffer);
void __RPC_STUB ISampleGrabber_GetCurrentBuffer_Stub(
    IRpcStubBuffer* This,
    IRpcChannelBuffer* pRpcChannelBuffer,
    PRPC_MESSAGE pRpcMessage,
    DWORD* pdwStubPhase);
HRESULT STDMETHODCALLTYPE ISampleGrabber_GetCurrentSample_Proxy(
    ISampleGrabber* This,
    IMediaSample **ppSample);
void __RPC_STUB ISampleGrabber_GetCurrentSample_Stub(
    IRpcStubBuffer* This,
    IRpcChannelBuffer* pRpcChannelBuffer,
    PRPC_MESSAGE pRpcMessage,
    DWORD* pdwStubPhase);
HRESULT STDMETHODCALLTYPE ISampleGrabber_SetCallback_Proxy(
    ISampleGrabber* This,
    ISampleGrabberCB *pCallback,
    LONG WhichMethodToCallback);
void __RPC_STUB ISampleGrabber_SetCallback_Stub(
    IRpcStubBuffer* This,
    IRpcChannelBuffer* pRpcChannelBuffer,
    PRPC_MESSAGE pRpcMessage,
    DWORD* pdwStubPhase);

#endif  /* __ISampleGrabber_INTERFACE_DEFINED__ */

/*****************************************************************************
 * IMediaDet interface
 */
#ifndef __IMediaDet_INTERFACE_DEFINED__
#define __IMediaDet_INTERFACE_DEFINED__

DEFINE_GUID(IID_IMediaDet, 0x65bd0710, 0x24d2, 0x4ff7, 0x93,0x24, 0xed,0x2e,0x5d,0x3a,0xba,0xfa);
#if defined(__cplusplus) && !defined(CINTERFACE)
MIDL_INTERFACE("65bd0710-24d2-4ff7-9324-ed2e5d3abafa")
IMediaDet : public IUnknown
{
    virtual HRESULT STDMETHODCALLTYPE get_Filter(
        IUnknown **pVal) = 0;

    virtual HRESULT STDMETHODCALLTYPE put_Filter(
        IUnknown *newVal) = 0;

    virtual HRESULT STDMETHODCALLTYPE get_OutputStreams(
        LONG *pVal) = 0;

    virtual HRESULT STDMETHODCALLTYPE get_CurrentStream(
        LONG *pVal) = 0;

    virtual HRESULT STDMETHODCALLTYPE put_CurrentStream(
        LONG newVal) = 0;

    virtual HRESULT STDMETHODCALLTYPE get_StreamType(
        GUID *pVal) = 0;

    virtual HRESULT STDMETHODCALLTYPE get_StreamTypeB(
        BSTR *pVal) = 0;

    virtual HRESULT STDMETHODCALLTYPE get_StreamLength(
        double *pVal) = 0;

    virtual HRESULT STDMETHODCALLTYPE get_Filename(
        BSTR *pVal) = 0;

    virtual HRESULT STDMETHODCALLTYPE put_Filename(
        BSTR newVal) = 0;

    virtual HRESULT STDMETHODCALLTYPE GetBitmapBits(
        double StreamTime,
        LONG *pBufferSize,
        char *pBuffer,
        LONG Width,
        LONG Height) = 0;

    virtual HRESULT STDMETHODCALLTYPE WriteBitmapBits(
        double StreamTime,
        LONG Width,
        LONG Height,
        BSTR Filename) = 0;

    virtual HRESULT STDMETHODCALLTYPE get_StreamMediaType(
        AM_MEDIA_TYPE *pVal) = 0;

    virtual HRESULT STDMETHODCALLTYPE GetSampleGrabber(
        ISampleGrabber **ppVal) = 0;

    virtual HRESULT STDMETHODCALLTYPE get_FrameRate(
        double *pVal) = 0;

    virtual HRESULT STDMETHODCALLTYPE EnterBitmapGrabMode(
        double SeekTime) = 0;

};
#ifdef __CRT_UUID_DECL
__CRT_UUID_DECL(IMediaDet, 0x65bd0710, 0x24d2, 0x4ff7, 0x93,0x24, 0xed,0x2e,0x5d,0x3a,0xba,0xfa)
#endif
#else
typedef struct IMediaDetVtbl {
    BEGIN_INTERFACE

    /*** IUnknown methods ***/
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        IMediaDet* This,
        REFIID riid,
        void **ppvObject);

    ULONG (STDMETHODCALLTYPE *AddRef)(
        IMediaDet* This);

    ULONG (STDMETHODCALLTYPE *Release)(
        IMediaDet* This);

    /*** IMediaDet methods ***/
    HRESULT (STDMETHODCALLTYPE *get_Filter)(
        IMediaDet* This,
        IUnknown **pVal);

    HRESULT (STDMETHODCALLTYPE *put_Filter)(
        IMediaDet* This,
        IUnknown *newVal);

    HRESULT (STDMETHODCALLTYPE *get_OutputStreams)(
        IMediaDet* This,
        LONG *pVal);

    HRESULT (STDMETHODCALLTYPE *get_CurrentStream)(
        IMediaDet* This,
        LONG *pVal);

    HRESULT (STDMETHODCALLTYPE *put_CurrentStream)(
        IMediaDet* This,
        LONG newVal);

    HRESULT (STDMETHODCALLTYPE *get_StreamType)(
        IMediaDet* This,
        GUID *pVal);

    HRESULT (STDMETHODCALLTYPE *get_StreamTypeB)(
        IMediaDet* This,
        BSTR *pVal);

    HRESULT (STDMETHODCALLTYPE *get_StreamLength)(
        IMediaDet* This,
        double *pVal);

    HRESULT (STDMETHODCALLTYPE *get_Filename)(
        IMediaDet* This,
        BSTR *pVal);

    HRESULT (STDMETHODCALLTYPE *put_Filename)(
        IMediaDet* This,
        BSTR newVal);

    HRESULT (STDMETHODCALLTYPE *GetBitmapBits)(
        IMediaDet* This,
        double StreamTime,
        LONG *pBufferSize,
        char *pBuffer,
        LONG Width,
        LONG Height);

    HRESULT (STDMETHODCALLTYPE *WriteBitmapBits)(
        IMediaDet* This,
        double StreamTime,
        LONG Width,
        LONG Height,
        BSTR Filename);

    HRESULT (STDMETHODCALLTYPE *get_StreamMediaType)(
        IMediaDet* This,
        AM_MEDIA_TYPE *pVal);

    HRESULT (STDMETHODCALLTYPE *GetSampleGrabber)(
        IMediaDet* This,
        ISampleGrabber **ppVal);

    HRESULT (STDMETHODCALLTYPE *get_FrameRate)(
        IMediaDet* This,
        double *pVal);

    HRESULT (STDMETHODCALLTYPE *EnterBitmapGrabMode)(
        IMediaDet* This,
        double SeekTime);

    END_INTERFACE
} IMediaDetVtbl;
interface IMediaDet {
    CONST_VTBL IMediaDetVtbl* lpVtbl;
};

#ifdef COBJMACROS
#ifndef WIDL_C_INLINE_WRAPPERS
/*** IUnknown methods ***/
#define IMediaDet_QueryInterface(This,riid,ppvObject) (This)->lpVtbl->QueryInterface(This,riid,ppvObject)
#define IMediaDet_AddRef(This) (This)->lpVtbl->AddRef(This)
#define IMediaDet_Release(This) (This)->lpVtbl->Release(This)
/*** IMediaDet methods ***/
#define IMediaDet_get_Filter(This,pVal) (This)->lpVtbl->get_Filter(This,pVal)
#define IMediaDet_put_Filter(This,newVal) (This)->lpVtbl->put_Filter(This,newVal)
#define IMediaDet_get_OutputStreams(This,pVal) (This)->lpVtbl->get_OutputStreams(This,pVal)
#define IMediaDet_get_CurrentStream(This,pVal) (This)->lpVtbl->get_CurrentStream(This,pVal)
#define IMediaDet_put_CurrentStream(This,newVal) (This)->lpVtbl->put_CurrentStream(This,newVal)
#define IMediaDet_get_StreamType(This,pVal) (This)->lpVtbl->get_StreamType(This,pVal)
#define IMediaDet_get_StreamTypeB(This,pVal) (This)->lpVtbl->get_StreamTypeB(This,pVal)
#define IMediaDet_get_StreamLength(This,pVal) (This)->lpVtbl->get_StreamLength(This,pVal)
#define IMediaDet_get_Filename(This,pVal) (This)->lpVtbl->get_Filename(This,pVal)
#define IMediaDet_put_Filename(This,newVal) (This)->lpVtbl->put_Filename(This,newVal)
#define IMediaDet_GetBitmapBits(This,StreamTime,pBufferSize,pBuffer,Width,Height) (This)->lpVtbl->GetBitmapBits(This,StreamTime,pBufferSize,pBuffer,Width,Height)
#define IMediaDet_WriteBitmapBits(This,StreamTime,Width,Height,Filename) (This)->lpVtbl->WriteBitmapBits(This,StreamTime,Width,Height,Filename)
#define IMediaDet_get_StreamMediaType(This,pVal) (This)->lpVtbl->get_StreamMediaType(This,pVal)
#define IMediaDet_GetSampleGrabber(This,ppVal) (This)->lpVtbl->GetSampleGrabber(This,ppVal)
#define IMediaDet_get_FrameRate(This,pVal) (This)->lpVtbl->get_FrameRate(This,pVal)
#define IMediaDet_EnterBitmapGrabMode(This,SeekTime) (This)->lpVtbl->EnterBitmapGrabMode(This,SeekTime)
#else
/*** IUnknown methods ***/
static FORCEINLINE HRESULT IMediaDet_QueryInterface(IMediaDet* This,REFIID riid,void **ppvObject) {
    return This->lpVtbl->QueryInterface(This,riid,ppvObject);
}
static FORCEINLINE ULONG IMediaDet_AddRef(IMediaDet* This) {
    return This->lpVtbl->AddRef(This);
}
static FORCEINLINE ULONG IMediaDet_Release(IMediaDet* This) {
    return This->lpVtbl->Release(This);
}
/*** IMediaDet methods ***/
static FORCEINLINE HRESULT IMediaDet_get_Filter(IMediaDet* This,IUnknown **pVal) {
    return This->lpVtbl->get_Filter(This,pVal);
}
static FORCEINLINE HRESULT IMediaDet_put_Filter(IMediaDet* This,IUnknown *newVal) {
    return This->lpVtbl->put_Filter(This,newVal);
}
static FORCEINLINE HRESULT IMediaDet_get_OutputStreams(IMediaDet* This,LONG *pVal) {
    return This->lpVtbl->get_OutputStreams(This,pVal);
}
static FORCEINLINE HRESULT IMediaDet_get_CurrentStream(IMediaDet* This,LONG *pVal) {
    return This->lpVtbl->get_CurrentStream(This,pVal);
}
static FORCEINLINE HRESULT IMediaDet_put_CurrentStream(IMediaDet* This,LONG newVal) {
    return This->lpVtbl->put_CurrentStream(This,newVal);
}
static FORCEINLINE HRESULT IMediaDet_get_StreamType(IMediaDet* This,GUID *pVal) {
    return This->lpVtbl->get_StreamType(This,pVal);
}
static FORCEINLINE HRESULT IMediaDet_get_StreamTypeB(IMediaDet* This,BSTR *pVal) {
    return This->lpVtbl->get_StreamTypeB(This,pVal);
}
static FORCEINLINE HRESULT IMediaDet_get_StreamLength(IMediaDet* This,double *pVal) {
    return This->lpVtbl->get_StreamLength(This,pVal);
}
static FORCEINLINE HRESULT IMediaDet_get_Filename(IMediaDet* This,BSTR *pVal) {
    return This->lpVtbl->get_Filename(This,pVal);
}
static FORCEINLINE HRESULT IMediaDet_put_Filename(IMediaDet* This,BSTR newVal) {
    return This->lpVtbl->put_Filename(This,newVal);
}
static FORCEINLINE HRESULT IMediaDet_GetBitmapBits(IMediaDet* This,double StreamTime,LONG *pBufferSize,char *pBuffer,LONG Width,LONG Height) {
    return This->lpVtbl->GetBitmapBits(This,StreamTime,pBufferSize,pBuffer,Width,Height);
}
static FORCEINLINE HRESULT IMediaDet_WriteBitmapBits(IMediaDet* This,double StreamTime,LONG Width,LONG Height,BSTR Filename) {
    return This->lpVtbl->WriteBitmapBits(This,StreamTime,Width,Height,Filename);
}
static FORCEINLINE HRESULT IMediaDet_get_StreamMediaType(IMediaDet* This,AM_MEDIA_TYPE *pVal) {
    return This->lpVtbl->get_StreamMediaType(This,pVal);
}
static FORCEINLINE HRESULT IMediaDet_GetSampleGrabber(IMediaDet* This,ISampleGrabber **ppVal) {
    return This->lpVtbl->GetSampleGrabber(This,ppVal);
}
static FORCEINLINE HRESULT IMediaDet_get_FrameRate(IMediaDet* This,double *pVal) {
    return This->lpVtbl->get_FrameRate(This,pVal);
}
static FORCEINLINE HRESULT IMediaDet_EnterBitmapGrabMode(IMediaDet* This,double SeekTime) {
    return This->lpVtbl->EnterBitmapGrabMode(This,SeekTime);
}
#endif
#endif

#endif

HRESULT STDMETHODCALLTYPE IMediaDet_get_Filter_Proxy(
    IMediaDet* This,
    IUnknown **pVal);
void __RPC_STUB IMediaDet_get_Filter_Stub(
    IRpcStubBuffer* This,
    IRpcChannelBuffer* pRpcChannelBuffer,
    PRPC_MESSAGE pRpcMessage,
    DWORD* pdwStubPhase);
HRESULT STDMETHODCALLTYPE IMediaDet_put_Filter_Proxy(
    IMediaDet* This,
    IUnknown *newVal);
void __RPC_STUB IMediaDet_put_Filter_Stub(
    IRpcStubBuffer* This,
    IRpcChannelBuffer* pRpcChannelBuffer,
    PRPC_MESSAGE pRpcMessage,
    DWORD* pdwStubPhase);
HRESULT STDMETHODCALLTYPE IMediaDet_get_OutputStreams_Proxy(
    IMediaDet* This,
    LONG *pVal);
void __RPC_STUB IMediaDet_get_OutputStreams_Stub(
    IRpcStubBuffer* This,
    IRpcChannelBuffer* pRpcChannelBuffer,
    PRPC_MESSAGE pRpcMessage,
    DWORD* pdwStubPhase);
HRESULT STDMETHODCALLTYPE IMediaDet_get_CurrentStream_Proxy(
    IMediaDet* This,
    LONG *pVal);
void __RPC_STUB IMediaDet_get_CurrentStream_Stub(
    IRpcStubBuffer* This,
    IRpcChannelBuffer* pRpcChannelBuffer,
    PRPC_MESSAGE pRpcMessage,
    DWORD* pdwStubPhase);
HRESULT STDMETHODCALLTYPE IMediaDet_put_CurrentStream_Proxy(
    IMediaDet* This,
    LONG newVal);
void __RPC_STUB IMediaDet_put_CurrentStream_Stub(
    IRpcStubBuffer* This,
    IRpcChannelBuffer* pRpcChannelBuffer,
    PRPC_MESSAGE pRpcMessage,
    DWORD* pdwStubPhase);
HRESULT STDMETHODCALLTYPE IMediaDet_get_StreamType_Proxy(
    IMediaDet* This,
    GUID *pVal);
void __RPC_STUB IMediaDet_get_StreamType_Stub(
    IRpcStubBuffer* This,
    IRpcChannelBuffer* pRpcChannelBuffer,
    PRPC_MESSAGE pRpcMessage,
    DWORD* pdwStubPhase);
HRESULT STDMETHODCALLTYPE IMediaDet_get_StreamTypeB_Proxy(
    IMediaDet* This,
    BSTR *pVal);
void __RPC_STUB IMediaDet_get_StreamTypeB_Stub(
    IRpcStubBuffer* This,
    IRpcChannelBuffer* pRpcChannelBuffer,
    PRPC_MESSAGE pRpcMessage,
    DWORD* pdwStubPhase);
HRESULT STDMETHODCALLTYPE IMediaDet_get_StreamLength_Proxy(
    IMediaDet* This,
    double *pVal);
void __RPC_STUB IMediaDet_get_StreamLength_Stub(
    IRpcStubBuffer* This,
    IRpcChannelBuffer* pRpcChannelBuffer,
    PRPC_MESSAGE pRpcMessage,
    DWORD* pdwStubPhase);
HRESULT STDMETHODCALLTYPE IMediaDet_get_Filename_Proxy(
    IMediaDet* This,
    BSTR *pVal);
void __RPC_STUB IMediaDet_get_Filename_Stub(
    IRpcStubBuffer* This,
    IRpcChannelBuffer* pRpcChannelBuffer,
    PRPC_MESSAGE pRpcMessage,
    DWORD* pdwStubPhase);
HRESULT STDMETHODCALLTYPE IMediaDet_put_Filename_Proxy(
    IMediaDet* This,
    BSTR newVal);
void __RPC_STUB IMediaDet_put_Filename_Stub(
    IRpcStubBuffer* This,
    IRpcChannelBuffer* pRpcChannelBuffer,
    PRPC_MESSAGE pRpcMessage,
    DWORD* pdwStubPhase);
HRESULT STDMETHODCALLTYPE IMediaDet_GetBitmapBits_Proxy(
    IMediaDet* This,
    double StreamTime,
    LONG *pBufferSize,
    char *pBuffer,
    LONG Width,
    LONG Height);
void __RPC_STUB IMediaDet_GetBitmapBits_Stub(
    IRpcStubBuffer* This,
    IRpcChannelBuffer* pRpcChannelBuffer,
    PRPC_MESSAGE pRpcMessage,
    DWORD* pdwStubPhase);
HRESULT STDMETHODCALLTYPE IMediaDet_WriteBitmapBits_Proxy(
    IMediaDet* This,
    double StreamTime,
    LONG Width,
    LONG Height,
    BSTR Filename);
void __RPC_STUB IMediaDet_WriteBitmapBits_Stub(
    IRpcStubBuffer* This,
    IRpcChannelBuffer* pRpcChannelBuffer,
    PRPC_MESSAGE pRpcMessage,
    DWORD* pdwStubPhase);
HRESULT STDMETHODCALLTYPE IMediaDet_get_StreamMediaType_Proxy(
    IMediaDet* This,
    AM_MEDIA_TYPE *pVal);
void __RPC_STUB IMediaDet_get_StreamMediaType_Stub(
    IRpcStubBuffer* This,
    IRpcChannelBuffer* pRpcChannelBuffer,
    PRPC_MESSAGE pRpcMessage,
    DWORD* pdwStubPhase);
HRESULT STDMETHODCALLTYPE IMediaDet_GetSampleGrabber_Proxy(
    IMediaDet* This,
    ISampleGrabber **ppVal);
void __RPC_STUB IMediaDet_GetSampleGrabber_Stub(
    IRpcStubBuffer* This,
    IRpcChannelBuffer* pRpcChannelBuffer,
    PRPC_MESSAGE pRpcMessage,
    DWORD* pdwStubPhase);
HRESULT STDMETHODCALLTYPE IMediaDet_get_FrameRate_Proxy(
    IMediaDet* This,
    double *pVal);
void __RPC_STUB IMediaDet_get_FrameRate_Stub(
    IRpcStubBuffer* This,
    IRpcChannelBuffer* pRpcChannelBuffer,
    PRPC_MESSAGE pRpcMessage,
    DWORD* pdwStubPhase);
HRESULT STDMETHODCALLTYPE IMediaDet_EnterBitmapGrabMode_Proxy(
    IMediaDet* This,
    double SeekTime);
void __RPC_STUB IMediaDet_EnterBitmapGrabMode_Stub(
    IRpcStubBuffer* This,
    IRpcChannelBuffer* pRpcChannelBuffer,
    PRPC_MESSAGE pRpcMessage,
    DWORD* pdwStubPhase);

#endif  /* __IMediaDet_INTERFACE_DEFINED__ */

/*****************************************************************************
 * MediaDet coclass
 */

DEFINE_GUID(CLSID_MediaDet, 0x65bd0711, 0x24d2, 0x4ff7, 0x93,0x24, 0xed,0x2e,0x5d,0x3a,0xba,0xfa);

#ifdef __cplusplus
class DECLSPEC_UUID("65bd0711-24d2-4ff7-9324-ed2e5d3abafa") MediaDet;
#ifdef __CRT_UUID_DECL
__CRT_UUID_DECL(MediaDet, 0x65bd0711, 0x24d2, 0x4ff7, 0x93,0x24, 0xed,0x2e,0x5d,0x3a,0xba,0xfa)
#endif
#endif

enum {
    E_NOTINTREE = 0x80040400,
    E_RENDER_ENGINE_IS_BROKEN = 0x80040401,
    E_MUST_INIT_RENDERER = 0x80040402,
    E_NOTDETERMINED = 0x80040403,
    E_NO_TIMELINE = 0x80040404,
    S_WARN_OUTPUTRESET = 40404
};

/* Begin additional prototypes for all interfaces */

ULONG           __RPC_USER BSTR_UserSize     (ULONG *, ULONG, BSTR *);
unsigned char * __RPC_USER BSTR_UserMarshal  (ULONG *, unsigned char *, BSTR *);
unsigned char * __RPC_USER BSTR_UserUnmarshal(ULONG *, unsigned char *, BSTR *);
void            __RPC_USER BSTR_UserFree     (ULONG *, BSTR *);

/* End additional prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __qedit_h__ */
