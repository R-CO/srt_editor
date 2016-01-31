///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __SRT_EDITOR_MAIN_FRAME_BASE_H__
#define __SRT_EDITOR_MAIN_FRAME_BASE_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/panel.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/sizer.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////

namespace rco
{
	///////////////////////////////////////////////////////////////////////////////
	/// Class SrtEditorMainFrameBase
	///////////////////////////////////////////////////////////////////////////////
	class SrtEditorMainFrameBase : public wxFrame 
	{
		private:
		
		protected:
			wxPanel* m_panel1;
			wxMenuBar* m_menubar1;
			wxMenu* file_menu;
			wxMenu* operations_menu;
			
			// Virtual event handlers, overide them in your derived class
			virtual void open_file_menuItem_OnMenuSelection( wxCommandEvent& event ) { event.Skip(); }
			virtual void save_file_menuItem_OnMenuSelection( wxCommandEvent& event ) { event.Skip(); }
			virtual void sort_by_time_menuItem_OnMenuSelection( wxCommandEvent& event ) { event.Skip(); }
			
		
		public:
			
			SrtEditorMainFrameBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Subtitle Editor by R-CO"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
			
			~SrtEditorMainFrameBase();
		
	};
	
} // namespace rco

#endif //__SRT_EDITOR_MAIN_FRAME_BASE_H__
