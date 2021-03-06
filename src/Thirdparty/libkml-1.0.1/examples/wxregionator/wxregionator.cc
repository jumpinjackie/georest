// Copyright 2008, Google Inc. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//  1. Redistributions of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//  2. Redistributions in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//  3. Neither the name of Google Inc. nor the names of its contributors may be
//     used to endorse or promote products derived from this software without
//     specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
// EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// This file contains the implementation of the main frame used in the
// application.

#include "wxregionator.h"
#include <kml/dom.h>
#include <kml/convenience/convenience.h>
#include <kml/convenience/csv_file.h>
#include <kml/engine.h>
#include <kml/regionator/feature_list_region_handler.h>
#include <kml/regionator/regionator.h>
#include <wx/dir.h>
#include <wx/file.h>
#include <wx/progdlg.h>

// IDs for the controls and menu commands.
enum {
  Regionator_Quit = wxID_EXIT,
  Regionator_About = wxID_ABOUT,
  Regionator_InputFile,
  Regionator_OutputDir,
  Regionator_GenerateKML
};

// Event tables.
BEGIN_EVENT_TABLE(MainFrame, wxFrame)
  EVT_MENU(Regionator_Quit, MainFrame::OnQuit)
  EVT_MENU(Regionator_About, MainFrame::OnAbout)
END_EVENT_TABLE()

MainFrame::MainFrame(const wxString& title)
  : wxFrame(NULL, -1, title, wxPoint(-1, -1), wxSize(450, 400)),
    panel_(NULL), input_file_ctrl_(NULL), output_dir_ctrl_(NULL) {

  // Menu bar setup.
  wxMenu* filemenu = new wxMenu;
  filemenu->Append(Regionator_Quit, _T("Exit"), _T("Quit this application"));
  wxMenu* helpmenu = new wxMenu;
  helpmenu->Append(Regionator_About, _T("About..."), _T("Show about dialog"));
  wxMenuBar* menubar = new wxMenuBar();
  menubar->Append(filemenu, _T("&File"));
  menubar->Append(helpmenu, _T("&Help"));
  SetMenuBar(menubar);

  // Status bar.
  CreateStatusBar(2);
  SetStatusText(_T("Regionator demo"));

  // Layout.
  panel_ = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(450, 400));
  wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

  // Input file picker.
  wxBoxSizer *hbox1 = new wxBoxSizer(wxHORIZONTAL);
  wxStaticText *st1 =  new wxStaticText(panel_, wxID_ANY,
                                        wxT("Input CSV file"));
  hbox1->Add(st1, 0, wxRIGHT, 10);
  input_file_ctrl_ = new wxFilePickerCtrl(panel_, Regionator_InputFile,
                                          wxEmptyString,
                                          wxT("Select input CSV file"),
                                          wxT("*"),
                                          wxDefaultPosition, wxDefaultSize,
                                          wxFLP_USE_TEXTCTRL);
  hbox1->Add(input_file_ctrl_, 1);
  vbox->Add(hbox1, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);
  vbox->Add(-1, 10);  // Spacer.

  // Output directory picker.
  wxBoxSizer *hbox2 = new wxBoxSizer(wxHORIZONTAL);
  wxStaticText *st2 = new wxStaticText(panel_, wxID_ANY,
                                       wxT("Output directory"));
  hbox2->Add(st2, 0, wxRIGHT, 10);
  output_dir_ctrl_ = new wxDirPickerCtrl(panel_, Regionator_OutputDir,
                                         wxEmptyString,
                                         wxT("Select output directory"),
                                         wxDefaultPosition, wxDefaultSize,
                                         wxDIRP_USE_TEXTCTRL);
  hbox2->Add(output_dir_ctrl_, 1);
  vbox->Add(hbox2, 0, wxLEFT | wxRIGHT | wxEXPAND, 10);
  vbox->Add(-1, 30);

  // OK and Cancel buttons.
  wxBoxSizer *hbox5 = new wxBoxSizer(wxHORIZONTAL);
  wxButton *btn1 = new wxButton(panel_, Regionator_GenerateKML,
                                wxT("Generate KML files"));
  hbox5->Add(btn1, 0);
  vbox->Add(hbox5, 0, wxALIGN_RIGHT | wxRIGHT | wxBOTTOM, 15);

  // Events.
  Connect(Regionator_GenerateKML, wxEVT_COMMAND_BUTTON_CLICKED,
          wxCommandEventHandler(MainFrame::GenerateRbnl));

  // Final sizing before display.
  vbox->SetMinSize(450,100);
  panel_->SetSizer(vbox);
  vbox->SetSizeHints(this);
  Centre();
}

