//-----------------------------------------------------------------------------
// Standard wxWidgets headers
//-----------------------------------------------------------------------------
// Firsqt, we have to include wxWidgets' header files.
// <wx/wx.h> is used for global include (wx/wx.h) which includes most of the commonly needed headers 
// (although not all of them as there are simply too many wxWidgets headers to pull in all of them)
// For the platforms with support for precompiled headers, as indicated by WX_PRECOMP, this global 
// header is already included by wx/wxprec.h so we only include it for the other ones:
// #include <wx/wx.h>
#include <wx/wx.h>
 
class MyApp : public wxApp
{
public:
    bool OnInit() override;
};

//-----------------------------------------------------------------------------
// wxWidgets macro: Declare the application.
//-----------------------------------------------------------------------------

// Create a new application object: this macro will allow wxWidgets to create
// the application object during program execution (it's better than using a
// static object for many reasons) and also declares the accessor function
// wxGetApp() which will return the reference of the right type (i.e. the_app and
// not wxApp).

// As in all programs, there must be a "main" function. Under wxWidgets, main is implemented 
// inside the wxIMPLEMENT_APP() macro, which creates an application instance of the specified 
// class and starts running the GUI event loop. It is used simply as: 
wxIMPLEMENT_APP(MyApp);


// Declare a new frame type: Here, this is going to be our main window frame
// The main window (the “main”Frame) is created by deriving a class from wxFrame. As the first step, 
// we have to define the class and its public constructor. Then, we have to add the definitions of a 
// number of event handlers, i.e.: for functions handling events such as mouse clicks, messages from the menu, 
// or for other button-event responses. The event handlers are defined as private members of the “main”Frame class. 
class MyFrame : public wxFrame
{
public:
    MyFrame();
 
private:
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
};


// In order to be able to react to a menu command, it must be given a unique identifier 
// which can be defined as a const variable or an enum element. The latter is often 
// used because typically many such constants will be needed.
// Notice that you don't need to define identifiers for "About" and "Exit", as wxWidgets 
// already predefines standard values such as wxID_ABOUT and wxID_EXIT. You should use 
// these whenever possible, as they can be handled in a special way by a particular platform.
enum
{
    ID_Hello = 1
};


// As mentioned before, wxApp::OnInit() is called upon startup and should be used (overrided) 
// to initialize the program. (Maybe showing a "splash screen" and creating the main and/or other windows. 
// Frames are created hidden by default, to allow the creation of child windows before displaying them. 
// We thus need to explicitly show them. Finally, we return true from this method to indicate successful initialization:
bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame();
    frame->Show(true);
    return true;
}


// This snippet shows an example on how we can use the wxMenuBar to instantiate a menu-bar 
// with a couple of menus and each one with menu items.  
//
// It also creates and sets a status-bar
//
// It also binds menu/menu-items to event-handling functions
MyFrame::MyFrame()
    : wxFrame(nullptr, wxID_ANY, "Hello World")
{
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
                     "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);

    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
 
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");

    // Set up the menu-bar for our window frame
    SetMenuBar( menuBar );
 
    CreateStatusBar();
    SetStatusText("Welcome to wxWidgets!");
 
    Bind(wxEVT_MENU, &MyFrame::OnHello, this, ID_Hello);
    Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
}


// This event handler function is about quitting of our app on clicking 
// on the menu item “Quit”. It is quite simple. It just calls the Close() function 
// (member of the core wxWindow class) 
void MyFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}


// This event handler function captures the mouse click on the menu item “About”. 
// Then, it displays a small window with some text in it. In this case it is a 
// typical "About" wxMessageBox modal pop-up window with information about the program
void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This is a wxWidgets Hello World example",
                 "About Hello World", wxOK | wxICON_INFORMATION);
}


// This event handler function handles the mouse click on the “Hello” menu item. 
// It uses the wxLogMessage to display again a default modal pop-up window box 
// with a body text having the string provided
void MyFrame::OnHello(wxCommandEvent& event)
{
    wxLogMessage("Hello world from wxWidgets!");
}
