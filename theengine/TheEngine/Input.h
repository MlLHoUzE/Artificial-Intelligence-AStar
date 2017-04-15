#ifndef _Input_HG_
#define _Input_HG_

//#include "externals.h"

#include "Globals.h"

namespace nInput
{
	namespace IsKeyPressed
	{
		inline bool A() { return glfwGetKey(g_window, GLFW_KEY_A) == GLFW_PRESS; }
		inline bool B() { return glfwGetKey(g_window, GLFW_KEY_B) == GLFW_PRESS; }
		inline bool C() { return glfwGetKey(g_window, GLFW_KEY_C) == GLFW_PRESS; }
		inline bool D() { return glfwGetKey(g_window, GLFW_KEY_D) == GLFW_PRESS; }
		inline bool E() { return glfwGetKey(g_window, GLFW_KEY_E) == GLFW_PRESS; }
		inline bool F() { return glfwGetKey(g_window, GLFW_KEY_F) == GLFW_PRESS; }
		inline bool G() { return glfwGetKey(g_window, GLFW_KEY_G) == GLFW_PRESS; }
		inline bool H() { return glfwGetKey(g_window, GLFW_KEY_H) == GLFW_PRESS; }
		inline bool I() { return glfwGetKey(g_window, GLFW_KEY_I) == GLFW_PRESS; }
		inline bool J() { return glfwGetKey(g_window, GLFW_KEY_J) == GLFW_PRESS; }
		inline bool K() { return glfwGetKey(g_window, GLFW_KEY_K) == GLFW_PRESS; }
		inline bool L() { return glfwGetKey(g_window, GLFW_KEY_L) == GLFW_PRESS; }
		inline bool M() { return glfwGetKey(g_window, GLFW_KEY_M) == GLFW_PRESS; }
		inline bool N() { return glfwGetKey(g_window, GLFW_KEY_N) == GLFW_PRESS; }
		inline bool O() { return glfwGetKey(g_window, GLFW_KEY_O) == GLFW_PRESS; }
		inline bool P() { return glfwGetKey(g_window, GLFW_KEY_P) == GLFW_PRESS; }
		inline bool Q() { return glfwGetKey(g_window, GLFW_KEY_Q) == GLFW_PRESS; }
		inline bool R() { return glfwGetKey(g_window, GLFW_KEY_R) == GLFW_PRESS; }
		inline bool S() { return glfwGetKey(g_window, GLFW_KEY_S) == GLFW_PRESS; }
		inline bool T() { return glfwGetKey(g_window, GLFW_KEY_T) == GLFW_PRESS; }
		inline bool U() { return glfwGetKey(g_window, GLFW_KEY_U) == GLFW_PRESS; }
		inline bool V() { return glfwGetKey(g_window, GLFW_KEY_V) == GLFW_PRESS; }
		inline bool W() { return glfwGetKey(g_window, GLFW_KEY_W) == GLFW_PRESS; }
		inline bool X() { return glfwGetKey(g_window, GLFW_KEY_X) == GLFW_PRESS; }
		inline bool Y() { return glfwGetKey(g_window, GLFW_KEY_Y) == GLFW_PRESS; }
		inline bool Z() { return glfwGetKey(g_window, GLFW_KEY_Z) == GLFW_PRESS; }

		inline bool UP() { return glfwGetKey(g_window, GLFW_KEY_UP) == GLFW_PRESS; }
		inline bool DOWN() { return glfwGetKey(g_window, GLFW_KEY_DOWN) == GLFW_PRESS; }
		inline bool LEFT() { return glfwGetKey(g_window, GLFW_KEY_LEFT) == GLFW_PRESS; }
		inline bool RIGHT() { return glfwGetKey(g_window, GLFW_KEY_RIGHT) == GLFW_PRESS; }
		

