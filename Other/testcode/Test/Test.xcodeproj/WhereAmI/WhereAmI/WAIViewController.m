//
//  WAIViewController.m
//  WhereAmI
//
//  Created by 佳 刘 on 12-10-17.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "WAIViewController.h"

@interface WAIViewController ()

@end

@implementation WAIViewController
@synthesize longitueLabel;
@synthesize startingPoint;
@synthesize latitudeLabel;
@synthesize locationManager;
@synthesize horizontalAccuracyLabel;
@synthesize altitudeLabel;
@synthesize verticalAccuracyLabel;
@synthesize distanceTraveledLabel;

- (void)viewDidLoad
{
    // 定位管理器
    self.locationManager = [[CLLocationManager alloc]init];
    locationManager.delegate = self;
    // 设置精度
    locationManager.desiredAccuracy = kCLLocationAccuracyBest;
    // 启动
    [locationManager startUpdatingLocation];
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
}

- (void)viewDidUnload
{
    self.locationManager = nil;
    self.latitudeLabel = nil;
    self.longitueLabel = nil;
    self.horizontalAccuracyLabel = nil;
    self.altitudeLabel = nil;
    self.verticalAccuracyLabel = nil;
    self.distanceTraveledLabel = nil;
    [super viewDidUnload];
    // Release any retained subviews of the main view.
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
}

#pragma mark -
#pragma mark core location delegate methods
- (void)locationManager:(CLLocationManager *)manager didUpdateToLocation:(CLLocation *)newLocation fromLocation:(CLLocation *)oldLocation {
    
    if (startingPoint == nil) {
        self.startingPoint = newLocation;
    }
    
    // 获取精度
    NSString *latitudeString = [NSString stringWithFormat:@"%g°",newLocation.coordinate.latitude];
    latitudeLabel.text = latitudeString;
    [latitudeLabel release];
    
    // 获取纬度
    NSString *longitudeString = [NSString stringWithFormat:@"%g°",newLocation.coordinate.longitude];
    longitueLabel.text = longitudeString;
    [longitudeString release];
    
    // 定位圆圈的半径
    NSString *horizontalAccuracyString = [NSString stringWithFormat:@"%gm",newLocation.horizontalAccuracy];
    horizontalAccuracyLabel.text = horizontalAccuracyString;
    [horizontalAccuracyString release];
    
    // 海拔
    NSString *altitudeString = [NSString stringWithFormat:@"%gm",newLocation.altitude];
    altitudeLabel.text = altitudeString;
    [altitudeString release];
    
    // 海拔的精确度
    NSString *verticalAccuracyString = [NSString stringWithFormat:@"%gm",newLocation.verticalAccuracy];
    verticalAccuracyLabel.text = verticalAccuracyString;
    [verticalAccuracyString release];
    
    CLLocationDistance distance = [newLocation distanceFromLocation:startingPoint];
    NSString *distanceString = [NSString stringWithFormat:@"%gm",distance];
    distanceTraveledLabel.text = distanceString;
    [distanceString release];
}

-(void)locationManager:(CLLocationManager *)manager didFailWithError:(NSError *)error {
    NSString *errorType = (error.code == kCLErrorDenied)?@"Access Denied":@"Unknown Error";
    UIAlertView *alert = [[[UIAlertView alloc]initWithTitle:@"Error getting location" message:errorType delegate:nil cancelButtonTitle:@"OK" otherButtonTitles: nil]autorelease];
    [alert show];
    
}

@end
