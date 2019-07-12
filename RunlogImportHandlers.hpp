// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include <xercesc/sax/HandlerBase.hpp>

XERCES_CPP_NAMESPACE_USE

XERCES_CPP_NAMESPACE_BEGIN
class AttributeList;
XERCES_CPP_NAMESPACE_END

class RunlogImportHandlers : public HandlerBase
{
public:
    // -----------------------------------------------------------------------
    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    RunlogImportHandlers();
    ~RunlogImportHandlers();


    // -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------
    XMLSize_t getElementCount() const
    {
        return fElementCount;
    }

    XMLSize_t getAttrCount() const
    {
        return fAttrCount;
    }

    XMLSize_t getCharacterCount() const
    {
        return fCharacterCount;
    }

    bool getSawErrors() const
    {
        return fSawErrors;
    }

    XMLSize_t getSpaceCount() const
    {
        return fSpaceCount;
    }


    // -----------------------------------------------------------------------
    //  Handlers for the SAX DocumentHandler interface
    // -----------------------------------------------------------------------
    void startElement(const XMLCh* const name, AttributeList& attributes);
    void characters(const XMLCh* const chars, const XMLSize_t length);
    void ignorableWhitespace(const XMLCh* const chars, const XMLSize_t length);
    void resetDocument();


    // -----------------------------------------------------------------------
    //  Handlers for the SAX ErrorHandler interface
    // -----------------------------------------------------------------------
    void warning(const SAXParseException& exc);
    void error(const SAXParseException& exc);
    void fatalError(const SAXParseException& exc);
    void resetErrors();


private:
    // -----------------------------------------------------------------------
    //  Private data members
    //
    //  fAttrCount
    //  fCharacterCount
    //  fElementCount
    //  fSpaceCount
    //      These are just counters that are run upwards based on the input
    //      from the document handlers.
    //
    //  fSawErrors
    //      This is set by the error handlers, and is queryable later to
    //      see if any errors occured.
    // -----------------------------------------------------------------------
    XMLSize_t       fAttrCount;
    XMLSize_t       fCharacterCount;
    XMLSize_t       fElementCount;
    XMLSize_t       fSpaceCount;
    bool            fSawErrors;
};
