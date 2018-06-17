#include <windows.h>
#include <iostream>
#include "kctable.h"

using namespace std;

HHOOK keyboardHook;

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
	PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)lParam;
	const char *info = NULL;

	if (nCode >= 0) {
		if      (wParam == WM_KEYDOWN)	   info = "��ͨ��������";
		else if (wParam == WM_KEYUP)       info = "��ͨ����̧��";
		else if (wParam == WM_SYSKEYDOWN)  info = "ϵͳ��������";
		else if (wParam == WM_SYSKEYUP)	   info = "ϵͳ����̧��";

		cout << info << "�������� [" << p->vkCode << "]������ [" << checkKeyTable(p->vkCode) << "]" << endl;
	}

	return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
}

int main() {
	MSG Msg;

	// ���ü���ȫ�ּ���
	keyboardHook = SetWindowsHookEx(
		WH_KEYBOARD_LL,  // ������������
		KeyboardProc,	 // ������
		NULL,		     // ��ǰʵ�����
		0				 // �������ھ��
	);

	if (keyboardHook == NULL) {
		cout << "���̼���ʧ�ܣ�error : " << GetLastError() << endl;
	}

	// ��Ϣѭ��
	while (GetMessage(&Msg, NULL, 0, 0) > 0) {
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	return 0;
}