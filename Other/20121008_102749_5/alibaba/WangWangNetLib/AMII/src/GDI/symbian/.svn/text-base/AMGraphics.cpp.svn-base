/*
 * AMGraphics.cpp
 *
 *  Created on: 2010-2-8
 *      Author: qing.chen
 */
#include <AMGDI.h>
#include <fbs.h>
#include <bitdev.h>
#include <bitstd.h>
#include <coecntrl.h>
#include <eikenv.h>
#include <libc\string.h>

#include "AMWindow.h"
#include "ImageConverterEngine.h"

#define REINTERPRET( Type, NewValue, OldValue ) Type NewValue = reinterpret_cast<Type>( OldValue )

enum CreateType
	{
	ScreenType = 0,
	SystemType,
	ImageType
	};

enum ScreenShowType
	{
	Append = 0,
	Update
	};

enum GraphicsOperation
	{
	DrawLine = 0,
	DrawRect,
	FillRect,
	DrawRoundRect,
	FillRoundRect,
	DrawArc,
	FillArc,
	FillPolygon,
	DrawPolygon,
	DrawTriangle,
	FillTriangle,
	DrawText,
	DrawImage,
	DrawImageArea,
	BitBlt,
	StretchBlt,
	GetClipRect
	};

struct Graphics
	{
	CreateType Type;
	AMRGB Color;
	AMFont Font;
	AMUInt32 Extra[1];
	};

struct WindowAndEnvironment
	{
	CCoeControl* window;
	CEikonEnv* env;
	};

static CWindowGc* BeginSystemDrawing( AMWindow* window );

static void EndSystemDrawing( AMWindow* window );

static CFbsBitGc* BeginImageDrawing( CFbsBitmap* bmp );

static void EndImageDrawing();

static void ShowScreen( Graphics* pGraphics, ScreenShowType showType );

static void DoGraphicsOperation( GraphicsOperation operation, AMGraphics graphics, AMPVoid data );

static void DoDrawOperation( GraphicsOperation operation, CBitmapContext* gc, CGraphicsContext::TPenStyle style, AMRGB color, AMPVoid data, TBool mask = EFalse );

AMInt32 AMGraphicsCreate(AMGraphics* pGraphics)
	{
	RWsSession* iWsSession = new ( ELeave ) RWsSession;
	User::LeaveIfError(iWsSession->Connect());
	RWindowGroup* iWindowGroup = new ( ELeave ) RWindowGroup(*iWsSession);
	User::LeaveIfError(iWindowGroup->Construct((TInt)iWindowGroup, EFalse));
	iWindowGroup->SetOrdinalPosition(0, ECoeWinPriorityAlwaysAtFront);
	iWindowGroup->EnableReceiptOfFocus(EFalse);
	RWsSprite* iSprite = new ( ELeave ) RWsSprite(*iWsSession);
	User::LeaveIfError(iSprite->Construct(*iWindowGroup, TPoint(0,0), 0));
	
	CFbsBitGc *bmpGc;
	CFbsBitmapDevice *bmpDevice;
	
	Graphics* g = (Graphics*) new char[ sizeof( Graphics ) + 4 * sizeof( AMUInt32 ) ];
	*pGraphics = g;
	g->Type = ScreenType;
	g->Color = KRgbBlack.Value();
	g->Extra[0] = (AMUInt32)iSprite;
	g->Extra[1] = (AMUInt32)iWsSession;
	g->Extra[2] = (AMUInt32)iWindowGroup;

	CFbsBitmap* mask = new (ELeave) CFbsBitmap();
	mask->Create(CEikonEnv::Static()->ScreenDevice()->SizeInPixels(), EGray2);
	bmpDevice = CFbsBitmapDevice::NewL(mask);
	CleanupStack::PushL( bmpDevice );
	bmpDevice->CreateContext(bmpGc);
	bmpGc->SetPenColor( KRgbBlack );
	bmpGc->SetBrushColor( KRgbBlack );
	bmpGc->SetPenStyle( CGraphicsContext::ESolidPen );
	bmpGc->SetBrushStyle( CGraphicsContext::ESolidBrush );
	bmpGc->DrawRect( TRect(TPoint(0,0), mask->SizeInPixels()) );
	g->Extra[3] = (AMUInt32)mask;
	CleanupStack::PopAndDestroy( bmpDevice );

	CFbsBitmap* image = new (ELeave) CFbsBitmap();
	image->Create(CEikonEnv::Static()->ScreenDevice()->SizeInPixels(), EColor16M);
	bmpDevice = CFbsBitmapDevice::NewL(image);
	CleanupStack::PushL( bmpDevice );
	bmpDevice->CreateContext(bmpGc);
	g->Extra[4] = (AMUInt32)image;
	CleanupStack::PopAndDestroy( bmpDevice );
	
	ShowScreen( g, Append );
	User::LeaveIfError(iSprite->Activate());
	return KErrNone;
	}

