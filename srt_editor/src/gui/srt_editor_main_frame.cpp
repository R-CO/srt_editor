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
#include "srt_editor_main_frame.h"

#include <wx/log.h>
#include <wx/string.h>
#include <wx/regex.h>
#include <wx/filedlg.h>
#include <wx/ffile.h>

namespace rco {

//
// this one can only parsing single-line subtitle
//
//wxString SrtEditorMainFrame::srt_format_regex_ = wxT("(\\d+)\n(\\d+:\\d{2}:\\d{2},\\d{3})\\s-->\\s(\\d+:\\d{2}:\\d{2},\\d{3})\n(.*)\n\n");

//
//  0: the string matches the whole regular expression
//  1: subtitle count
//  2: start time
//  3: hours (start time)
//  4: minutes (start time)
//  5: seconds (start time)
//  6: milliseconds (start time)
//  7: end time
//  8: hours (end time)
//  9: minutes (end time)
// 10: seconds (end time)
// 11: milliseconds (end time)
// 12: subtitle text   <--- support multi-line
//
wxString SrtEditorMainFrame::srt_format_regex_ = 
  wxT("(\\d+)\n((\\d+):(\\d{2}):(\\d{2}),(\\d{3}))\\s-->\\s((\\d+):(\\d{2}):(\\d{2}),(\\d{3}))\n([\\s]*(.*|.+\n.+)*(?=\n{2}|$))");

SrtEditorMainFrame::SrtEditorMainFrame(wxWindow* parent)
  :
  SrtEditorMainFrameBase(parent),
  file_buffer_(new(std::nothrow) wxString),
  srt_content_(new(std::nothrow) std::vector<SrtContent>)
{

}

void SrtEditorMainFrame::open_file_menuItem_OnMenuSelection(wxCommandEvent& event)
{
  // TODO: Implement open_file_menuItem_OnMenuSelection
  wxFileDialog
    openFileDialog(this, _("Open srt file"), "", "",
                   "srt files (*.srt)|*.srt", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
  if (openFileDialog.ShowModal() == wxID_CANCEL)
    return;     // the user changed idea...

                // proceed loading the file chosen by the user;
                // this can be done with e.g. wxWidgets input streams:
  wxFFile input_file(openFileDialog.GetPath());
  if (!input_file.IsOpened()) {
    wxLogError("Cannot open file '%s'.", openFileDialog.GetPath());
    return;
  }

  input_file.ReadAll(file_buffer_.get());
}

void SrtEditorMainFrame::save_file_menuItem_OnMenuSelection(wxCommandEvent& event)
{
  // TODO: Implement save_file_menuItem_OnMenuSelection
}

void SrtEditorMainFrame::sort_by_time_menuItem_OnMenuSelection(wxCommandEvent& event)
{
  // TODO: Implement sort_by_time_menuItem_OnMenuSelection
  if (file_buffer_->size() <= 0) {
    return;
  }

  wxRegEx regex(srt_format_regex_, wxRE_ADVANCED + wxRE_NEWLINE);
  bool is_expression_ok = regex.IsValid();

  wxString last;
  if (is_expression_ok == true) {
    wxString buffer = *file_buffer_;
    size_t index = 0;
    while (regex.Matches(buffer.substr(index)) == true) {
      wxString match = regex.GetMatch(buffer.substr(index), 0);
      last = match;
      wxString count = regex.GetMatch(buffer.substr(index), 1);
      wxString start = regex.GetMatch(buffer.substr(index), 2);
      wxString subtitle = regex.GetMatch(buffer.substr(index), 12);
      index += match.size();
    }

  }

}

}
