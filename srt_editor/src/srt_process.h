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
#ifndef SRT_EDITOR_SRT_PROCESS_H
#define SRT_EDITOR_SRT_PROCESS_H

#include <list>

#include <wx/scopedptr.h>
#include <wx/string.h>

namespace rco {

struct SrtFormatContent
{
  void Reset() {
    count_ = 0;
    start_hours_ = 0;
    start_minutes_ = 0;
    start_seconds_ = 0;
    start_milliseconds_ = 0;
    end_hours_ = 0;
    end_minutes_ = 0;
    end_seconds_ = 0;
    end_milliseconds_ = 0;
    subtitle_.clear();
  }

  int count_;
  int start_hours_;
  int start_minutes_;
  int start_seconds_;
  int start_milliseconds_;
  int end_hours_;
  int end_minutes_;
  int end_seconds_;
  int end_milliseconds_;
  wxString subtitle_;
};

bool IsSrtFormatContentObjectALessThanObjectB(const SrtFormatContent &a, const SrtFormatContent &b);

class SrtFileContent
{
public:
  SrtFileContent();
  ~SrtFileContent();

  inline const bool IsOk(void) {
    return is_parse_ok_;
  }
  bool ParseSrtFile(const wxString &file_buffer);
  bool SaveToFile(const wxString &file_path);
  void SortByTime(void);

  static const wxString kSrtFormatRegex;

private:
  enum SrtFormatContentParseIndex
  {
    kWholeRegex = 0,  //  0: the string matches the whole regular expression
    kSubtitleCount = 1,  //  1: subtitle count
    kStartTime = 2,  //  2: start time
    kStartHours = 3,  //  3: hours (start time)
    kStartMinutes = 4,  //  4: minutes (start time)
    kStartSeconds = 5,  //  5: seconds (start time)
    kStartMilliseconds = 6,  //  6: milliseconds (start time)
    kEndTime = 7,  //  7: end time
    kEndHours = 8,  //  8: hours (end time)
    kEndMinutes = 9,  //  9: minutes (end time)
    kEndSeconds = 10, // 10: seconds (end time)
    kEndMilliseconds = 11, // 11: milliseconds (end time)
    kSubtitleText = 12, // 12: subtitle text   <--- support multi-line
  };

  bool is_parse_ok_;
  wxScopedPtr<std::list<SrtFormatContent>> srt_contents_;
};

} // end of namespace rco

#endif
