#ifndef CONFIG_H
# define CONFIG_H

#ifdef _WINDOWS

# include <stdint.h>
# include <stdlib.h>
# include <limits.h>
//# include <winsock2.h>

typedef uint32_t __uid32_t;
typedef uint32_t __gid32_t;
typedef uint32_t uid_t;
typedef int socklen_t;

struct sockaddr_un {
	uint16_t sun_family;
	char sun_path[_MAX_PATH];
};

enum  {
	SHUT_RD = 0, /* No more receptions.  */
	SHUT_WR, /* No more transmissions.  */
	SHUT_RDWR /* No more receptions or transmissions.  */
};

#endif

#define CK_PTR *
#ifdef _WINDOWS
#define CK_DECLARE_FUNCTION(returnType, name) \
   __declspec(dllexport) returnType __cdecl name
#else
#define CK_DECLARE_FUNCTION(returnType, name) \
   returnType name
#endif
#define CK_DECLARE_FUNCTION_POINTER(returnType, name) \
   returnType (* (name))
#define CK_CALLBACK_FUNCTION(returnType, name) \
   returnType (* (name))

#endif	/* CONFIG_H */
