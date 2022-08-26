#include <windows.h>
#include <stdio.h>


int main() {
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));  // allocate memory
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	// Start the child process.
	if(!CreateProcess(NULL, 								// No module name (use command line).
					  "C:\\WINDOWS\\system32\\mspaint.exe", // Command line.
					  NULL, 								// Process handle not inheritable.
					  NULL, 								// Thread handle not inheritable.
					  FALSE,								// Set handle inheritance to FALSE.
					  0, 									// No creation flags.
					  NULL, 								// Use parent's environment block.
					  NULL, 								// Use parent's starting directory.
					  &si, 									// Pointer to STARTUPINFO structure.
					  &pi)) {								// Pointer to PROCESS_INFORMATION structure.
		printf("CreateProcess failed (%d).\n", GetLastError());
		return -1;
	}
	// Wait until child process exits.
	WaitForSingleObject(pi.hProcess, INFINITE);
	printf("parent exit");
	// Close process and thread handles.
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}
