#pragma once

#ifdef NOBISLIBRARY_EXPORTS
#define NOBISLIBRARY_API __declspec(dllexport)
#else
#define NOBISLIBRARY_API __declspec(dllimport)
#endif
