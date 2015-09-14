#ifndef _CPPCDS_CONFIG_H_
#define _CPPCDS_CONFIG_H_

// disable warning 'initializers put in unrecognized initialization area'
#pragma warning ( disable : 4075 )
// disable warning 'empty controlled statement found'
#pragma warning ( disable : 4390 )
// disable warning 'debug symbol greater than 255 chars'
#pragma warning ( disable : 4786 )

// Assert define
#define _cppcds_assert(expr)\
	if (!(expr)){fprintf(stderr, "%s: %d cppcds assertion failure: %s\n"),\
	__FILE__, __LINE__, #expr; abort();}

#define  true 1
#define  false 0

#endif