void MainFrame::GenerateRbnl(wxCommandEvent& event) {
  // Ensure the values for the input and output are sane.
  if (!ValidateFormFields(input_file_ctrl_->GetPath().c_str(),
                          output_dir_ctrl_->GetPath())) {
    return;
  }

  // Check if the output dir is empty. Bail if the dir wasn't empty and the
  // user elected not to continue.
  if (!AskIfOutputDirNotEmpty(output_dir_ctrl_->GetPath())) {
    return;
  }

  // Parse the CSV file into a FeatureList of Point Placemarks sorted by score.
  kmlconvenience::FeatureList feature_list;
  kmlconvenience::CsvFile placemarks(&feature_list);
  // TODO: ParseCsvFile should return a bool?
  placemarks.ParseCsvFile(input_file_ctrl_->GetPath().c_str());
  feature_list.Sort();

  // Give the FeatureList to the FeatureListRegionHandler.
  kmlregionator::FeatureListRegionHandler feature_list_region_handler(
      &feature_list);

  // Create a root Region based on the bounding box of the FeatureList.
  kmlengine::Bbox bbox;
  feature_list.ComputeBoundingBox(&bbox);

  // TODO: snap.
  kmldom::RegionPtr root = kmlconvenience::CreateRegion2d(bbox.get_north(),
                                                          bbox.get_south(),
                                                          bbox.get_east(),
                                                          bbox.get_west(),
                                                          256, -1);

  // Create a Regionator instance and walk the hierarchy starting at root.
  kmlregionator::Regionator regionator(feature_list_region_handler, root);

  // TODO: a way to monitor progress would be useful.
  wxString info("Regionation in progress");
  wxProgressDialog dialog(info, info, 1, this, wxPD_CAN_ABORT | wxPD_APP_MODAL);
  while(!regionator.Regionate(output_dir_ctrl_->GetPath().c_str())) {
    dialog.Pulse();
  }
}

void MainFrame::OnQuit(wxCommandEvent& event) {
  delete output_dir_ctrl_;
  delete input_file_ctrl_;
  delete panel_;
  Close(true);
}

void MainFrame::OnAbout(wxCommandEvent& event) {
  wxMessageBox(wxString::Format(
    _T("Welcome to the Regionator!\n")
    _T("\n")
    _T("http://libkml.googlecode.com/")
  ),
  _T("About Regionator"),
  wxOK | wxICON_INFORMATION,
  this);
}

// Private.
bool MainFrame::ValidateFormFields(const wxChar* input_file,
                                   const wxString& output_dir) {
  wxString errors;
  // Ensure the CSV file is readable.
  if (!wxFile::Access(input_file, wxFile::read)) {
    errors.Printf(_T("Error: input file is not readable\n"));
  // Ensure the output dir exists.
  } else if (!wxDir::Exists(output_dir)) {
    errors.Printf(_T("Error: the output directory must exist\n"));
  }
  if (errors.empty()) {
    return true;
  }
  wxMessageDialog err_dialog(this, errors, _T("Cannot continue"),
                             wxOK | wxICON_ERROR);
  err_dialog.ShowModal();
  return false;
}

// Private.
bool MainFrame::AskIfOutputDirNotEmpty(const wxString& output_dir) {
  wxDir dir(output_dir);
  if (dir.HasFiles()) {
    wxString warning;
    warning.Printf(_T("Output directory is not empty\n")
                   _T("Would you like to continue anyway?\n"));
    wxMessageDialog dialog(this, warning, _T("Warning"),
                           wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);
    return dialog.ShowModal() == wxID_YES;
  }
  return true;
}

