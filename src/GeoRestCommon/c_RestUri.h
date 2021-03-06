//
//  Copyright (C) 2009 by  Haris Kurtagic  www.sl-king.com
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

#ifndef _c_RestUri_h
#define _c_RestUri_h


#include "c_RestUriPathParam.h"

#include "c_RestUriRequestMetadata.h"

/// <summary>
/// Purpose of this class is to store request header variables, request parameters
/// and request meta data for use in Common MapAgent API (CMA).
/// </summary>
	

class IsapiPostParser;


	
class REST_COMMON_API c_RestUri : public MgDisposable
{
    EXTERNAL_API:
  c_RestUri(const std::string& FullUri,const std::string& BaseUri,const std::string& RestUri,const std::string& HttpMethod,const std::string& XmlPostData);

        
        
        //void SetPostData(IsapiPostParser* PostData);
        //IsapiPostParser* GetPostData();
        
       

        /// <summary>
        /// Makes available the pointer to RequestParam class.
        /// User will use this class instance to add
        /// all parameters specified for a request.
        /// </summary>
        /// <returns>Pointer to MgHttpRequestParam class</returns>
        c_RestUriRequestParam* GetRequestParam();

        /// <summary>
        /// Makes available the pointer to RequestMetadata class.
        /// User will use this class instance to add
        /// all required request metadata.
        /// </summary>
        /// <returns>Pointer to MgHttpRequestMetadata class</returns>
        c_RestUriRequestMetadata* GetRequestMetadata();

        
public:
  enum e_HttpMethod
  {
    e_HttpMethod_Undefined,
    e_HttpMethod_Get,
    e_HttpMethod_Post,
    e_HttpMethod_Put,
    e_HttpMethod_Delete,
    e_HttpMethod_Option,
    e_HttpMethod_Head,
  };

    INTERNAL_API:
        c_RestUri();

        /// <summary>
        /// Destructor to clean up internal objects
        /// </summary>
        virtual ~c_RestUri();
        
        c_RestUriPathSegment* GetUriPathParameters();
        
        const std::string& GetHttpMethodString() { return m_HttpMethod; }
        void SetHttpMethod(const std::string& HttpMethod) { m_HttpMethod = HttpMethod; }
        
        e_HttpMethod GetHttpMethod();
        
        
        
        const std::string& GetBaseUri() const { return m_BaseUri; }
        //void SetBaseUri(const std::string& BaseUri) { m_BaseUri = BaseUri; }
        
        // GetFullUri.. creates new full uri by changing original one
        // RemoveParams- parameters to be removed from original parameters
        // AddParams- parameters to be be added to original parameters
        // If parameter already exists and needs to be replaced then it has to be added to remove and also to add list
        // if only in add list then it will be added if already not defined
        void GetFullUri(std::string& Uri,MgStringCollection* RemoveParams,MgStringPropertyCollection* AddParams) const;
        
        const std::string& GetOriginalFullUri() const { return m_OriginalFullUri; }
        //void SetFullUri(const std::string& FullUri) { m_FullUri = FullUri; }
        
        //const std::string& GetRestUri() const { return m_RestUri; }
        
        static void ParseUri(const std::string& Uri, std::vector < std::string > & UriSegments);
        static void ParseQuery(const char* pszQuery, c_RestUriRequestParam* params);
        static void ParsePath(const std::string& Uri, c_RestUriPathSegment* Params);
        
    protected:
        /// <summary>
        /// This method is responsible for releasing all
        /// its member variables and then destruct itself.
        /// </summary>
        /// <returns>Returns nothing</returns>
        virtual void Dispose();

        /// <summary>
        /// Get the class Id
        /// </summary>
        /// <returns>
        /// The integer value
        /// </returns>
        INT32 GetClassId();
        
        
        static void ParseOneParameter(string sParameter, c_RestUriRequestParam* params);
        
protected:
           
      Ptr<c_RestUriRequestParam> m_RestRequestParam;
      Ptr<c_RestUriRequestMetadata> m_RestRequestMetadata;
                 
      std::string m_RestUri;
      std::string m_BaseUri;
      
      std::string m_OriginalFullUri;
      std::string m_OriginalFullUri_WithoutQuery; // WithoutQuery is original full uri wuthout query
      std::string m_OriginalFullUri_Query;   // query part of full uri
      
      
      std::string m_HttpMethod;
      Ptr<c_RestUriPathSegment> m_UriPathParameters;
      
     
    public: 
      

CLASS_ID:
        static const INT32 m_cls_id = 0; //HttpHandler_MapAgent_HttpRestRequest;
};

#endif
