//
//  FontBook.h
//  emptyExample
//
//  Created by Nick Hardeman on 3/13/12.
//  Copyright (c) 2012. All rights reserved.
//

#pragma once 

#include "ofMain.h"

class Font {
public:
    string name, url;
    map<int, ofTrueTypeFont> ttfs;
    
    ~Font() {
        ttfs.clear();
    }
    
    bool bHasSize(int a_size) {
		return ttfs.find(a_size) != ttfs.end();
	}
    
    void addSize( int a_size, int lineHeight = 0, bool _bAntiAliased=true, bool _bFullCharacterSet=false, 
                    bool makeContours=false, float simplifyAmt=0.3, int dpi=0 ) {
        if(!bHasSize(a_size)) {
            ofTrueTypeFont _ttf;
            _ttf.loadFont( url, a_size, _bAntiAliased, _bFullCharacterSet, makeContours, simplifyAmt, dpi );
            
            if(lineHeight > 0) {
                _ttf.setLineHeight( lineHeight );
            }
            ttfs[a_size] = _ttf;
        }
    }
    
    ofTrueTypeFont* getFont( int a_size, int lineHeight = 0 ) {
        if(!bHasSize(a_size)) {
            addSize( a_size, lineHeight );
        }
        return &ttfs[a_size];
    }
    
};

class FontBook {
public:
	
	static FontBook* Instance();
	
	static void addFont( string a_url, string a_name );
    static ofTrueTypeFont* getFont( string a_name, int a_size, int lineHeight=0 );
    static string fitStringInWidth( ofTrueTypeFont* a_font, string inStr, float a_maxWidth );
    static string truncateStringToWidth( ofTrueTypeFont* a_font, string inStr, float a_maxWidth, string a_trunc=" ..." );
    static void destroy();
	
private:
	static FontBook* __instance;
    map<string,Font*> _fonts;
    bool bHasFont(string a_name) {
        return _fonts.find(a_name) != _fonts.end();
    }
};