AMInt32 AMCreateImageGraphics(AMGraphics* pGraphics, AMImage image)
	{
	REINTERPRET( CFbsBitmap*, bmp, image );
	
	Graphics* g = (Graphics*) new char[ sizeof( Graphics ) ];
	g->Extra[0] = (AMUInt32)image;
	g->Type = ImageType;
	g->Color = KRgbBlack.Value();
	*pGraphics = g;
	return KErrNone;
	}

AMInt32 AMCreateSystemGraphics(AMGraphics* pGraphics, AMHandle hPlatformGraphics)
	{
	REINTERPRET( WindowAndEnvironment*, temp, hPlatformGraphics );
	Graphics* g = (Graphics*) new char[ sizeof( Graphics ) + sizeof( AMUInt32 ) ];
	memset( g, NULL, sizeof( Graphics ) + sizeof( AMUInt32 ) );
	g->Extra[0] = (AMUInt32)temp->window;
	g->Extra[1] = (AMUInt32)temp->env;
	g->Type = SystemType;
	g->Color = KRgbBlack.Value();
	*pGraphics = g;
	return KErrNone;
	}

AMInt32 AMGraphicsDestroy(AMGraphics graphics)
	{
	REINTERPRET( Graphics*, temp, graphics );
	if( ImageType == temp->Type )
		{
		REINTERPRET( CFbsBitGc*, gc, temp->Extra[0] );
		delete gc;
		CleanupStack::PopAndDestroy( temp );
		}
	else if( SystemType == temp->Type )
		{
		REINTERPRET( AMWindow*, gc, temp->Extra[0] );
		}
	else if( ScreenType == temp->Type )
		{
		REINTERPRET( CFbsBitGc*, imageGc, temp->Extra[6] );
		delete imageGc;
		REINTERPRET( CFbsBitGc*, maskGc, temp->Extra[4] );
		delete maskGc;
		REINTERPRET( CFbsBitmap*, image, temp->Extra[5] );
		delete image;
		REINTERPRET( CFbsBitmap*, mask, temp->Extra[3] );
		delete mask;
		REINTERPRET( RWsSprite*, sprite, temp->Extra[0] );
		sprite->Close();
		delete sprite;
		REINTERPRET( RWindowGroup*, group, temp->Extra[2] );
		group->Close();
		delete group;
		REINTERPRET( RWsSession*, session, temp->Extra[1] );
		session->Close();
		delete session;
		
		delete temp;
		}
	return KErrNone;
	}

AMInt32 AMGetGraphicWidth(AMGraphics graphics)
	{
	REINTERPRET( Graphics*, temp, graphics );
	if( ImageType == temp->Type )
		{
		REINTERPRET( CFbsBitGc*, gc, temp->Extra[0] );
		return gc->Device()->SizeInPixels().iWidth;
		}
	else if( SystemType == temp->Type )
		{
		REINTERPRET( AMWindow*, window, temp->Extra[0] );
		return window->Rect().Width();
		}
	else if( ScreenType == temp->Type )
		{
		REINTERPRET( CFbsBitmap*, bitmap, temp->Extra[4] );
		CFbsBitmapDevice *bmpDevice = CFbsBitmapDevice::NewL(bitmap);
		CleanupStack::PushL( bmpDevice );
		AMInt32 ret = bmpDevice->SizeInPixels().iWidth;
		CleanupStack::PopAndDestroy( bmpDevice );
		return ret;
		}
	return KErrNotFound;
	}

