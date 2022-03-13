#pragma once

#include <wx/wx.h>

class ChatbotFrame : public wxFrame
{
public:
	ChatbotFrame();
	void ButtonChatbotAsk(wxCommandEvent&);
	void ButtonResetHistory(wxCommandEvent& );
	void OnExit(wxCommandEvent& );
	void OnAbout(wxCommandEvent& );
	void ButtonAnswers(wxCommandEvent& );
	void ButtonQuestions(wxCommandEvent& );
	/*void OnEnter(wxCommandEvent& );*/
	void UserInput(wxCommandEvent& );
	void ButtonLucky(wxCommandEvent& );
	void ButtonHelp(wxCommandEvent& );
	wxString var_wxString;
	~ChatbotFrame();
	//DECLARE_EVENT_TABLE();
public:
	wxTextCtrl* user_input_text = nullptr;
	wxTextCtrl* chatbot_answer = nullptr;
	wxTextCtrl* answers_given = nullptr;
	wxTextCtrl* questions_asked = nullptr;
	wxBoxSizer* sizer_vertical_box = nullptr;
	wxBoxSizer* sizer_horizontal_box = nullptr;
	wxPanel* panel_left = nullptr;
	wxPanel* panel_right = nullptr;
	wxComboBox* user_input_select = nullptr;
	wxDialog* onAnswers = nullptr;
	wxDialog* onQuestion = nullptr;
};

