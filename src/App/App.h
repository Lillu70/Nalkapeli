

// ===================================
// Copyright (c) 2024 by Valtteri Kois
// All rights reserved.
// ===================================

#pragma once

#include "..\Utility\Primitives.h"
#include "..\Utility\Assert.h"
#include "..\Platform\Input.h"
#include "..\Utility\Intrinsics.h"
#include "..\Utility\Bits.h"
#include "..\Utility\Allocator_Shell.h"
#include "..\Utility\Dynamic_Array.h"
#include "..\Utility\Vector_Ex.h"
#include "..\Utility\Maths.h"
#include "..\Utility\Utility.h"
#include "..\Utility\String.h"
#include "..\Utility\String_Ex.h"
#include "..\Platform\Platform_Interface.h"
#include "..\Utility\Instrumentation.h"
#include "..\Utility\Allocator.h"


static Allocator_Shell s_allocator;
static Paged_General_Allocator s_mem;
static Linear_Allocator s_scrach_buffer = {};

#include "Misc\Build_In_Assets.cpp"
#include "Misc\Terminus_Font.h"

#include "Core\Renderer.h"
#include "Core\Renderer.cpp"

#include "Misc\Image_Loader.cpp"

#include "Core\Action.h"

#include "Core\GUI.h"
#include "Core\GUI.cpp"

#include "Misc\Random_Machine.h"

#include "Menus\Menu.h"

static Platform_Calltable s_platform;
static Canvas s_canvas;

#include "Misc\Settings.h"
#include "Menus\Localisation_Impl.h"

#include "TTeller\Editor.h"
#include "TTeller\Editor.cpp"

#include "TTeller\Story_Engine.h"
#include "TTeller\Story_Engine.cpp"

#include "Menus\Menu_Core.h"
#include "Menus\Main_Menus.cpp"
#include "Menus\Editor_Menus.cpp"
#include "Menus\Game_Menus.cpp"

#include "Misc\Memory_Display.cpp"