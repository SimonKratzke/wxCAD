#include "cMain.h"

int itemCounter = 0; //Dieser Counter muss verwendet werden, da wxWidgets/listBox anscheinend keine isEmpty() funktion besitzt.
int itemIDcounter = 0; //Dieser Counter wird dazu verendet, eine individuelle ID für jeden punkt zu erstellen. Von diesem Wert sollte nie etwas abgezogen werden!
int facCounter = 0;
int n = -1;
wxArrayString choiceArr; //dieses Array beinhaltet alle punkte und wird für die wxChoice Dinger und die Facettenliste verwendet
wxArrayString normalChoice; //dieses Array ist nicht dynamisch und beinhaltet alle möglichkeiten der Normale.
auto pointArr = new int[itemIDcounter][4]; //in diesem Array werden punkte mit ID als int gespeichert
auto facArr = new int[facCounter][10];




wxBEGIN_EVENT_TABLE(cMain, wxFrame, m_dia1)
	EVT_BUTTON(10001, OnButtonClicked)
	EVT_BUTTON(10010, OnDltBtnClicked)
	EVT_BUTTON(10011, OpenDialogBtn)
	EVT_BUTTON(10101, OpenStlExport)
	
wxEND_EVENT_TABLE()



cMain::cMain() : wxFrame(nullptr, wxID_ANY, "CADwx", wxPoint(30, 30), wxSize(800, 1000)) {
	m_spinX = new wxSpinCtrl(this, wxID_ANY, "0", wxPoint(10, 10), wxSize(150, 50), wxSP_ARROW_KEYS, 0, 10, 0, "X");
	m_spinY = new wxSpinCtrl(this, wxID_ANY, "0", wxPoint(170, 10), wxSize(150, 50), wxSP_ARROW_KEYS, 0, 10, 0, "Y");
	m_spinZ = new wxSpinCtrl(this, wxID_ANY, "0", wxPoint(330, 10), wxSize(150, 50), wxSP_ARROW_KEYS, 0, 10, 0, "Z");
	m_btn1 = new wxButton(this, 10001, "Punkt erstellen", wxPoint(490, 10), wxSize(150, 50));
	m_list1 = new wxListBox(this, wxID_ANY, wxPoint(10, 70), wxSize(300, 300));
	m_dlt1 = new wxButton(this, 10010, "Punkt entfernen", wxPoint(330, 70), wxSize(150, 50));
	m_openDia1 = new wxButton(this, 10011, "Dreiecksfacette erstellen", wxPoint(330, 130), wxSize(200, 50));
	m_dia1 = new wxDialog(this, wxID_ANY, "Facette", wxPoint(10, 10), wxSize(500, 500), wxDEFAULT_DIALOG_STYLE, "Test?");
	m_chX = new wxChoice(m_dia1, wxID_ANY, wxPoint(10, 10), wxSize(150, 50), 0, NULL, 0, wxDefaultValidator, "ChoiceX");
	m_chY = new wxChoice(m_dia1, wxID_ANY, wxPoint(10, 70), wxSize(150, 50), 0, NULL, 0, wxDefaultValidator, "ChoiceY");
	m_chZ = new wxChoice(m_dia1, wxID_ANY, wxPoint(10, 130), wxSize(150, 50), 0, NULL, 0, wxDefaultValidator, "ChoiceZ");
	m_chN = new wxChoice(m_dia1, wxID_ANY, wxPoint(10, 190), wxSize(150, 50), 0, NULL, 0, wxDefaultValidator, "ChoiceN");
	m_facCrtBtn = new wxButton(m_dia1, 10100, "Facette hinzufügen",wxPoint(10, 250), wxSize(200, 50));
	m_facList = new wxListBox(this, wxID_ANY, wxPoint(10, 380), wxSize(500, 300));
	m_stlBtn = new wxButton(this, 10101, ".Stl Export", wxPoint(330, 190), wxSize(150, 50));
	m_stldia = new wxDialog(this, wxID_ANY, "Stl Kopieren:", wxPoint(10, 10), wxSize(500, 500), wxDEFAULT_DIALOG_STYLE, "Test?");
	m_stlTxt = new wxStaticText(m_stldia, wxID_ANY, "", wxPoint(10, 10), wxSize(300, 300), 0, "Test?");
	
	
	m_facCrtBtn->Bind(wxEVT_BUTTON, &cMain::CloseDialogBtn, this);
}


void cMain::OnButtonClicked(wxCommandEvent& evt) {
	m_list1->AppendString(_("#") + _(wxString::Format(wxT("%i"), itemIDcounter)) + _(" ") + _(wxString::Format(wxT("%i"), m_spinX->GetValue())) + _(", ") + _(wxString::Format(wxT("%i"), m_spinY->GetValue())) + _(", ") + _(wxString::Format(wxT("%i"), m_spinZ->GetValue())) + _(", "));
	pointArr[itemCounter][0] = itemIDcounter;
	pointArr[itemCounter][1] = m_spinX->GetValue();
	pointArr[itemCounter][2] = m_spinY->GetValue();
	pointArr[itemCounter][3] = m_spinZ->GetValue();
	itemIDcounter++;
	itemCounter++;
	evt.Skip();
}

void cMain::OnDltBtnClicked(wxCommandEvent& evt) {
	if (itemCounter > 0 && m_list1->GetSelection() != -1) { // anscheinend ist GetSelected bei -1 wenn nichts ausgewählt ist.
		m_list1->Delete(m_list1->GetSelection());
		itemCounter--;
	}
	evt.Skip();
}

void cMain::OpenDialogBtn(wxCommandEvent& evt) {
	for (int i = 0; i < itemCounter; i++)
	{
		choiceArr.Add(m_list1->GetString(i));
	}
	normalChoice.Add("X+");		// Das Array bitte noch anders befüllen - Danke im voraus
	normalChoice.Add("X-");		// "
	normalChoice.Add("Y+");		// "
	normalChoice.Add("Y-");		// "
	normalChoice.Add("Z+");		// "
	normalChoice.Add("Z-");		// "


	m_chX->Append(choiceArr);
	m_chY->Append(choiceArr);
	m_chZ->Append(choiceArr);
	m_chN->Append(normalChoice);
	m_dia1->ShowModal();
	evt.Skip();
}


void cMain::CloseDialogBtn(wxCommandEvent& evt) {
	if (m_chX->GetSelection() != wxNOT_FOUND && m_chY->GetSelection() != wxNOT_FOUND && m_chZ->GetSelection() != wxNOT_FOUND) {
		m_facList->AppendString(wxString(_(choiceArr[m_chX->GetSelection()])) + _ (" | ") + _(choiceArr[m_chY->GetSelection()]) + _(" | ") + _(choiceArr[m_chZ->GetSelection()])+ _ ("   N=") + _(normalChoice[m_chN->GetSelection()]));

		switch (m_chN->GetSelection())
		{
			case 0:
				n = 0;
				break;
			case 1:
				n = 1;
				break;
			case 2:
				n = 2;
				break;
			case 3:
				n = 3;
				break;
			case 4:
				n = 4;
				break;
			case 5:
				n = 5;
				break;
		}

		facArr[facCounter][0] = n;
	}
	m_dia1->EndModal(0);
	m_chX->Clear();
	m_chY->Clear();
	m_chZ->Clear();
	m_chN->Clear();
	facCounter++;
	evt.Skip();
}

void cMain::OpenStlExport(wxCommandEvent& evt) {
	m_stldia->Show();
	
}