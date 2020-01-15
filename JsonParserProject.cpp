//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORM("uMaain.cpp", uMain);
USEFORM("..\zadanie2\MailSenderFromFireWare\uConnectionManager.cpp", ConnectionManager); /* TDataModule: File Type */
USEFORM("uJsonParser.cpp", JsonParser);
USEFORM("uJbDetailsManager.cpp", JbDetailsManager); /* TDataModule: File Type */
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->CreateForm(__classid(TuMain), &uMain);
		Application->CreateForm(__classid(TConnectionManager), &ConnectionManager);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