AMInt32 AMGetGraphicHeigth(AMGraphics graphics)
	{
	REINTERPRET( Graphics*, temp, graphics );
	if( ImageType == temp->Type )
		{
		REINTERPRET( CFbsBitGc*, gc, temp->Extra[0] );
		return gc->Device()->SizeInPixels().iHeight;
		}
	else if( SystemType == temp->Type )
		{
		REINTERPRET( AMWindow*, window, temp->Extra[0] );
		return window->Rect().Height();
		}
	else if( ScreenType == temp->Type )
		{
		REINTERPRET( CFbsBitmap*, bitmap, temp->Extra[4] );
		CFbsBitmapDevice *bmpDevice = CFbsBitmapDevice::NewL(bitmap);
		CleanupStack::PushL( bmpDevice );
		AMInt32 ret = bmpDevice->SizeInPixels().iHeight;
		CleanupStack::PopAndDestroy( bmpDevice );
		return ret;
		}
	return KErrNotFound;
	}

AMRGB AMGetColor(AMGraphics graphics)
	{
	REINTERPRET( Graphics*, temp, graphics );
	return temp->Color;
	}

AMInt32 AMSetColor(AMGraphics graphics, AMRGB rgb)
	{
	REINTERPRET( Graphics*, temp, graphics );
	temp->Color = rgb;
	return KErrNone;
	}

ADAPTER_API AMRGB AMGetBGColor(AMGraphics graphics)
	{
		//todo:
		return 0;
	}

ADAPTER_API AMInt32 AMSetBGColor(AMGraphics graphics, AMRGB rgb)
	{
		//todo:
		return 0;
	}

ADAPTER_API AMRGB AMGetFGColor(AMGraphics graphics)
	{
		//todo:
		return 0;
	}

ADAPTER_API AMInt32 AMSetFGColor(AMGraphics graphics, AMRGB rgb)
	{
		//todo:
		return 0;
	}


AMInt32 AMDrawLine(AMGraphics graphics, AMPoint* p1, AMPoint* p2)
	{
	AMPoint data[2] = { *p1, *p2 };
	DoGraphicsOperation( DrawLine, graphics, &data );
	}

AMInt32 AMDrawRect(AMGraphics graphics, AMRect* rect)
	{
	DoGraphicsOperation( DrawRect, graphics, rect );
	}

AMInt32 AMFillRect(AMGraphics graphics, AMRect* rect)
	{
	DoGraphicsOperation( FillRect, graphics, rect );
	}

AMInt32 AMDrawRoundRect(AMGraphics graphics, AMRect* rect, AMInt32 arcWidth, AMInt32 arcHeight)
	{
	AMInt32 data[6] = { rect->x, rect->y, rect->w, rect->h, arcWidth, arcHeight };
	DoGraphicsOperation( DrawRoundRect, graphics, data );
	}

AMInt32 AMFillRoundRect(AMGraphics graphics, AMRect* rect, AMInt32 arcWidth, AMInt32 arcHeight)
	{
	AMInt32 data[6] = { rect->x, rect->y, rect->w, rect->h, arcWidth, arcHeight };
	DoGraphicsOperation( FillRoundRect, graphics, data );
	}

AMInt32 AMFillArc(AMGraphics graphics, AMRect* rect, AMInt32 startAngle, AMInt32 arcAngle)
	{
	AMInt32 data[6] = { rect->x, rect->y, rect->w, rect->h, startAngle, arcAngle };
	DoGraphicsOperation( DrawArc, graphics, data );
	}

AMInt32 AMDrawArc(AMGraphics graphics, AMRect* rect, AMInt32 startAngle, AMInt32 arcAngle)
	{
	AMInt32 data[6] = { rect->x, rect->y, rect->w, rect->h, startAngle, arcAngle };
	DoGraphicsOperation( FillArc, graphics, data );
	}

AMInt32 AMFillPolygon(AMGraphics graphics, AMPoint points[], AMInt32 nPoints)
	{
	AMInt32 data[2] = { (AMInt32)points, nPoints };
	DoGraphicsOperation( FillPolygon, graphics, data );
	}

AMInt32 AMDrawPolygon(AMGraphics graphics, AMPoint points[], AMInt32 nPoints)
	{
	AMInt32 data[2] = { (AMInt32)points, nPoints };
	DoGraphicsOperation( DrawPolygon, graphics, data );
	}

AMInt32 AMDrawTriangle(AMGraphics graphics, AMPoint* p1, AMPoint* p2,  AMPoint* p3)
	{
	AMPoint data[3] = { *p1, *p2, *p3 };
	DoGraphicsOperation( DrawTriangle, graphics, data );
	}

AMInt32 AMFillTriangle(AMGraphics graphics, AMPoint* p1, AMPoint* p2,  AMPoint* p3)
	{
	AMPoint data[3] = { *p1, *p2, *p3 };
	DoGraphicsOperation( FillTriangle, graphics, data );
	}

