#pragma once
#include <string>
#include "imgui.h"
#include "Machine.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx10.h"
#include <d3d10_1.h>
#include <d3d10.h>
#include <tchar.h>
class GUI
{
private:
	Machine voleMachine;
public:
	void show();

};

