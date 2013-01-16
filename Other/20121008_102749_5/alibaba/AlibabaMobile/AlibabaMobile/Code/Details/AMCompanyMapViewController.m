//
//  AMCompanyMapViewController.m
//  AlibabaMobile
//
//  Created by  on 12-2-6.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//
#import <Foundation/Foundation.h>
#import "AMCompanyMapViewController.h"
#import "AMCompanyDetail.h"
#import "SystemUtils.h"
#import "AMGeoInfo.h"
#import "StringUtils.h"
#import "AMAddress.h"
#import "AMLogUtils.h"
#import "AMLogTypeCode.h"

@implementation AMCompanyMapViewController

@synthesize mMapView;

- (void) viewWillAppear:(BOOL)animated
{
    [AMLogUtils appendLog:APP_COM_DETAL_SIX];
}

- (void) dealloc
{
    [mCompanyDetail release];
    [mMapView release];
    
    [super dealloc];
}

#pragma mark - View lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    mCompanyDetail = [self.dataDict objectForKey:TAB_VIEW_COMPANY_DETAIL];
    
    NSString * filePath = [SystemUtils getAppFilePath:@"alimap.html"];
    NSURL *url = [NSURL fileURLWithPath:filePath];
    NSURLRequest *request = [NSURLRequest requestWithURL:url];
    self.mMapView.delegate = self;  
    
    [self.mMapView loadRequest:request];
    
   

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
    double latitude = [self dealTheCoordianteNum:mCompanyDetail.geoInfo.latitude];
    double longitude =  [self dealTheCoordianteNum:mCompanyDetail.geoInfo.longitude];
    NSString * companyName = mCompanyDetail.name;
    NSString * companyAddress = [self getAddressString:mCompanyDetail.address];
    
    NSString * initParamsFunStr = [NSString stringWithFormat: @"function initParams(){latitude=%f;longitude=%f;companyName=\"%@\";companyAddress=\"%@\";} initParams(); initAlimap();", latitude, longitude, companyName, companyAddress];
//    NSLog(initParamsFunStr);
    [self.mMapView stringByEvaluatingJavaScriptFromString:initParamsFunStr];
   
}


@end
