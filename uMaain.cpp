//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uMaain.h"
#include "uJbDetailsManager.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TuMain *uMain;
//---------------------------------------------------------------------------
__fastcall TuMain::TuMain(TComponent* Owner)
	: TForm(Owner)
{
	 JbDetailsManager = new TJbDetailsManager(17,this);
}
//---------------------------------------------------------------------------

void TuMain::LoadListView(TListView *lv, TStringList *data){
	lv->Items->Clear();
	TListItem * List;
	for (int i = 0; i < data->Count; i++) {
		List = lv->Items->Add();
		List->Caption=i;
		List->SubItems->Add(data->Strings[i]);

	}
}
void __fastcall TuMain::saveClick(TObject *Sender)
{
	if(JbDetailsManager->Save()) ShowMessage("Zapisano!");
}
//---------------------------------------------------------------------------

void __fastcall TuMain::loadClick(TObject *Sender)
{
	//tests
	JbDetailsManager->Load(17);
	reloadClick(this);
}
//---------------------------------------------------------------------------

void __fastcall TuMain::parseClick(TObject *Sender)
{
	if (odMain->Execute()) {
		TStringStream * tmp = new TStringStream();
		tmp->LoadFromFile(odMain->FileName);
		String Respond = tmp->DataString;
		delete tmp;
		JbDetailsManager->ParseRespond(Respond);
		reloadClick(this);
	}else ShowMessage("Wybierz plik!");

}
//---------------------------------------------------------------------------

void __fastcall TuMain::reloadClick(TObject *Sender)
{
	LoadListView(lvProfiles,JbDetailsManager->CompanyDetailsList->CompanyPkdList->ToStringList());
	LoadListView(lvBranches,JbDetailsManager->CompanyDetailsList->CompanyBranchList->ToStringList());
	LoadListView(lvDepentComp,JbDetailsManager->CompanyDetailsList->CompanyDependList->ToStringList());
	LoadListView(lvRepresent,JbDetailsManager->CompanyDetailsList->CompanyRepresentationList->ToStringList());
	//ShowMessage(JbDetailsManager->CompanyDetailsList->CompanyBranchList->ToStringList()->Text);
}
//---------------------------------------------------------------------------