AMInt32 AMDrawText(AMGraphics graphics, const AMWChar* str, AMPoint* point, AMInt32 startPos, AMInt32 len)
//AMInt32 AMDrawText(AMGraphics graphics, const AMChar* str, AMPoint* point, AMInt32 startPos, AMInt32 len)
	{
	//REINTERPRET( const AMUChar*, temp, str );
	TPtrC ptr((const TUint16*)str);
	HBufC* buf = HBufC::NewLC( ptr.Length() );
	buf->Des().Copy( ptr );

	AMInt32 data[5] = { 0, (AMInt32)buf, (AMInt32)point, startPos, len };

	REINTERPRET( Graphics*, g, graphics );
	if( g->Font != NULL )
		{
		data[0] = (AMInt32)g->Font;
		}
	else
		{
		REINTERPRET( CEikonEnv*, env, g->Extra[1] );
		data[0] = (AMInt32)env->NormalFont();
		}

	DoGraphicsOperation( DrawText, graphics, data );
	CleanupStack::PopAndDestroy( buf );
	}

AMInt32 AMGetClipX(AMGraphics graphics)
{
	return 0;
}

AMInt32 AMGetClipY(AMGraphics graphics)
{
	return 0;
}

AMInt32 AMGetClipWidth(AMGraphics graphics)
{
	REINTERPRET( Graphics*, temp, graphics );
	if( SystemType == temp->Type )
		{
		REINTERPRET( AMWindow*, window, temp->Extra[0] );
		return window->Rect().Width();
		}
}

AMInt32 AMGetClipHeight(AMGraphics graphics)
{
	REINTERPRET( Graphics*, temp, graphics );
	if( SystemType == temp->Type )
		{
		REINTERPRET( AMWindow*, window, temp->Extra[0] );
		return window->Rect().Width();
		}
}

AMInt32 AMClipRect(AMGraphics graphics, AMRect* rect)
	{
	AMPoint data[1] = { (AMInt32)rect };
	//DoGraphicsOperation( GetClipRect, graphics, data );	
	
	REINTERPRET( Graphics*, temp, graphics );
	if( ImageType == temp->Type )
		{
		REINTERPRET( CFbsBitmap*, bmp, temp->Extra[0] );
		CFbsBitGc* bmpGc = BeginImageDrawing( bmp );
		TText8* This = (TText8*)bmpGc;
		TRect* Rect = (TRect*)(This + 0x30);
		rect->x = Rect->iTl.iX;
		rect->y = Rect->iTl.iY;
		rect->w = Rect->Size().iWidth;
		rect->h = Rect->Size().iHeight;
		EndImageDrawing();
		}
	else if( SystemType == temp->Type )
		{
		REINTERPRET( AMWindow*, window, temp->Extra[0] );
		CWindowGc* gc = BeginSystemDrawing( window );
		gc->SetClippingRect( TRect( TPoint( rect->x, rect->y ), TSize( rect->w, rect->h ) ) );
		EndSystemDrawing( window );
		}
	else if( ScreenType == temp->Type )
		{
		REINTERPRET( CFbsBitmap*, bitmap, temp->Extra[4] );
		CFbsBitGc* bmpGc = BeginImageDrawing( bitmap );
		TText8* This = (TText8*)bmpGc;
		TRect* rect = (TRect*)(This + 0x30);
		EndImageDrawing();
		
		REINTERPRET( CFbsBitmap*, mask, temp->Extra[3] );
		CFbsBitGc *maskGc = BeginImageDrawing( mask );
		This = (TText8*)maskGc;
		rect = (TRect*)(This + 0x30);
		ShowScreen( temp, Update );
		}
	}

AMInt32  AMSetClip(AMGraphics graphics, AMRect* rect)
	{
	
	}

AMFont AMGetFont(AMGraphics graphics)
	{
	REINTERPRET( Graphics*, temp, graphics );
	return temp->Font;
	}

AMFont AMSetFont(AMGraphics graphics, AMFont font)
	{
	REINTERPRET( Graphics*, temp, graphics );
	AMFont ret = temp->Font;
	temp->Font = font;
	return ret;
	}

