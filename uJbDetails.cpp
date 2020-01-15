//---------------------------------------------------------------------------

#pragma hdrstop

#include "uJbDetails.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

//-----------------------------------------------------------

//jb pkd
JbPkd::JbPkd(int Id, int NrJb, String Pkd, bool Active){
	JbPkd::_Id = Id;
	JbPkd::_NrJb = NrJb;
	JbPkd::_Pkd = Pkd;
	JbPkd::_Active = Active;
}

String JbPkd::GetStringValue(){
	return JbPkd::_Pkd;
}
//-------------------------------------------------------------

//jb oddzialy
JbBranch::JbBranch(int Id, int NrJb, String BranchName, bool Active){
	JbBranch::_Id = Id;
	JbBranch::_NrJb = NrJb;
	JbBranch::_BranchName = BranchName;
	JbBranch::_Active = Active;
}

String JbBranch::GetStringValue(){
	return JbBranch::_BranchName;
}
//-------------------------------------------------------------

//jb oragnizacje zalezne
JbDependComp::JbDependComp(int Id, int NrJb, String DepCompName, bool Active){
	JbDependComp::_Id = Id;
	JbDependComp::_NrJb = NrJb;
	JbDependComp::_DepCompName = DepCompName;
	JbDependComp::_Active = Active;
}

String JbDependComp::GetStringValue(){
	return _DepCompName;
}
//-------------------------------------------------------------

//jb reprezentacja
JbRepresentingPerson::JbRepresentingPerson(int Id, int NrJb, String FullName, String Function, bool Active){
	JbRepresentingPerson::_Id = Id;
	JbRepresentingPerson::_NrJb = NrJb;
	JbRepresentingPerson::_FullName = FullName;
	JbRepresentingPerson::_Function = Function;
	JbRepresentingPerson::_Active = Active;
}

String JbRepresentingPerson::GetStringValue(){
	return JbRepresentingPerson::_FullName + " - " + JbRepresentingPerson::_Function;
}
//-------------------------------------------------------------
//funckje glownej klasy
JbDetailsList::JbDetailsList(int JbNr){
	JbDetailsList::_JbNr = JbNr;
	JbDetailsList::_CompanyPkdList = new JbDetailsContainer<JbPkd*>();
	JbDetailsList::_CompanyBranchList = new JbDetailsContainer<JbBranch*>();
	JbDetailsList::_CompanyDependList = new JbDetailsContainer<JbDependComp*>;
	JbDetailsList::_CompanyRepresentationList = new JbDetailsContainer<JbRepresentingPerson*>;
}
JbDetailsList::~JbDetailsList(){
	delete JbDetailsList::_CompanyPkdList;
	delete JbDetailsList::_CompanyBranchList;
	delete JbDetailsList::_CompanyDependList;
	delete JbDetailsList::_CompanyRepresentationList;
}

