#pragma once
//Target Windows Vista and later
#define WINVER 0x0600
#define _WIN32_WINNT 0x0600
#define NTDDI_VERSION NTDDI_VISTA
#include <sdkddkver.h>
#define WIN32_LEAN_AND_MEAN

//#define NOUSER
//#define NOVIRTUALKEYCODES
//#define NOMSG
//#define NOTEXTMETRIC
//#define NOWINSTYLES
//#define NOCOLOR
//#define NOKEYSTATES
//#define NOMB
//#define NOSYSMETRICS

#define NOSHOWWINDOW
#define NOGDICAPMASKS
#define NOMENUS
#define NOICONS
#define NOSYSCOMMANDS
#define NORASTEROPS
#define OEMRESOURCE
#define NOATOM
#define NOCLIPBOARD
#define NOCTLMGR
#define NODRAWTEXT
#define NOKERNEL
#define NONLS
#define NOMEMMGR
#define NOMETAFILE
#define NOMINMAX
#define NOOPENFILE
#define NOSCROLL
#define NOSERVICE
#define NOSOUND
#define NOWH
#define NOCOMM
#define NOKANJI
#define NOHELP
#define NOPROFILER
#define NODEFERWINDOWPOS
#define NOMCX
#define NORPC
#define NOPROXYSTUB
#define NOIMAGE
#define NOTAPE
#define STRICT

#include <Windows.h>
#include <stdint.h>
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

//Standard library

#include <memory>
#include <vector>
#include <array>

//Internal files

#include "Debugging/Log.h"
#include "Debugging/BenchmarkTimer.h"
#include "Core/Game/GameSettings.h"