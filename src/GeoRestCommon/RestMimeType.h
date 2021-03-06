//
//  Copyright (C) 2010 by Haris Kurtagic
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of version 2.1 of the GNU Lesser
//  General Public License as published by the Free Software Foundation.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//

#ifndef RESTMGMIMETYPE_H
#define RESTMGMIMETYPE_H

/// \defgroup MgMimeType MgMimeType
/// \ingroup Common_Module
/// \{

///////////////////////////////////////////////////////////////////////////////
/// \brief
/// Mime types for data to be sent to clients.
class REST_COMMON_API RestMimeType
{
PUBLISHED_API:
    /// \if INTERNAL
    /// The "value(xxx)" comments are used by SWIG to build constants.php.  Do not alter them.
    /// \endif

    /// application/agf
    static const STRING Agf;      ///\if INTERNAL value("application/agf") \endif

    /// application/octet-stream
    static const STRING Binary;   ///\if INTERNAL value("application/octet-stream") \endif

    /// model/vnd.dwf
    static const STRING Dwf;      ///\if INTERNAL value("model/vnd.dwf") \endif

    /// image/gif
    static const STRING Gif;      ///\if INTERNAL value("image/gif") \endif

    /// image/jpeg
    static const STRING Jpeg;     ///\if INTERNAL value("image/jpeg") \endif

    /// image/png
    static const STRING Png;      ///\if INTERNAL value("image/png") \endif

    /// text/plain
    static const STRING Text;     ///\if INTERNAL value("text/plain") \endif

    /// image/tiff
    static const STRING Tiff;     ///\if INTERNAL value("image/tiff") \endif

    /// text/xml
    static const STRING Xml;      ///\if INTERNAL value("text/xml") \endif

    /// application/json
    static const STRING Json;      ///\if INTERNAL value("application/json") \endif
    
    /// application/json
    static const STRING JsonP;      ///\if INTERNAL value("application/json") \endif

    /// text/html
    static const STRING Html;     ///\if INTERNAL value("text/html") \endif

    /// application/vnd.google-earth.kml+xml
    static const STRING Kml;      ///\if INTERNAL value("application/vnd.google-earth.kml+xml") \endif

    /// application/vnd.google-earth.kmz
    static const STRING Kmz;      ///\if INTERNAL value("application/vnd.google-earth.kmz") \endif
    
    static const STRING Atom;      /// L"application/xml+atom";
    
    
};
/// \}

#endif