		inline bool NUM0() { return glfwGetKey(g_window, GLFW_KEY_0) == GLFW_PRESS; }
		inline bool NUM1() { return glfwGetKey(g_window, GLFW_KEY_1) == GLFW_PRESS; }
		inline bool NUM2() { return glfwGetKey(g_window, GLFW_KEY_2) == GLFW_PRESS; }
		inline bool NUM3() { return glfwGetKey(g_window, GLFW_KEY_3) == GLFW_PRESS; }
		inline bool NUM4() { return glfwGetKey(g_window, GLFW_KEY_4) == GLFW_PRESS; }
		inline bool NUM5() { return glfwGetKey(g_window, GLFW_KEY_5) == GLFW_PRESS; }
		inline bool NUM6() { return glfwGetKey(g_window, GLFW_KEY_6) == GLFW_PRESS; }
		inline bool NUM7() { return glfwGetKey(g_window, GLFW_KEY_7) == GLFW_PRESS; }
		inline bool NUM8() { return glfwGetKey(g_window, GLFW_KEY_8) == GLFW_PRESS; }
		inline bool NUM9() { return glfwGetKey(g_window, GLFW_KEY_9) == GLFW_PRESS; }

		inline bool ESCAPE() { return glfwGetKey(g_window, GLFW_KEY_ESCAPE) == GLFW_PRESS; }
		inline bool ENTER() { return glfwGetKey(g_window, GLFW_KEY_ENTER) == GLFW_PRESS; }
		inline bool TAB() { return glfwGetKey(g_window, GLFW_KEY_TAB) == GLFW_PRESS; }

		inline bool F1() { return glfwGetKey(g_window, GLFW_KEY_F1) == GLFW_PRESS; }
		inline bool F2() { return glfwGetKey(g_window, GLFW_KEY_F2) == GLFW_PRESS; }
		inline bool F3() { return glfwGetKey(g_window, GLFW_KEY_F3) == GLFW_PRESS; }
		inline bool F4() { return glfwGetKey(g_window, GLFW_KEY_F4) == GLFW_PRESS; }
		inline bool F5() { return glfwGetKey(g_window, GLFW_KEY_F5) == GLFW_PRESS; }
		inline bool F6() { return glfwGetKey(g_window, GLFW_KEY_F6) == GLFW_PRESS; }
		inline bool F7() { return glfwGetKey(g_window, GLFW_KEY_F7) == GLFW_PRESS; }
		inline bool F8() { return glfwGetKey(g_window, GLFW_KEY_F8) == GLFW_PRESS; }
		inline bool F9() { return glfwGetKey(g_window, GLFW_KEY_F9) == GLFW_PRESS; }
		inline bool F10() { return glfwGetKey(g_window, GLFW_KEY_F10) == GLFW_PRESS; }
		inline bool F11() { return glfwGetKey(g_window, GLFW_KEY_F11) == GLFW_PRESS; }
		inline bool F12() { return glfwGetKey(g_window, GLFW_KEY_F12) == GLFW_PRESS; }

		inline bool KEYPAD0() { return glfwGetKey(g_window, GLFW_KEY_KP_0) == GLFW_PRESS; }
		inline bool KEYPAD1() { return glfwGetKey(g_window, GLFW_KEY_KP_1) == GLFW_PRESS; }
		inline bool KEYPAD2() { return glfwGetKey(g_window, GLFW_KEY_KP_2) == GLFW_PRESS; }
		inline bool KEYPAD3() { return glfwGetKey(g_window, GLFW_KEY_KP_3) == GLFW_PRESS; }
		inline bool KEYPAD4() { return glfwGetKey(g_window, GLFW_KEY_KP_4) == GLFW_PRESS; }
		inline bool KEYPAD5() { return glfwGetKey(g_window, GLFW_KEY_KP_5) == GLFW_PRESS; }
		inline bool KEYPAD6() { return glfwGetKey(g_window, GLFW_KEY_KP_6) == GLFW_PRESS; }
		inline bool KEYPAD7() { return glfwGetKey(g_window, GLFW_KEY_KP_7) == GLFW_PRESS; }
		inline bool KEYPAD8() { return glfwGetKey(g_window, GLFW_KEY_KP_8) == GLFW_PRESS; }
		inline bool KEYPAD9() { return glfwGetKey(g_window, GLFW_KEY_KP_9) == GLFW_PRESS; }
		inline bool KEYPADENTER() { return glfwGetKey(g_window, GLFW_KEY_KP_ENTER) == GLFW_PRESS; }