AMInt32 AMDrawImage(AMGraphics graphics, AMPoint* point, AMImage img, AMDrawMode /* drawMode */)
	{
	AMInt32 data[2] = { (AMInt32)img, (AMInt32)point };
	DoGraphicsOperation( DrawImage, graphics, data );
	}

AMInt32 AMDrawImageArea(AMGraphics graphics, AMPoint* point, AMImage img, AMRect* rect, AMDrawMode /* drawMode */)
	{
	AMInt32 data[3] = { (AMInt32)img, (AMInt32)point, (AMInt32)rect };
	DoGraphicsOperation( DrawImageArea, graphics, data );
	}

AMInt32 AMBitBlt(AMGraphics dst, AMRect* rect, AMGraphics src, AMPoint* point, AMDrawMode /* drawMode */)
	{
	REINTERPRET( Graphics*, temp, src );
	REINTERPRET( CFbsBitmap*, bmp, temp->Extra[0] );
	AMInt32 data[3] = { (AMInt32)rect, (AMInt32)bmp, (AMInt32)point };
	DoGraphicsOperation( BitBlt, dst, data );
	}

AMInt32 AMStretchBlt(AMGraphics dst, AMRect* dstRect, AMGraphics src, AMRect* srcRect, AMDrawMode /* drawMode */)
	{
	REINTERPRET( Graphics*, temp, src );
	REINTERPRET( CFbsBitmap*, bmp, temp->Extra[0] );
	AMInt32 data[3] = { (AMInt32)dstRect, (AMInt32)bmp, (AMInt32)srcRect };
	DoGraphicsOperation( StretchBlt, dst, data );
	}

AMInt32 AMScale (AMGraphics graphics, AMFloat x, AMFloat y) 
	{
	REINTERPRET( Graphics*, temp, graphics );
	if( ImageType == temp->Type )
		{
		CImageConverterEngine* engine = CImageConverterEngine::NewL( (AMPVoid*)&temp->Extra[0] );
		CleanupStack::PushL( engine );
		engine->StartToScale( x, y );
		CleanupStack::PopAndDestroy( engine );
		}
	else if( SystemType == temp->Type )
		{
		return 0;
		}
	else if( ScreenType == temp->Type )
		{
		CImageConverterEngine* engine = CImageConverterEngine::NewL( (AMPVoid*)&temp->Extra[4] );
		CleanupStack::PushL( engine );
		engine->StartToScale( x, y );
		
		engine->ResetImage( (AMPVoid*)&temp->Extra[3] );
		engine->StartToScale( x, y );
		
		CleanupStack::PopAndDestroy( engine );
		
		ShowScreen( temp, Update );
		}
	return 0;
	}

AMInt32 AMRotate(AMGraphics graphics, AMFloat angle)
	{
	REINTERPRET( Graphics*, temp, graphics );
	if( ImageType == temp->Type )
		{
		CImageConverterEngine* engine = CImageConverterEngine::NewL( (AMPVoid*)&temp->Extra[0] );
		CleanupStack::PushL( engine );
		engine->StartToRotate( angle );
		CleanupStack::PopAndDestroy( engine );
		}
	else if( SystemType == temp->Type )
		{
		return 0;
		}
	else if( ScreenType == temp->Type )
		{
		CImageConverterEngine* engine = CImageConverterEngine::NewL( (AMPVoid*)&temp->Extra[4] );
		CleanupStack::PushL( engine );
		engine->StartToRotate( angle );
		
		engine->ResetImage( (AMPVoid*)&temp->Extra[3] );
		engine->StartToRotate( angle );
		
		CleanupStack::PopAndDestroy( engine );
		
		ShowScreen( temp, Update );
		}
	return 0;
	}

AMInt32 AMUpdateRect(AMGraphics graphics, AMRect* rect)
	{
	REINTERPRET( Graphics*, temp, graphics );
	if( ImageType == temp->Type )
		{
		return KErrNone;
		}
	else if( SystemType == temp->Type )
		{
		REINTERPRET( AMWindow*, window, temp->Extra[0] );
		window->DrawNow( TRect( TPoint( rect->x, rect->y ), TSize( rect->w, rect->h ) ) );
		}
	else if( ScreenType == temp->Type )
		{
		return KErrNone;
		}
	}

CWindowGc* BeginSystemDrawing( AMWindow* window )
	{
	CWindowGc& gc = window->SystemGc();
	TRect rect = window->Rect();
	window->ActivateGc();
	window->Window().Invalidate( rect );
	window->Window().BeginRedraw( rect );
	return &gc;
	}

