//---------------------------------------------------------------------------

#ifndef uJbDetailsManagerH
#define uJbDetailsManagerH

#include <vcl.h>
#include <Data.DB.hpp>
#include <FireDAC.Comp.Client.hpp>
#include <FireDAC.Comp.DataSet.hpp>
#include <FireDAC.DApt.hpp>
#include <FireDAC.DApt.Intf.hpp>
#include <FireDAC.DatS.hpp>
#include <FireDAC.Phys.Intf.hpp>
#include <FireDAC.Stan.Async.hpp>
#include <FireDAC.Stan.Error.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Stan.Option.hpp>
#include <FireDAC.Stan.Param.hpp>
#include <System.Classes.hpp>
#include "uJsonParser.h"

//---------------------------------------------------------------------------
class TJbDetailsManager : public TDataModule
{
__published:	// IDE-managed Components
	TFDQuery *fdqPkd;
	TFDQuery *fdqBranch;
	TFDQuery *fdqDepend;
	TFDQuery *fdqRepresentation;
	void __fastcall DataModuleDestroy(TObject *Sender);
private:	// User declarations
	int _JbNr;
	JbDetailsList * _JbDetailsList;

	void LoadCompanyPkdList(int JbNr);
	void LoadCompanyBranchList(int JbNr);
	void LoadCompanyDependList(int JbNr);
	void LoadCompanyRepresentationList(int JbNr);

	void SaveCompanyPkdList();
	void SaveCompanyBranchList();
	void SaveCompanyDependList();
	void SaveCompanyRepresentationList();
public:		// User declarations
	bool Save();
	bool Load();
	bool Load(int JbNr); //wczytaj inna niz podana w konstruktorze
	void ParseRespond(String Respond);

	__property JbDetailsList * CompanyDetailsList = {read = _JbDetailsList};
	__fastcall TJbDetailsManager(int JbNr, TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TJbDetailsManager *JbDetailsManager;
//---------------------------------------------------------------------------
#endif
