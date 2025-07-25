/*********************************************************************
*                    SEGGER Microcontroller GmbH                     *
*                        The Embedded Experts                        *
**********************************************************************
*                                                                    *
*            (c) 1995 - 2024 SEGGER Microcontroller GmbH             *
*                                                                    *
*       www.segger.com     Support: support@segger.com               *
*                                                                    *
**********************************************************************
*                                                                    *
*       SEGGER SystemView * Real-time application analysis           *
*                                                                    *
**********************************************************************
*                                                                    *
* All rights reserved.                                               *
*                                                                    *
* SEGGER strongly recommends to not make any changes                 *
* to or modify the source code of this software in order to stay     *
* compatible with the SystemView and RTT protocol, and J-Link.       *
*                                                                    *
* Redistribution and use in source and binary forms, with or         *
* without modification, are permitted provided that the following    *
* condition is met:                                                  *
*                                                                    *
* o Redistributions of source code must retain the above copyright   *
*   notice, this condition and the following disclaimer.             *
*                                                                    *
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND             *
* CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,        *
* INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF           *
* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE           *
* DISCLAIMED. IN NO EVENT SHALL SEGGER Microcontroller BE LIABLE FOR *
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR           *
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT  *
* OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;    *
* OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF      *
* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT          *
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE  *
* USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH   *
* DAMAGE.                                                            *
*                                                                    *
**********************************************************************
*                                                                    *
*       SystemView version: 3.60e                                    *
*                                                                    *
**********************************************************************
-------------------------- END-OF-HEADER -----------------------------
File    : SEGGER_SYSVIEW.h
Purpose : System visualization API.
Revision: $Rev: 28768 $
*/

#ifndef SEGGER_SYSVIEW_H
#define SEGGER_SYSVIEW_H

/*********************************************************************
*
*       #include Section
*
**********************************************************************
*/

#include "SEGGER.h"
#include "SEGGER_SYSVIEW_ConfDefaults.h"

