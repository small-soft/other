/*
 
 Copyright 2010 www.adview.cn. All rights reserved.
 
 */

#import "AdViewAdapterYouMi.h"
#import "AdViewAdNetworkConfig.h"
#import "AdViewViewImpl.h"
#import "AdViewLog.h"
#import "AdViewAdNetworkAdapter+Helpers.h"
#import "AdViewAdNetworkRegistry.h"
#import "YouMiView.h"
#import "SingletonAdapterBase.h"

#define AD_VIEW_RETAIN		0

@interface AdViewAdapterYouMiImpl : SingletonAdapterBase <YouMiDelegate> {
}

@end

static AdViewAdapterYouMiImpl *gYouMiImpl = nil;

@implementation AdViewAdapterYouMi

+ (AdViewAdNetworkType)networkType {
  return AdViewAdNetworkTypeYOUMI;
}

+ (void)load {
	if(NSClassFromString(@"YouMiView") != nil) {
		[[AdViewAdNetworkRegistry sharedRegistry] registerClass:self];
	}
}

- (void)getAd {
	if (nil == gYouMiImpl) 
		gYouMiImpl = [[AdViewAdapterYouMiImpl alloc] init];
	YouMiView *youMiView = nil;
	//AWLogInfo(@"youmi --getAd--%@", self);
	[gYouMiImpl setAdapterValue:YES ByAdapter:self];
	youMiView = (YouMiView*)[gYouMiImpl getIdelAdView];
	
	if (nil == youMiView) {
		[adViewView adapter:self didFailAd:nil];
		return;
	}

	self.adNetworkView = youMiView;
#if AD_VIEW_RETAIN	
	[adViewView adapter:self didReceiveAdView:youMiView];
#else
	//[adViewView adapter:self shouldAddAdView:youMiView];
#endif
	[youMiView release];
	AWLogInfo(@"YouMi getAd success!");
}

- (void)stopBeingDelegate {
	YouMiView *youMiView = (YouMiView *)self.adNetworkView;
	//AWLogInfo(@"--Youmi stopBeingDelegate--");
	[gYouMiImpl setAdapterValue:NO ByAdapter:self];
	if (youMiView != nil) {
#if AD_VIEW_RETAIN
		[gYouMiImpl addIdelAdView:youMiView];
#endif
		self.adNetworkView = nil;
	}
}

- (void)updateSizeParameter {
	BOOL isIPad = [AdViewAdNetworkAdapter helperIsIpad];
	
	AdviewBannerSize	sizeId = AdviewBannerSize_Auto;
	if ([adViewDelegate respondsToSelector:@selector(PreferBannerSize)]) {
		sizeId = [adViewDelegate PreferBannerSize];
	}
	
	if (sizeId > AdviewBannerSize_Auto) {
		switch (sizeId) {
			case AdviewBannerSize_320x50:
				self.nSizeAd = YouMiBannerContentSizeIdentifier320x50;
				break;
			case AdviewBannerSize_300x250:
				self.nSizeAd = YouMiBannerContentSizeIdentifier300x250;
				break;
			case AdviewBannerSize_480x60:
				self.nSizeAd = YouMiBannerContentSizeIdentifier468x60;
				break;
			case AdviewBannerSize_728x90:
				self.nSizeAd = YouMiBannerContentSizeIdentifier728x90;
				break;
			default:
				break;
		}
	} else if (isIPad) {
		self.nSizeAd = YouMiBannerContentSizeIdentifier728x90;
	} else {
		self.nSizeAd = YouMiBannerContentSizeIdentifier320x50;
	}
}

- (void)dealloc {	
  [super dealloc];
}

@end

@implementation AdViewAdapterYouMiImpl

