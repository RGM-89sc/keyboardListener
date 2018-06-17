#include <windows.h>
#include <iostream>
#include "kctable.h"

using namespace std;

HHOOK keyboardHook;

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
	PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)lParam;
	const char *info = NULL;

	if (nCode >= 0) {
		if      (wParam == WM_KEYDOWN)	   info = "普通按键按下";
		else if (wParam == WM_KEYUP)       info = "普通按键抬起";
		else if (wParam == WM_SYSKEYDOWN)  info = "系统按键按下";
		else if (wParam == WM_SYSKEYUP)	   info = "系统按键抬起";

		cout << info << "，键盘码 [" << p->vkCode << "]，按键 [" << checkKeyTable(p->vkCode) << "]" << endl;
	}

	return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
}

int main() {
	MSG Msg;

	// 设置键盘全局监听
	keyboardHook = SetWindowsHookEx(
		WH_KEYBOARD_LL,  // 监听键盘类型
		KeyboardProc,	 // 处理函数
		NULL,		     // 当前实例句柄
		0				 // 监听窗口句柄
	);

	if (keyboardHook == NULL) {
		cout << "键盘监听失败！error : " << GetLastError() << endl;
	}

	// 消息循环
	while (GetMessage(&Msg, NULL, 0, 0) > 0) {
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	return 0;
}