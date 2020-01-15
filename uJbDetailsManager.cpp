//---------------------------------------------------------------------------

#pragma hdrstop

#include "uJbDetailsManager.h"
#include "uConnectionManager.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma classgroup "Vcl.Controls.TControl"
#pragma resource "*.dfm"
TJbDetailsManager *JbDetailsManager;
//---------------------------------------------------------------------------
__fastcall TJbDetailsManager::TJbDetailsManager(int JbNr, TComponent* Owner)
	: TDataModule(Owner)
{
	_JbNr = JbNr;
	_JbDetailsList = new JbDetailsList(JbNr);
}
//---------------------------------------------------------------------------
void __fastcall TJbDetailsManager::DataModuleDestroy(TObject *Sender)
{
	delete _JbDetailsList;
}
//---------------------------------------------------------------------------

bool TJbDetailsManager::Load(){
	bool Result = true;
	try {
		LoadCompanyPkdList(_JbNr);
		LoadCompanyBranchList(_JbNr);
		LoadCompanyDependList(_JbNr);
		LoadCompanyRepresentationList(_JbNr);
	} catch (Exception &e) {
		ShowMessage(e.Message);
		Result = false;
	}
	return Result;
}
bool TJbDetailsManager::Load(int JbNr){
	_JbNr = JbNr;
	Load();
}

void TJbDetailsManager::LoadCompanyPkdList(int JbNr){
	fdqPkd->SQL->Text = "SELECT * FROM t_jbpkd WHERE jb_nr = :JbNr";
	fdqPkd->ParamByName("JbNr")->AsInteger = JbNr;
	fdqPkd->Open();
	_JbDetailsList->CompanyPkdList->Clear();
	for (int i = 0; i < fdqPkd->RecordCount; i++) {
		int Id = fdqPkd->FieldByName("jb_id")->AsInteger,
			NrJb = fdqPkd->FieldByName("jb_nr")->AsInteger;
		String Pkd = fdqPkd->FieldByName("jb_pkd")->AsString;
		bool Active = fdqPkd->FieldByName("jb_aktywny")->AsBoolean;
		_JbDetailsList->CompanyPkdList->Add(new JbPkd(Id,NrJb,Pkd,Active));
		//if(fdqPkd->Locate("jb_pkd",Pkd,TLocateOptions())) ShowMessage(1);
		fdqPkd->Next();
	}
}

void TJbDetailsManager::LoadCompanyBranchList(int JbNr){
	fdqBranch->SQL->Text = "SELECT * FROM t_jboddzialy WHERE jb_nr = :JbNr";
	fdqBranch->ParamByName("JbNr")->AsInteger = JbNr;
	fdqBranch->Open();
	_JbDetailsList->CompanyBranchList->Clear();
	for (int i = 0; i < fdqBranch->RecordCount; i++) {
		int Id = fdqBranch->FieldByName("jb_id")->AsInteger,
			NrJb = fdqBranch->FieldByName("jb_nr")->AsInteger;
		String BranchName = fdqBranch->FieldByName("jb_nazwa_oddzialu")->AsString;
		bool Active = fdqBranch->FieldByName("jb_aktywny")->AsBoolean;
		_JbDetailsList->CompanyBranchList->Add(new JbBranch(Id,NrJb,BranchName,Active));
		fdqBranch->Next();
	}
}

void TJbDetailsManager::LoadCompanyDependList(int JbNr){
	fdqDepend->SQL->Text = "SELECT * FROM t_jborganzal WHERE jb_nr = :JbNr";
	fdqDepend->ParamByName("JbNr")->AsInteger = JbNr;
	fdqDepend->Open();
	_JbDetailsList->CompanyDependList->Clear();
	for (int i = 0; i < fdqDepend->RecordCount; i++) {
		int Id = fdqDepend->FieldByName("jb_id")->AsInteger,
			NrJb = fdqDepend->FieldByName("jb_nr")->AsInteger;
		String DependCompName = fdqDepend->FieldByName("jb_nazwa_organu")->AsString;
		bool Active = fdqDepend->FieldByName("jb_aktywny")->AsBoolean;
		_JbDetailsList->CompanyDependList->Add(new JbDependComp(Id,NrJb,DependCompName,Active));
		fdqDepend->Next();
	}
}

