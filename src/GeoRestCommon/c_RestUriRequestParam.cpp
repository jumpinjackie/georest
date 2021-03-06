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
#include "stdafx.h"
#include "c_RestUriRequestParam.h"

//////////////////////////////////////////////////////////////////
/// <summary>
/// Constructor. Initialize string property collection.
/// </summary>
c_RestUriRequestParam::c_RestUriRequestParam()
{
    m_reqParamCollection = new MgStringPropertyCollection(false, false);
}

/// <summary>
/// Adds the parameter and value to the collection.
/// Parameter name  - case-insensitive
/// Parameter value - case-sensitive
/// </summary>
/// <param name="name">Input
/// Name of the parameter
/// No two parameters can have same name.
/// </param>
/// <param name="value">Input
/// Value corresponding to the parameter.
/// NULL value is NOT allowed but empty string is allowed.
/// </param>
/// <returns>
/// TRUE  -  Parameter is successfully added.
/// FALSE -  Parameter could not be added.
/// Possible cause is parameter already exist or its value is NULL.
/// </returns>
bool c_RestUriRequestParam::AddParameter(CREFSTRING name, CREFSTRING value, bool AddEmptyVal)
{
    if (AddEmptyVal || value.length()!=0 && !m_reqParamCollection->Contains(name))
    {
        m_reqParamCollection->Add(name, value);
        return true;
    }

    return false;
}

/// <summary>
/// Removes the parameter and value from the collection.
/// Parameter name  - case-insensitive
/// </summary>
/// <param name="name">Input
/// Name of the parameter to be removed.
/// </param>
/// <returns>
/// TRUE  -  Parameter is successfully removed.
/// FALSE -  Parameter could not be removed.
/// Possible cause is parameter does not exist.
/// </returns>
bool c_RestUriRequestParam::RemoveParameter(CREFSTRING name)
{
    if (m_reqParamCollection->Contains(name))
    {
        m_reqParamCollection->Remove(name);
        return true;
    }

    return false;
}

/// <summary>
/// Retrieve the value for the specified parameter.
/// Parameter name  - case-insensitive
/// </summary>
/// <param name="name">Input
/// Name of the parameter for which value to be retrieved.
/// </param>
/// <returns>
/// Value for the specified parameter or empty string if parameter does not
/// exist.
/// </returns>
STRING c_RestUriRequestParam::GetParameterValue(CREFSTRING parameterName)
{
    try
    {
        return m_reqParamCollection->GetValue(parameterName);
    }
    catch(...)
    {
    
    }
    return L"";
}

STRING c_RestUriRequestParam::GetParameterType(CREFSTRING parameterName)
{
    try
    {
        return m_paramTypeCollection.GetValue(parameterName);
    }
    catch(...)
    {
    
    }
    return L"";
}

/// <summary>
/// Update the value for the specified parameter.
/// Parameter name  - case-insensitive
/// Parameter value - case-sensitive
/// </summary>
/// <param name="name">Input
/// Name of the parameter to be updated.
/// </param>
/// <param name="value">Input
/// Value corresponding to the parameter.
/// NULL value is NOT allowed but empty string is allowed.
/// </param>
/// <returns>
/// TRUE  -  Parameter is successfully updated.
/// FALSE -  Parameter could not be updated.
/// Possible cause is parameter does not exist.
/// </returns>
bool c_RestUriRequestParam::SetParameterValue(CREFSTRING name, CREFSTRING value)
{
    if (m_reqParamCollection->Contains(name))
    {
        m_reqParamCollection->SetValue(name, value);
        return true;
    }

    return false;
}

bool c_RestUriRequestParam::SetParameterType(CREFSTRING name, CREFSTRING value)
{
    if (m_reqParamCollection->Contains(name))
    {
        if (m_paramTypeCollection.Contains(name))
        {
            m_paramTypeCollection.SetValue(name, value);
        }
        else
        {
            m_paramTypeCollection.Add(name, value);
        }
        return true;
    }

    return false;
}

