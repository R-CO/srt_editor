﻿//The MIT License(MIT)
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
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MErtHANTABILITY,
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
#ifndef __srt_editor_main_frame__
#define __srt_editor_main_frame__

/**
@file
Subclass of SrtEditorMainFrameBase, which is generated by wxFormBuilder.
*/

#include <list>

#include <wx/scopedptr.h>
#include <wx/string.h>

#include "srt_editor_main_frame_base.h"
#include "../srt_process.h"

//// end generated include

namespace rco {

/** Implementing SrtEditorMainFrameBase */
class SrtEditorMainFrame : public SrtEditorMainFrameBase
{
public:
  /** Constructor */
  SrtEditorMainFrame(wxWindow* parent);

protected:
  // Handlers for SrtEditorMainFrameBase events.
  void open_file_menuItem_OnMenuSelection(wxCommandEvent& event);
  void save_file_menuItem_OnMenuSelection(wxCommandEvent& event);
  void sort_by_time_menuItem_OnMenuSelection(wxCommandEvent& event);

private:
  wxScopedPtr<wxString> file_buffer_;
  SrtFileContent srt_file_content;
};

}

#endif // __srt_editor_main_frame__