void TJbDetailsManager::LoadCompanyRepresentationList(int JbNr){
	fdqRepresentation->SQL->Text = "SELECT * FROM t_jbadkierownictwo WHERE jb_nr = :JbNr";
	fdqRepresentation->ParamByName("JbNr")->AsInteger = JbNr;
	fdqRepresentation->Open();
	_JbDetailsList->CompanyRepresentationList->Clear();
	for (int i = 0; i < fdqRepresentation->RecordCount; i++) {
		int Id = fdqRepresentation->FieldByName("jb_id")->AsInteger,
			NrJb = fdqRepresentation->FieldByName("jb_nr")->AsInteger;
		String FullName = fdqRepresentation->FieldByName("jb_osoba_kier")->AsString,
				Function = fdqRepresentation->FieldByName("jb_funkcja_kier")->AsString;
		bool Active = fdqRepresentation->FieldByName("jb_aktywny")->AsBoolean;
		_JbDetailsList->CompanyRepresentationList->Add(new JbRepresentingPerson(Id,NrJb,FullName,Function,Active));
		fdqRepresentation->Next();
	}
}

void TJbDetailsManager::ParseRespond(String Respond){
	JsonParser = new TJsonParser(this,_JbNr);
	JsonParser->ParseData(Respond,_JbDetailsList);
	delete JsonParser;
}


bool TJbDetailsManager::Save(){
	bool Result = true;
	try {
		fdqPkd->Connection->TxOptions->AutoCommit = false;
		fdqPkd->Connection->StartTransaction();
		SaveCompanyPkdList();
		SaveCompanyBranchList();
		SaveCompanyDependList();
		SaveCompanyRepresentationList();
		fdqPkd->Connection->Commit();
	} catch (Exception &e) {
		fdqPkd->Connection->Rollback();
		ShowMessage (e.Message);
		Result = false;
	}
	fdqPkd->Connection->TxOptions->AutoCommit = true;
	return Result;
}
void DeActiveAll(TFDQuery *fdqTmp){
	for (int i = 0; i < fdqTmp->RecordCount; i++) {
		fdqTmp->Edit();
		fdqTmp->FieldByName("jb_aktywny")->AsBoolean = false;
		fdqTmp->Post();
		fdqTmp->Next();
	}
}

void TJbDetailsManager::SaveCompanyPkdList(){
	fdqPkd->SQL->Text = "SELECT * FROM t_jbpkd WHERE jb_nr = :JbNr";
	fdqPkd->ParamByName("JbNr")->AsInteger = _JbNr;
	fdqPkd->Open();
	DeActiveAll(fdqPkd);
	for (int i = 0; i < _JbDetailsList->CompanyPkdList->Count; i++) {
		String CompName = _JbDetailsList->CompanyPkdList->Items[i]->GetStringValue();
		if(fdqPkd->Locate("jb_pkd",CompName,TLocateOptions() << loCaseInsensitive)){
				fdqPkd->Edit();
				fdqPkd->FieldByName("jb_aktywny")->AsBoolean = _JbDetailsList->CompanyPkdList->Items[i]->Active;
				fdqPkd->Post();
		}else{
			fdqPkd->Insert();
			fdqPkd->FieldByName("jb_nr")->AsInteger = _JbNr;
			fdqPkd->FieldByName("jb_pkd")->AsString = _JbDetailsList->CompanyPkdList->Items[i]->GetStringValue();
			fdqPkd->FieldByName("jb_aktywny")->AsBoolean = _JbDetailsList->CompanyPkdList->Items[i]->Active;
			fdqPkd->Post();
		}

	}
	fdqPkd->ApplyUpdates(0);
}

