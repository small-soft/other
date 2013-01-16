//
//  AMCompanyMapViewController.m
//  AlibabaMobile
//
//  Created by  on 12-2-6.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//
#import <Foundation/Foundation.h>
#import "AMCustomerInfoMapViewController.h"
//#import "AMCompanyDetail.h"
#import "SystemUtils.h"
#import "AMGeoInfo.h"
#import "StringUtils.h"
#import "AMAddress.h"
#import "AMLogUtils.h"
#import "AMLogTypeCode.h"

@implementation AMCustomerInfoMapViewController

@synthesize mMapView;
@synthesize targetLatitude = _targetLatitude;
@synthesize targetLongitude = _targetLongitude;
@synthesize targetCompanyName = _targetCompanyName;
@synthesize targetCompanyAddress = _targetCompanyAddress;


- (void) viewWillAppear:(BOOL)animated
{

}

- (void) dealloc
{
//    [mCompanyDetail release];
    [mMapView release];
    [_targetCompanyAddress release];
    [_targetCompanyName release];
    [super dealloc];
}

-(NSString*)webViewNavigationTitle
{
    return @"公司地图";
}

-(NSString*)webViewBackButtonTitle
{
    return @"客户资料";
}

#pragma mark - View lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    
//    mCompanyDetail = [self.dataDict objectForKey:TAB_VIEW_COMPANY_DETAIL];
    
    NSString * filePath = [SystemUtils getAppFilePath:@"alimap.html"];
    NSURL *url = [NSURL fileURLWithPath:filePath];
    NSURLRequest *request = [NSURLRequest requestWithURL:url];
    self.mMapView.delegate = self;  
    [self.mMapView loadRequest:request];
    
   

}
-(void) viewDidUnload
{
    self.mMapView = nil;
    [super viewDidUnload];
}

- (NSString *) getNoNilString:(NSString *) str
{
    return str != nil? str:@"";
}

- (NSString *) getAddressString:(AMAddress *)address
{
    if(address != nil){
        NSString * provinceName = [self getNoNilString:[address provinceName]];
        NSString * areaName = [self getNoNilString:[address areaName]];
        NSString * streetName = [self getNoNilString:[address streetAddress]];
        
        if([StringUtils getIndexOf:provinceName inFather:areaName] >=0){
            return [areaName stringByAppendingString:streetName];
            
        }else{
            return [[provinceName stringByAppendingString:areaName] stringByAppendingString:streetName];
        }
    }else{
        return nil;
    }
}

- (double) dealTheCoordianteNum:(NSString *) src
{
    src = [src stringByReplacingOccurrencesOfString:@"." withString:@""];
    double value = src.doubleValue;
    value /= pow(10, 5);
    
    return value;
}

- (void)webViewDidFinishLoad:(UIWebView *)webView
{
    double latitude = self.targetLatitude;
    double longitude =  self.targetLongitude;
    NSString * companyName = self.targetCompanyName;
    NSString * companyAddress = self.targetCompanyAddress;
    
//    double latitude = 22.543640;
//    double longitude =  114.087210;
//    NSString * companyName = @"深圳市康义康科技有限公司";
//    NSString * companyAddress = @"广东华强北路现代之窗大厦A座";
    
    
//    NSString *mapInfo = [NSString stringWithFormat: @"function initParams(){latitude=%f;longitude=%f;companyName=\"%@\";companyAddress=\"%@\";} initParams(); initAlimap();", latitude, longitude, companyName, companyAddress];
//    NSLog(@"mapInfo=%@",mapInfo);
//    NSString * initParamsFunStr = [NSString stringWithFormat: @"function initParams(){latitude=%f;longitude=%f;companyName=\"%@\";companyAddress=\"%@\";} initParams(); initAlimap();", latitude, longitude, companyName, companyAddress];
    
        NSString * initParamsFunStr = [NSString stringWithFormat: @"function initParams(){latitude=%f;longitude=%f;companyName=\"%@\";companyAddress=\"%@\";} initParams(); initAlimap();", latitude, longitude, companyName, companyAddress];
    
//    [NSString stringWithFormat: @" function initParams(){latitude=22.543640;longitude=114.087210;companyName="深圳市康义康科技有限公司";companyAddress="广东华强北路现代之窗大厦A座";} initParams(); initAlimap();];

    [self.mMapView stringByEvaluatingJavaScriptFromString:initParamsFunStr];
   
}


@end
