#pragma once
#include "wx/wx.h"
#include "wx/spinctrl.h"
#include <string.h>
#include "wx/dialog.h"


class cMain : public wxFrame
{
public:
	cMain();

public:
	wxSpinCtrl* m_spinX = nullptr;
	wxSpinCtrl* m_spinY = nullptr;
	wxSpinCtrl* m_spinZ = nullptr;
	wxButton* m_btn1 = nullptr;
	wxListBox* m_list1 = nullptr;
	wxButton* m_dlt1 = nullptr;
	wxButton* m_openDia1 = nullptr;
	wxDialog* m_dia1 = nullptr;
	wxChoice* m_chX = nullptr;
	wxChoice* m_chY = nullptr;
	wxChoice* m_chZ = nullptr;
	wxChoice* m_chN = nullptr;
	wxButton* m_facCrtBtn = nullptr;
	wxListBox* m_facList = nullptr;
	wxDialog* m_stldia = nullptr;
	wxStaticText* m_stlTxt = nullptr;
	wxButton* m_stlBtn = nullptr;
	

	void OnButtonClicked(wxCommandEvent& evt);
	void OnDltBtnClicked(wxCommandEvent& evt);
	void OpenDialogBtn(wxCommandEvent& evt);
	void CloseDialogBtn(wxCommandEvent& evt);
	void OpenStlExport(wxCommandEvent& evt);



	wxDECLARE_EVENT_TABLE();
};

