
#ifndef AVGLOBAL_H
#define AVGLOBAL_H

typedef int					AV_int32;	
typedef unsigned int		AV_uint32;	
typedef int					AV_BOOL;		
typedef void*				AV_HANDLE;		
typedef unsigned char		AV_BYTE;	
typedef float				AV_float;

#ifdef WIN32
typedef __int64				AV_int64;	
typedef unsigned __int64	AV_uint64;	
#else
typedef long long			AV_int64;
typedef unsigned long long	AV_uint64;
#endif	
	
#endif


