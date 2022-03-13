#pragma once

#include <wx/aboutdlg.h>
#include <wx/wx.h>
#include "ChatbotFrame.h"

class ChatbotApp : public wxApp
{
public:
	virtual bool OnInit();
private:
	ChatbotFrame* m_frame0 = nullptr;
};

