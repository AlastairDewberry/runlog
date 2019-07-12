// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include "RunlogImport.hpp"
#include <xercesc/sax/AttributeList.hpp>
#include <xercesc/sax/SAXParseException.hpp>
#include <xercesc/sax/SAXException.hpp>



// ---------------------------------------------------------------------------
//  RunlogImportHandlers: Constructors and Destructor
// ---------------------------------------------------------------------------
RunlogImportHandlers::RunlogImportHandlers() :

    fAttrCount(0)
    , fCharacterCount(0)
    , fElementCount(0)
    , fSpaceCount(0)
    , fSawErrors(false)
{
}

RunlogImportHandlers::~RunlogImportHandlers()
{
}


// ---------------------------------------------------------------------------
//  RunlogImportHandlers: Implementation of the SAX DocumentHandler interface
// ---------------------------------------------------------------------------
void RunlogImportHandlers::startElement(const   XMLCh* const    /* name */
                                    ,       AttributeList&  attributes)
{
    fElementCount++;
    fAttrCount += attributes.getLength();
}

void RunlogImportHandlers::characters(  const   XMLCh* const    /* chars */
								    , const XMLSize_t       length)
{
    fCharacterCount += length;
}

void RunlogImportHandlers::ignorableWhitespace( const   XMLCh* const /* chars */
										    , const XMLSize_t    length)
{
    fSpaceCount += length;
}

void RunlogImportHandlers::resetDocument()
{
    fAttrCount = 0;
    fCharacterCount = 0;
    fElementCount = 0;
    fSpaceCount = 0;
}


// ---------------------------------------------------------------------------
//  RunlogImportHandlers: Overrides of the SAX ErrorHandler interface
// ---------------------------------------------------------------------------
void RunlogImportHandlers::error(const SAXParseException& e)
{
    fSawErrors = true;
    XERCES_STD_QUALIFIER cerr << "\nError at file " << StrX(e.getSystemId())
		 << ", line " << e.getLineNumber()
		 << ", char " << e.getColumnNumber()
         << "\n  Message: " << StrX(e.getMessage()) << XERCES_STD_QUALIFIER endl;
}

void RunlogImportHandlers::fatalError(const SAXParseException& e)
{
    fSawErrors = true;
    XERCES_STD_QUALIFIER cerr << "\nFatal Error at file " << StrX(e.getSystemId())
		 << ", line " << e.getLineNumber()
		 << ", char " << e.getColumnNumber()
         << "\n  Message: " << StrX(e.getMessage()) << XERCES_STD_QUALIFIER endl;
}

void RunlogImportHandlers::warning(const SAXParseException& e)
{
    XERCES_STD_QUALIFIER cerr << "\nWarning at file " << StrX(e.getSystemId())
		 << ", line " << e.getLineNumber()
		 << ", char " << e.getColumnNumber()
         << "\n  Message: " << StrX(e.getMessage()) << XERCES_STD_QUALIFIER endl;
}

void RunlogImportHandlers::resetErrors()
{
    fSawErrors = false;
}
