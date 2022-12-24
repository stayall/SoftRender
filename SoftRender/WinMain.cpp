#include <windows.h>
#include <ShObjIdl.h>
#include <atlbase.h>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	HRESULT hr;
	hr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
	if (SUCCEEDED(hr))
	{
		CComPtr<IFileOpenDialog> pFileOpen;

		hr = CoCreateInstance(__uuidof(FileOpenDialog), nullptr, CLSCTX_ALL, IID_PPV_ARGS(&pFileOpen));
		//hr = pFileOpen.CoCreateInstance(__uuidof(FileOpenDialog));

		if (SUCCEEDED(hr))
		{
			hr = pFileOpen->Show(nullptr);
			if (SUCCEEDED(hr))
			{
				CComPtr < IShellItem> pShellItem;
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
				}
			}
			
		}
		CoUninitialize();
	}
	return 0;
}