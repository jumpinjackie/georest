//
// StreamCopier.h
//
// $Id: //poco/1.3/Foundation/include/Poco/StreamCopier.h#1 $
//
// Library: Foundation
// Package: Streams
// Module:  StreamCopier
//
// Definition of class StreamCopier.
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#ifndef Foundation_StreamCopier_INCLUDED
#define Foundation_StreamCopier_INCLUDED


#include "Poco/Foundation.h"
#include <istream>
#include <ostream>


namespace Poco {


class Foundation_API StreamCopier
	/// This class provides static methods to copy the contents from one stream
	/// into another.
{
public:
    static std::streamsize copyStream(std::istream& istr, std::ostream& ostr, unsigned bufferSize = 8192);
		/// Writes all bytes readable from istr to ostr, using an internal buffer.
		///
		/// Returns the number of bytes copied.

    static std::streamsize copyStreamUnbuffered(std::istream& istr, std::ostream& ostr);
		/// Writes all bytes readable from istr to ostr.
		///
		/// Returns the number of bytes copied.

    static std::streamsize copyToString(std::istream& istr, std::string& str, unsigned bufferSize = 8192);
		/// Appends all bytes readable from istr to the given string, using an internal buffer.
		///
		/// Returns the number of bytes copied.
};


} // namespace Poco


#endif // Foundation_StreamCopier_INCLUDED
