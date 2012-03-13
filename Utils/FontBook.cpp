//
//  FontBook.cpp
//  emptyExample
//
//  Created by Nick Hardeman on 3/13/12.
//

#include "FontBook.h"

FontBook* FontBook::__instance = 0;

//--------------------------------------------------------------
FontBook* FontBook::Instance() {
	if (__instance == 0) {
		__instance = new FontBook();
	}
	return __instance;
}

//--------------------------------------------------------------
void FontBook::addFont( string a_url, string a_name ) {
	Instance();
    if(!__instance->bHasFont( a_name )) {
        Font* f     = new Font();
        f->url      = a_url;
        f->name     = a_name;
        __instance->_fonts[f->name] = f;
    }
}

//--------------------------------------------------------------
ofTrueTypeFont* FontBook::getFont(string a_name, int a_size, int lineHeight ) {
	Instance();
    if(__instance->bHasFont(a_name)) {
        return __instance->_fonts[a_name]->getFont( a_size, lineHeight );
    }
	return NULL;
}

//--------------------------------------------------------------
string FontBook::fitStringInWidth( ofTrueTypeFont* a_font, string inStr, float a_maxWidth ) {
    string outString = inStr;
    int lastFound   = (int)inStr.size();
    int numTries    = 0;
    int found       = 0;
    
    // find_last_not_of ( char c, size_t pos = npos ) const;
    ofRectangle drawStrRect = a_font->getStringBoundingBox(outString, 0, 0);
    
    if(drawStrRect.width < a_maxWidth) return outString;
    
    while(drawStrRect.width >= a_maxWidth) {
        numTries++;
        found = (int)outString.find_last_of(" ", lastFound);
        if (found != string::npos) {
            outString = outString.substr(0, found) + "\n" + outString.substr(found+1 );
            drawStrRect = a_font->getStringBoundingBox(outString, 0, 0);
            lastFound = found;
        } else {
            break;
        }
        if(numTries > 50) {
            ofLog(OF_LOG_WARNING, "FontBook :: fitStringInWidth : num tries exceeded = " + ofToString( numTries, 0));  
            break;
        }
    }
    
    return outString;
}

//--------------------------------------------------------------
string FontBook::truncateStringToWidth( ofTrueTypeFont* a_font, string inStr, float a_maxWidth, string a_trunc ) {
    string outString = inStr;
    int lastFound   = (int)inStr.size();
    int numTries    = 0;
    int found       = 0;
    
    // find_last_not_of ( char c, size_t pos = npos ) const;
    ofRectangle drawStrRect = a_font->getStringBoundingBox(outString, 0, 0);
    if(drawStrRect.width < a_maxWidth) return outString;
    
    while(drawStrRect.width >= a_maxWidth) {
        numTries++;
        found = (int)outString.find_last_of(" ", lastFound);
        if (found != string::npos) {
            outString = outString.substr(0, found);
            //cout << "numTries: " << numTries << " out = " <<  outString << " found = " << found << endl;
            drawStrRect = a_font->getStringBoundingBox(outString, 0, 0);
            //outString += a_trunc;
            lastFound = found;
        } else {
            break;
        }
        if(numTries > 50) {
            ofLog(OF_LOG_WARNING, "FontBook :: fitStringInWidth : num tries exceeded = " + ofToString( numTries, 0));  
            break;
        }
    }
    if(numTries > 1) outString += a_trunc;
    return outString;
}

//--------------------------------------------------------------
void FontBook::destroy() {
    for(map<string, Font*>::iterator it = __instance->_fonts.begin(); it != __instance->_fonts.end(); ++it) {
        delete ((Font*)it->second);
    }
    
    if (__instance != 0) {
        delete __instance;
        __instance = NULL;
    }
}

