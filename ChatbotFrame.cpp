#include "ChatbotFrame.h"
#include <string>
#include <iostream>
#include <string>
#include <fstream>
#include<vector>
#include<time.h>

using namespace std;




class Paragraph {
public:
    string text, file;
    int score, no;

    Paragraph() {
        text = "";
        file = "";
        score = -1;
        no = -1;
    }

    Paragraph(string _text, string _file, int _score, int _no) {
        text = _text;
        score = _score;
        no = _no;
        file = _file;
    }
};

int countWordInText(string text, string word) {
    int i = 0, j, ok, score = 0;
    for (i = 0; i < text.length(); i++) {
        if (text[i] == '   ' || text[i] == ' ' || i == 0) {
            if (i != 0) i++;
            j = i;
            ok = 1;
            while (text[i] != '   ' && text[i] != ' ') {
                if (text[i] != word[i - j] && tolower(text[i]) != word[i - j]) {
                    if (word[i - j] != '\0') {
                        ok = 0;
                        break;
                    }
                    else break;
                }
                i++;
            }
            if (ok) score++;
        }
    }
    return score;
}


void splitTextIntoParagraphs(string text, string file, Paragraph paragraphs[], int& n) {
    string temp = "";
    for (int i = 0; i < text.length(); i++) {
        while (!(text[i] == '\n' && text[i + 1] == ' ') && i < text.length()) {
            temp += text[i];
            i++;
        }
        paragraphs[n] = Paragraph(temp, file, 0, n);
        n++;
        temp = "";
    }
}


void scoreParagraphs(Paragraph paragraphs[], int n, vector<string> words) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < words.size(); j++) {
            paragraphs[i].score += countWordInText(paragraphs[i].text, words[j]) - 2;
        }
    }
    for (int i = 0; i < n; i++)
        for (int j = i; j < n; j++) {
            if (paragraphs[i].score < paragraphs[j].score)
                swap(paragraphs[i], paragraphs[j]);
        }
}

string showParagraphs(Paragraph paragraphs[], int n) {
    string answer = "";
    for (int i = 0; i < 10; i++)
        if (paragraphs[i].score > 0) {
            answer += paragraphs[i].text + "\nMatches: " + to_string(paragraphs[i].score) + " Source: " + paragraphs[i].file + " Paragraph number: " + to_string(paragraphs[i].no + 1) + "\n\n\n";
        }
    return answer;
}

int random(int n) {
    srand(time(NULL));
    return rand() % n;
}
//--------------------------------------------------------------------------------------------------------------



string findLearningSources() {
    string answer = "1. Introduction\n2. Bioprocess Control Statement\n3. Bioprocess Intelligent Control";
    return answer;
}
//--------------------------------------------------------------------------------------------------------------


