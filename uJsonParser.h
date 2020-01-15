//---------------------------------------------------------------------------

#ifndef uJsonParserH
#define uJsonParserH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <System.JSON.hpp>
#include "uJbDetails.h"
//---------------------------------------------------------------------------

class TJsonParser : public TForm
{
__published:	// IDE-managed Components
private:	// User declarations
	int _JbNr;
	
public:		// User declarations
	bool ParseData(String Respond, JbDetailsList * TMP_DetList);

	__fastcall TJsonParser(TComponent* Owner, int JbNr);
};
//---------------------------------------------------------------------------
extern PACKAGE TJsonParser *JsonParser;
//---------------------------------------------------------------------------
#endif