/// <summary>
/// Retrieve the list of all parameters.
/// </summary>
/// <returns>
/// A string collection containing names of all parameters.
/// </returns>
MgStringCollection* c_RestUriRequestParam::GetParameterNames()
{
    Ptr<MgStringCollection> mgsCollection;
    mgsCollection = new MgStringCollection();

    for (int i = 0; i < m_reqParamCollection->GetCount(); i++)
    {
        mgsCollection->Add(m_reqParamCollection->GetName(i));
    }

    return SAFE_ADDREF((MgStringCollection*)mgsCollection);
}

/// <summary>
/// Retrieve the list of all parameters.
/// </summary>
/// <returns>
/// A string collection containing names of all parameters.
/// </returns>
void c_RestUriRequestParam::GetAsUriQuery(REFSTRING Query,MgStringCollection* RemoveParams,MgStringPropertyCollection* AddParams)
{
  Query.reserve(512);
   
  Ptr<MgStringPropertyCollection> params;
  if( RemoveParams || AddParams)    
  {
    params = new MgStringPropertyCollection();
    int count = m_reqParamCollection->GetCount();
    for(int ind=0;ind<count;ind++)
    {
      STRING param_name = m_reqParamCollection->GetName(ind);
      STRING param_value = m_reqParamCollection->GetValue(ind);
      if( RemoveParams && RemoveParams->Contains(param_name))
      {
        // it is to be removed just skip it  - do nothing
      } 
      else
      {
        params->Add(param_name,param_value);
      } 
    }
    
    if( AddParams )
    {
      int count = AddParams->GetCount();
      for(int ind=0;ind<count;ind++)
      {
        STRING param_name = AddParams->GetName(ind);
        STRING param_value = AddParams->GetValue(ind);
        
        if( params->Contains(param_name) )
        {
        // parameter name which is supposed to be added allready exists
        // do nothing; if user wanted to replace parameter then he needs to add parameter into remove list to
        // in this way we are adding posibility to add only if not already exists
        }
        else
        {
          params->Add(param_name,param_value);
        }
      }
    }    
  }
  else
  {
    params = m_reqParamCollection;
  }
    
  for (int i = 0; i < params->GetCount(); i++)
  {
    
    STRING param_name = params->GetName(i);
    STRING param_value = params->GetValue(i);
    
    if( i>=1 )
    {
      Query = Query.append(L"&");
    }
    Query = Query.append(param_name);
    Query = Query.append(L"=");
    Query = Query.append(param_value);
    
  }    
  
  
}

/// <summary>
/// Tells if the specified parameter exists.
/// </summary>
/// <param name="name">Input
/// Name of the parameter.
/// </param>
/// <returns>
/// True is the specified parameters exists
/// </returns>
bool c_RestUriRequestParam::ContainsParameter(CREFSTRING name)
{
    return m_reqParamCollection->Contains(name);
}

/// <summary>
/// Retrieve the list of all parameters.
/// </summary>
MgStringPropertyCollection* c_RestUriRequestParam::GetParameters()
{
    return m_reqParamCollection;
}

void c_RestUriRequestParam::Dispose()
{
    delete this;
}

INT32 c_RestUriRequestParam::GetClassId()
{
    return 0;
}

c_RestUriRequestParam::~c_RestUriRequestParam()
{
}

/// <summary>
/// Stores POSTed XML data as a string
/// </summary>
/// <param name="name">Input
/// The XML data
/// </param>
void c_RestUriRequestParam::SetXmlPostData(const char* xmlData)
{
    m_xmlPostData = xmlData;
}


void c_RestUriRequestParam::SetPostData(string Data)
{
    m_PostData = Data;
}

/// <summary>
/// Returns POSTed XML data as a string
/// </summary>
/// <returns>
/// A string containing the XML data
/// </returns>
string& c_RestUriRequestParam::GetXmlPostData()
{
    return m_xmlPostData;
}


string& c_RestUriRequestParam::GetPostData()
{
    return m_PostData;
}