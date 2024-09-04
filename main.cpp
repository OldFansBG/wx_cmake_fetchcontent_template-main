#include <wx/wx.h>
#include <wx/filedlg.h>
#include "extractor.h"

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString &title);

private:
    void OnBrowse(wxCommandEvent &event);

    wxDECLARE_EVENT_TABLE();
};

enum
{
    ID_Browse = 1
};

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_BUTTON(ID_Browse, MyFrame::OnBrowse)
        wxEND_EVENT_TABLE()

            wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame("ISO File Browser");
    frame->Show(true);
    return true;
}

MyFrame::MyFrame(const wxString &title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(400, 300))
{
    wxPanel *panel = new wxPanel(this, -1);

    wxButton *browseButton = new wxButton(panel, ID_Browse, wxT("Browse ISO Files"),
                                          wxPoint(20, 20), wxSize(150, 30));
}

void MyFrame::OnBrowse(wxCommandEvent &event)
{
    wxFileDialog openFileDialog(this, _("Open ISO file"), "", "",
                                "ISO files (*.iso)|*.iso", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return; // the user changed their mind

    // Get the path of the selected ISO file
    wxString isoFilePath = openFileDialog.GetPath();
    wxMessageBox("You selected: " + isoFilePath, "Info", wxOK | wxICON_INFORMATION);

    // Extract ISO file
    // Assume the output directory is a fixed path for this example
    std::string outputFolderPath = "extracted_files";
    ISOExtractor extractor;

    if (!extractor.extractISO(isoFilePath.ToStdString(), outputFolderPath))
    {
        wxMessageBox("Failed to extract ISO file.", "Error", wxOK | wxICON_ERROR);
    }
    else
    {
        wxMessageBox("ISO extracted successfully!", "Success", wxOK | wxICON_INFORMATION);
    }
}