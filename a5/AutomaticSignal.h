#ifndef __AUTOMATICSIGNAL_H__
#define __AUTOMATICSIGNAL_H__

#define AUTOMATIC_SIGNAL uCondition blocked;
#define WAITUNTIL( pred, before, after ) \
    if ( !pred ){ \
        before; \
        while ( !blocked.empty() ) { blocked.signal(); } \
        do { \
            blocked.wait(); \
        } while ( !pred ); \
        after; \
    }
#define RETURN( expr... ) \
    while( !blocked.empty() ) { blocked.signal(); } \
    return expr;

#endif