#ifdef __cplusplus
extern "C" {
#endif


/*********************************************************************
*
*       Defines, fixed
*
**********************************************************************
*/

#define SEGGER_SYSVIEW_MAJOR          3
#define SEGGER_SYSVIEW_MINOR          32
#define SEGGER_SYSVIEW_REV            0
#define SEGGER_SYSVIEW_VERSION        ((SEGGER_SYSVIEW_MAJOR * 10000) + (SEGGER_SYSVIEW_MINOR * 100) + SEGGER_SYSVIEW_REV)

#define SEGGER_SYSVIEW_INFO_SIZE      9   // Minimum size, which has to be reserved for a packet. 1-2 byte of message type, 0-2  byte of payload length, 1-5 bytes of timestamp.
#define SEGGER_SYSVIEW_QUANTA_U32     5   // Maximum number of bytes to encode a U32, should be reserved for each 32-bit value in a packet.

#define SEGGER_SYSVIEW_LOG            (0u)
#define SEGGER_SYSVIEW_WARNING        (1u)
#define SEGGER_SYSVIEW_ERROR          (2u)
#define SEGGER_SYSVIEW_FLAG_APPEND    (1u << 6)

#define SEGGER_SYSVIEW_PREPARE_PACKET(p)  (p) + 4
//
// SystemView events. First 32 IDs from 0 .. 31 are reserved for these
//
#define   SYSVIEW_EVTID_NOP                0  // Dummy packet.
#define   SYSVIEW_EVTID_OVERFLOW           1
#define   SYSVIEW_EVTID_ISR_ENTER          2
#define   SYSVIEW_EVTID_ISR_EXIT           3
#define   SYSVIEW_EVTID_TASK_START_EXEC    4
#define   SYSVIEW_EVTID_TASK_STOP_EXEC     5
#define   SYSVIEW_EVTID_TASK_START_READY   6
#define   SYSVIEW_EVTID_TASK_STOP_READY    7
#define   SYSVIEW_EVTID_TASK_CREATE        8
#define   SYSVIEW_EVTID_TASK_INFO          9
#define   SYSVIEW_EVTID_TRACE_START       10
#define   SYSVIEW_EVTID_TRACE_STOP        11
#define   SYSVIEW_EVTID_SYSTIME_CYCLES    12
#define   SYSVIEW_EVTID_SYSTIME_US        13
#define   SYSVIEW_EVTID_SYSDESC           14
#define   SYSVIEW_EVTID_MARK_START        15
#define   SYSVIEW_EVTID_MARK_STOP         16
#define   SYSVIEW_EVTID_IDLE              17
#define   SYSVIEW_EVTID_ISR_TO_SCHEDULER  18
#define   SYSVIEW_EVTID_TIMER_ENTER       19
#define   SYSVIEW_EVTID_TIMER_EXIT        20
#define   SYSVIEW_EVTID_STACK_INFO        21
#define   SYSVIEW_EVTID_MODULEDESC        22
#define   SYSVIEW_EVTID_DATA_SAMPLE       23
#define   SYSVIEW_EVTID_INIT              24
#define   SYSVIEW_EVTID_NAME_RESOURCE     25
#define   SYSVIEW_EVTID_PRINT_FORMATTED   26
#define   SYSVIEW_EVTID_NUMMODULES        27
#define   SYSVIEW_EVTID_END_CALL          28
#define   SYSVIEW_EVTID_TASK_TERMINATE    29

#define   SYSVIEW_EVTID_EX                31
//
// SystemView extended events. Sent with ID 31.
//
#define   SYSVIEW_EVTID_EX_MARK           0
#define   SYSVIEW_EVTID_EX_NAME_MARKER    1
#define   SYSVIEW_EVTID_EX_HEAP_DEFINE    2
#define   SYSVIEW_EVTID_EX_HEAP_ALLOC     3
#define   SYSVIEW_EVTID_EX_HEAP_ALLOC_EX  4
#define   SYSVIEW_EVTID_EX_HEAP_FREE      5
#define   SYSVIEW_EVTID_EX_REGISTER_DATA  6
//
// Event masks to disable/enable events
//
#define   SYSVIEW_EVTMASK_NOP               (1 << SYSVIEW_EVTID_NOP)
#define   SYSVIEW_EVTMASK_OVERFLOW          (1 << SYSVIEW_EVTID_OVERFLOW)
#define   SYSVIEW_EVTMASK_ISR_ENTER         (1 << SYSVIEW_EVTID_ISR_ENTER)
#define   SYSVIEW_EVTMASK_ISR_EXIT          (1 << SYSVIEW_EVTID_ISR_EXIT)
#define   SYSVIEW_EVTMASK_TASK_START_EXEC   (1 << SYSVIEW_EVTID_TASK_START_EXEC)
#define   SYSVIEW_EVTMASK_TASK_STOP_EXEC    (1 << SYSVIEW_EVTID_TASK_STOP_EXEC)
#define   SYSVIEW_EVTMASK_TASK_START_READY  (1 << SYSVIEW_EVTID_TASK_START_READY)
#define   SYSVIEW_EVTMASK_TASK_STOP_READY   (1 << SYSVIEW_EVTID_TASK_STOP_READY)
#define   SYSVIEW_EVTMASK_TASK_CREATE       (1 << SYSVIEW_EVTID_TASK_CREATE)
#define   SYSVIEW_EVTMASK_TASK_INFO         (1 << SYSVIEW_EVTID_TASK_INFO)
#define   SYSVIEW_EVTMASK_TRACE_START       (1 << SYSVIEW_EVTID_TRACE_START)
#define   SYSVIEW_EVTMASK_TRACE_STOP        (1 << SYSVIEW_EVTID_TRACE_STOP)
#define   SYSVIEW_EVTMASK_SYSTIME_CYCLES    (1 << SYSVIEW_EVTID_SYSTIME_CYCLES)
#define   SYSVIEW_EVTMASK_SYSTIME_US        (1 << SYSVIEW_EVTID_SYSTIME_US)
#define   SYSVIEW_EVTMASK_SYSDESC           (1 << SYSVIEW_EVTID_SYSDESC)
#define   SYSVIEW_EVTMASK_USER_START        (1 << SYSVIEW_EVTID_USER_START)
#define   SYSVIEW_EVTMASK_USER_STOP         (1 << SYSVIEW_EVTID_USER_STOP)
#define   SYSVIEW_EVTMASK_IDLE              (1 << SYSVIEW_EVTID_IDLE)
#define   SYSVIEW_EVTMASK_ISR_TO_SCHEDULER  (1 << SYSVIEW_EVTID_ISR_TO_SCHEDULER)
#define   SYSVIEW_EVTMASK_TIMER_ENTER       (1 << SYSVIEW_EVTID_TIMER_ENTER)
#define   SYSVIEW_EVTMASK_TIMER_EXIT        (1 << SYSVIEW_EVTID_TIMER_EXIT)
#define   SYSVIEW_EVTMASK_STACK_INFO        (1 << SYSVIEW_EVTID_STACK_INFO)
#define   SYSVIEW_EVTMASK_MODULEDESC        (1 << SYSVIEW_EVTID_MODULEDESC)
#define   SYSVIEW_EVTMASK_DATA_SAMPLE       (1 << SYSVIEW_EVTID_DATA_SAMPLE)
#define   SYSVIEW_EVTMASK_INIT              (1 << SYSVIEW_EVTID_INIT)
#define   SYSVIEW_EVTMASK_NAME_RESOURCE     (1 << SYSVIEW_EVTID_NAME_RESOURCE)
#define   SYSVIEW_EVTMASK_PRINT_FORMATTED   (1 << SYSVIEW_EVTID_PRINT_FORMATTED)
#define   SYSVIEW_EVTMASK_NUMMODULES        (1 << SYSVIEW_EVTID_NUMMODULES)
#define   SYSVIEW_EVTMASK_END_CALL          (1 << SYSVIEW_EVTID_END_CALL)
#define   SYSVIEW_EVTMASK_TASK_TERMINATE    (1 << SYSVIEW_EVTID_TASK_TERMINATE)

#define   SYSVIEW_EVTMASK_EX                (1 << SYSVIEW_EVTID_EX)

#define   SYSVIEW_EVTMASK_ALL_INTERRUPTS    ( SYSVIEW_EVTMASK_ISR_ENTER           \
                                            | SYSVIEW_EVTMASK_ISR_EXIT            \
                                            | SYSVIEW_EVTMASK_ISR_TO_SCHEDULER)
