#!/bin/bash
clear

RLexe=RunlogImport.x
#xmldata=sample.xml
xmldata=test.gpx

# Delete old executable
[ -f "$RLexe" ] && rm ./$RLexe

g++ -g -Wall -pedantic -I/opt/include -L/opt/lib RunlogImport.cpp RunlogImportHandlers.cpp -o $RLexe -lxerces-c
# -DMAIN_TEST
# >(tee compile.output)

echo ""
ls -lt
echo ""

[ -f "$RLexe" ] && ./$RLexe $xmldata
