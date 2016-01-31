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
*** Date: 2016-01-31
***/
#include "srt_process.h"

#include <list>

#include <wx/regex.h>
#include <wx/scopedptr.h>
#include <wx/txtstrm.h>
#include <wx/wfstream.h>

namespace rco {

bool IsSrtFormatContentObjectALessThanObjectB(const SrtFormatContent &a, const SrtFormatContent &b)
{
  if (a.start_hours_ < b.start_hours_) {
    return true;
  } else if (a.start_hours_ == b.start_hours_) {
    if (a.start_minutes_ < b.start_minutes_) {
      return true;
    } else if (a.start_minutes_ == b.start_minutes_) {
      if (a.start_seconds_ < b.start_seconds_) {
        return true;
      } else if (a.start_seconds_ == b.start_seconds_) {
        if (a.start_milliseconds_ < b.start_milliseconds_) {
          return true;
        } else {
          return false;
        }
      } else {
        return false;
      }
    } else {
      return false;
    }
  } else {
    return false;
  }
}

//
// this one can only parsing single-line subtitle
//
//wxString SrtFileContent::kSrtFormatRegex = wxT("(\\d+)\n(\\d+:\\d{2}:\\d{2},\\d{3})\\s-->\\s(\\d+:\\d{2}:\\d{2},\\d{3})\n(.*)\n\n");

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
const wxString SrtFileContent::kSrtFormatRegex =
wxT("(\\d+)\n((\\d+):(\\d{2}):(\\d{2}),(\\d{3}))\\s-->\\s((\\d+):(\\d{2}):(\\d{2}),(\\d{3}))\n([\\s]*(.*|.+\n.+)*)(?=\n{2}|$)");

SrtFileContent::SrtFileContent()
  : srt_contents_(new(std::nothrow) std::list<SrtFormatContent>)
{
  is_parse_ok_ = false;
}

SrtFileContent::~SrtFileContent()
{
}

bool SrtFileContent::ParseSrtFile(const wxString &file_buffer)
{
  if (file_buffer.size() <= 0) {
    return false;
  }

  is_parse_ok_ = false;
  srt_contents_->clear();

  wxRegEx regex(kSrtFormatRegex, wxRE_ADVANCED + wxRE_NEWLINE);
  bool is_expression_ok = regex.IsValid();

  if (is_expression_ok == true) {
    size_t index = 0;
    wxString sub_file_buffer = file_buffer.substr(index);
    SrtFormatContent temp_srt_format_content;
    wxString match;
    wxString count;
    wxString start_hours;
    wxString start_minutes;
    wxString start_seconds;
    wxString start_milliseconds;
    wxString end_hours;
    wxString end_minutes;
    wxString end_seconds;
    wxString end_milliseconds;
    wxString subtitle;

    while (regex.Matches(sub_file_buffer) == true) {
      match = regex.GetMatch(sub_file_buffer, kWholeRegex);
      count = regex.GetMatch(sub_file_buffer, kSubtitleCount);
      start_hours = regex.GetMatch(sub_file_buffer, kStartHours);
      start_minutes = regex.GetMatch(sub_file_buffer, kStartMinutes);
      start_seconds = regex.GetMatch(sub_file_buffer, kStartSeconds);
      start_milliseconds = regex.GetMatch(sub_file_buffer, kStartMilliseconds);
      end_hours = regex.GetMatch(sub_file_buffer, kEndHours);
      end_minutes = regex.GetMatch(sub_file_buffer, kEndMinutes);
      end_seconds = regex.GetMatch(sub_file_buffer, kEndSeconds);
      end_milliseconds = regex.GetMatch(sub_file_buffer, kEndMilliseconds);
      subtitle = regex.GetMatch(sub_file_buffer, kSubtitleText);

      if (count.ToLong(reinterpret_cast<long *>(&temp_srt_format_content.count_)) == false) {
        return false;
      }
      if (start_hours.ToLong(reinterpret_cast<long *>(&temp_srt_format_content.start_hours_)) == false) {
        return false;
      }
      if (start_minutes.ToLong(reinterpret_cast<long *>(&temp_srt_format_content.start_minutes_)) == false) {
        return false;
      }
      if (start_seconds.ToLong(reinterpret_cast<long *>(&temp_srt_format_content.start_seconds_)) == false) {
        return false;
      }
      if (start_milliseconds.ToLong(reinterpret_cast<long *>(&temp_srt_format_content.start_milliseconds_)) == false) {
        return false;
      }
      if (end_hours.ToLong(reinterpret_cast<long *>(&temp_srt_format_content.end_hours_)) == false) {
        return false;
      }
      if (end_minutes.ToLong(reinterpret_cast<long *>(&temp_srt_format_content.end_minutes_)) == false) {
        return false;
      }
      if (end_seconds.ToLong(reinterpret_cast<long *>(&temp_srt_format_content.end_seconds_)) == false) {
        return false;
      }
      if (end_milliseconds.ToLong(reinterpret_cast<long *>(&temp_srt_format_content.end_milliseconds_)) == false) {
        return false;
      }
      temp_srt_format_content.subtitle_ = subtitle;

      srt_contents_->push_back(temp_srt_format_content);

      index += match.size();
      sub_file_buffer = file_buffer.substr(index);
    }
  } else {
    return false;
  }

  is_parse_ok_ = true;

  return is_parse_ok_;
}

bool SrtFileContent::SaveToFile(const wxString & file_path)
{
  wxFFileOutputStream file_output_stream(file_path, "w");
  if (file_output_stream.IsOk() == false) {
    return false;
  }
  wxTextOutputStream text_output_stream(file_output_stream, wxEOL_UNIX);

  for (std::list<SrtFormatContent>::iterator itor = srt_contents_->begin();
  itor != srt_contents_->end(); ++itor) {
    text_output_stream << wxString::Format(wxT("%d\n"), itor->count_)
      + wxString::Format(wxT("%02d:%02d:%02d,%03d --> "),
                         itor->start_hours_,
                         itor->start_minutes_,
                         itor->start_seconds_,
                         itor->start_milliseconds_)
      + wxString::Format(wxT("%02d:%02d:%02d,%03d\n"),
                         itor->end_hours_,
                         itor->end_minutes_,
                         itor->end_seconds_,
                         itor->end_milliseconds_)
      + itor->subtitle_ << endl << endl;
  }

  file_output_stream.Close();

  return true;
}

void SrtFileContent::SortByTime(void)
{
  srt_contents_->sort(IsSrtFormatContentObjectALessThanObjectB);

  int count = 0;
  for (std::list<SrtFormatContent>::iterator itor = srt_contents_->begin();
  itor != srt_contents_->end(); ++itor, ++count) {
    itor->count_ = count;
  }
}

} // end of namespace rco
