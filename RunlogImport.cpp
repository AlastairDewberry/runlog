// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include "RunlogImport.hpp"
#if defined(XERCES_NEW_IOSTREAMS)
#include <fstream>
#else
#include <fstream.h>
#endif
#include <xercesc/util/OutOfMemoryException.hpp>

// ---------------------------------------------------------------------------
//  Local helper methods
// ---------------------------------------------------------------------------
void usage()
{
    XERCES_STD_QUALIFIER cout << "\nUsage:\n"
            "    RunlogImport [-v=level] <XML file | XML folder>\n\n"
            "This program invokes the SAX Parser, and then prints the\n"
            "number of elements, attributes, spaces and characters found\n"
            "in each XML file, using SAX API.\n\n"
            "Options:\n"
            "    -v=level   Verbosity level.\n"
         << XERCES_STD_QUALIFIER endl;
}


// ---------------------------------------------------------------------------
//  Program entry point
// ---------------------------------------------------------------------------
int main(int argC, char* argV[])
{

    // Check command line and extract arguments.
    if (argC < 2)
    {
        usage();
        return 1;
    }

    const char*              xmlFile = 0;
    //SAXParser::ValSchemes    valScheme = SAXParser::Val_Auto;
    bool                     errorOccurred = false;
    int                      diagLevel = 5;

    // Check if additional diagnostics required
    if (!strncmp(argV[1], "-v=", 3)
    ||  !strncmp(argV[1], "-V=", 3)) {

      const char* const parm = &argV[1][3];

      XERCES_STD_QUALIFIER cout << "diagnostic level: " << parm << " default (" << diagLevel << ")"
            << XERCES_STD_QUALIFIER endl;

      // get new diagnostic level

    }

    // Get xml filename
    xmlFile = argV[argC-1];

    // Initialize the XML4C2 system
    try
    {
      XMLPlatformUtils::Initialize();
    }

    catch (const XMLException& toCatch)
    {
        XERCES_STD_QUALIFIER cerr << "Error during initialization! Message:\n"
            << StrX(toCatch.getMessage()) << XERCES_STD_QUALIFIER endl;
        return 1;
    }

    //
    //  Create and initialise SAX parser object.
    //
    SAXParser* parser = new SAXParser;

    parser->setValidationScheme(SAXParser::Val_Auto);
    parser->setDoNamespaces(false);
    parser->setDoSchema(false);
    parser->setHandleMultipleImports (true);
    parser->setValidationSchemaFullChecking(false);

    //
    //  Create our SAX handler object and install it on the parser, as the
    //  document and error handler.
    //
    RunlogImportHandlers handler;
    parser->setDocumentHandler(&handler);
    parser->setErrorHandler(&handler);


    //
    //  Get the starting time and kick off the parse of the indicated
    //  file. Catch any exceptions that might propogate out of it.
    //
    unsigned long duration;

    //reset error count first
    handler.resetErrors();

    try
    {
        const unsigned long startMillis = XMLPlatformUtils::getCurrentMillis();
        parser->parse(xmlFile);
        const unsigned long endMillis = XMLPlatformUtils::getCurrentMillis();
        duration = endMillis - startMillis;
    }
    catch (const OutOfMemoryException&)
    {
        XERCES_STD_QUALIFIER cerr << "OutOfMemoryException" << XERCES_STD_QUALIFIER endl;
        errorOccurred = true;
    }
    catch (const XMLException& e)
    {
        XERCES_STD_QUALIFIER cerr << "\nError during parsing: '" << xmlFile << "'\n"
            << "Exception message is:  \n"
            << StrX(e.getMessage()) << "\n" << XERCES_STD_QUALIFIER endl;
        errorOccurred = true;
    }

    catch (...)
    {
        XERCES_STD_QUALIFIER cerr << "\nUnexpected exception during parsing: '" << xmlFile << "'\n";
        errorOccurred = true;
    }


    // Print out the stats that we collected and time taken
    if (!handler.getSawErrors())
    {
        XERCES_STD_QUALIFIER cout << xmlFile << ": " << duration << " ms ("
            << handler.getElementCount() << " elems, "
            << handler.getAttrCount() << " attrs, "
            << handler.getSpaceCount() << " spaces, "
            << handler.getCharacterCount() << " chars)" << XERCES_STD_QUALIFIER endl;
    }
    else
        errorOccurred = true;

    //
    //  Delete the parser itself.  Must be done prior to calling Terminate, below.
    //
    delete parser;

    // And call the termination method
    XMLPlatformUtils::Terminate();

    if (errorOccurred)
        return 4;
    else
        return 0;

}
