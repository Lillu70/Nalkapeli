
#pragma once

#include "..\Utility\Assert.h"
#include "..\Utility\Primitives.h"
#include "..\Utility\Intrinsics.h"
#include "..\Utility\Instrumentation.h"
#include "..\Utility\Bits.h"
#include "..\Utility\Vector_Ex.h"
#include "..\Utility\Maths.h"
#include "..\Utility\Utility.h"
#include "..\Utility\Allocator.h"
#include "..\Utility\Dynamic_Array.h"
#include "..\Utility\String.h"
#include "..\Platform\Input.h"
#include "..\Platform\Platform_Interface.h"

#include "Terminus_Font.h"

#include "Renderer.h"
#include "Renderer.cpp"

#include "Action.h"

#include "GUI.h"
#include "GUI.cpp"

#include "Nalkapeli.h"

#define INTERIM_MEM_SIZE KiB * 32

static Platform_Calltable s_platform;

static Allocator_Shell s_allocator;
static General_Allocator s_mem;

static Linear_Allocator s_interim_mem;

static Canvas s_canvas;
