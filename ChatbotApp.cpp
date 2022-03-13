#include "ChatbotApp.h"

wxIMPLEMENT_APP(ChatbotApp);

bool ChatbotApp::OnInit()
{
	m_frame0 = new ChatbotFrame();
	m_frame0->Show(true);
	return true;
}