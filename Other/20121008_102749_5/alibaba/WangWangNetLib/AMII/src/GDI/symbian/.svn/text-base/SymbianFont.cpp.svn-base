/*
 * Font.cpp
 *
 *  Created on: 2010-2-5
 *      Author: Administrator
 */

#include <gdi.h>
#include <eikenv.h>
#include <libc\string.h>

#include "AMFont.h"
#include "AMAssert.h"

#define CAST( Type, Value ) reinterpret_cast<Type>( Value )

AMInt32 AMFontCreate(AMFont* pFont,AMFontFace face, AMFontStyle style, AMFontSize size)
{
	return 0;
}

AMInt32 AMFontCreate(AMFont* pFont)
	{
	CFont* font;
	TFontSpec FontSpec = CEikonEnv::Static()->NormalFont()->FontSpecInTwips();
	TInt ret = CEikonEnv::Static()->ScreenDevice()->GetNearestFontInTwips(font , FontSpec);
	if( KErrNone == ret )
		{
		*pFont = font;
		}
	return ret;
	}

AMInt32 AMFontDestroy(AMFont font)
	{
	CFont* temp = CAST( CFont*, font );
	CEikonEnv::Static()->ScreenDevice()->ReleaseFont( temp );
	return KErrNone;
	}

AMInt32 AMGetBitmapFont(AMFont* pFont, const AMChar* fontName)
	{
	const AMUChar* temp = CAST( const AMUChar*, fontName ); 
	TPtrC8 name( temp );
	
	TFileName Name;
	Name.Copy( name );

	CFont* font;
	TFontSpec FontSpec( Name, CEikonEnv::Static()->NormalFont()->FontSpecInTwips().iHeight );
	TInt ret = CEikonEnv::Static()->ScreenDevice()->GetNearestFontInTwips(font , FontSpec);
	if( KErrNone == ret )
		{
		*pFont = font;
		}
	return ret;
	}

AMInt32 AMCreateSystemFont(AMFont* pFont, AMFontFace face, AMFontStyle style, AMFontSize size)
	{
	CFont* font;
	TFontSpec FontSpec;
	
	switch( face )
		{
		case AMFONT_FACE_SYSTEM:
			{
			FontSpec.iTypeface.SetIsSymbol( ETrue );
			break;
			}
		case AMFONT_FACE_PROPORTIONAL:
			{
			FontSpec.iTypeface.SetIsProportional( ETrue );
			break;
			}
		case AMFONT_FACE_MONOSPACE:
			{
			FontSpec.iTypeface.SetIsSerif( ETrue );
			break;
			}
		}
	
	if( style & AMFONT_STYLE_PLAIN )
		{
		//FontSpec.iFontStyle.SetStrokeWeight( EStrokeWeightBold );
		}
	else
		{
		//FontSpec.iFontStyle.SetStrokeWeight( EStrokeWeightNormal );
		}
	if( style & AMFONT_STYLE_ITALIC )
		{
		FontSpec.iFontStyle.SetPosture( EPostureItalic );
		}
	else
		{
		FontSpec.iFontStyle.SetPosture( EPostureUpright );
		}
	if( style & AMFONT_STYLE_BOLD )
		{
		FontSpec.iFontStyle.SetStrokeWeight( EStrokeWeightBold );
		}
	else
		{
		FontSpec.iFontStyle.SetStrokeWeight( EStrokeWeightNormal );
		}
	
	FontSpec.iHeight = size;
	
	TInt ret = CEikonEnv::Static()->ScreenDevice()->GetNearestFontInTwips(font , FontSpec);
	if( KErrNone == ret )
		{
		*pFont = font;
		}
	return ret;
	}

AMBool  AMIsTrueTypeFileSupported()
	{
	return ETrue;
	}

AMInt32 AMCreateTrueTypeFont(AMFont* pFont, const AMChar* fileName)
	{
	return AMGetBitmapFont( pFont, fileName );
	}

AMInt32 AMCharsWidth(AMFont font, const AMWChar* text, AMInt32 length)
//AMInt32 AMCharsWidth(AMFont font, const AMChar* text, AMInt32 length)
	{
	//const AMUChar* temp = CAST( const AMUChar*, text ); 
	TPtrC Text( (const TUint16*)text, length );
	
	//TFileName Name;
	//Name.Copy( Text );
	
	CFont* Font = CAST( CFont*, font );
	return Font->TextWidthInPixels( Text );
	}

AMInt32 AMCharHeight(AMFont font)
	{
	CFont* temp = CAST( CFont*, font );
	return temp->HeightInPixels();
	}

AMFontFace AMGetFace(AMFont font)
	{
	
	}

AMFontSize AMGetSize(AMFont font)
	{
	
	}

AMFontStyle AMGetStyle(AMFont font)
	{
	
	}
