﻿//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "uJsonParser.h"
#include "uConnectionManager.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TJsonParser *JsonParser;
//---------------------------------------------------------------------------
__fastcall TJsonParser::TJsonParser(TComponent* Owner, int JbNr)
	: TForm(Owner)
{
	_JbNr = JbNr;  //jb_nr
}

//---------------------------------------------------------------------------

bool TJsonParser::ParseData(String Respond, JbDetailsList * TMP_DetList){
	_JbNr = TMP_DetList->JbNr;
	bool Result = true;
	try {
		TJSONObject *krsObjectMain = (TJSONObject*) TJSONObject::ParseJSONValue(Respond);
		TJSONObject *krsObjDetails = (TJSONObject*) krsObjectMain->GetValue("layers");
		TJSONArray 	*ProfileArray = (TJSONArray*) krsObjDetails->Get("dzialalnosci")->JsonValue;
		TJSONArray 	*CompanyArray = (TJSONArray*) krsObjDetails->Get("firmy")->JsonValue;
		TJSONArray 	*RepresentationArray = (TJSONArray*) krsObjDetails->Get("reprezentacja")->JsonValue;
		TJSONArray 	*BranchesArray = (TJSONArray*) krsObjDetails->Get("oddzialy")->JsonValue;

		//profile dzialanosci (pkd)
		TMP_DetList->CompanyPkdList->Clear();
		for (int i = 0; i < ProfileArray->Count; i++) {
		   TJSONObject *profile = (TJSONObject*) ProfileArray->Items[i];
		   String Pkd = profile->GetValue("str")->Value();
		   TMP_DetList->CompanyPkdList->Add(new JbPkd(0,_JbNr,Pkd,true));
		}


		 //firme powiązane (zależne)
		TMP_DetList->CompanyDependList->Clear();
		for (int i = 0; i < CompanyArray->Count; i++) {
		   TJSONObject *company = (TJSONObject*) CompanyArray->Items[i];
		   String CompName = company->GetValue("nazwa")->Value();
		   TMP_DetList->CompanyDependList->Add(new JbDependComp(0,_JbNr,CompName,true));
		}


		 //reprezentacja z funkcjami
		TMP_DetList->CompanyRepresentationList->Clear();
		for (int i = 0; i < RepresentationArray->Count; i++) {
		   TJSONObject *person = (TJSONObject*) RepresentationArray->Items[i];
		   String Name = person->GetValue("nazwa")->Value(),
				  Function = person->GetValue("funkcja")->Value();
		   TMP_DetList->CompanyRepresentationList->Add(new JbRepresentingPerson(0,_JbNr,Name,Function,true));
		}


		 //oddzialy
		TMP_DetList->CompanyBranchList->Clear();
		for (int i = 0; i < BranchesArray->Count; i++) {
		   TJSONObject *branch = (TJSONObject*) BranchesArray->Items[i];
		   String BranchName = branch->GetValue("nazwa")->Value();
		   TMP_DetList->CompanyBranchList->Add(new JbBranch(0,_JbNr,BranchName,true));
		}

		 krsObjectMain->Free();
	} catch (Exception &e) {
		ShowMessage(e.Message);
		Result = false;
	}
	return Result;
}



 /*
bool TJsonParser::SaveToDatabase(){
	bool Result = true;
	try {
		fdqSave->Connection->TxOptions->AutoCommit = false;
		fdqSave->Connection->StartTransaction();
		SaveCompanyProfileList(_CompanyProfiles);
		SavecompanyDependList(_DependentCompany);
		SaveCompanyRepresentation(_Persons);
		SaveCompanyBranches(_Branches);
		fdqSave->Connection->Commit();
		fdqSave->Connection->TxOptions->AutoCommit = true;
	} catch (Exception &e) {
		fdqSave->Connection->Rollback();
		ShowMessage(e.Message);
		Result = false;
	}
	fdqSave->Connection->TxOptions->AutoCommit = true;
	return Result;
}

void TJsonParser::SaveCompanyProfileList(TStringList * CompProfiles){
	String Query = "INSERT INTO public.t_jbpkd (jb_nr, jb_pkd) VALUES (:AuditId, :Pkd)";
	for (int i = 0; i < CompProfiles->Count; i++) {
		fdqSave->SQL->Text = Query;
		fdqSave->ParamByName("AuditId")->AsInteger = _AuditId;
		fdqSave->ParamByName("Pkd")->AsString = CompProfiles->Strings[i];
		fdqSave->ExecSQL();
	}
}
void TJsonParser::SavecompanyDependList(TStringList * CompDepend){
	String Query = "INSERT INTO public.t_jborganzal (jb_nazwa_organu, jb_nr) VALUES (:CompName, :AuditId)";
	for (int i = 0; i < CompDepend->Count; i++) {
		fdqSave->SQL->Text = Query;
		fdqSave->ParamByName("CompName")->AsString = CompDepend->Strings[i];
		fdqSave->ParamByName("AuditId")->AsInteger = _AuditId;
		fdqSave->ExecSQL();
	}
}
void TJsonParser::SaveCompanyRepresentation(std::vector<Person*> Persons){
	String Query = "INSERT INTO public.t_jbadkierownictwo (jb_osoba_kier, jb_funkcja_kier, jb_nr) VALUES (:PersonName, :PersonFunction, :AuditId)";
	for (int i = 0; i < Persons.size(); i++) {
		fdqSave->SQL->Text = Query;
		fdqSave->ParamByName("PersonName")->AsString = Persons[i]->FullName;
		fdqSave->ParamByName("PersonFunction")->AsString = Persons[i]->Function;
		fdqSave->ParamByName("AuditId")->AsInteger = _AuditId;
		fdqSave->ExecSQL();
	}
}
void TJsonParser::SaveCompanyBranches(TStringList * CompBranches){
	String Query = "INSERT INTO public.t_jboddzialy (jb_nazwa_oddzialu, jb_nr) VALUES (:BranchName, :AuditId)";
	for (int i = 0; i < CompBranches->Count; i++) {
		fdqSave->SQL->Text = Query;
		fdqSave->ParamByName("BranchName")->AsString = CompBranches->Strings[i];
		fdqSave->ParamByName("AuditId")->AsInteger = _AuditId;
		fdqSave->ExecSQL();
	}
}
  */

