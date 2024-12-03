#include "../libs/vigenere.h"
#include <functional>
#include <thread>
#include <vector>
#include <wx/wx.h>
#include "../libs/playfair.h"

//TODO:: Add Playfair radio button;
//TODO:: Add Playfair Functionality;
class VigenereUI : public wxApp {
public:
  virtual bool OnInit();
};

class MyFrame : public wxFrame {
public:
  MyFrame(const wxString &title);

private:
  void VigenereOnEncrypt(wxCommandEvent &event);
  void VigenereOnDecrypt(wxCommandEvent &event);
  void OnClear(wxCommandEvent &event);

  wxTextCtrl *keyInput;
  wxTextCtrl *textInput;
  wxTextCtrl *resultOutput;

  wxDECLARE_EVENT_TABLE();
};

enum { ID_Encrypt = 1, ID_Decrypt = 2 };

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame) EVT_BUTTON(ID_Encrypt, MyFrame::VigenereOnEncrypt)
    EVT_BUTTON(ID_Decrypt, MyFrame::VigenereOnDecrypt)
        EVT_BUTTON(wxID_ANY, MyFrame::OnClear) wxEND_EVENT_TABLE()

            wxIMPLEMENT_APP(VigenereUI);

bool VigenereUI::OnInit() {
  MyFrame *frame = new MyFrame("Vigenere Cipher App");
  frame->Show(true);
  return true;
}

MyFrame::MyFrame(const wxString &title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(500, 400)) {
  wxPanel *panel = new wxPanel(this, wxID_ANY);

  wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
  wxGridSizer *gridsizer = new wxGridSizer(2,2,5,5);

  wxStaticText *keyLabel = new wxStaticText(panel, wxID_ANY, "Key:");
  keyInput = new wxTextCtrl(panel, wxID_ANY);
  wxStaticText *textLabel = new wxStaticText(panel, wxID_ANY, "Text:");
  textInput = new wxTextCtrl(panel, wxID_ANY);
  wxStaticText *resultLabel = new wxStaticText(panel, wxID_ANY, "Result:");
  resultOutput = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition,
                                wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY);

  wxButton *encryptButton = new wxButton(panel, ID_Encrypt, "Encrypt");
  wxButton *decryptButton = new wxButton(panel, ID_Decrypt, "Decrypt");
  wxButton *clearButton = new wxButton(panel, wxID_ANY, "Clear");

  //this adds the elements to the grid instance running on top of the frame

  vbox->Add(keyLabel, 0, wxEXPAND | wxALL, 10);
  vbox->Add(keyInput, 0, wxEXPAND | wxALL, 10);
  vbox->Add(textLabel, 0, wxEXPAND | wxALL, 10);
  vbox->Add(textInput, 0, wxEXPAND | wxALL, 10);
  gridsizer->Add(encryptButton, 0, wxEXPAND);
  gridsizer->Add(decryptButton, 0, wxEXPAND);
  gridsizer->Add(clearButton, 0, wxEXPAND);
  vbox->Add(gridsizer,0,wxEXPAND|wxALL,10);
  vbox->Add(resultLabel, 0, wxEXPAND | wxALL, 10);
  vbox->Add(resultOutput, 1, wxEXPAND | wxALL, 10);

  panel->SetSizer(vbox);
}

void MyFrame::OnClear(wxCommandEvent &event) {
  keyInput->SetValue("");
  textInput->SetValue("");
  resultOutput->SetValue("");
}

void MyFrame::VigenereOnEncrypt(wxCommandEvent &event) {
  std::string key = std::string(keyInput->GetValue().mb_str());
  std::string text = std::string(textInput->GetValue().mb_str());

  // Create pairs and process text
  VEC_OF_PAIRS pairs = generate_pairs(key, text);
  int mid = pairs.size() / 2;

  std::vector<char> thread1Result, thread2Result;
  std::thread t1(encrypt_parallel, 0, mid, std::ref(pairs),
                 std::ref(thread1Result));
  std::thread t2(encrypt_parallel, mid, pairs.size(), std::ref(pairs),
                 std::ref(thread2Result));
  t1.join();
  t2.join();

  // Combine results
  std::vector<char> result(thread1Result.begin(), thread1Result.end());
  result.insert(result.end(), thread2Result.begin(), thread2Result.end());

  // Display the result
  resultOutput->SetValue(wxString(std::string(result.begin(), result.end())));
}

void MyFrame::VigenereOnDecrypt(wxCommandEvent &event) {
  std::string key = std::string(keyInput->GetValue().mb_str());
  std::string text = std::string(textInput->GetValue().mb_str());

  // Create pairs and process text
  VEC_OF_PAIRS pairs = generate_pairs(key, text);
  int mid = pairs.size() / 2;

  std::vector<char> thread1Result, thread2Result;
  std::thread t1(decrypt_parallel, 0, mid, std::ref(pairs),
                 std::ref(thread1Result));
  std::thread t2(decrypt_parallel, mid, pairs.size(), std::ref(pairs),
                 std::ref(thread2Result));
  t1.join();
  t2.join();

  // Combine results
  std::vector<char> result(thread1Result.begin(), thread1Result.end());
  result.insert(result.end(), thread2Result.begin(), thread2Result.end());

  // Display the result
  resultOutput->SetValue(wxString(std::string(result.begin(), result.end())));
}