void EndSystemDrawing( AMWindow* window )
	{
	window->Window().EndRedraw();
	window->DeactivateGc();
	}

CFbsBitGc* BeginImageDrawing( CFbsBitmap* bmp )
	{
	CFbsBitGc *bmpGc;
	CFbsBitmapDevice *bmpDevice;
	
	bmpDevice = CFbsBitmapDevice::NewL(bmp);
	CleanupStack::PushL( bmpDevice );
	bmpDevice->CreateContext(bmpGc);
	CleanupStack::PushL( bmpGc );
	return bmpGc;
	}

void EndImageDrawing()
	{
	CleanupStack::PopAndDestroy( 2 );	// bmpGc, bmpDevice
	}

void ShowScreen( Graphics* pGraphics, ScreenShowType showType )
	{
	REINTERPRET( CFbsBitmap*, bitmap, pGraphics->Extra[4] );
	REINTERPRET( CFbsBitmap*, mask, pGraphics->Extra[3] );
	TSpriteMember CurImage;
	CurImage.iBitmap = bitmap;
	CurImage.iMaskBitmap = mask;
	CurImage.iInvertMask = EFalse;
	CurImage.iDrawMode=CGraphicsContext::EDrawModePEN;
	CurImage.iOffset = TPoint (0,0);
	CurImage.iInterval = 0;	
	REINTERPRET( RWsSprite*, sprite, pGraphics->Extra[0] );
	if( Append == showType )
		{
		sprite->AppendMember(CurImage);
		}
	else
		{
		sprite->UpdateMember( 0, CurImage );
		}
	}

void DoGraphicsOperation( GraphicsOperation operation, AMGraphics graphics, AMPVoid data )
	{
	REINTERPRET( Graphics*, temp, graphics );
	if( ImageType == temp->Type )
		{
		REINTERPRET( CFbsBitmap*, bmp, temp->Extra[0] );
		CBitmapContext* bmpGc = BeginImageDrawing( bmp );
		DoDrawOperation( operation, bmpGc, CGraphicsContext::ESolidPen, temp->Color, data );
		EndImageDrawing();
		}
	else if( SystemType == temp->Type )
		{
		REINTERPRET( AMWindow*, window, temp->Extra[0] );
		CBitmapContext* gc = BeginSystemDrawing( window );
		DoDrawOperation( operation, gc, CGraphicsContext::ESolidPen, temp->Color, data );
		EndSystemDrawing( window );
		}
	else if( ScreenType == temp->Type )
		{
		REINTERPRET( CFbsBitmap*, mask, temp->Extra[3] );
		CBitmapContext *maskGc = BeginImageDrawing( mask );
		DoDrawOperation( operation, maskGc, CGraphicsContext::ESolidPen, KRgbWhite.Value(), data, ETrue );
		EndImageDrawing();
		
		REINTERPRET( CFbsBitmap*, bitmap, temp->Extra[4] );
		CBitmapContext* bmpGc = BeginImageDrawing( bitmap );
		DoDrawOperation( operation, bmpGc, CGraphicsContext::ESolidPen, temp->Color, data );
		EndImageDrawing();

		ShowScreen( temp, Update );
		}
	}

