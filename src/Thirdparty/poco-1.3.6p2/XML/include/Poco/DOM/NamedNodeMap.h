//
// NamedNodeMap.h
//
// $Id: //poco/1.3/XML/include/Poco/DOM/NamedNodeMap.h#1 $
//
// Library: XML
// Package: DOM
// Module:  DOM
//
// Definition of the DOM NamedNodeMap interface.
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


#ifndef DOM_NamedNodeMap_INCLUDED
#define DOM_NamedNodeMap_INCLUDED


#include "Poco/XML/XML.h"
#include "Poco/DOM/DOMObject.h"
#include "Poco/XML/XMLString.h"


namespace Poco {
namespace XML {


class Node;


class XML_API NamedNodeMap: public DOMObject
	/// Objects implementing the NamedNodeMap interface are used to represent collections
	/// of nodes that can be accessed by name. Note that NamedNodeMap does not inherit
	/// from NodeList; NamedNodeMaps are not maintained in any particular order.
	/// Objects contained in an object implementing NamedNodeMap may also be accessed
	/// by an ordinal index, but this is simply to allow convenient enumeration
	/// of the contents of a NamedNodeMap, and does not imply that the DOM specifies
	/// an order to these Nodes.
	///
	/// NamedNodeMap objects in the DOM are live.
	///
	/// A NamedNodeMap returned from a method must be released with a call to 
	/// release() when no longer needed.
{
public:
	virtual Node* getNamedItem(const XMLString& name) const = 0;
		/// Retrieves a node specified by name.

	virtual Node* setNamedItem(Node* arg) = 0;
		/// Adds a node using its nodeName attribute. If a node with that name is already
		/// present in this map, it is replaced by the new one.
		/// As the nodeName attribute is used to derive the name which the node must
		/// be stored under, multiple nodes of certain types (those that have a "special"
		/// string value) cannot be stored as the names would clash. This is seen as
		/// preferable to allowing nodes to be aliased.

	virtual Node* removeNamedItem(const XMLString& name) = 0;
		/// Removes a node specified by name. When this map contains the attributes
		/// attached to an element, if the removed attribute is known to have a default
		/// value, an attribute immediately appears containing the default value.

	virtual Node* item(unsigned long index) const = 0;
		/// Returns the index'th item in the map. If index is greater
		/// than or equal to the number of nodes in the map, this
		/// returns null.

	virtual unsigned long length() const = 0;
		/// Returns the number of nodes in the map. The range of valid
		/// child node indices is 0 to length - 1 inclusive.
	
	// DOM Level 2
	virtual Node* getNamedItemNS(const XMLString& namespaceURI, const XMLString& localName) const = 0;
		/// Retrieves a node specified by name.

	virtual Node* setNamedItemNS(Node* arg) = 0;
		/// Adds a node using its nodeName attribute.
		/// If a node with that namespace URI and that local name is already 
		/// present in this map, it is replaced by the new one.

	virtual Node* removeNamedItemNS(const XMLString& namespaceURI, const XMLString& localName) = 0;
		/// Removes a node specified by name.
	
protected:
	virtual ~NamedNodeMap();
};


} } // namespace Poco::XML


#endif // DOM_NamedNodeMap_INCLUDED