string openFile(string input) {
    ifstream file(input + ".txt");
    string answer((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
    return answer;
}
//--------------------------------------------------------------------------------------------------------------



string searchFor(string input) {
    string answer;

    vector<string> words;
    int n, i = 0;
    Paragraph paragraphs[100];
    splitTextIntoParagraphs(openFile("introduction"), "introduction", paragraphs, n);
    splitTextIntoParagraphs(openFile("bioprocess_control_statement"), "bioprocess_control_statement", paragraphs, n);
    splitTextIntoParagraphs(openFile("bioprocess_intelligent_control"), "bioprocess_intelligent_control", paragraphs, n);
    string temp = "";
    for (int i = 0; i <= input.length(); i++) {
        if (input[i] != ' ' && input[i] != '\0')
            temp += input[i];
        else {
            words.push_back(temp);
            temp = "";
        }
    }

    for (int i = 0; i < words.size(); i++) {
        
        
        scoreParagraphs(paragraphs, n, words);
        answer += showParagraphs(paragraphs, n);
        return answer;
    }
}





//--------------------------------------------------------------------------------------------------------------




string feelingLucky() {
    Paragraph paragraphs[100];
    string answer = "";
    int i, n = 0;
    splitTextIntoParagraphs(openFile("introduction"), "introduction", paragraphs, n);
    splitTextIntoParagraphs(openFile("bioprocess_control_statement"), "bioprocess_control_statement", paragraphs, n);
    splitTextIntoParagraphs(openFile("bioprocess_intellgent_control"), "bioprocess_intelligent_control", paragraphs, n);
    i = random(n);
    answer += paragraphs[i].text + "\n\nSource: " + paragraphs[i].file + " Paragraph Number: " + to_string(paragraphs[i].no + 1) + "\n";
    return answer;
}


//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

enum
{
	ID_BUTTON_ANSWERS = wxID_LAST+1,
	ID_BUTTON_QUESTIONS,
	ID_BUTTON_CHATBOT_ASK,
    ID_BUTTON_HELP,
	ID_BUTTON_RESET_HISTORY,
	ID_USER_INPUT,
	ID_CHATBOT_ANSWER ,
	ID_BUTTON_LUCKY,
	ID_ABOUT,
};

ChatbotFrame::ChatbotFrame() : wxFrame(nullptr, wxID_ANY, "Chatbot", wxPoint(450,200),wxSize(500,550))
{
	chatbot_answer = new wxTextCtrl(this, ID_CHATBOT_ANSWER, wxEmptyString, wxPoint(10,110), wxDefaultSize, wxTE_READONLY | wxTE_MULTILINE);
	chatbot_answer->SetBackgroundColour(wxColour(200, 200, 200));
	
	user_input_text = new wxTextCtrl(this, ID_USER_INPUT,wxEmptyString, wxDefaultPosition,wxDefaultSize, wxTE_LEFT | wxTE_PROCESS_ENTER | wxTE_NO_VSCROLL);
	
	user_input_select = new wxComboBox(this, ID_USER_INPUT, "Choose", wxDefaultPosition, wxDefaultSize, wxArrayString(), wxCB_READONLY);

	user_input_select->Append(_T("Show learning sources"));
	user_input_select->Append(_T("Open file:"));
	user_input_select->Append(_T("Tell me something about:"));
	

	sizer_vertical_box = new wxBoxSizer(wxVERTICAL);
	
	auto sizer_user_input = new wxBoxSizer(wxHORIZONTAL);
	sizer_user_input->Add(user_input_select,1, wxEXPAND  | wxLEFT | wxBOTTOM, 6);
	sizer_user_input->AddSpacer(1);
	sizer_user_input->Add(user_input_text, 1, wxEXPAND | wxRIGHT | wxBOTTOM, 6);


	sizer_vertical_box->Add(chatbot_answer, 1, wxEXPAND | wxLEFT | wxTOP | wxRIGHT, 6);
	sizer_vertical_box->AddSpacer(1);
	sizer_vertical_box->Add(sizer_user_input);

	panel_right = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(150, 100));
	panel_right->SetBackgroundColour(wxColour(200, 200, 200));
	

	auto button_lucky = new wxButton(panel_right, ID_BUTTON_LUCKY, "I'm feeling lucky",wxDefaultPosition, wxSize(150,30));
	//auto button_chatbot_ask = new wxButton(panel_right, ID_BUTTON_CHATBOT_ASK, "Chatbot will ask you",wxPoint(0,30), wxSize(150,30));
	auto button_answers = new wxButton(panel_right, ID_BUTTON_ANSWERS, "Answers history", wxPoint(0,30), wxSize(150,30));
	auto button_questions = new wxButton(panel_right, ID_BUTTON_QUESTIONS, "Questions history", wxPoint(0,60), wxSize(150,30));
	auto button_reset_history= new wxButton(panel_right, ID_BUTTON_RESET_HISTORY, "Reset history", wxPoint(0,90), wxSize(150,30));
	auto button_help = new wxButton(panel_right, ID_BUTTON_HELP, "Help", wxPoint(0,120), wxSize(150,30));


	sizer_horizontal_box = new wxBoxSizer(wxHORIZONTAL);
	sizer_horizontal_box->Add(sizer_vertical_box,1, wxEXPAND);
	sizer_horizontal_box->Add(panel_right, 0, wxEXPAND | wxBOTTOM| wxTOP| wxRIGHT, 6);
	this->SetSizer(sizer_horizontal_box);

	wxMenu* menuOptions = new wxMenu;
	menuOptions->Append(wxID_ABOUT, "About");
	menuOptions->Append(wxID_EXIT, "Exit");

	wxMenuBar* menuBar = new wxMenuBar;
	menuBar->Append(menuOptions, "Options");
	

	SetMenuBar(menuBar);
	CreateStatusBar();

	onAnswers = new wxDialog(this, ID_BUTTON_ANSWERS, _T("Answers history"), wxPoint(450,200), wxSize(500,450));
	onQuestion = new wxDialog(this, ID_BUTTON_QUESTIONS, _T("Questions history"), wxPoint(450, 200));
	answers_given = new wxTextCtrl(onAnswers, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY | wxTE_MULTILINE);
	answers_given->SetBackgroundColour(wxColour(200, 200, 200));
	questions_asked = new wxTextCtrl(onQuestion, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY | wxTE_MULTILINE);
	questions_asked->SetBackgroundColour(wxColour(200, 200, 200));

	//Bind(wxEVT_BUTTON, &ChatbotFrame::ButtonChatbotAsk, this, ID_BUTTON_CHATBOT_ASK);
	Bind(wxEVT_BUTTON, &ChatbotFrame::ButtonLucky, this, ID_BUTTON_LUCKY);
	Bind(wxEVT_BUTTON, &ChatbotFrame::ButtonAnswers, this, ID_BUTTON_ANSWERS);
	Bind(wxEVT_BUTTON, &ChatbotFrame::ButtonQuestions, this, ID_BUTTON_QUESTIONS);
	Bind(wxEVT_BUTTON, &ChatbotFrame::ButtonResetHistory, this, ID_BUTTON_RESET_HISTORY);
	Bind(wxEVT_BUTTON, &ChatbotFrame::ButtonHelp, this, ID_BUTTON_HELP);
	Bind(wxEVT_MENU, &ChatbotFrame::OnExit, this, wxID_EXIT);
	Bind(wxEVT_MENU, &ChatbotFrame::OnAbout, this, wxID_ABOUT);
	Bind(wxEVT_COMMAND_TEXT_ENTER, &ChatbotFrame::UserInput, this, ID_USER_INPUT);
}

void ChatbotFrame::UserInput(wxCommandEvent& event)
{
	int user_selection_id = user_input_select->GetCurrentSelection();
    wxString answer;

    chatbot_answer->Clear();
    chatbot_answer->AppendText("YOUR RESULT IS BELOW:\n");
    if (user_selection_id == 0)
    {
        answer = findLearningSources();
        chatbot_answer->AppendText(answer);
        chatbot_answer->AppendText("\n");
    }

    if (user_selection_id == 1)
    {
        answer = openFile(event.GetString().ToStdString());
        chatbot_answer->AppendText(answer);
    }

    if (user_selection_id == 2)
    {
        answer = searchFor(event.GetString().ToStdString());
        chatbot_answer->AppendText(answer);
    }

    answers_given->AppendText(answer);
    answers_given->AppendText("\n");
    questions_asked->AppendText(user_input_select->GetValue() + _T(" ") + event.GetString());
    questions_asked->AppendText("\n");
}

void ChatbotFrame::ButtonLucky(wxCommandEvent& event)
{
	
    chatbot_answer->Clear();
    chatbot_answer->AppendText("YOUR RESULT IS BELOW:\n");
    wxString answer = feelingLucky();
	chatbot_answer->AppendText(answer);
	answers_given->AppendText(answer + "\n");
}

void ChatbotFrame::ButtonChatbotAsk(wxCommandEvent& WXUNUSED(event))
{
    chatbot_answer->Clear();
}


void ChatbotFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
	//informatii despre proiect/aplicatie
	wxDialog onAboutInfo(this, wxID_ABOUT, _T("Informations"),wxDefaultPosition, wxDefaultSize);
	auto text_about = new wxTextCtrl(&onAboutInfo, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY | wxTE_MULTILINE);
	text_about->SetBackgroundColour(wxColour(200, 200, 200));
	text_about->AppendText(_T("Version: 1.0\n"));
	text_about->AppendText(_T("Authos:\n"));
	text_about->AppendText(_T("Marina Stefan\n"));
	text_about->AppendText(_T("Spoiala Andrei-Cristian\n"));
	text_about->AppendText(_T("Toma Bogdan-Gabriel\n"));
	text_about->AppendText(_T("Zareey-Golmeli Shahin-Eduard\n"));
	//text_about->Clear();
	onAboutInfo.ShowModal();
	
}

void ChatbotFrame::OnExit(wxCommandEvent& WXUNUSED(event))
{
	int ans = wxMessageBox("Are you sure you want to close the program? Chatbot will miss you...", "Close Chatbot", wxYES_NO);
	if (ans == wxYES)
		Close();
}

void ChatbotFrame::ButtonAnswers(wxCommandEvent& WXUNUSED(event))
{
	onAnswers->ShowModal();

}
void ChatbotFrame::ButtonQuestions(wxCommandEvent& WXUNUSED(event))
{
	onQuestion->ShowModal();

}

void ChatbotFrame::ButtonResetHistory(wxCommandEvent& WXUNUSED(event))
{
	answers_given->Clear();
	questions_asked->Clear();
}

void ChatbotFrame::ButtonHelp(wxCommandEvent& WXUNUSED(event))
{
    chatbot_answer->Clear();
    chatbot_answer->AppendText("Next to the input box is the menu with the available commands.\nIn the right pane are shortcuts to predefined commands. To use them you have to left click on the corresponding button.\nIn the input box enter what you are interested in based on the menu commands.\n");
}

ChatbotFrame::~ChatbotFrame(){}
