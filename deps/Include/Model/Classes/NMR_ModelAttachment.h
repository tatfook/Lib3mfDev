/*++

Copyright (C) 2015 netfabb GmbH (Original Author)

All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

Abstract:

NMR_ModelResource.h defines the Model Resource Class.
A model resource is an in memory representation of the 3MF
resource object.

--*/

#ifndef __NMR_MODELATTACHMENT
#define __NMR_MODELATTACHMENT

#include "Model/Classes/NMR_Model.h" 
#include "Model/Classes/NMR_ModelMetaData.h" 
#include "Common/NMR_Types.h" 
#include "Model/Classes/NMR_ModelTypes.h" 

#include <string>

namespace NMR {

	class CModelAttachment {
	private:
		CModel * m_pModel;
		PImportStream m_pStream;
		std::wstring m_sPathURI;
		std::wstring m_sRelationShipType;

	public:
		CModelAttachment() = delete;
		CModelAttachment(_In_ CModel * pModel, _In_ const std::wstring sPathURI, _In_ const std::wstring sRelationShipType, _In_ PImportStream pStream);
		~CModelAttachment();
				
		_Ret_notnull_ CModel * getModel();
		std::wstring getPathURI();
		std::wstring getRelationShipType();
		PImportStream getStream ();

		void setStream(_In_ PImportStream pStream);
		void setRelationShipType(_In_ const std::wstring sRelationShipType);
	};

	typedef std::shared_ptr <CModelAttachment> PModelAttachment;

}

#endif // __NMR_MODELATTACHMENT