- (UIView*)createAdView {
	YouMiView *ret = nil;
	Class youmiViewClass = NSClassFromString (@"YouMiView");
	
	if (0 == youmiViewClass) {
		AWLogInfo(@"no youmi lib, can not create.");
		return nil;
	}
	
	[youmiViewClass setShouldGetLocation:[mAdapter helperUseGpsMode]];
	
	[mAdapter updateSizeParameter];
	
	if ([mAdapter.networkConfig.pubId length] < 1
		&& [mAdapter.networkConfig.pubId2 length] < 1) {
		AWLogWarn(@"Youmi appid and secret key is empty.");
		return nil;
	}
	
	ret = [[youmiViewClass alloc] initWithContentSizeIdentifier:mAdapter.nSizeAd delegate: self];
	if (nil == ret)
		return nil;
	
	ret.textColor = [mAdapter helperTextColorToUse];
	ret.backgroundColor = [mAdapter helperBackgroundColorToUse];
	ret.subTextColor = [UIColor blueColor];
	
	ret.testing = [self isTestMode];
	
	mAdapter.adNetworkView = ret;
	
	[ret performSelector:@selector(setYppID:) withObject:mAdapter.networkConfig.pubId];
    [ret performSelector:@selector(setAppSecret:) withObject:mAdapter.networkConfig.pubId2];
	[ret performSelector:@selector(start)];
	return ret;
}

- (void)dealloc {
	[super dealloc];
}

#pragma mark -
#pragma mark YouMiView Delegate Methods

/*
 *开发者应用ID
 *
 *详解:前往有米主页:http://www.youmi.net/ 注册一个开发者帐户，同时注册一个应用，获取对应应用的ID
 */
- (NSString *)appIdForAd:(YouMiView *)adView{
	NSString *apID;
	
	if (nil == mAdapter) return @"";
	
	if ([mAdapter.adViewDelegate respondsToSelector:@selector(youMiApIDString)]) {
		apID = [mAdapter.adViewDelegate youMiApIDString];
	}
	else {
		apID = mAdapter.networkConfig.pubId;
	}
	return apID;
	
//	return @"6e9e6d15741495b6";
}


/*
 *开发者的安全密钥
 *
 *详解:前往有米主页:http://www.youmi.net/ 注册一个开发者帐户，同时注册一个应用，获取对应应用的安全密钥
 */
- (NSString *)appSecretForAD:(YouMiView *)adView{
	if ([mAdapter.adViewDelegate respondsToSelector:@selector(youMiApSecretString)]) {
		return [mAdapter.adViewDelegate youMiApSecretString];
	}
	else {
		return mAdapter.networkConfig.pubId2;
	}
	return @"";
//	return @"90d29d1be5d71a7c";
}

#pragma mark -
#pragma mark optional notification methods

// 补充:
//      第一次返回成功数据后调用
- (void)didReceiveAd:(YouMiView *)adView {	
	AWLogInfo(@"--Single---***-更新广告成功-***--------");
	if (![self isAdViewValid:adView])
		return;
	
	[mAdapter.adViewView adapter:mAdapter didReceiveAdView:adView];
}

- (void)didFailToReceiveAd:(YouMiView *)adView  error:(NSError *)error {
	AWLogInfo(@"--Single---***-更新广告失败-***--------");	
	if (nil != error)
		AWLogInfo(@"%@", [error localizedDescription]);
	if (![self isAdViewValid:adView])
		return;
	[mAdapter.adViewView adapter:mAdapter didFailAd:nil];
}

- (void)willPresentScreen:(YouMiView *)adView {
	AWLogInfo(@"--Single---***-将要触发全屏广告-***--------");
	
	[mAdapter helperNotifyDelegateOfFullScreenModal];
}


- (void)didPresentScreen:(YouMiView *)adView {
	AWLogInfo(@"--Single---***-全屏广告显示完成-***--------");
}

- (void)willDismissScreen:(YouMiView *)adView {
}

- (void)didDismissScreen:(YouMiView *)adView {
	AWLogInfo(@"--Single---***-全屏广告消失-***--------");
	
	[mAdapter helperNotifyDelegateOfFullScreenModalDismissal];	
}
	//return [mAdapter helperBackgroundColorToUse];
	//return [UIColor blueColor];
	//return [mAdapter helperTextColorToUse];


@end
