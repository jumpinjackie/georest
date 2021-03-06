//
// StringPartSource.cpp
//
// $Id: //poco/1.3/Net/src/StringPartSource.cpp#1 $
//
// Library: Net
// Package: Messages
// Module:  StringPartSource
//
// Copyright (c) 2005-2006, Applied Informatics Software Engineering GmbH.
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


#include "Poco/Net/StringPartSource.h"


namespace Poco {
namespace Net {


StringPartSource::StringPartSource(const std::string& str):
	PartSource("text/plain"),
	_istr(str)
{
}


StringPartSource::StringPartSource(const std::string& str, const std::string& mediaType):
	PartSource(mediaType),
	_istr(str)
{
}


StringPartSource::StringPartSource(const std::string& str, const std::string& mediaType, const std::string& filename):
	PartSource(mediaType),
	_istr(str),
	_filename(filename)
{
}


StringPartSource::~StringPartSource()
{
}


std::istream& StringPartSource::stream()
{
	return _istr;
}

	
const std::string& StringPartSource::filename()
{
	return _filename;
}


} } // namespace Poco::Net
