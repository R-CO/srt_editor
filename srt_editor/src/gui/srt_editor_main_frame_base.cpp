///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "srt_editor_main_frame_base.h"

///////////////////////////////////////////////////////////////////////////
using namespace rco;

SrtEditorMainFrameBase::SrtEditorMainFrameBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	m_panel1 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	bSizer1->Add( m_panel1, 1, wxEXPAND | wxALL, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	m_menubar1 = new wxMenuBar( 0 );
	file_menu = new wxMenu();
	wxMenuItem* open_file_menuItem_;
	open_file_menuItem_ = new wxMenuItem( file_menu, wxID_ANY, wxString( _("&Open") ) + wxT('\t') + wxT("CTRL+O"), wxEmptyString, wxITEM_NORMAL );
	file_menu->Append( open_file_menuItem_ );
	
	wxMenuItem* save_file_menuItem_;
	save_file_menuItem_ = new wxMenuItem( file_menu, wxID_ANY, wxString( _("&Save") ) + wxT('\t') + wxT("CTRL+S"), wxEmptyString, wxITEM_NORMAL );
	file_menu->Append( save_file_menuItem_ );
	
	m_menubar1->Append( file_menu, _("&File") ); 
	
	operations_menu = new wxMenu();
	wxMenuItem* sort_by_time_menuItem_;
	sort_by_time_menuItem_ = new wxMenuItem( operations_menu, wxID_ANY, wxString( _("&Sort sbutitle by time") ) + wxT('\t') + wxT("CTRL+T"), wxEmptyString, wxITEM_NORMAL );
	operations_menu->Append( sort_by_time_menuItem_ );
	
	m_menubar1->Append( operations_menu, _("&Operation") ); 
	
	this->SetMenuBar( m_menubar1 );
	
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( open_file_menuItem_->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( SrtEditorMainFrameBase::open_file_menuItem_OnMenuSelection ) );
	this->Connect( save_file_menuItem_->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( SrtEditorMainFrameBase::save_file_menuItem_OnMenuSelection ) );
	this->Connect( sort_by_time_menuItem_->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( SrtEditorMainFrameBase::sort_by_time_menuItem_OnMenuSelection ) );
}

SrtEditorMainFrameBase::~SrtEditorMainFrameBase()
{
	// Disconnect Events
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( SrtEditorMainFrameBase::open_file_menuItem_OnMenuSelection ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( SrtEditorMainFrameBase::save_file_menuItem_OnMenuSelection ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( SrtEditorMainFrameBase::sort_by_time_menuItem_OnMenuSelection ) );
	
}
