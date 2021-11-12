/*********************************/
/* Author   :   Spectrum         */
/* Date     :   20 Sep 2021      */
/* Version  :   V01              */
/*********************************/

#ifndef STD_TYPES_H
#define STD_TYPES_H

typedef unsigned char 			    u8;
typedef signed char				    s8;

typedef unsigned short  		    u16;
typedef signed short 		    	s16;

typedef unsigned long 		    	u32;
typedef signed long				    s32;

typedef unsigned long long 			u64;
typedef signed long long 			s64;

typedef  float					    f32;
typedef  double					    f64;


#define false		0
#define true		1

enum{Error,NoError};
enum{Low,High};

#define NULL 	((char *)0)

#endif
