//The MIT License(MIT)
//
//Copyright(c) 2016 R-CO
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files(the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions :
//
//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.
/**
*** Author: R-CO
*** Mail: daniel1820kobe@gmail.com
*** Date: 2016-01-27
***/
#include "srt_editor_main_frame.h"

#include <wx/ffile.h>
#include <wx/filedlg.h>
#include <wx/log.h>
#include <wx/msgdlg.h>
#include <wx/regex.h>
#include <wx/string.h>

namespace rco {

SrtEditorMainFrame::SrtEditorMainFrame(wxWindow* parent)
  :
  SrtEditorMainFrameBase(parent),
  file_buffer_(new(std::nothrow) wxString)
{

}

void SrtEditorMainFrame::open_file_menuItem_OnMenuSelection(wxCommandEvent& event)
{
  wxFileDialog
    openFileDialog(this, _("Open srt file"), "", "",
                   "srt files (*.srt)|*.srt", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
  if (openFileDialog.ShowModal() == wxID_CANCEL) {
    return;
  }
  wxFFile input_file(openFileDialog.GetPath());
  if (!input_file.IsOpened()) {
    wxLogError("Cannot open file '%s'.", openFileDialog.GetPath());
    return;
  }

  input_file.ReadAll(file_buffer_.get());
  if (srt_file_content.ParseSrtFile(*file_buffer_) == false) {
    wxMessageBox(_("Can not parse the file!"));
  }
}

void SrtEditorMainFrame::save_file_menuItem_OnMenuSelection(wxCommandEvent& event)
{
  if (srt_file_content.IsOk() == true) {
    wxFileDialog 
      saveFileDialog(this, _("Save srt file"), "", "",
                     "srt files (*.srt)|*.srt", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    if (saveFileDialog.ShowModal() == wxID_CANCEL) {
      return;
    }
    
    if (srt_file_content.SaveToFile(saveFileDialog.GetPath()) == false) {
      wxLogError("Cannot save current contents in file '%s'.", saveFileDialog.GetPath());
      return;
    }
  } else {
    wxMessageBox(_("Please open a *.srt file first."));
  }
}

void SrtEditorMainFrame::sort_by_time_menuItem_OnMenuSelection(wxCommandEvent& event)
{
  if (srt_file_content.IsOk() == true) {
    srt_file_content.SortByTime();
  } else {
    wxMessageBox(_("Please open a *.srt file first."));
  }
}

} // end of namespace rco
