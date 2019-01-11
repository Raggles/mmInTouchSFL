/* Generic typedefs */
typedef long    ACCID;
typedef long    HPT;
typedef int     PTYPE;

/* Values for PTYPE */
#define PT_DISCRETE     1
#define PT_INTEGER      2
#define PT_REAL         3
#define PT_STRING       4

#ifdef  __cplusplus
extern "C" {
#endif
/* initialization and shutdown */
ACCID   WINAPI PtAccInit( HWND hWnd, int nExtraBytes );
int     WINAPI PtAccShutdown( ACCID accID );

/* status */
int     WINAPI PtAccOK( ACCID accID );

/* Handle Manipulation */
HPT     WINAPI PtAccHandleCreate( ACCID accID, const char far *lpszName );
int     WINAPI PtAccHandleActivate( ACCID accID, HPT hPt );
int     WINAPI PtAccHandleDeactivate( ACCID accID, HPT hPt );
int     WINAPI PtAccHandleDelete( ACCID accID, HPT hPt );

/* More general Manipulation */
HPT     WINAPI PtAccActivate( ACCID accID, const char far *lpszName );
PTYPE   WINAPI PtAccType( ACCID accID, HPT hPt );
int     WINAPI PtAccDeactivate( ACCID accID, HPT hPt );
int     WINAPI PtAccDelete( ACCID accID, HPT hPt );

/* Only for use in Windows  */
HPT     WINAPI PtAccActivateAndNotify( ACCID accID,
                        const char far *lpszName );
int     WINAPI PtAccHandleActivateAndNotify( ACCID accID, HPT hPt );
HPT     WINAPI PtAccActivateAndSendNotify( ACCID accID,
                        const char far *lpszName );
int     WINAPI PtAccHandleActivateAndSndNotify( ACCID accID, HPT hPt );
ACCID   WINAPI PtAccACCIDFromHPT( HPT hPt );
void    WINAPI PtAccShutdownAllAssociated( HWND hWnd );

/* Extra bytes per entry */
int     WINAPI PtAccSetExtraInt( ACCID accID, HPT hPt, int nOffset,
                                    int nValue );
int     WINAPI PtAccGetExtraInt( ACCID accID, HPT hPt, int nOffset );
long    WINAPI PtAccSetExtraLong( ACCID accID, HPT hPt, int nOffset,
                                    long lValue );
long    WINAPI PtAccGetExtraLong( ACCID accID, HPT hPt, int nOffset );

/* Read routines */
int     WINAPI PtAccReadD( ACCID accID, HPT hPt );
long    WINAPI PtAccReadI( ACCID accID, HPT hPt );
#if defined(__BORLANDC__)
float   WINAPI PtAccGetR(  ACCID accID, HPT hPt );
double  WINAPI PtAccGetA(  ACCID accID, HPT hPt );
#define PtAccReadR PtAccGetR
#define PtAccReadA PtAccGetA
#else
float   WINAPI PtAccReadR( ACCID accID, HPT hPt );
double  WINAPI PtAccReadA( ACCID accID, HPT hPt );
#endif
void    WINAPI PtAccReadM( ACCID accID, HPT hPt,
                                    char far *lpszVal, int nMax);

/* User Write routines */
int     WINAPI PtAccWriteD( ACCID accID, HPT hPt, int bValue );
int     WINAPI PtAccWriteI( ACCID accID, HPT hPt, long lValue );
int     WINAPI PtAccWriteR( ACCID accID, HPT hPt, float fValue );
int     WINAPI PtAccWriteA( ACCID accID, HPT hPt, double dValue );
int     WINAPI PtAccWriteM( ACCID accID, HPT hPt,
                                        const char far *lpszValue );

/* DOS-only routines */
void    far pascal PtAccWait(       ACCID accID, long millisec );
HPT     far pascal PtAccWaitChange( ACCID accID, HPT hPt, long millisec );
long    far pascal PtAccSystemTime( void );

#ifdef  __cplusplus
}
#endif


/* Message */
#ifndef DBCHGMSG
#define DBCHGMSG        "dbValueChanged"
#endif