void TJbDetailsManager::SaveCompanyBranchList(){
	fdqBranch->SQL->Text = "SELECT * FROM t_jboddzialy WHERE jb_nr = :JbNr";
	fdqBranch->ParamByName("JbNr")->AsInteger = _JbNr;
	fdqBranch->Open();
	DeActiveAll(fdqBranch);
	for (int i = 0; i < _JbDetailsList->CompanyBranchList->Count; i++) {
		String BranchName = _JbDetailsList->CompanyBranchList->Items[i]->GetStringValue();
		if(fdqBranch->Locate("jb_nazwa_oddzialu",BranchName,TLocateOptions() << loCaseInsensitive)){
				fdqBranch->Edit();
				fdqBranch->FieldByName("jb_aktywny")->AsBoolean = _JbDetailsList->CompanyBranchList->Items[i]->Active;
				fdqBranch->Post();
		}else{
			fdqBranch->Insert();
			fdqBranch->FieldByName("jb_nr")->AsInteger = _JbNr;
			fdqBranch->FieldByName("jb_nazwa_oddzialu")->AsString = _JbDetailsList->CompanyBranchList->Items[i]->GetStringValue();
			fdqBranch->FieldByName("jb_aktywny")->AsBoolean = _JbDetailsList->CompanyBranchList->Items[i]->Active;
			fdqBranch->Post();
		}
	}
	fdqBranch->ApplyUpdates(0);
}

void TJbDetailsManager::SaveCompanyDependList(){
	fdqDepend->SQL->Text = "SELECT * FROM t_jborganzal WHERE jb_nr = :JbNr";
	fdqDepend->ParamByName("JbNr")->AsInteger = _JbNr;
	fdqDepend->Open();
	DeActiveAll(fdqDepend);
	for (int i = 0; i < _JbDetailsList->CompanyDependList->Count; i++) {
		String CompName = _JbDetailsList->CompanyDependList->Items[i]->GetStringValue();
		if(fdqDepend->Locate("jb_nazwa_organu",CompName,TLocateOptions() << loCaseInsensitive)){
				fdqDepend->Edit();
				fdqDepend->FieldByName("jb_aktywny")->AsBoolean = _JbDetailsList->CompanyDependList->Items[i]->Active;
				fdqDepend->Post();
		}else{
			fdqDepend->Insert();
			fdqDepend->FieldByName("jb_nr")->AsInteger = _JbNr;
			fdqDepend->FieldByName("jb_nazwa_organu")->AsString = _JbDetailsList->CompanyDependList->Items[i]->GetStringValue();
			fdqDepend->FieldByName("jb_aktywny")->AsBoolean = _JbDetailsList->CompanyDependList->Items[i]->Active;
			fdqDepend->Post();
		}
	}
	fdqDepend->ApplyUpdates(0);
}

void TJbDetailsManager::SaveCompanyRepresentationList(){
	fdqRepresentation->SQL->Text = "SELECT * FROM t_jbadkierownictwo WHERE jb_nr = :JbNr";
	fdqRepresentation->ParamByName("JbNr")->AsInteger = _JbNr;
	fdqRepresentation->Open();
	DeActiveAll(fdqRepresentation);
	for (int i = 0; i < _JbDetailsList->CompanyRepresentationList->Count; i++) {
		String FullName = _JbDetailsList->CompanyRepresentationList->Items[i]->FullName;
		if(fdqRepresentation->Locate("jb_osoba_kier",FullName,TLocateOptions() << loCaseInsensitive)){
				fdqRepresentation->Edit();
				fdqRepresentation->FieldByName("jb_aktywny")->AsBoolean = _JbDetailsList->CompanyRepresentationList->Items[i]->Active;
				fdqRepresentation->FieldByName("jb_funkcja_kier")->AsString = _JbDetailsList->CompanyRepresentationList->Items[i]->Function;
				fdqRepresentation->Post();
		}else{
			fdqRepresentation->Insert();
			fdqRepresentation->FieldByName("jb_nr")->AsInteger = _JbNr;
			fdqRepresentation->FieldByName("jb_osoba_kier")->AsString = _JbDetailsList->CompanyRepresentationList->Items[i]->FullName;
			fdqRepresentation->FieldByName("jb_funkcja_kier")->AsString = _JbDetailsList->CompanyRepresentationList->Items[i]->Function;
			fdqRepresentation->FieldByName("jb_aktywny")->AsBoolean = _JbDetailsList->CompanyRepresentationList->Items[i]->Active;
			fdqRepresentation->Post();
		}
	}
	fdqRepresentation->ApplyUpdates(0);
}