#define   SYSVIEW_EVTMASK_ALL_TASKS         ( SYSVIEW_EVTMASK_TASK_START_EXEC     \
                                            | SYSVIEW_EVTMASK_TASK_STOP_EXEC      \
                                            | SYSVIEW_EVTMASK_TASK_START_READY    \
                                            | SYSVIEW_EVTMASK_TASK_STOP_READY     \
                                            | SYSVIEW_EVTMASK_TASK_CREATE         \
                                            | SYSVIEW_EVTMASK_TASK_INFO           \
                                            | SYSVIEW_EVTMASK_STACK_INFO          \
                                            | SYSVIEW_EVTMASK_TASK_TERMINATE)

/*********************************************************************
*
*       Structures
*
**********************************************************************
*/

typedef struct {
  U32          TaskID;
  const char*  sName;
  U32          Prio;
  U32          StackBase;
  U32          StackSize;
  U32          StackUsage;
} SEGGER_SYSVIEW_TASKINFO;

typedef struct {
  U32          TaskID;
  U32          StackBase;
  U32          StackSize;
  U32          StackUsage;
} SEGGER_SYSVIEW_STACKINFO;

typedef struct {
  U32          ID;
  union {
    U32*   pU32;
    I32*   pI32;
    float* pFloat;
  } pValue;  
} SEGGER_SYSVIEW_DATA_SAMPLE;

