#include <windows.h>
#include <ShObjIdl.h>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	HRESULT hr;
	hr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
	if (SUCCEEDED(hr))
	{
		IFileOpenDialog* pFileOpen;

		hr = CoCreateInstance(CLSID_FileOpenDialog, nullptr, CLSCTX_ALL, IID_IFileOpenDialog, reinterpret_cast<LPVOID*>(&pFileOpen));
		if (SUCCEEDED(hr))
		{
			hr = pFileOpen->Show(nullptr);
			if (SUCCEEDED(hr))
			{
				IShellItem* pShellItem;
				hr = pFileOpen->GetResult(&pShellItem);

				if (SUCCEEDED(hr))
				{
					PWSTR file;
					hr = pShellItem->GetDisplayName(SIGDN_FILESYSPATH, &file);
					if (SUCCEEDED(hr))
					{
						MessageBox(nullptr, file, L"File Path", MB_OK);
						CoTaskMemFree(file);
					}
					pShellItem->Release();
				}
			}
			pFileOpen->Release();
		}
		CoUninitialize();
	}
	return 0;
}