		inline bool LEFTSHIFT() { return glfwGetKey(g_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS; }
		inline bool RIGHTSHIFT() { return glfwGetKey(g_window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS; }
		inline bool LEFTCONTROL() { return glfwGetKey(g_window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS; }
		inline bool RIGHTCONTROL() { return glfwGetKey(g_window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS; }
		inline bool LEFTALT() { return glfwGetKey(g_window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS; }
		inline bool RIGHTALT() { return glfwGetKey(g_window, GLFW_KEY_RIGHT_ALT) == GLFW_PRESS; }


		inline bool MOUSEBUTTONRIGHT() { return glfwGetKey(g_window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS; }
		inline bool MOUSEBUTTONLEFT() { return glfwGetKey(g_window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS; }
		inline bool MOUSEBUTTONMIDDLE() { return glfwGetKey(g_window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS; }
		
	}

	namespace IsKeyRepeated
	{
		inline bool A() { return glfwGetKey(g_window, GLFW_KEY_A) == GLFW_REPEAT; }
		inline bool B() { return glfwGetKey(g_window, GLFW_KEY_B) == GLFW_REPEAT; }
		inline bool C() { return glfwGetKey(g_window, GLFW_KEY_C) == GLFW_REPEAT; }
		inline bool D() { return glfwGetKey(g_window, GLFW_KEY_D) == GLFW_REPEAT; }
		inline bool E() { return glfwGetKey(g_window, GLFW_KEY_E) == GLFW_REPEAT; }
		inline bool F() { return glfwGetKey(g_window, GLFW_KEY_F) == GLFW_REPEAT; }
		inline bool G() { return glfwGetKey(g_window, GLFW_KEY_G) == GLFW_REPEAT; }
		inline bool H() { return glfwGetKey(g_window, GLFW_KEY_H) == GLFW_REPEAT; }
		inline bool I() { return glfwGetKey(g_window, GLFW_KEY_I) == GLFW_REPEAT; }
		inline bool J() { return glfwGetKey(g_window, GLFW_KEY_J) == GLFW_REPEAT; }
		inline bool K() { return glfwGetKey(g_window, GLFW_KEY_K) == GLFW_REPEAT; }
		inline bool L() { return glfwGetKey(g_window, GLFW_KEY_L) == GLFW_REPEAT; }
		inline bool M() { return glfwGetKey(g_window, GLFW_KEY_M) == GLFW_REPEAT; }
		inline bool N() { return glfwGetKey(g_window, GLFW_KEY_N) == GLFW_REPEAT; }
		inline bool O() { return glfwGetKey(g_window, GLFW_KEY_O) == GLFW_REPEAT; }
		inline bool P() { return glfwGetKey(g_window, GLFW_KEY_P) == GLFW_REPEAT; }
		inline bool Q() { return glfwGetKey(g_window, GLFW_KEY_Q) == GLFW_REPEAT; }
		inline bool R() { return glfwGetKey(g_window, GLFW_KEY_R) == GLFW_REPEAT; }
		inline bool S() { return glfwGetKey(g_window, GLFW_KEY_S) == GLFW_REPEAT; }
		inline bool T() { return glfwGetKey(g_window, GLFW_KEY_T) == GLFW_REPEAT; }
		inline bool U() { return glfwGetKey(g_window, GLFW_KEY_U) == GLFW_REPEAT; }
		inline bool V() { return glfwGetKey(g_window, GLFW_KEY_V) == GLFW_REPEAT; }
		inline bool W() { return glfwGetKey(g_window, GLFW_KEY_W) == GLFW_REPEAT; }
		inline bool X() { return glfwGetKey(g_window, GLFW_KEY_X) == GLFW_REPEAT; }
		inline bool Y() { return glfwGetKey(g_window, GLFW_KEY_Y) == GLFW_REPEAT; }
		inline bool Z() { return glfwGetKey(g_window, GLFW_KEY_Z) == GLFW_REPEAT; }

		inline bool UP() { return glfwGetKey(g_window, GLFW_KEY_UP) == GLFW_REPEAT; }
		inline bool DOWN() { return glfwGetKey(g_window, GLFW_KEY_DOWN) == GLFW_REPEAT; }
		inline bool LEFT() { return glfwGetKey(g_window, GLFW_KEY_LEFT) == GLFW_REPEAT; }
		inline bool RIGHT() { return glfwGetKey(g_window, GLFW_KEY_RIGHT) == GLFW_REPEAT; }


		inline bool NUM0() { return glfwGetKey(g_window, GLFW_KEY_0) == GLFW_REPEAT; }
		inline bool NUM1() { return glfwGetKey(g_window, GLFW_KEY_1) == GLFW_REPEAT; }
		inline bool NUM2() { return glfwGetKey(g_window, GLFW_KEY_2) == GLFW_REPEAT; }
		inline bool NUM3() { return glfwGetKey(g_window, GLFW_KEY_3) == GLFW_REPEAT; }
		inline bool NUM4() { return glfwGetKey(g_window, GLFW_KEY_4) == GLFW_REPEAT; }
		inline bool NUM5() { return glfwGetKey(g_window, GLFW_KEY_5) == GLFW_REPEAT; }
		inline bool NUM6() { return glfwGetKey(g_window, GLFW_KEY_6) == GLFW_REPEAT; }
		inline bool NUM7() { return glfwGetKey(g_window, GLFW_KEY_7) == GLFW_REPEAT; }
		inline bool NUM8() { return glfwGetKey(g_window, GLFW_KEY_8) == GLFW_REPEAT; }
		inline bool NUM9() { return glfwGetKey(g_window, GLFW_KEY_9) == GLFW_REPEAT; }

		inline bool ESCAPE() { return glfwGetKey(g_window, GLFW_KEY_ESCAPE) == GLFW_REPEAT; }
		inline bool ENTER() { return glfwGetKey(g_window, GLFW_KEY_ENTER) == GLFW_REPEAT; }
		inline bool TAB() { return glfwGetKey(g_window, GLFW_KEY_TAB) == GLFW_REPEAT; }

		inline bool F1() { return glfwGetKey(g_window, GLFW_KEY_F1) == GLFW_REPEAT; }
		inline bool F2() { return glfwGetKey(g_window, GLFW_KEY_F2) == GLFW_REPEAT; }
		inline bool F3() { return glfwGetKey(g_window, GLFW_KEY_F3) == GLFW_REPEAT; }
		inline bool F4() { return glfwGetKey(g_window, GLFW_KEY_F4) == GLFW_REPEAT; }
		inline bool F5() { return glfwGetKey(g_window, GLFW_KEY_F5) == GLFW_REPEAT; }
		inline bool F6() { return glfwGetKey(g_window, GLFW_KEY_F6) == GLFW_REPEAT; }
		inline bool F7() { return glfwGetKey(g_window, GLFW_KEY_F7) == GLFW_REPEAT; }
		inline bool F8() { return glfwGetKey(g_window, GLFW_KEY_F8) == GLFW_REPEAT; }
		inline bool F9() { return glfwGetKey(g_window, GLFW_KEY_F9) == GLFW_REPEAT; }
		inline bool F10() { return glfwGetKey(g_window, GLFW_KEY_F10) == GLFW_REPEAT; }
		inline bool F11() { return glfwGetKey(g_window, GLFW_KEY_F11) == GLFW_REPEAT; }
		inline bool F12() { return glfwGetKey(g_window, GLFW_KEY_F12) == GLFW_REPEAT; }

		inline bool KEYPAD0() { return glfwGetKey(g_window, GLFW_KEY_KP_0) == GLFW_REPEAT; }
		inline bool KEYPAD1() { return glfwGetKey(g_window, GLFW_KEY_KP_1) == GLFW_REPEAT; }
		inline bool KEYPAD2() { return glfwGetKey(g_window, GLFW_KEY_KP_2) == GLFW_REPEAT; }
		inline bool KEYPAD3() { return glfwGetKey(g_window, GLFW_KEY_KP_3) == GLFW_REPEAT; }
		inline bool KEYPAD4() { return glfwGetKey(g_window, GLFW_KEY_KP_4) == GLFW_REPEAT; }
		inline bool KEYPAD5() { return glfwGetKey(g_window, GLFW_KEY_KP_5) == GLFW_REPEAT; }
		inline bool KEYPAD6() { return glfwGetKey(g_window, GLFW_KEY_KP_6) == GLFW_REPEAT; }
		inline bool KEYPAD7() { return glfwGetKey(g_window, GLFW_KEY_KP_7) == GLFW_REPEAT; }
		inline bool KEYPAD8() { return glfwGetKey(g_window, GLFW_KEY_KP_8) == GLFW_REPEAT; }
		inline bool KEYPAD9() { return glfwGetKey(g_window, GLFW_KEY_KP_9) == GLFW_REPEAT; }
		inline bool KEYPADENTER() { return glfwGetKey(g_window, GLFW_KEY_KP_ENTER) == GLFW_REPEAT; }


		inline bool LEFTSHIFT() { return glfwGetKey(g_window, GLFW_KEY_LEFT_SHIFT) == GLFW_REPEAT; }
		inline bool RIGHTSHIFT() { return glfwGetKey(g_window, GLFW_KEY_RIGHT_SHIFT) == GLFW_REPEAT; }
		inline bool LEFTCONTROL() { return glfwGetKey(g_window, GLFW_KEY_LEFT_CONTROL) == GLFW_REPEAT; }
		inline bool RIGHTCONTROL() { return glfwGetKey(g_window, GLFW_KEY_RIGHT_CONTROL) == GLFW_REPEAT; }
		inline bool LEFTALT() { return glfwGetKey(g_window, GLFW_KEY_LEFT_ALT) == GLFW_REPEAT; }
		inline bool RIGHTALT() { return glfwGetKey(g_window, GLFW_KEY_RIGHT_ALT) == GLFW_REPEAT; }


		inline bool MOUSEBUTTONRIGHT() { return glfwGetKey(g_window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_REPEAT; }
		inline bool MOUSEBUTTONLEFT() { return glfwGetKey(g_window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_REPEAT; }
		inline bool MOUSEBUTTONMIDDLE() { return glfwGetKey(g_window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_REPEAT; }

	}

	namespace IsKeyRelease
	{
		inline bool A() { return glfwGetKey(g_window, GLFW_KEY_A) == GLFW_RELEASE; }
		inline bool B() { return glfwGetKey(g_window, GLFW_KEY_B) == GLFW_RELEASE; }
		inline bool C() { return glfwGetKey(g_window, GLFW_KEY_C) == GLFW_RELEASE; }
		inline bool D() { return glfwGetKey(g_window, GLFW_KEY_D) == GLFW_RELEASE; }
		inline bool E() { return glfwGetKey(g_window, GLFW_KEY_E) == GLFW_RELEASE; }
		inline bool F() { return glfwGetKey(g_window, GLFW_KEY_F) == GLFW_RELEASE; }
		inline bool G() { return glfwGetKey(g_window, GLFW_KEY_G) == GLFW_RELEASE; }
		inline bool H() { return glfwGetKey(g_window, GLFW_KEY_H) == GLFW_RELEASE; }
		inline bool I() { return glfwGetKey(g_window, GLFW_KEY_I) == GLFW_RELEASE; }
		inline bool J() { return glfwGetKey(g_window, GLFW_KEY_J) == GLFW_RELEASE; }
		inline bool K() { return glfwGetKey(g_window, GLFW_KEY_K) == GLFW_RELEASE; }
		inline bool L() { return glfwGetKey(g_window, GLFW_KEY_L) == GLFW_RELEASE; }
		inline bool M() { return glfwGetKey(g_window, GLFW_KEY_M) == GLFW_RELEASE; }
		inline bool N() { return glfwGetKey(g_window, GLFW_KEY_N) == GLFW_RELEASE; }
		inline bool O() { return glfwGetKey(g_window, GLFW_KEY_O) == GLFW_RELEASE; }
		inline bool P() { return glfwGetKey(g_window, GLFW_KEY_P) == GLFW_RELEASE; }
		inline bool Q() { return glfwGetKey(g_window, GLFW_KEY_Q) == GLFW_RELEASE; }
		inline bool R() { return glfwGetKey(g_window, GLFW_KEY_R) == GLFW_RELEASE; }
		inline bool S() { return glfwGetKey(g_window, GLFW_KEY_S) == GLFW_RELEASE; }
		inline bool T() { return glfwGetKey(g_window, GLFW_KEY_T) == GLFW_RELEASE; }
		inline bool U() { return glfwGetKey(g_window, GLFW_KEY_U) == GLFW_RELEASE; }
		inline bool V() { return glfwGetKey(g_window, GLFW_KEY_V) == GLFW_RELEASE; }
		inline bool W() { return glfwGetKey(g_window, GLFW_KEY_W) == GLFW_RELEASE; }
		inline bool X() { return glfwGetKey(g_window, GLFW_KEY_X) == GLFW_RELEASE; }
		inline bool Y() { return glfwGetKey(g_window, GLFW_KEY_Y) == GLFW_RELEASE; }
		inline bool Z() { return glfwGetKey(g_window, GLFW_KEY_Z) == GLFW_RELEASE; }

		inline bool UP() { return glfwGetKey(g_window, GLFW_KEY_UP) == GLFW_RELEASE; }
		inline bool DOWN() { return glfwGetKey(g_window, GLFW_KEY_DOWN) == GLFW_RELEASE; }
		inline bool LEFT() { return glfwGetKey(g_window, GLFW_KEY_LEFT) == GLFW_RELEASE; }
		inline bool RIGHT() { return glfwGetKey(g_window, GLFW_KEY_RIGHT) == GLFW_RELEASE; }


		inline bool NUM0() { return glfwGetKey(g_window, GLFW_KEY_0) == GLFW_RELEASE; }
		inline bool NUM1() { return glfwGetKey(g_window, GLFW_KEY_1) == GLFW_RELEASE; }
		inline bool NUM2() { return glfwGetKey(g_window, GLFW_KEY_2) == GLFW_RELEASE; }
		inline bool NUM3() { return glfwGetKey(g_window, GLFW_KEY_3) == GLFW_RELEASE; }
		inline bool NUM4() { return glfwGetKey(g_window, GLFW_KEY_4) == GLFW_RELEASE; }
		inline bool NUM5() { return glfwGetKey(g_window, GLFW_KEY_5) == GLFW_RELEASE; }
		inline bool NUM6() { return glfwGetKey(g_window, GLFW_KEY_6) == GLFW_RELEASE; }
		inline bool NUM7() { return glfwGetKey(g_window, GLFW_KEY_7) == GLFW_RELEASE; }
		inline bool NUM8() { return glfwGetKey(g_window, GLFW_KEY_8) == GLFW_RELEASE; }
		inline bool NUM9() { return glfwGetKey(g_window, GLFW_KEY_9) == GLFW_RELEASE; }

		inline bool ESCAPE() { return glfwGetKey(g_window, GLFW_KEY_ESCAPE) == GLFW_RELEASE; }
		inline bool ENTER() { return glfwGetKey(g_window, GLFW_KEY_ENTER) == GLFW_RELEASE; }
		inline bool TAB() { return glfwGetKey(g_window, GLFW_KEY_TAB) == GLFW_RELEASE; }

		inline bool F1() { return glfwGetKey(g_window, GLFW_KEY_F1) == GLFW_RELEASE; }
		inline bool F2() { return glfwGetKey(g_window, GLFW_KEY_F2) == GLFW_RELEASE; }
		inline bool F3() { return glfwGetKey(g_window, GLFW_KEY_F3) == GLFW_RELEASE; }
		inline bool F4() { return glfwGetKey(g_window, GLFW_KEY_F4) == GLFW_RELEASE; }
		inline bool F5() { return glfwGetKey(g_window, GLFW_KEY_F5) == GLFW_RELEASE; }
		inline bool F6() { return glfwGetKey(g_window, GLFW_KEY_F6) == GLFW_RELEASE; }
		inline bool F7() { return glfwGetKey(g_window, GLFW_KEY_F7) == GLFW_RELEASE; }
		inline bool F8() { return glfwGetKey(g_window, GLFW_KEY_F8) == GLFW_RELEASE; }
		inline bool F9() { return glfwGetKey(g_window, GLFW_KEY_F9) == GLFW_RELEASE; }
		inline bool F10() { return glfwGetKey(g_window, GLFW_KEY_F10) == GLFW_RELEASE; }
		inline bool F11() { return glfwGetKey(g_window, GLFW_KEY_F11) == GLFW_RELEASE; }
		inline bool F12() { return glfwGetKey(g_window, GLFW_KEY_F12) == GLFW_RELEASE; }

		inline bool KEYPAD0() { return glfwGetKey(g_window, GLFW_KEY_KP_0) == GLFW_RELEASE; }
		inline bool KEYPAD1() { return glfwGetKey(g_window, GLFW_KEY_KP_1) == GLFW_RELEASE; }
		inline bool KEYPAD2() { return glfwGetKey(g_window, GLFW_KEY_KP_2) == GLFW_RELEASE; }
		inline bool KEYPAD3() { return glfwGetKey(g_window, GLFW_KEY_KP_3) == GLFW_RELEASE; }
		inline bool KEYPAD4() { return glfwGetKey(g_window, GLFW_KEY_KP_4) == GLFW_RELEASE; }
		inline bool KEYPAD5() { return glfwGetKey(g_window, GLFW_KEY_KP_5) == GLFW_RELEASE; }
		inline bool KEYPAD6() { return glfwGetKey(g_window, GLFW_KEY_KP_6) == GLFW_RELEASE; }
		inline bool KEYPAD7() { return glfwGetKey(g_window, GLFW_KEY_KP_7) == GLFW_RELEASE; }
		inline bool KEYPAD8() { return glfwGetKey(g_window, GLFW_KEY_KP_8) == GLFW_RELEASE; }
		inline bool KEYPAD9() { return glfwGetKey(g_window, GLFW_KEY_KP_9) == GLFW_RELEASE; }
		inline bool KEYPADENTER() { return glfwGetKey(g_window, GLFW_KEY_KP_ENTER) == GLFW_RELEASE; }


		inline bool LEFTSHIFT() { return glfwGetKey(g_window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE; }
		inline bool RIGHTSHIFT() { return glfwGetKey(g_window, GLFW_KEY_RIGHT_SHIFT) == GLFW_RELEASE; }
		inline bool LEFTCONTROL() { return glfwGetKey(g_window, GLFW_KEY_LEFT_CONTROL) == GLFW_RELEASE; }
		inline bool RIGHTCONTROL() { return glfwGetKey(g_window, GLFW_KEY_RIGHT_CONTROL) == GLFW_RELEASE; }
		inline bool LEFTALT() { return glfwGetKey(g_window, GLFW_KEY_LEFT_ALT) == GLFW_RELEASE; }
		inline bool RIGHTALT() { return glfwGetKey(g_window, GLFW_KEY_RIGHT_ALT) == GLFW_RELEASE; }


		inline bool MOUSEBUTTONRIGHT() { return glfwGetKey(g_window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE; }
		inline bool MOUSEBUTTONLEFT() { return glfwGetKey(g_window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE; }
		inline bool MOUSEBUTTONMIDDLE() { return glfwGetKey(g_window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_RELEASE; }

	}
}


#endif