typedef enum {
  SEGGER_SYSVIEW_TYPE_U32   = 0,
  SEGGER_SYSVIEW_TYPE_I32   = 1,
  SEGGER_SYSVIEW_TYPE_FLOAT = 2
} SEGGER_SYSVIEW_DATA_TYPE;

typedef struct {
  U32                           ID;
  SEGGER_SYSVIEW_DATA_TYPE      DataType;
  I32                           Offset;
  I32                           RangeMin;
  I32                           RangeMax;
  float                         ScalingFactor;                   
  const char*                   sName;
  const char*                   sUnit;
}  SEGGER_SYSVIEW_DATA_REGISTER;

typedef struct SEGGER_SYSVIEW_MODULE_STRUCT SEGGER_SYSVIEW_MODULE;

struct SEGGER_SYSVIEW_MODULE_STRUCT {
  const char*                   sModule;
        U32                     NumEvents;
        U32                     EventOffset;
        void                    (*pfSendModuleDesc)(void);
        SEGGER_SYSVIEW_MODULE*  pNext;
};

typedef void (SEGGER_SYSVIEW_SEND_SYS_DESC_FUNC)(void);


/*********************************************************************
*
*       Global data
*
**********************************************************************
*/

#ifdef   EXTERN
  #undef EXTERN
#endif

#ifndef SEGGER_SYSVIEW_C       // Defined in SEGGER_SYSVIEW.c which includes this header beside other C-files
  #define EXTERN extern
#else
  #define EXTERN
#endif

EXTERN unsigned int SEGGER_SYSVIEW_TickCnt;
EXTERN unsigned int SEGGER_SYSVIEW_InterruptId;

#undef EXTERN

/*********************************************************************
*
*       API functions
*
**********************************************************************
*/

typedef struct {
  U64  (*pfGetTime)               (void);
  void (*pfSendTaskList)          (void);
} SEGGER_SYSVIEW_OS_API;

/*********************************************************************
*
*       Control and initialization functions
*/
void SEGGER_SYSVIEW_Init                          (U32 SysFreq, U32 CPUFreq, const SEGGER_SYSVIEW_OS_API *pOSAPI, SEGGER_SYSVIEW_SEND_SYS_DESC_FUNC pfSendSysDesc);
void SEGGER_SYSVIEW_SetRAMBase                    (U32 RAMBaseAddress);
void SEGGER_SYSVIEW_Start                         (void);
void SEGGER_SYSVIEW_Stop                          (void);
void SEGGER_SYSVIEW_GetSysDesc                    (void);
void SEGGER_SYSVIEW_SendTaskList                  (void);
void SEGGER_SYSVIEW_SendTaskInfo                  (const SEGGER_SYSVIEW_TASKINFO* pInfo);
void SEGGER_SYSVIEW_SendStackInfo                 (const SEGGER_SYSVIEW_STACKINFO* pInfo);
void SEGGER_SYSVIEW_SendSysDesc                   (const char* sSysDesc);
int  SEGGER_SYSVIEW_IsStarted                     (void);
int  SEGGER_SYSVIEW_GetChannelID                  (void);

void  SEGGER_SYSVIEW_SampleData                   (const SEGGER_SYSVIEW_DATA_SAMPLE *pInfo);