void DoDrawOperation( GraphicsOperation operation, CBitmapContext* gc, CGraphicsContext::TPenStyle style, AMRGB color, AMPVoid data, TBool mask )
	{
	switch( operation )
		{
		case DrawLine:
		case DrawRect:
		case DrawRoundRect:
		case DrawArc:
		case DrawPolygon:
		case DrawTriangle:
		case DrawText:
			{
			gc->SetPenStyle( style );
			gc->SetPenColor( color );
			break;
			}
		case FillRect:
		case FillRoundRect:
		case FillArc:
		case FillPolygon:
		case FillTriangle:
			{
			gc->SetPenStyle( CGraphicsContext::ENullPen );
			gc->SetBrushColor( color );
			gc->SetBrushStyle( CGraphicsContext::ESolidBrush );
			break;
			}
		default:
			break;
		}
	
	switch( operation )
		{
		case DrawText:
			{
			REINTERPRET( AMInt32*, pdata, data );
			if( 0 == pdata[0] )
				{

				}
			else
				{
				REINTERPRET( AMInt32*, pdata, data );
				REINTERPRET( CFont*, font, pdata[0] );
				REINTERPRET( HBufC*, buf, pdata[1] );
				REINTERPRET( TPoint*, point, pdata[2] );

				gc->UseFont( font );
				gc->DrawText( buf->Mid( pdata[3], pdata[4] ), *point );
				gc->DiscardFont();
				}
			break;
			}
		case DrawLine:
			{
			REINTERPRET( AMPoint*, pdata, data );
			gc->DrawLine( TPoint( pdata[0].x, pdata[0].y ), TPoint( pdata[1].x, pdata[1].y ) );
			break;
			}
		case DrawRect:
		case FillRect:
			{
			REINTERPRET( AMRect*, pdata, data );
			gc->DrawRect( TRect( TPoint( pdata->x, pdata->y ), TSize( pdata->w, pdata->h ) ) );
			break;
			}
		case DrawRoundRect:
		case FillRoundRect:
			{
			REINTERPRET( AMInt32*, pdata, data );
			gc->DrawRoundRect( TRect( TPoint( pdata[0], pdata[1] ), TSize( pdata[2], pdata[3] ) ), TSize( pdata[4], pdata[5] ) );
			break;
			}
		case DrawArc:
		case FillArc:
			{
			REINTERPRET( AMInt32*, pdata, data );
			//gc->DrawArc( TRect( TPoint( pdata[0], pdata[1] ), TSize( pdata[2], pdata[3] ) ), TSize( pdata[4], pdata[5] ) );
			break;
			}
		case DrawPolygon:
		case FillPolygon:
			{
			REINTERPRET( AMInt32*, pdata, data );
			REINTERPRET( TPoint*, plist, pdata[0] );
			gc->DrawPolygon( plist, pdata[1] );
			break;
			}
		case DrawTriangle:
		case FillTriangle:
			{
			REINTERPRET( TPoint*, pdata, data );
			gc->DrawPolygon( pdata, 3 );
			break;
			}
		case DrawImage:
			{
			REINTERPRET( AMInt32*, pdata, data );
			REINTERPRET( CFbsBitmap*, bmp, pdata[0] );
			REINTERPRET( TPoint*, point, pdata[1] );
			if( !mask )
				{
				gc->BitBlt( *point, bmp );
				}
			else
				{
				gc->SetBrushColor( KRgbWhite );
				gc->SetBrushStyle( CGraphicsContext::ESolidBrush );
				gc->DrawRect( TRect( *point, bmp->SizeInPixels() ) );
				}
			break;
			}
		case DrawImageArea:
			{
			REINTERPRET( AMInt32*, pdata, data );
			REINTERPRET( CFbsBitmap*, bmp, pdata[0] );
			REINTERPRET( TPoint*, point, pdata[1] );
			REINTERPRET( TRect*, rect, pdata[2] );
			gc->DrawBitmap( TRect( *point, TSize( rect->Width(), rect->Height() ) ), bmp, *rect );
			break;
			}
		case BitBlt:
			{
			REINTERPRET( AMInt32*, pdata, data );
			REINTERPRET( TRect*, rect, pdata[0] );
			REINTERPRET( CFbsBitmap*, bmp, pdata[1] );
			REINTERPRET( TPoint*, point, pdata[2] );
			gc->BitBlt( *point, bmp, *rect );
			break;
			}
		case StretchBlt:
			{
			REINTERPRET( AMInt32*, pdata, data );
			REINTERPRET( TRect*, dstRect, pdata[0] );
			REINTERPRET( TRect*, srcRect, pdata[2] );
			
			TReal x = dstRect->Width() / srcRect->Width();
			TReal y = dstRect->Height() / srcRect->Height();
			CImageConverterEngine* engine = CImageConverterEngine::NewL( (AMPVoid*)&pdata[1] );
			CleanupStack::PushL( engine );
			engine->StartToScale( x, y );
			gc->BitBlt( srcRect->iTl, (CFbsBitmap*)pdata[1], *dstRect );
			
			x = 1 / x;
			y = 1 / y;
			engine->ResetImage( (AMPVoid*)&pdata[1] );
			engine->StartToScale( x, y );
			CleanupStack::PopAndDestroy( engine );
			break;
			}
		case GetClipRect:
			{
			break;
			}
		default:
			break;
		}
	}

AMInt32  AMSetAlpha(AMGraphics graphics, AMUInt8 alpha)
{
	  return 0;
}


AMUInt8 AMGetAlpha(AMGraphics graphics)
{
	 return 0;
}