/*********************************************************************
*
*       Event recording functions
*/
void SEGGER_SYSVIEW_RecordVoid                    (unsigned int EventId);
void SEGGER_SYSVIEW_RecordU32                     (unsigned int EventId, U32 Para0);
void SEGGER_SYSVIEW_RecordU32x2                   (unsigned int EventId, U32 Para0, U32 Para1);
void SEGGER_SYSVIEW_RecordU32x3                   (unsigned int EventId, U32 Para0, U32 Para1, U32 Para2);
void SEGGER_SYSVIEW_RecordU32x4                   (unsigned int EventId, U32 Para0, U32 Para1, U32 Para2, U32 Para3);
void SEGGER_SYSVIEW_RecordU32x5                   (unsigned int EventId, U32 Para0, U32 Para1, U32 Para2, U32 Para3, U32 Para4);
void SEGGER_SYSVIEW_RecordU32x6                   (unsigned int EventId, U32 Para0, U32 Para1, U32 Para2, U32 Para3, U32 Para4, U32 Para5);
void SEGGER_SYSVIEW_RecordU32x7                   (unsigned int EventId, U32 Para0, U32 Para1, U32 Para2, U32 Para3, U32 Para4, U32 Para5, U32 Para6);
void SEGGER_SYSVIEW_RecordU32x8                   (unsigned int EventId, U32 Para0, U32 Para1, U32 Para2, U32 Para3, U32 Para4, U32 Para5, U32 Para6, U32 Para7);
void SEGGER_SYSVIEW_RecordU32x9                   (unsigned int EventId, U32 Para0, U32 Para1, U32 Para2, U32 Para3, U32 Para4, U32 Para5, U32 Para6, U32 Para7, U32 Para8);
void SEGGER_SYSVIEW_RecordU32x10                  (unsigned int EventId, U32 Para0, U32 Para1, U32 Para2, U32 Para3, U32 Para4, U32 Para5, U32 Para6, U32 Para7, U32 Para8, U32 Para9);
void SEGGER_SYSVIEW_RecordString                  (unsigned int EventId, const char* pString);
void SEGGER_SYSVIEW_RecordSystime                 (void);
void SEGGER_SYSVIEW_RecordEnterISR                (void);
void SEGGER_SYSVIEW_RecordExitISR                 (void);
void SEGGER_SYSVIEW_RecordExitISRToScheduler      (void);
void SEGGER_SYSVIEW_RecordEnterTimer              (U32 TimerId);
void SEGGER_SYSVIEW_RecordExitTimer               (void);
void SEGGER_SYSVIEW_RecordEndCall                 (unsigned int EventID);
void SEGGER_SYSVIEW_RecordEndCallU32              (unsigned int EventID, U32 Para0);

void SEGGER_SYSVIEW_OnIdle                        (void);
void SEGGER_SYSVIEW_OnTaskCreate                  (U32 TaskId);
void SEGGER_SYSVIEW_OnTaskTerminate               (U32 TaskId);
void SEGGER_SYSVIEW_OnTaskStartExec               (U32 TaskId);
void SEGGER_SYSVIEW_OnTaskStopExec                (void);
void SEGGER_SYSVIEW_OnTaskStartReady              (U32 TaskId);
void SEGGER_SYSVIEW_OnTaskStopReady               (U32 TaskId, unsigned int Cause);
void SEGGER_SYSVIEW_MarkStart                     (unsigned int MarkerId);
void SEGGER_SYSVIEW_MarkStop                      (unsigned int MarkerId);
void SEGGER_SYSVIEW_Mark                          (unsigned int MarkerId);
void SEGGER_SYSVIEW_NameMarker                    (unsigned int MarkerId, const char* sName);

void SEGGER_SYSVIEW_HeapDefine                    (void* pHeap, void* pBase, unsigned int HeapSize, unsigned int MetadataSize);
void SEGGER_SYSVIEW_HeapAlloc                     (void* pHeap, void* pUserData, unsigned int UserDataLen);
void SEGGER_SYSVIEW_HeapAllocEx                   (void* pHeap, void* pUserData, unsigned int UserDataLen, unsigned int Tag);
void SEGGER_SYSVIEW_HeapFree                      (void* pHeap, void* pUserData);

void SEGGER_SYSVIEW_NameResource                  (U32 ResourceId, const char* sName);
void SEGGER_SYSVIEW_RegisterData                  ( SEGGER_SYSVIEW_DATA_REGISTER* pInfo);

int  SEGGER_SYSVIEW_SendPacket                    (U8* pPacket, U8* pPayloadEnd, unsigned int EventId);

/*********************************************************************
*
*       Event parameter encoding functions
*/
U8*  SEGGER_SYSVIEW_EncodeU32                     (U8* pPayload, U32 Value);
U8*  SEGGER_SYSVIEW_EncodeData                    (U8* pPayload, const char* pSrc, unsigned int Len);
U8*  SEGGER_SYSVIEW_EncodeString                  (U8* pPayload, const char* s, unsigned int MaxLen);
U8*  SEGGER_SYSVIEW_EncodeId                      (U8* pPayload, U32 Id);
U32  SEGGER_SYSVIEW_ShrinkId                      (U32 Id);


/*********************************************************************
*
*       Middleware module registration
*/
void SEGGER_SYSVIEW_RegisterModule                (SEGGER_SYSVIEW_MODULE* pModule);
void SEGGER_SYSVIEW_RecordModuleDescription       (const SEGGER_SYSVIEW_MODULE* pModule, const char* sDescription);
void SEGGER_SYSVIEW_SendModule                    (U8 ModuleId);
void SEGGER_SYSVIEW_SendModuleDescription         (void);
void SEGGER_SYSVIEW_SendNumModules                (void);

/*********************************************************************
*
*       printf-Style functions
*/
#ifndef SEGGER_SYSVIEW_EXCLUDE_PRINTF // Define in project to avoid warnings about variable parameter list
void SEGGER_SYSVIEW_PrintfHostEx                  (const char* s, U32 Options, ...);
void SEGGER_SYSVIEW_VPrintfHostEx                 (const char* s, U32 Options, va_list* pParamList);
void SEGGER_SYSVIEW_PrintfTargetEx                (const char* s, U32 Options, ...);
void SEGGER_SYSVIEW_VPrintfTargetEx               (const char* s, U32 Options, va_list* pParamList);
void SEGGER_SYSVIEW_PrintfHost                    (const char* s, ...);
void SEGGER_SYSVIEW_VPrintfHost                   (const char* s, va_list* pParamList);
void SEGGER_SYSVIEW_PrintfTarget                  (const char* s, ...);
void SEGGER_SYSVIEW_VPrintfTarget                 (const char* s, va_list* pParamList);
void SEGGER_SYSVIEW_WarnfHost                     (const char* s, ...);
void SEGGER_SYSVIEW_VWarnfHost                    (const char* s, va_list* pParamList);
void SEGGER_SYSVIEW_WarnfTarget                   (const char* s, ...);
void SEGGER_SYSVIEW_VWarnfTarget                  (const char* s, va_list* pParamList);
void SEGGER_SYSVIEW_ErrorfHost                    (const char* s, ...);
void SEGGER_SYSVIEW_VErrorfHost                   (const char* s, va_list* pParamList);
void SEGGER_SYSVIEW_ErrorfTarget                  (const char* s, ...);
void SEGGER_SYSVIEW_VErrorfTarget                 (const char* s, va_list* pParamList);
#endif

void SEGGER_SYSVIEW_Print                         (const char* s);
void SEGGER_SYSVIEW_Warn                          (const char* s);
void SEGGER_SYSVIEW_Error                         (const char* s);

/*********************************************************************
*
*       Run-time configuration functions
*/
void SEGGER_SYSVIEW_EnableEvents                  (U32 EnableMask);
void SEGGER_SYSVIEW_DisableEvents                 (U32 DisableMask);

/*********************************************************************
*
*       Application-provided functions
*/
void SEGGER_SYSVIEW_Conf                          (void);
U32  SEGGER_SYSVIEW_X_GetTimestamp                (void);
U32  SEGGER_SYSVIEW_X_GetInterruptId              (void);

void SEGGER_SYSVIEW_X_StartComm                   (void);
void SEGGER_SYSVIEW_X_OnEventRecorded             (unsigned NumBytes);

#ifdef __cplusplus
}
#endif

/*********************************************************************
*
*       Compatibility API defines
*/
#define SEGGER_SYSVIEW_OnUserStart      SEGGER_SYSVIEW_MarkStart
#define SEGGER_SYSVIEW_OnUserStop       SEGGER_SYSVIEW_MarkStop

#endif

/*************************** End of file ****************************/
